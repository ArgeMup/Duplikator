#include <Arduino.h>
#include "Gorev_Wifi.h"
#include "Gorev_Cihaz.h"
#include "Gorev_Olcumler.h"
#include "Gorev_Led.h"
#include "HttpSunucu.h"
#include "SntpIstemci.h"
#include "Ortak.h"
#include "esp_task_wdt.h"
#include "Hafiza.h"

#pragma region icKullanim
extern "C"
{
  #include "HazirKod_C_Ayarlar.h"

  ////////////////////////////////////////////////////////////////////////////////
  #define _Gunluk_Baslik "main"	//Gunluk ciktilarini tum dosyada kapatmak icin NULL olmali
  #include "Gunluk.h"					//Kaynak kod icinde tanimlanmali
  ////////////////////////////////////////////////////////////////////////////////

  #include "Gorev.h"
  Tip_Isaretci_Gorev Gorev;

  #include  "TcpSunucu.h"
}

Tip_void Gunluk_Disari_Aktarma_Islemi(Tip_Isaretci Tampon, Tip_u32 Adet)
{
  Serial.write((const char *)Tampon, Adet);
  TcpSunucu_Gonder(Tampon, Adet);
}
_Tip_Sure_Islem Zamanlama_An_Okuma_Islemi()
{
  return millis();
}
#pragma endregion

void setup() 
{
  esp_task_wdt_init(15, true);
  esp_task_wdt_add(NULL);

  Serial.begin(921600);
  Gunluk_Baslat(Gunluk_Disari_Aktarma_Islemi);
  Zamanlama_Baslat(Zamanlama_An_Okuma_Islemi);
  Hafiza_Baslat();
  pinMode(Bacak_Led_Yesil, OUTPUT);

  Gorev =  Gorev_Yeni();
	if (Gorev == NULL) 
  {
    Gunluk_BeklenmeyenDurum("Gorev == NULL");
    ESP.restart();
  }

  if (!Gorev_Islem_Ekle(Gorev, Gorev_WIFI_Islem)) 
  {
    Gunluk_BeklenmeyenDurum("Gorev_Islem_Ekle(Gorev, WIFI_Gorev_Islem, NULL)");
    ESP.restart();
  }

  if (!Gorev_Islem_Ekle(Gorev, Gorev_Cihaz_Islem)) 
  {
    Gunluk_BeklenmeyenDurum("Gorev_Islem_Ekle(Gorev, Gorev_Cihaz_Islem, NULL)");
    ESP.restart();
  }

  if (!Gorev_Islem_Ekle(Gorev, Gorev_Olcumler_Islem)) 
  {
    Gunluk_BeklenmeyenDurum("Gorev_Islem_Ekle(Gorev, Gorev_Olcumler_Islem, NULL)");
    ESP.restart();
  }

  if (!Gorev_Islem_Ekle(Gorev, Gorev_Led_Islem)) 
  {
    Gunluk_BeklenmeyenDurum("Gorev_Islem_Ekle(Gorev, Gorev_Led_Islem, NULL)");
    ESP.restart();
  }

  Gunluk_Bilgi("Basladi");
}

unsigned long za;
bool Yesil_led = false;
void loop() 
{
  esp_task_wdt_reset();

  HttpSunucu_Calistir();
  Gorev_Calistir(Gorev);
  delay(AnaDonguDahaHizliCalissin_BitisAni > millis() ? 0 : 5);

  if (za < millis())
  {
    Gunluk("----- %d %ld %ld %ld %ld %s", Gorev_Wifi_Durum(), esp_get_free_heap_size(), uxTaskGetStackHighWaterMark(NULL), ESP.getFreeHeap(), xPortGetFreeHeapSize(), SntpIstemci_Yazdir().c_str());
    za = millis() + 5000;

    Yesil_led = !Yesil_led;
    digitalWrite(Bacak_Led_Yesil, Yesil_led);
  }
}
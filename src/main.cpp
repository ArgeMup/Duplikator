#include <Arduino.h>
#include "Gorev_Wifi.h"

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
}

Tip_void Gunluk_Disari_Aktarma_Islemi(Tip_Isaretci Tampon, Tip_u32 Adet)
{
  Serial.write((const char *)Tampon, Adet);
}
_Tip_Sure_Islem Zamanlama_An_Okuma_Islemi()
{
  return millis();
}
#pragma endregion

void setup() 
{
  Serial.begin(921600);
  Gunluk_Baslat(Gunluk_Disari_Aktarma_Islemi);
  Zamanlama_Baslat(Zamanlama_An_Okuma_Islemi);

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

  Gunluk_Bilgi("Basladi");
}

unsigned long za;
void loop() 
{
  #ifdef DEBUG
  if (za < millis())
  {
    Gunluk("----- %d %ld %ld %ld %ld\r\n", Gorev_Wifi_Durum , esp_get_free_heap_size(), uxTaskGetStackHighWaterMark(NULL), ESP.getFreeHeap(), xPortGetFreeHeapSize());
    za = millis() + 5000;
  }
  #endif

  Tip_u32 TavsiyeEdilenBeklemeMiktari = Gorev_Calistir(Gorev);
  //Gunluk("Tip_u32 TavsiyeEdilenBeklemeMiktari = Gorev_Calistir(Gorev); -> %u", TavsiyeEdilenBeklemeMiktari);
  if (TavsiyeEdilenBeklemeMiktari > 1000) TavsiyeEdilenBeklemeMiktari = 1000;
  else TavsiyeEdilenBeklemeMiktari += 1;
  delay(TavsiyeEdilenBeklemeMiktari);
}
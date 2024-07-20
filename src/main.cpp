#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>

// Set these to your desired credentials.
const char *ssid = "_test_";
const char *password = "11233455667889";

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

Tip_i32 WIFI_Gorev_Islem(Tip_Isaretci_Gorev_Detaylar Detaylar)
{
  switch (Detaylar->CalistirilacakAdim)
  {
    default:
    case 0:
      WiFi.begin(ssid, password);
      Detaylar->CalistirilacakAdim = 5;
      break;
  
    case 5:
    case 6:
      if (WiFi.isConnected())
      {
        #ifdef DEBUG
          if (Detaylar->CalistirilacakAdim == 5)
          {
            char adres[32];
            WiFi.localIP().toString().toCharArray(adres, sizeof(adres));
            Gunluk("IP Adresi : %s", adres);

            Detaylar->CalistirilacakAdim++;
          }
        #endif     
      }
      else Detaylar->CalistirilacakAdim = 100;
      break;

      case 100:
        WiFi.disconnect();
        Detaylar->CalistirilacakAdim++;
        break;
      case 101:
        WiFi.reconnect();
        Detaylar->CalistirilacakAdim = 5;
        break;
  }

  Gorev_Islem_CikVeTekrarCalistir(5000);
}

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

  if (!Gorev_Islem_Ekle(Gorev, WIFI_Gorev_Islem)) 
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
    Gunluk("----- %d %ld %ld %ld %ld\r\n", WiFi.status() , esp_get_free_heap_size(), uxTaskGetStackHighWaterMark(NULL), ESP.getFreeHeap(), xPortGetFreeHeapSize());
    za = millis() + 5000;
  }
  #endif

  Tip_u32 TavsiyeEdilenBeklemeMiktari = Gorev_Calistir(Gorev);
  //Gunluk("Tip_u32 TavsiyeEdilenBeklemeMiktari = Gorev_Calistir(Gorev); -> %u", TavsiyeEdilenBeklemeMiktari);
  if (TavsiyeEdilenBeklemeMiktari > 1000) TavsiyeEdilenBeklemeMiktari = 1000;
  else TavsiyeEdilenBeklemeMiktari += 1;
  delay(TavsiyeEdilenBeklemeMiktari);
}
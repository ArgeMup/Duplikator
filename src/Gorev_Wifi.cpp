#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include "Gorev_Wifi.h"

const char *ssid = "_test_";
const char *password = "11233455667889";

extern "C"
{
  #include "HazirKod_C_Ayarlar.h"

  ////////////////////////////////////////////////////////////////////////////////
  #define _Gunluk_Baslik "main"	//Gunluk ciktilarini tum dosyada kapatmak icin NULL olmali
  #include "Gunluk.h"					//Kaynak kod icinde tanimlanmali
  ////////////////////////////////////////////////////////////////////////////////
}

Tip_i32 Gorev_WIFI_Islem(Tip_Isaretci_Gorev_Detaylar Detaylar)
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

            if (WiFi.getMode() == WIFI_MODE_APSTA) 
            {
              Gunluk("AP kapatildi %d", WiFi.mode(WIFI_MODE_STA));
            }

            Detaylar->CalistirilacakAdim++;
          }
        #endif     
      }
      else Detaylar->CalistirilacakAdim = 100;
      break;

      case 100:
        if (WiFi.getMode() != WIFI_MODE_APSTA) 
        {
          Gunluk("AP acildi %d", WiFi.softAP("Duplikator", "123456789"));
        }

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

uint8_t Gorev_Wifi_Durum()
{
  return (uint8_t)WiFi.status();
}
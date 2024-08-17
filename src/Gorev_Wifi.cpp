#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <ESPmDNS.h>

#include "Ortak.h"
#include "Gorev_Wifi.h"
#include "SntpIstemci.h"
#include "HttpSunucu.h"
#include "Hafiza.h"

extern "C"
{
  #include "HazirKod_C_Ayarlar.h"

  ////////////////////////////////////////////////////////////////////////////////
  #define _Gunluk_Baslik "main"	//Gunluk ciktilarini tum dosyada kapatmak icin NULL olmali
  #include "Gunluk.h"					//Kaynak kod icinde tanimlanmali
  ////////////////////////////////////////////////////////////////////////////////

  #include "TcpSunucu.h"
}

Tip_i32 Gorev_WIFI_Islem(Tip_Isaretci_Gorev_Detaylar Detaylar)
{
  switch (Detaylar->CalistirilacakAdim)
  {
    default:
    case 0:
      SntpIstemci_Baslat();
      WiFi.setHostname(Uygulama_Adi);
      WiFi.begin(Ayarlar.Wifi.ErisimNoktasi, Ayarlar.Wifi.Parola);
      WiFi.setSleep(WIFI_PS_MIN_MODEM);
      MDNS.begin(Uygulama_Adi);
      HttpSunucu_Baslat();

      Detaylar->CalistirilacakAdim = 5;
      break;
  
    case 5:
    case 6:
      if (WiFi.isConnected())
      {
        if (Detaylar->CalistirilacakAdim == 5)
        {
          #ifdef DEBUG
            char adres[32];
            WiFi.localIP().toString().toCharArray(adres, sizeof(adres));
            Gunluk("IP Adresi : %s", adres);
          #endif

          if (WiFi.getMode() == WIFI_MODE_APSTA) 
          {
            Gunluk("AP kapatildi %d", WiFi.mode(WIFI_MODE_STA));
          }

          Detaylar->CalistirilacakAdim++;
        }

        TcpSunucu_Calistir();
      }
      else Detaylar->CalistirilacakAdim = 100;
      break;

      case 100:
        TcpSunucu_Durdur();

        if (WiFi.getMode() != WIFI_MODE_APSTA) 
        {
          Gunluk("AP acildi %d", WiFi.softAP(Uygulama_Adi, Wifi_ErisimNoktasi_Parolasi));
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

uint8_t Gorev_Wifi_InternetVarMi()
{
  return WiFi.status() == WL_CONNECTED;
}

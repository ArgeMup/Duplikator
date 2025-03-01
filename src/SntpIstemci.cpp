#include <Arduino.h>
#include "time.h"
#include "sntp.h"
#include "Ortak.h"

#include "SntpIstemci.h"

extern "C"
{
  ////////////////////////////////////////////////////////////////////////////////
  #define _Gunluk_Baslik "Sntp"	//Gunluk ciktilarini tum dosyada kapatmak icin NULL olmali
  #include "Gunluk.h"			    //Kaynak kod icinde tanimlanmali
  ////////////////////////////////////////////////////////////////////////////////
}

unsigned long SaatOkunduAni = 0;

bool SntpIstemci_SaatDogruMu()
{
  return SaatOkunduAni > 0 && ( (millis() - SaatOkunduAni) < (75*60*1000 /*75 dk*/) ); //Tolerans 15 dk
}
bool SntpIstemci_Yazdir(char* Tampon, uint32_t Adet)
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)) return false;

  uint8_t snc = strftime(Tampon, Adet, "%Y-%m-%d", &timeinfo);
  snc += snprintf(Tampon + snc, Adet - snc, " %s", Gunler[timeinfo.tm_wday]); 
  snc += strftime(Tampon + snc, Adet - snc, " %X", &timeinfo);

  return snc > 0;
}
String SntpIstemci_Yazdir()
{
  char dizi[32];
  if (!SntpIstemci_Yazdir(dizi, sizeof(dizi))) return "";

  return dizi;
}
int8_t SntpIstemci_HaftaninGunu()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)) return -1;

  return timeinfo.tm_wday;
}
uint16_t SntpIstemci_SaatDakika()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)) return 0;

  return (uint16_t)(timeinfo.tm_hour << 8) + (uint8_t)timeinfo.tm_min;
}

void SaatOkundu(struct timeval *tv)
{
  struct tm timeinfo;
  bool snc = getLocalTime(&timeinfo);
  
  if (snc) SaatOkunduAni = millis();

  Gunluk("Saat guncelleme sonucu : %d", snc);
}
void SntpIstemci_Baslat()
{
    // set notification call-back function
    sntp_set_time_sync_notification_cb( SaatOkundu );
    sntp_set_sync_interval(3600000);
    Gunluk("Tetikleme %ld msn", sntp_get_sync_interval());

    /**
     * NTP server address could be aquired via DHCP,
     *
     * NOTE: This call should be made BEFORE esp32 aquires IP address via DHCP,
     * otherwise SNTP option 42 would be rejected by default.
     * NOTE: configTime() function call if made AFTER DHCP-client run
     * will OVERRIDE aquired NTP server address
     */
    sntp_servermode_dhcp(1);    // (optional)

    /**
     * A more convenient approach to handle TimeZones with daylightOffset 
     * would be to specify a environmnet variable with TimeZone definition including daylight adjustmnet rules.
     * A list of rules for your zone could be obtained from https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h
     */
    const char* ntpServer1 = "pool.ntp.org";
    const char* ntpServer2 = "time.nist.gov";
    const char* time_zone = "<+03>-3";
    configTzTime(time_zone, ntpServer1, ntpServer2);
}
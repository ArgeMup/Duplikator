#ifndef __Gorev__Wifi__H__
#define __Gorev__Wifi__H__

extern "C"
{
  #include "Gorev.h"
}

Tip_i32 Gorev_WIFI_Islem(Tip_Isaretci_Gorev_Detaylar Detaylar);
uint8_t Gorev_Wifi_Durum();
uint8_t Gorev_Wifi_InternetVarMi();

#endif
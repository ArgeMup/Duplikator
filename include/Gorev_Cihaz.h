#ifndef __Cihaz__H__
#define __Cihaz__H__

extern "C"
{
  #include "Gorev.h"
}

int32_t Gorev_Cihaz_Islem(Tip_Isaretci_Gorev_Detaylar Detaylar);

String Cihaz_Aciklama();
void Cihaz_Aciklama(String YeniAciklama);
bool Cihaz_IlkAcilis_AsamasindaMi();
bool Cihaz_OnIsitma_AsamasindaMi();
void Cihaz_OnIsitma_Atla();
bool Cihaz_CikisAcikMi(uint8_t Bacak);
uint8_t Cihaz_Durum_0Programli_1Kapali_2Kontrollu();
void Cihaz_Durum_0Programli_1Kapali_2Kontrollu(uint8_t YeniDurum);

#endif
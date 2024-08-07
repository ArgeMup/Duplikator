#ifndef __Olcumler__H__
#define __Olcumler__H__

extern "C"
{
  #include "Gorev.h"
}

struct Olcumler_
{
    float KazanSicakligi;
    float CevreSicakligi;
    float AkimTuketimi_A;
    float _3v3;
};
extern struct Olcumler_ Olcumler;

enum Girisler {  Bacak_KazanSicakligi = 34, Bacak_CevreSicakligi, Bacak_AkimTuketimi = 34, Bacak_3v3 = 34, Bacak_Buton = 23 };

int32_t Gorev_Olcumler_Islem(Tip_Isaretci_Gorev_Detaylar Detaylar);

#endif
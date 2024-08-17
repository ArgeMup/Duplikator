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
    float _3v3;
};
extern struct Olcumler_ Olcumler;

int32_t Gorev_Olcumler_Islem(Tip_Isaretci_Gorev_Detaylar Detaylar);

#endif
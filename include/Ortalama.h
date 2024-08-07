#ifndef __Ortalama__H__
#define __Ortalama__H__

#include "stdint.h"
#include "malloc.h"
#include "string.h"

class Ortalama_
{
private:
  uint16_t Kapasite;
  uint8_t * Dizi;
  uint16_t Sayac = 0;
  uint8_t Toplam = 0;

public:
  Ortalama_(uint16_t OrtalamaDizisiKapasitesi)
  {
    Kapasite = OrtalamaDizisiKapasitesi;
    Dizi = (uint8_t*)malloc(Kapasite);
    memset(Dizi, 0, Kapasite);
  }
  ~Ortalama_()
  {
    free(Dizi);
  }

  uint8_t Ortalama;
  uint8_t Ekle(uint8_t YeniDeger)
  {
    Toplam -= Dizi[Sayac];
    Toplam += YeniDeger;

    Dizi[Sayac] = YeniDeger;
    if (++Sayac >= Kapasite) Sayac = 0;
    Ortalama = Toplam / Kapasite;

    return Ortalama;
  }
};

#endif
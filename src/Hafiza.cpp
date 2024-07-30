#include "Hafiza.h"
#include "Ortak.h"
#include <Preferences.h>
#include "crypto.h"

extern "C"
{
  ////////////////////////////////////////////////////////////////////////////////
  #define _Gunluk_Baslik "Hafiza"	//Gunluk ciktilarini tum dosyada kapatmak icin NULL olmali
  #include "Gunluk.h"					//Kaynak kod icinde tanimlanmali
  ////////////////////////////////////////////////////////////////////////////////
}

struct Ayarlar_ Ayarlar;

uint16_t DogrulukKontrolu(uint8_t* Tampon, uint32_t Adet)
{
  uint8_t top = 0x55, ov = 0xAA;

  for (uint32_t i = 0; i < Adet; i++) 
  {
      top += Tampon[i] + ov;
      ov ^= Tampon[i] + top;
  }

  return (top << 8) + ov;
}

void Hafiza_Baslat()
{
  uint16_t Doko_alinan, Doko_hesaplanan;

  Preferences FizikiAlan;
  FizikiAlan.begin(Uygulama_Adi, true);

  if (FizikiAlan.getBytes("ayrlr", &Ayarlar, sizeof(Ayarlar)) != sizeof(Ayarlar)) 
  {
    Gunluk_Hata("Alinamadi");
    goto YenidenBaslat;
  }

  Doko_alinan = Ayarlar.DogrulukKontrolu;
  Ayarlar.DogrulukKontrolu = 0;
  Doko_hesaplanan = DogrulukKontrolu((uint8_t *)&Ayarlar, sizeof(Ayarlar));
  if (Doko_alinan != Doko_hesaplanan)
  {
    Gunluk_Hata("Doko gecemedi");
    goto YenidenBaslat;
  }
  goto Cikis;

  YenidenBaslat:
  Gunluk_BeklenmeyenDurum("Yeniden Baslatildi");
  memset(&Ayarlar, 0, sizeof(Ayarlar));
  strcpy(Ayarlar.Program.Tumu[0].Adi, "Ornek Program");
  Ayarlar.Program.Tumu[0].Gunler[1].Etkin = true; //pzt
  Ayarlar.Program.Tumu[0].Gunler[1].Baslama_Saati = 9;
  Ayarlar.Program.Tumu[0].Gunler[1].CalismaSuresi_Saat = 2;
  Ayarlar.Program.Tumu[0].OnIsitma.Isitici_Sicakligi = 90;
  Ayarlar.Program.Tumu[0].OnIsitma.Karistirma_Sicakligi = 50;
  Ayarlar.Program.Tumu[0].OnIsitma.Karistirma_CalismaSuresi_Dk = 1;
  Ayarlar.Program.Tumu[0].OnIsitma.Karistirma_DurmaSuresi_Dk = 2;
  Ayarlar.Program.Tumu[0].Kullanim.Isitici_Sicakligi = 60;
  Ayarlar.Program.Tumu[0].Kullanim.Karistirma_Sicakligi = 50;
  Ayarlar.Program.Tumu[0].Kullanim.Karistirma_CalismaSuresi_Dk = 2;
  Ayarlar.Program.Tumu[0].Kullanim.Karistirma_DurmaSuresi_Dk = 2;
  strcpy(Ayarlar.Wifi.ErisimNoktasi, "_test_");
  strcpy(Ayarlar.Wifi.Parola, "11233455667889");
  Ayarlar.Cihaz.KazanIsiOlcer.Hassasiyet = 2;

  Cikis:
  FizikiAlan.end();
  memset(&Cihaz, 0, sizeof(Cihaz));
}

bool Hafiza_Kaydet()
{
  Cihaz.Durum = Durum_Kapali;

  Ayarlar.DogrulukKontrolu = 0;
  Ayarlar.DogrulukKontrolu = DogrulukKontrolu((uint8_t *)&Ayarlar, sizeof(Ayarlar));

  Preferences FizikiAlan;
  FizikiAlan.begin(Uygulama_Adi, false);

  bool sonuc = false;

  if (FizikiAlan.putBytes("ayrlr", &Ayarlar, sizeof(Ayarlar)) == sizeof(Ayarlar)) sonuc = true;
  else Gunluk_Hata("Yazilamadi");

  FizikiAlan.end();
  return sonuc;
}
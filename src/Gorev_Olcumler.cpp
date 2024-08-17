#include "Gorev_Olcumler.h"
#include "Arduino.h"
#include "Gorev_Cihaz.h"
#include "Gorev_Led.h"
#include "Hafiza.h"
#include "Ortak.h"

extern "C"
{
  ////////////////////////////////////////////////////////////////////////////////
  #define _Gunluk_Baslik "Olcumler"	//Gunluk ciktilarini tum dosyada kapatmak icin NULL olmali
  #include "Gunluk.h"			    //Kaynak kod icinde tanimlanmali
  ////////////////////////////////////////////////////////////////////////////////
}

struct Olcumler_ Olcumler = { -1, -1, -1 };

#define _Ortalama_Sayisi ( 100 )
uint32_t Olcumler_toplam;
uint16_t Olcumler_mv_sayac;
uint16_t Olcumler_buton_sayac = 0;

float NTC_SicaklikHesapla(float Direnc)
{
  #define NTC_ReferansNoktasi_Sicaklik          ( 25.0f )
  #define NTC_ReferansNoktasi_Direnc            ( 4700.0f ) 
  #define NTC_Beta                              ( 3950.0f ) 
  #define NTC_ReferansNoktasi_Sicaklik_Kelvin   ( NTC_ReferansNoktasi_Sicaklik + 273.15f )

  float T_inv = ( 1.0f / NTC_ReferansNoktasi_Sicaklik_Kelvin ) + ( ( 1.0f / NTC_Beta ) * log( Direnc / NTC_ReferansNoktasi_Direnc ) );
  float T_Kelvin = 1.0f / T_inv;
  float T_Celsius = T_Kelvin - 273.15f; 

  return T_Celsius;
}
double PTC_SicaklikHesapla(float Direnc) 
{
  #define PTC_ReferansNoktasi_Sicaklik          ( 60.0f )
  #define PTC_ReferansNoktasi_Direnc            ( 2571.0f )
  #define PTC_alfa                              ( 0.0071f /* alpha -> PTC 60°C %/K / 100 */ )

  return PTC_ReferansNoktasi_Sicaklik + ( ( ( Direnc / PTC_ReferansNoktasi_Direnc ) - 1.0f ) / PTC_alfa );
}
float DirencDegeriniHesapla(float UstDirenc_ohm, float AltDirencUzerindekiGerilim_mV)
{
    float ReferansGerilim_mV = 3300.0f;
    float UstDirencUzerindekiGerilim_mV = ReferansGerilim_mV - AltDirencUzerindekiGerilim_mV;
    float SeriAkim_mA = UstDirencUzerindekiGerilim_mV / UstDirenc_ohm;

    return AltDirencUzerindekiGerilim_mV / SeriAkim_mA;
}

int32_t Gorev_Olcumler_Islem(Tip_Isaretci_Gorev_Detaylar Detaylar)
{
  float DirencDegeri;

  switch (Detaylar->CalistirilacakAdim)
  {
  case 0:
    analogSetClockDiv(255);
    analogReadResolution(12); //0 mV ~ 2500 mV
    analogSetAttenuation(ADC_11db);
    pinMode(Bacak_Buton, INPUT_PULLUP);

    Detaylar->CalistirilacakAdim++;
    break;
  
  case 1:
    Olcumler_mv_sayac = 0;
    Olcumler_toplam = 0;
    adcAttachPin(Bacak_3v3);
    Detaylar->CalistirilacakAdim++;
    break;
  case 2:
    Olcumler_toplam += analogReadMilliVolts(Bacak_3v3);
    if (++ Olcumler_mv_sayac == _Ortalama_Sayisi)
    {
      DirencDegeri = (float)Olcumler_toplam / (float)_Ortalama_Sayisi;
      if (DirencDegeri < 100 || DirencDegeri > 2400) Olcumler._3v3 = -1;
      else Olcumler._3v3 = DirencDegeri * 2.0f /*Esit direnclerle bolundu*/ /1000.0f/*V olarak*/;
      Detaylar->CalistirilacakAdim++;
    }
    break;

  case 3:
    Olcumler_mv_sayac = 0;
    Olcumler_toplam = 0;
    adcAttachPin(Bacak_KazanSicakligi);
    Detaylar->CalistirilacakAdim++;
    break;
  case 4:
    Olcumler_toplam += analogReadMilliVolts(Bacak_KazanSicakligi);
    if (++ Olcumler_mv_sayac == _Ortalama_Sayisi)
    {
      DirencDegeri = (float)Olcumler_toplam / (float)_Ortalama_Sayisi;
      if (DirencDegeri < 100 || DirencDegeri > 2400) Olcumler.KazanSicakligi = -1111;
      else
      {
        DirencDegeri = DirencDegeriniHesapla(2350, DirencDegeri);
        Olcumler.KazanSicakligi = PTC_SicaklikHesapla(DirencDegeri) + (float)Ayarlar.Cihaz.KazanIsiOlcer.Duzelt;
      }
      Detaylar->CalistirilacakAdim++;
    }
    break;

  case 5:
    Olcumler_mv_sayac = 0;
    Olcumler_toplam = 0;
    adcAttachPin(Bacak_CevreSicakligi);
    Detaylar->CalistirilacakAdim++;
    break;
  case 6:
    Olcumler_toplam += analogReadMilliVolts(Bacak_CevreSicakligi);
    if (++ Olcumler_mv_sayac == _Ortalama_Sayisi)
    {
      DirencDegeri = (float)Olcumler_toplam / (float)_Ortalama_Sayisi;
      if (DirencDegeri < 20 || DirencDegeri > 2450) Olcumler.CevreSicakligi = -1111;
      else
      {
        DirencDegeri = DirencDegeriniHesapla(10220, DirencDegeri);
        Olcumler.CevreSicakligi = NTC_SicaklikHesapla(DirencDegeri);
      }
      Detaylar->CalistirilacakAdim = 1;
    }
    break;
  }

  if (digitalRead(Bacak_Buton) == false)
  {
    if (++Olcumler_buton_sayac > 2222/*+10sn*/)
    {
      //bekle
      Olcumler_buton_sayac = 2222;
    }
    else if (Olcumler_buton_sayac == 2200/*11sn*/)
    {
      //buton arızasını raporla
      Led_Calistir(Led_Durum_Hatali);
      Cihaz_Aciklama("Buton arızalı (sürekli basılı) görünüyor, sadece arayüzden kontrol edilebilir");
    }
    else if (Olcumler_buton_sayac == 2000/*10sn*/)
    {
      //buton arızası
      Cihaz_Durum_0Programli_1Kapali_2Kontrollu(1);
    }
    else if (Olcumler_buton_sayac == 370/*~2sn*/)
    {
      //Calisiyor -> Kapalı
      //Kapalı -> Kontrollü
      if (Cihaz_Durum_0Programli_1Kapali_2Kontrollu() == 1) Cihaz_Durum_0Programli_1Kapali_2Kontrollu(2);
      else Cihaz_Durum_0Programli_1Kapali_2Kontrollu(1);
    }
    else if (Olcumler_buton_sayac == 30/*150msn*/)
    {
      Led_Calistir(Led_Durum_Butona_Basildi);
    }
  }
  else 
  {
    if (Olcumler_buton_sayac > 0) Gunluk("%d", Olcumler_buton_sayac);
    Olcumler_buton_sayac = 0;
    Led_Durdur(Led_Durum_Butona_Basildi); //basılmadıgı icin zorla kapat
  }

  Gorev_Islem_CikVeTekrarCalistir(5);
}
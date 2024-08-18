#include "Gorev_Led.h"
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Ortak.h"

extern "C"
{
  ////////////////////////////////////////////////////////////////////////////////
  #define _Gunluk_Baslik "Led"	//Gunluk ciktilarini tum dosyada kapatmak icin NULL olmali
  #include "Gunluk.h"			    //Kaynak kod icinde tanimlanmali
  ////////////////////////////////////////////////////////////////////////////////
}

Adafruit_NeoPixel pixels(1, Bacak_Led, NEO_GRB + NEO_KHZ800);
uint32_t  Sayac_Genel;
uint16_t LedlerinDurumu = Led_Durum_KMYB;
bool GuncellemeVar = false;
void Led_Calistir(Led_Durum_ Durum)
{
  if (Bit_Oku(LedlerinDurumu, (uint8_t)Durum) == 1) return;

  if (Durum >= Led_Durum_Kapali) LedlerinDurumu &= _Led_Durum_DigerleriniKapat;

  Bit_Yaz_1(LedlerinDurumu, (uint8_t)Durum);

  GuncellemeVar = true;
}
void Led_Durdur(Led_Durum_ Durum)
{
  if (Bit_Oku(LedlerinDurumu, (uint8_t)Durum) == 0) return;

  Bit_Yaz_0(LedlerinDurumu, (uint8_t)Durum);

  GuncellemeVar = true;
}

#define _y_Uyari  ( 0xF0 ) //F0 240
#define _y_Normal ( 0xA0 ) //daha soguk calismasi icin A0 160
#define _d        ( 0x40 ) //64
union  
{
  uint32_t _32;
  struct
  {         
    uint8_t Mavi, Yesil, Kirmizi, _;
  } _8;
} _Renk_GUncel = { 0 }, Renk_Hedef = { pixels.Color(_y_Uyari, _y_Uyari, _y_Uyari) };
#define _Sabitlendi ( _Renk_GUncel._32 == Renk_Hedef._32 )

int32_t Gorev_Led_Islem(Tip_Isaretci_Gorev_Detaylar Detaylar)
{
  int32_t gecikme = 5; //en az
  bool Sabitlendi = _Sabitlendi;
  if (GuncellemeVar)
  {
    GuncellemeVar = false;

    if (Bit_Oku(LedlerinDurumu, Led_Durum_Butona_Basildi) && 
        Detaylar->CalistirilacakAdim >= 20 &&
        Detaylar->CalistirilacakAdim <= 24) { /*bos gec*/ }
    else Detaylar->CalistirilacakAdim = 1;
  }

  switch (Detaylar->CalistirilacakAdim)
  {
  case 0:
    pixels.begin(); 
    pixels.setBrightness(255);
    Detaylar->CalistirilacakAdim++;
    break;

  case 1:
    if      (Bit_Oku(LedlerinDurumu, Led_Durum_Http_Istegi))              Detaylar->CalistirilacakAdim = 10;
    else if (Bit_Oku(LedlerinDurumu, Led_Durum_Butona_Basildi))           Detaylar->CalistirilacakAdim = 20;
    else if (Bit_Oku(LedlerinDurumu, Led_Durum_Hatali))                   Detaylar->CalistirilacakAdim = 30;
    else if (Bit_Oku(LedlerinDurumu, Led_Durum_KMYB))                     Detaylar->CalistirilacakAdim = 40;
    else if (Bit_Oku(LedlerinDurumu, Led_Durum_Kapali))                   Detaylar->CalistirilacakAdim = 50;
    else if (Bit_Oku(LedlerinDurumu, Led_Durum_Calisiyor_Bekliyor))       Detaylar->CalistirilacakAdim = 60;
    else if (Bit_Oku(LedlerinDurumu, Led_Durum_Calisiyor_OnIsitma))       Detaylar->CalistirilacakAdim = 70;
    else if (Bit_Oku(LedlerinDurumu, Led_Durum_Calisiyor))                Detaylar->CalistirilacakAdim = 80;
    else if (Bit_Oku(LedlerinDurumu, Led_Durum_Calisiyor_Karistiriyor))   Detaylar->CalistirilacakAdim = 90;
    break;

  case 10: //Led_Durum_Http_Istegi
    Renk_Hedef._32 = pixels.Color(0, 0, 0); //siyah
    Detaylar->CalistirilacakAdim++;
    break;
  case 11:
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(_y_Uyari, _y_Uyari, _y_Uyari); //beyaz
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 12:
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(0, 0, 0); //siyah
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 13:
    if (Sabitlendi) 
    {
      Detaylar->CalistirilacakAdim = 1;
      Bit_Yaz_0(LedlerinDurumu, (uint8_t)Led_Durum_Http_Istegi);
    }
    break;  

  case 20: //Led_Durum_Butona_Basildi
    Renk_Hedef._32 = pixels.Color(0, 0, 0); //siyah
    Detaylar->CalistirilacakAdim++;
    break;
  case 21: 
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(_y_Uyari, _y_Uyari, _y_Uyari); //beyaz
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 22:
    gecikme = 41;
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(0, 0, 0); //siyah
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 23:
    gecikme = 41;
    if (Sabitlendi) 
    {
      Sayac_Genel = 500;
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 24:
    gecikme = 10;
    if (--Sayac_Genel == 0)
    {
      Detaylar->CalistirilacakAdim = 1;
      Bit_Yaz_0(LedlerinDurumu, (uint8_t)Led_Durum_Butona_Basildi);
    }
    break;  

  case 30: //Led_Durum_Hatali
    Renk_Hedef._32 = pixels.Color(_y_Uyari, 0, 0); //çok kirmizi
    Detaylar->CalistirilacakAdim++;
    break;
  case 31:
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(_d, 0, 0); //az kırmızı
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 32:
    if (Sabitlendi) Detaylar->CalistirilacakAdim = 30;
    break;   

  case 40: //Led_Durum_KMYB
    Renk_Hedef._32 = pixels.Color(_y_Uyari, 0, 0);
    Detaylar->CalistirilacakAdim++;
    break;
  case 41:
    gecikme = 20;
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(0, 0, 0);
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 42:
    gecikme = 20;
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(0, _y_Uyari, 0);
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 43:
    gecikme = 20;
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(0, 0, 0);
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 44:
    gecikme = 20;
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(0, 0, _y_Uyari);
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 45:
    gecikme = 20;
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(0, 0, 0);
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 46:
    gecikme = 20;
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(_y_Uyari, _y_Uyari, _y_Uyari);
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 47:
    gecikme = 20;
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(0, 0, 0);
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 48:
    gecikme = 20;
    if (Sabitlendi) Detaylar->CalistirilacakAdim = 40;
    break;

  case 50: //Led_Durum_Kapali
    Renk_Hedef._32 = pixels.Color(0, 0, 0); //siyah
    Detaylar->CalistirilacakAdim++;
    break;
  case 51:
    if (Sabitlendi) 
    {
      Sayac_Genel = 500;
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 52:
    if (--Sayac_Genel == 0) Detaylar->CalistirilacakAdim++;
    break;   
  case 53:
    Renk_Hedef._32 = pixels.Color(0, 0, _y_Normal); //mavi
    Detaylar->CalistirilacakAdim++;
    break;
  case 54:
    if (Sabitlendi) Detaylar->CalistirilacakAdim = 50;
    break;

  case 60: //Led_Durum_Calisiyor_Bekliyor
    Renk_Hedef._32 = pixels.Color(0, 0, _y_Normal); //mavi
    Detaylar->CalistirilacakAdim++;
    break;
  case 61:
    if (Sabitlendi) 
    {
      Sayac_Genel = 500;
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 62:
    if (--Sayac_Genel == 0) Detaylar->CalistirilacakAdim++;
    break;   
  case 63:
    Renk_Hedef._32 = pixels.Color(0, 0, 0); //siyah
    Detaylar->CalistirilacakAdim++;
    break;
  case 64:
    if (Sabitlendi) Detaylar->CalistirilacakAdim = 60;
    break;

  case 70: //Led_Durum_Calisiyor_OnIsitma
    Renk_Hedef._32 = pixels.Color(_y_Normal, _y_Normal, 0); //sarı
    Detaylar->CalistirilacakAdim++;
    break;
  case 71:
    if (Sabitlendi) 
    {
      Sayac_Genel = 500;
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 72:
    if (--Sayac_Genel == 0) Detaylar->CalistirilacakAdim++;
    break;   
  case 73:
    Renk_Hedef._32 = pixels.Color(0, 0, 0); //siyah
    Detaylar->CalistirilacakAdim++;
    break;
  case 74:
    if (Sabitlendi) Detaylar->CalistirilacakAdim = 70;
    break;

  case 80: //Led_Durum_Calisiyor
    Renk_Hedef._32 = pixels.Color(0, _y_Normal, 0); //yeşil
    Detaylar->CalistirilacakAdim++;
    break;
  case 81:
    if (Sabitlendi) 
    {
      Sayac_Genel = 500;
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 82:
    if (--Sayac_Genel == 0) Detaylar->CalistirilacakAdim++;
    break;   
  case 83:
    Renk_Hedef._32 = pixels.Color(0, 0, 0); //siyah
    Detaylar->CalistirilacakAdim++;
    break;
  case 84:
    if (Sabitlendi) Detaylar->CalistirilacakAdim = 80;
    break;

  case 90: //Led_Durum_Calisiyor_Karistiriyor
    Renk_Hedef._32 = pixels.Color(0, _d, 0); // az yeşil
    Detaylar->CalistirilacakAdim++;
    break;
  case 91:
    if (Sabitlendi) 
    {
      Renk_Hedef._32 = pixels.Color(0, _y_Normal, 0); // yeşil
      Detaylar->CalistirilacakAdim++;
    }
    break;
  case 92:
    if (Sabitlendi) Detaylar->CalistirilacakAdim = 90;
    break;
  }

  if (!Sabitlendi)
  {
    if (Renk_Hedef._8.Kirmizi > _Renk_GUncel._8.Kirmizi) _Renk_GUncel._8.Kirmizi += 8;
    else if (Renk_Hedef._8.Kirmizi < _Renk_GUncel._8.Kirmizi) _Renk_GUncel._8.Kirmizi -= 8;
    if (Renk_Hedef._8.Yesil > _Renk_GUncel._8.Yesil) _Renk_GUncel._8.Yesil += 8;
    else if (Renk_Hedef._8.Yesil < _Renk_GUncel._8.Yesil) _Renk_GUncel._8.Yesil -= 8;
    if (Renk_Hedef._8.Mavi > _Renk_GUncel._8.Mavi) _Renk_GUncel._8.Mavi += 8;
    else if (Renk_Hedef._8.Mavi < _Renk_GUncel._8.Mavi) _Renk_GUncel._8.Mavi -= 8;

    pixels.setPixelColor(0, _Renk_GUncel._32);
    pixels.show();
  }

  //Gunluk("%d %d %d %d %d", Detaylar->CalistirilacakAdim, LedlerinDurumu, _Renk_GUncel._32, Renk_Hedef._32, gecikme);
  Gorev_Islem_CikVeTekrarCalistir(gecikme);
}
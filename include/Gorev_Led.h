#ifndef __Led__H__
#define __Led__H__

extern "C"
{
  #include "Gorev.h"
}

enum Led_Durum_
{
  Led_Durum_Http_Istegi,              //10 Kendi kapanır, f0d0b0 acık kahve -> 503010 koyu kahve -> 1sn icinde
  Led_Durum_Butona_Basildi,           //20 Kendi kapanır, f0d0b0 acık kahve -> 503010 koyu kahve -> 5sn icinde 
  Led_Durum_Hatali,                   //30 Kapanmaz, kırmıı kapalı esit
  Led_Durum_KMYB,                     //40 Kapanmaz, sürekli dönecek KırmızıYesilMaviBeyaz

                                      //Kapanmaz, Son kuruln digerilerini siler  
  Led_Durum_Kapali,                   //50 mavi kısa kapalı uzun
  Led_Durum_Calisiyor_Bekliyor,       //60 mavi uzun
  Led_Durum_Calisiyor_OnIsitma,       //70 sarı uzun kapalı kısa
  Led_Durum_Calisiyor,                //80 yesil uzun kapalı kısa
  Led_Durum_Calisiyor_Karistiriyor,   //90 yeşil ve koyu yeşil eşit
  _Led_Durum_DigerleriniKapat = BitDizisi_Uret_Ters
                                (
                                  Bit_SolaKaydir_1(Led_Durum_Kapali) + 
                                  Bit_SolaKaydir_1(Led_Durum_Calisiyor_Bekliyor) + 
                                  Bit_SolaKaydir_1(Led_Durum_Calisiyor_OnIsitma) + 
                                  Bit_SolaKaydir_1(Led_Durum_Calisiyor) + 
                                  Bit_SolaKaydir_1(Led_Durum_Calisiyor_Karistiriyor)
                                )
};

void Led_Calistir(Led_Durum_ Durum);
void Led_Durdur(Led_Durum_ Durum);

int32_t Gorev_Led_Islem(Tip_Isaretci_Gorev_Detaylar Detaylar);

#endif
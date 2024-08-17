#include "Arduino.h"
#include "Gorev_Cihaz.h"
#include "Hafiza.h"
#include "SntpIstemci.h"
#include "Gorev_Wifi.h"
#include "Gorev_Olcumler.h"
#include "Gorev_Led.h"
#include "Ortak.h"

extern "C"
{
  ////////////////////////////////////////////////////////////////////////////////
  #define _Gunluk_Baslik "Cihaz"	//Gunluk ciktilarini tum dosyada kapatmak icin NULL olmali
  #include "Gunluk.h"			    //Kaynak kod icinde tanimlanmali
  ////////////////////////////////////////////////////////////////////////////////

  #include "YaziIslemleri.h"
}

enum Durum_ {           Durum_IlkAcilis,    Durum_IlkAcilis_Test,
                        Durum_Programli,    Durum_Programli_Calisiyor,
                        Durum_Kontrollu,    Durum_Kontrollu_Calisiyor,
                        Durum_Kapali,       Durum_Kapali_Beklemede };

enum Asama_ {           Asama_OnIsitma,     Asama_OnIsitma_Calisiyor,   Asama_OnIsitma_SogumasiBekleniyor, 
                        Asama_Kullanim,     Asama_Kullanim_Calisiyor };

enum Asama_Karsitirici_ { Asama_Karistirici_IlkAcilis, Asama_Karistirici_Calisiyor, Asama_Karistirici_Duruyor };

Durum_ Durum = Durum_IlkAcilis;
Asama_ Asama = Asama_OnIsitma;
Asama_Karsitirici_ Asama_Karsitirici = Asama_Karistirici_IlkAcilis;
unsigned long Karistirici_Zamanlamasi = 0;
String Aciklama;
struct Ayarlar_Program_Biri_Gun_ *SeciliProgram_Gun = NULL;
struct Ayarlar_Program_Biri_IsitmaProfili_ *SeciliProgram_IsitmaProfili = NULL;

String Cihaz_Aciklama()
{
  return Aciklama;
}
void Cihaz_Aciklama(String YeniAciklama)
{
  Aciklama = YeniAciklama;
}

uint8_t Cihaz_Durum_0Programli_1Kapali_2Kontrollu()
{
  if (Durum >= Durum_Programli && Durum <= Durum_Programli_Calisiyor) return 0;
  else if (Durum >= Durum_Kontrollu && Durum <= Durum_Kontrollu_Calisiyor) return 2;
  else return 1;
}
void Cihaz_Durum_0Programli_1Kapali_2Kontrollu(uint8_t YeniDurum)
{
  if (Cihaz_Durum_0Programli_1Kapali_2Kontrollu() == YeniDurum ||
      Cihaz_IlkAcilis_AsamasindaMi() ) return;

  switch (YeniDurum)
  {
    default:
    case 0:
      Durum = Durum_Programli;
      Gunluk("Yeni durum : Programli");
      break;
  
    case 1:
      Durum = Durum_Kapali;
      Gunluk("Yeni durum : Kapali");
      break;

    case 2:
      Durum = Durum_Kontrollu;
      Gunluk("Yeni durum : Kontrollu");
      break;
  }
}

bool Cihaz_IlkAcilis_AsamasindaMi()
{
  return Durum <= Durum_IlkAcilis_Test;
}
bool Cihaz_OnIsitma_AsamasindaMi()
{
  return (Durum == Durum_Programli_Calisiyor || Durum == Durum_Kontrollu_Calisiyor) && Asama > Asama_OnIsitma && Asama < Asama_Kullanim;
}
void Cihaz_OnIsitma_Atla()
{
  if (Cihaz_OnIsitma_AsamasindaMi()) Asama = Asama_Kullanim;
}
bool Cihaz_CikisAcikMi(uint8_t Bacak)
{
  return digitalRead(Bacak);
}

Tip_i32 Gorev_Cihaz_Islem(Tip_Isaretci_Gorev_Detaylar Detaylar)
{
  switch (Durum)
  {
    default:
    case Durum_IlkAcilis:
      pinMode(Bacak_Karistirici, OUTPUT); digitalWrite(Bacak_Karistirici, false);
      pinMode(Bacak_Sogutucu, OUTPUT);    digitalWrite(Bacak_Sogutucu, false);
      pinMode(Bacak_Isitici1, OUTPUT);    digitalWrite(Bacak_Isitici1, false);
      pinMode(Bacak_Isitici2, OUTPUT);    digitalWrite(Bacak_Isitici2, false);

      Led_Calistir(Led_Durum_KMYB);

      Durum = Durum_IlkAcilis_Test;
      Aciklama.clear();
      Gorev_Islem_CikVeTekrarCalistir(15000);

    case Durum_IlkAcilis_Test:
      Led_Durdur(Led_Durum_KMYB);

      if (Olcumler.KazanSicakligi < 0 || Olcumler._3v3 < 0)
      {
        Aciklama = "Ölçüm alan donanımlardan en az birisi hatalı (-1). Durum düzelene kadar sistem beklemede kalacak !";
        Led_Calistir(Led_Durum_Hatali);
      }
      else
      {
        Led_Durdur(Led_Durum_Hatali);
        Durum = Durum_Programli;
        Aciklama.clear();
      }
      break;

    case Durum_Kapali:
      Led_Durdur(Led_Durum_Hatali);
      Led_Calistir(Led_Durum_Kapali);
      Aciklama.clear();
      digitalWrite(Bacak_Karistirici, false);
      digitalWrite(Bacak_Sogutucu, false);
      digitalWrite(Bacak_Isitici1, false);
      digitalWrite(Bacak_Isitici2, false);
      Durum = Durum_Kapali_Beklemede;
    case Durum_Kapali_Beklemede:
      break;

    case Durum_Kontrollu:
      SeciliProgram_Gun = NULL;
      Durum = Durum_Kontrollu_Calisiyor;
      Asama = Asama_OnIsitma;
      Aciklama = "Bekleyiniz";
      break;

    case Durum_Programli:
      if (!SntpIstemci_SaatDogruMu())
      {
        Led_Calistir(Led_Durum_Hatali);

        if (!Gorev_Wifi_InternetVarMi())
        {
          Aciklama = "İnternet bağlantisi kurulamadı";
        }
        else
        {
          Aciklama = "Saat sunucusuna bağlantı kurulamadı";
        }
      }
      else
      {
        Led_Durdur(Led_Durum_Hatali);

        int8_t HaftaninGunu = SntpIstemci_HaftaninGunu();
        if (!Ayarlar.Program.Tumu[Ayarlar.Program.SeciliProgramNo].Gunler[HaftaninGunu].Etkin)
        {
          Aciklama = "Bugün için çalışma planlanmadı";
          Led_Calistir(Led_Durum_Calisiyor_Bekliyor);
        }
        else
        {
          uint16_t Guncel = SntpIstemci_SaatDakika();
          uint16_t Program_Baslangic = (Ayarlar.Program.Tumu[Ayarlar.Program.SeciliProgramNo].Gunler[HaftaninGunu].Baslama_Saati << 8) + Ayarlar.Program.Tumu[Ayarlar.Program.SeciliProgramNo].Gunler[HaftaninGunu].Baslama_Dakika;
          uint16_t Program_Bitis = Program_Baslangic + (Ayarlar.Program.Tumu[Ayarlar.Program.SeciliProgramNo].Gunler[HaftaninGunu].CalismaSuresi_Saat << 8);
          if (Program_Bitis > 0x1700 /*23:00*/) Program_Bitis = 0x1700;
          Gunluk("Program %d Gun %d Guncel %X Baslama %X Bitis %X", Ayarlar.Program.SeciliProgramNo, HaftaninGunu, Guncel, Program_Baslangic, Program_Bitis);
          
          if (Guncel < Program_Baslangic || Guncel >= Program_Bitis)
          {
            Aciklama = "Bu saat dilimi için çalışma planlanmadı";
            Led_Calistir(Led_Durum_Calisiyor_Bekliyor);
          }
          else
          {
            //Programi baslat
            SeciliProgram_Gun = &Ayarlar.Program.Tumu[Ayarlar.Program.SeciliProgramNo].Gunler[HaftaninGunu];
            Durum = Durum_Programli_Calisiyor;
            Asama = Asama_OnIsitma;
            Aciklama = "Bekleyiniz";
          }
        }
      }
      break;

    case Durum_Programli_Calisiyor:
      if (!SntpIstemci_SaatDogruMu()) 
      {
        Durum = Durum_IlkAcilis; //hata var
        Gunluk("!SntpIstemci_SaatDogruMu()");
      }
      else
      {
        uint16_t Guncel = SntpIstemci_SaatDakika();
        uint16_t Program_Baslangic = (SeciliProgram_Gun->Baslama_Saati << 8) + SeciliProgram_Gun->Baslama_Dakika;
        uint16_t Program_Bitis = Program_Baslangic + (SeciliProgram_Gun->CalismaSuresi_Saat << 8);
          
        if (Guncel >= Program_Bitis) Durum = Durum_IlkAcilis; //program bitti
      }
      if (Durum == Durum_IlkAcilis) break;
      //Alta gecerek devam edecek
        
    case Durum_Kontrollu_Calisiyor:
      if (Olcumler.KazanSicakligi < 0 || Olcumler._3v3 < 0)
      {
        digitalWrite(Bacak_Karistirici, false);
        digitalWrite(Bacak_Sogutucu, false);
        digitalWrite(Bacak_Isitici1, false);
        digitalWrite(Bacak_Isitici2, false);

        Asama = Asama_OnIsitma;

        Aciklama = "Ölçüm alan donanımlardan en az birisi hatalı (-1). Durum düzelene kadar sistem beklemede kalacak !";
        Led_Calistir(Led_Durum_Hatali);
      }
      else
      {
        Led_Durdur(Led_Durum_Hatali);
        switch (Asama)
        {
          default:
          case Asama_OnIsitma:
            digitalWrite(Bacak_Karistirici, false);
            digitalWrite(Bacak_Sogutucu, false);
            digitalWrite(Bacak_Isitici1, false);
            digitalWrite(Bacak_Isitici2, false);

            SeciliProgram_IsitmaProfili = &Ayarlar.Program.Tumu[Ayarlar.Program.SeciliProgramNo].OnIsitma;

            Aciklama = "Ön ısıtma aşamasında";
            Led_Calistir(Led_Durum_Calisiyor_OnIsitma);

            Asama = Asama_OnIsitma_Calisiyor;
            break;

          case Asama_OnIsitma_Calisiyor:
            if (Olcumler.KazanSicakligi >= SeciliProgram_IsitmaProfili->Isitici_Sicakligi) 
            {
              digitalWrite(Bacak_Isitici1, false);
              digitalWrite(Bacak_Isitici2, false);

              SeciliProgram_IsitmaProfili = &Ayarlar.Program.Tumu[Ayarlar.Program.SeciliProgramNo].Kullanim;

              Aciklama = "Ön ısıtma sonrası soğutma aşamasında";

              Asama = Asama_OnIsitma_SogumasiBekleniyor;
            }
            else
            {
              digitalWrite(Bacak_Isitici1, true);
              digitalWrite(Bacak_Isitici2, true);
            }
            break;

          case Asama_OnIsitma_SogumasiBekleniyor:
            if (Olcumler.KazanSicakligi < SeciliProgram_IsitmaProfili->Isitici_Sicakligi) 
            {
              digitalWrite(Bacak_Sogutucu, false); 

              Asama = Asama_Kullanim;
            }
            else digitalWrite(Bacak_Sogutucu, true);
            break;

          case Asama_Kullanim:
            digitalWrite(Bacak_Karistirici, false);
            digitalWrite(Bacak_Sogutucu, false);
            digitalWrite(Bacak_Isitici1, false);
            digitalWrite(Bacak_Isitici2, false);

            Aciklama = "Kullanıma hazır";
            Led_Calistir(Led_Durum_Calisiyor);

            Asama = Asama_Kullanim_Calisiyor;
            break;

          case Asama_Kullanim_Calisiyor:
            int8_t Azami = SeciliProgram_IsitmaProfili->Isitici_Sicakligi + Ayarlar.Cihaz.KazanIsiOlcer.Hassasiyet;
            int8_t Asgari = SeciliProgram_IsitmaProfili->Isitici_Sicakligi - Ayarlar.Cihaz.KazanIsiOlcer.Hassasiyet;

            if (Olcumler.KazanSicakligi < Asgari)
            {
              digitalWrite(Bacak_Isitici1, true);
              digitalWrite(Bacak_Isitici2, true);
            }
            else if (Olcumler.KazanSicakligi > Azami)
            {
              digitalWrite(Bacak_Isitici1, false);
              digitalWrite(Bacak_Isitici2, false);
            }
            break;
        }
      
        bool KaristiriciKontrolEdildi = false;
        if (Asama == Asama_OnIsitma_Calisiyor || Asama == Asama_OnIsitma_SogumasiBekleniyor || Asama == Asama_Kullanim_Calisiyor)
        {
          if (Olcumler.KazanSicakligi > SeciliProgram_IsitmaProfili->Karistirma_Sicakligi)
          {
            switch (Asama_Karsitirici)
            {
              default:
              case Asama_Karistirici_IlkAcilis:
                if (SeciliProgram_IsitmaProfili->Karistirma_CalismaSuresi_Dk == 0)
                {
                  if (YI_Bul(Aciklama.c_str(), "re=0)") < 0) Aciklama += "\nKaristirici çalışmayacak (Süre=0)";
                }
                else
                {
                  Karistirici_Zamanlamasi = 0;
                  Asama_Karsitirici = Asama_Karistirici_Duruyor;
                }
                break;
              
              case Asama_Karistirici_Calisiyor:
              case Asama_Karistirici_Duruyor:
                KaristiriciKontrolEdildi = true;

                if (Karistirici_Zamanlamasi < millis())
                {
                  //zaman asimi oldu
                  
                  if (Asama_Karsitirici == Asama_Karistirici_Calisiyor) 
                  {
                    Asama_Karsitirici = Asama_Karistirici_Duruyor;
                    
                    digitalWrite(Bacak_Karistirici, SeciliProgram_IsitmaProfili->Karistirma_DurmaSuresi_Dk == 0);
                    Karistirici_Zamanlamasi = millis() + (SeciliProgram_IsitmaProfili->Karistirma_DurmaSuresi_Dk * 60 * 1000);

                    if (Asama >= Asama_Kullanim) Led_Calistir(Led_Durum_Calisiyor);
                  }
                  else
                  { 
                    Asama_Karsitirici = Asama_Karistirici_Calisiyor;

                    digitalWrite(Bacak_Karistirici, true);
                    Karistirici_Zamanlamasi = millis() + (SeciliProgram_IsitmaProfili->Karistirma_CalismaSuresi_Dk * 60 * 1000);

                    if (Asama >= Asama_Kullanim) Led_Calistir(Led_Durum_Calisiyor_Karistiriyor);
                  }
                }
                break;
            }
          }
        }
        else Asama_Karsitirici = Asama_Karistirici_IlkAcilis;
        if (!KaristiriciKontrolEdildi) digitalWrite(Bacak_Karistirici, false);
      }
      break;
  }

  Gorev_Islem_CikVeTekrarCalistir(500);
}
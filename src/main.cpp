#include <Arduino.h>

#pragma region icKullanim
extern "C"
{
  #include "HazirKod_C_Ayarlar.h"

  ////////////////////////////////////////////////////////////////////////////////
  #define _Gunluk_Baslik "main"	//Gunluk ciktilarini tum dosyada kapatmak icin NULL olmali
  #include "Gunluk.h"					//Kaynak kod icinde tanimlanmali
  ////////////////////////////////////////////////////////////////////////////////
}

Tip_void Gunluk_Disari_Aktarma_Islemi(Tip_Isaretci Tampon, Tip_u32 Adet)
{
  Serial.write((const char *)Tampon, Adet);
}
_Tip_Sure_Islem Zamanlama_An_Okuma_Islemi()
{
  return millis();
}
#pragma endregion

void setup() 
{
  Serial.begin(115200);
  Gunluk_Baslat(Gunluk_Disari_Aktarma_Islemi);
  Zamanlama_Baslat(Zamanlama_An_Okuma_Islemi);
}

void loop() 
{
}
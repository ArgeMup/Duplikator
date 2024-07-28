#ifndef __Hafiza__H__
#define __Hafiza__H__

#include <Arduino.h>
#define Ayarlar_Program_Sayisi  ( 15 )
enum Durum_ { Kapali, Kontrollü, Programli };

void Hafiza_Baslat();
bool Hafiza_Kaydet();

struct Ayarlar_
{
    struct Ayarlar_Program_
    {
        enum Durum_ Durum;
        uint8_t SeciliProgramNo;

        struct Ayarlar_Program_Biri_
        {
            char Adi[32];
            struct Ayarlar_Program_Biri_Gun_
            {
                bool Etkin;
                uint8_t Baslama_Saati, Baslama_Dakika;
                uint8_t CalismaSuresi_Saat;
            } Gunler[7];

            struct Ayarlar_Program_Biri_IsitmaProfili_
            {
                uint8_t Isitici_Sicakligi;
                uint8_t Karistirma_Sicakligi;
                uint8_t Karistirma_CalismaSuresi_Dk, Karistirma_DurmaSuresi_Dk;
            } OnIsitma, Kullanim;
        } Tümü[Ayarlar_Program_Sayisi];
    } Program;

    struct Ayarlar_Wifi_
    {
        char ErisimNoktasi[64];
        char Parola[64];
    } Wifi;

    struct Ayarlar_Cihaz_
    {
        struct Ayarlar_Cihaz_Kalibrasyon_
        {
            int8_t Duzelt;
            uint8_t Hassasiyet;
        } KazanIsiOlcer;

        char SonYazilimYuklemeZamani[32];
    } Cihaz;

    /////////////////////////////////////////////
    uint16_t DogrulukKontrolu;
};

extern struct Ayarlar_ Ayarlar;

#endif
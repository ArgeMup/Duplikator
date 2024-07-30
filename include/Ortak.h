#ifndef __Ortak__H__
#define __Ortak__H__

extern const char *Uygulama_Adi;
extern const char *Wifi_ErisimNoktasi_Adi;
extern const char *Wifi_ErisimNoktasi_Parolasi;
extern const char Html_SayiGirisi[];
extern const char Html_Ayarlar_Tablo[];
extern unsigned long AnaDonguDahaHizliCalissin_BitisAni;
extern const char * Gunler[];

enum Durum_ { Durum_Kapali, Durum_Kontrollu, Durum_Programli };
struct Cihaz_
{
    Durum_ Durum;
};
extern struct Cihaz_ Cihaz;

#endif
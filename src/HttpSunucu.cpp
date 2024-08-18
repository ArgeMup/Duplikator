#include <WebServer.h>
#include <Update.h>

#include "HttpSunucu.h"
#include "SntpIstemci.h"
#include "Ortak.h"
#include "Html_Ana_Sayfa.h"
#include "Html_Ayarlar.h"
#include "Hafiza.h"
#include "Gorev_Cihaz.h"
#include "Gorev_Olcumler.h"
#include "Gorev_Led.h"

extern "C"
{
    ////////////////////////////////////////////////////////////////////////////////
    #define _Gunluk_Baslik "HttpSunucu"	//Gunluk ciktilarini tum dosyada kapatmak icin NULL olmali
    #include "Gunluk.h"					//Kaynak kod icinde tanimlanmali
    ////////////////////////////////////////////////////////////////////////////////

    #include "YaziIslemleri.h"
}

WebServer server(80);

String BasliklariYazdir()
{
  String message = "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) 
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  message += "\nHeadres: ";
  message += server.headers();
  message += "\n";
  for (uint8_t i = 0; i < server.headers(); i++) 
  {
    message += " " + server.headerName(i) + ": " + server.header(i) + "\n";
  }
  
  char tampon[1024];
  message.toCharArray(tampon, sizeof(tampon));
  Gunluk("%s", tampon);

  return message;
}
String SayiGirisi(String Ad, String Aciklama, String Deger, String Asgari, String Azami)
{
    String ham = Html_SayiGirisi;

    ham.replace("??? Sayi Girisi Adi ???", Ad);
    ham.replace("??? Sayi Girisi Aciklama ???", Aciklama);
    ham.replace("??? Sayi Girisi Degeri ???", Deger);
    ham.replace("??? Sayi Girisi Aralik ???", "min=\"" + Asgari + "\" max=\"" + Azami + "\"");

    return ham;
}
bool SayiOku(String Adi, int* KopyalanacakDegisken)
{
    String okunan = server.arg(Adi);
    if (okunan.isEmpty()) return false;

    *KopyalanacakDegisken = okunan.toInt();
    return true;
}
String Ayarlar_Tablo_Satir(int ProgramNo, int GunNo)
{
    char dizi[64];
    String ham = Html_Ayarlar_Tablo;
    ham.replace("??? 1 Gun No ???", String(GunNo));
    ham.replace("??? 1 Onay ???", Ayarlar.Program.Tumu[ProgramNo].Gunler[GunNo].Etkin ? "checked" : "");
    ham.replace("??? 1 Gun ???", Gunler[GunNo]);
    ham.replace("??? 1 Saat ???", YI_Yazdir(dizi, sizeof(dizi), "%02d:%02d", Ayarlar.Program.Tumu[ProgramNo].Gunler[GunNo].Baslama_Saati, Ayarlar.Program.Tumu[ProgramNo].Gunler[GunNo].Baslama_Dakika));
    ham.replace("??? 1 Sure ???", String(Ayarlar.Program.Tumu[ProgramNo].Gunler[GunNo].CalismaSuresi_Saat));

    return ham;
}
String ProgramAdlari(int SeciliProgram)
{
    String ProgramAdlari;
    for (size_t i = 0; i < Ayarlar_Program_Sayisi; i++)
    {
        //<option value="1">1 : Program 1</option>
        ProgramAdlari += "<option value=\"" + String(i) + "\"" + (SeciliProgram == i ? " selected" : "") + ">" + String(i+1) + " : " + Ayarlar.Program.Tumu[i].Adi + "</option>";
    }

    return ProgramAdlari;
}

void Gonder_AnaSayfa() 
{
    String sayfa = Html_Ana_Sayfa;
    char dizi[64];
    
    //Program
    sayfa.replace("??? Uygulama ???", "Sea Dent " + String(Uygulama_Adi));
    sayfa.replace("/*??? Durum ???*/", YI_Yazdir(dizi, sizeof(dizi), "%d", Cihaz_Durum_0Programli_1Kapali_2Kontrollu()));
    sayfa.replace("??? Aciklama ???", Cihaz_Aciklama());
    sayfa.replace("??? Programlar ???", ProgramAdlari(Ayarlar.Program.SeciliProgramNo));
    sayfa.replace("??? OnIsitmayiAtla ???", Cihaz_OnIsitma_AsamasindaMi() ? "block" : "none");
    sayfa.replace("??? Karistirici ???", Cihaz_CikisAcikMi(Bacak_Karistirici) ? "🟢" : "🔴");
    sayfa.replace("??? Sogutucu ???", Cihaz_CikisAcikMi(Bacak_Sogutucu) ? "🟢" : "🔴");
    sayfa.replace("??? Isitici 1 ???", Cihaz_CikisAcikMi(Bacak_Isitici1) ? "🟢" : "🔴");
    sayfa.replace("??? Isitici 2 ???", Cihaz_CikisAcikMi(Bacak_Isitici2) ? "🟢" : "🔴");
    sayfa.replace("??? Kazan ???", YI_Yazdir(dizi, sizeof(dizi), _Yazdirma_Sablon_NoktaliSayi " °C", Olcumler.KazanSicakligi));
    sayfa.replace("??? Cevre ???", YI_Yazdir(dizi, sizeof(dizi), _Yazdirma_Sablon_NoktaliSayi " °C, " _Yazdirma_Sablon_NoktaliSayi "V", Olcumler.CevreSicakligi, Olcumler._3v3));

    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", sayfa);
}
void Gonder_AnaSayfa_Durum_Sec()
{
    Led_Calistir(Led_Durum_Http_Istegi);
    Gunluk("Gonder_AnaSayfa_Program_Sec");

    int Secim;
    if (!SayiOku("Secim", &Secim) || Secim < 0 || Secim > 2)
    {
        String msj = "Parametreler uygun değil";
        Gunluk_Hata("%s", msj.c_str());
        server.send(400, "text/plain", msj);
        return;
    }

    Cihaz_Durum_0Programli_1Kapali_2Kontrollu((uint8_t)Secim);

    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "BASARILI");
}
void Gonder_AnaSayfa_Program_Sec()
{
    Led_Calistir(Led_Durum_Http_Istegi);
    Gunluk("Gonder_AnaSayfa_Program_Sec");

    int Secim;
    if (!SayiOku("Secim", &Secim) || Secim < 0 || Secim >= Ayarlar_Program_Sayisi)
    {
        String msj = "Parametreler uygun değil";
        Gunluk_Hata("%s", msj.c_str());
        server.send(400, "text/plain", msj);
        return;
    }

    Ayarlar.Program.SeciliProgramNo = Secim;

    if (!Hafiza_Kaydet())
    {
        String msj = "Kaydedilemedi";
        Gunluk_Hata("%s", msj.c_str());
        server.send(400, "text/plain", msj);
        return;
    }

    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "BASARILI");
}
void Gonder_AnaSayfa_OnIsitmayiAtla()
{
    Led_Calistir(Led_Durum_Http_Istegi);
    Gunluk("Gonder_AnaSayfa_OnIsitmayiAtla");

    Cihaz_OnIsitma_Atla();

    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "BASARILI");
}
void Gonder_Ayarlar_Secim(int SeciliProgram) 
{
    String sayfa = Html_Ayarlar;
    
    //Program
    sayfa.replace("??? 1 Programlar ???", ProgramAdlari(SeciliProgram));
    sayfa.replace("??? 1 Program Adi ???", Ayarlar.Program.Tumu[SeciliProgram].Adi);
    sayfa.replace("??? 1 Program No ???", String(SeciliProgram));
    String TabloIcerigi;
    for (size_t i = 1; i < 7; i++)
    {
        TabloIcerigi += Ayarlar_Tablo_Satir(SeciliProgram, i);
    }
    TabloIcerigi += Ayarlar_Tablo_Satir(SeciliProgram, 0);
    sayfa.replace("??? 1 Tablo ???", TabloIcerigi);
    TabloIcerigi.clear();
    TabloIcerigi += SayiGirisi("1oi_is", "Isıtıcı Sıcaklığı (°C)", String(Ayarlar.Program.Tumu[SeciliProgram].OnIsitma.Isitici_Sicakligi), "1", "100");
    TabloIcerigi += SayiGirisi("1oi_ks", "Karıştırma Sıcaklığı (°C)", String(Ayarlar.Program.Tumu[SeciliProgram].OnIsitma.Karistirma_Sicakligi), "25", "100");
    TabloIcerigi += SayiGirisi("1oi_kc", "Karıştırma Çalışma Süresi (Dk)", String(Ayarlar.Program.Tumu[SeciliProgram].OnIsitma.Karistirma_CalismaSuresi_Dk), "0", "60");
    TabloIcerigi += SayiGirisi("1oi_kd", "Karıştırma Durma Süresi (Dk)", String(Ayarlar.Program.Tumu[SeciliProgram].OnIsitma.Karistirma_DurmaSuresi_Dk), "0", "60");
    sayfa.replace("??? 1 OnIsitma ???", TabloIcerigi);
    TabloIcerigi.clear();
    TabloIcerigi += SayiGirisi("1k_is", "Isıtıcı Sıcaklığı (°C)", String(Ayarlar.Program.Tumu[SeciliProgram].Kullanim.Isitici_Sicakligi), "1", "100");
    TabloIcerigi += SayiGirisi("1k_ks", "Karıştırma Sıcaklığı (°C)", String(Ayarlar.Program.Tumu[SeciliProgram].Kullanim.Karistirma_Sicakligi), "25", "100");
    TabloIcerigi += SayiGirisi("1k_kc", "Karıştırma Çalışma Süresi (Dk)", String(Ayarlar.Program.Tumu[SeciliProgram].Kullanim.Karistirma_CalismaSuresi_Dk), "0", "60");
    TabloIcerigi += SayiGirisi("1k_kd", "Karıştırma Durma Süresi (Dk)", String(Ayarlar.Program.Tumu[SeciliProgram].Kullanim.Karistirma_DurmaSuresi_Dk), "0", "60");
    sayfa.replace("??? 1 Kullanim ???", TabloIcerigi);

    //Wifi
    sayfa.replace("??? 2 Adresi ???", WiFi.localIP().toString());
    sayfa.replace("??? 2 Adi ???", Ayarlar.Wifi.ErisimNoktasi);
    
    //Cihaz
    char gecici_tampon[128];
    sayfa.replace("??? 3 Saat ???", SntpIstemci_Yazdir());
    sayfa.replace("??? 3 Frekans ???", String(YI_Yazdir(gecici_tampon, sizeof(gecici_tampon), "%d MHz", ESP.getCpuFreqMHz())));
    
    const int MS_IN_SECOND = 1000;
	const int MS_IN_MINUTE = MS_IN_SECOND * 60;
	const int MS_IN_HOUR = MS_IN_MINUTE * 60;
	const int MS_IN_DAY = MS_IN_HOUR * 24;
    unsigned long msn = millis();
	int gun = msn / MS_IN_DAY;
	msn %= MS_IN_DAY;
	int saat = msn / MS_IN_HOUR;
	msn %= MS_IN_HOUR;
	int dakika = msn / MS_IN_MINUTE;
	msn %= MS_IN_MINUTE;
	int saniye = msn / MS_IN_SECOND;
	msn %= MS_IN_SECOND;
    sayfa.replace("??? 3 Calisma ???", YI_Yazdir(gecici_tampon, sizeof(gecici_tampon), "%02d.%02d:%02d:%02d", gun, saat, dakika, saniye));
    
    sprintf(gecici_tampon, "%s_%d_%d", Uygulama_Adi, Surum_Yuksek, Surum_Dusuk);
    sayfa.replace("??? 3 Surum ???", String(gecici_tampon) + " " + String(Ayarlar.Cihaz.SonYazilimYuklemeZamani));
    sayfa.replace("??? 3 Kalibrasyon ???", 
        SayiGirisi("3KazanSicakligi", "Kazan sıcaklığını düzelt (30 °C -> " + String(30 + Ayarlar.Cihaz.KazanIsiOlcer.Duzelt) + " °C)", String(Ayarlar.Cihaz.KazanIsiOlcer.Duzelt), "-15", "15") + 
        SayiGirisi("3KazanHassasiyeti", "Kazan sıcaklığı hata payı (" + String(50 - Ayarlar.Cihaz.KazanIsiOlcer.Hassasiyet) + " °C - " + String(50 + Ayarlar.Cihaz.KazanIsiOlcer.Hassasiyet) + " °C)", String(Ayarlar.Cihaz.KazanIsiOlcer.Hassasiyet), "1", "15"));

    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", sayfa);
}
void Gonder_Ayarlar() 
{
    Gonder_Ayarlar_Secim(Ayarlar.Program.SeciliProgramNo);
}
void Gonder_Ayarlar_Program_Sec()
{
    Gunluk("Gonder_Ayarlar_Program_Sec");

    int Secim;
    if (!SayiOku("Secim", &Secim))
    {
        String msj = "Parametreler uygun değil";
        Gunluk_Hata("%s", msj.c_str());
        server.send(400, "text/plain", msj);
        return;
    }

    Gonder_Ayarlar_Secim(Secim);
}
void Gonder_Ayarlar_Program_Kaydet()
{
    Led_Calistir(Led_Durum_Http_Istegi);
    String hata_msj;
    Gunluk("Gonder_Ayarlar_Program_Kaydet");

    int _1No, _1oi_is, _1oi_ks, _1oi_kc, _1oi_kd, _1k_is, _1k_ks, _1k_kc, _1k_kd;
    if (!SayiOku("1No", &_1No) || _1No < 0 || _1No >= Ayarlar_Program_Sayisi ||
        !SayiOku("1oi_is", &_1oi_is) || !SayiOku("1oi_ks", &_1oi_ks) || !SayiOku("1oi_kc", &_1oi_kc) || !SayiOku("1oi_kd", &_1oi_kd) || 
        !SayiOku("1k_is", &_1k_is) || !SayiOku("1k_ks", &_1k_ks) || !SayiOku("1k_kc", &_1k_kc) || !SayiOku("1k_kd", &_1k_kd))
    {
        hata_msj = "Parametreler uygun değil";
        goto Hata;
    }

    strcpy(Ayarlar.Program.Tumu[_1No].Adi, server.arg("1Adi").c_str());

    char dizi[64];
    for (size_t i = 0; i < 7; i++)
    {
        Ayarlar.Program.Tumu[_1No].Gunler[i].Etkin = server.arg(YI_Yazdir(dizi, sizeof(dizi), "1Gun_%d", i)) == "E";

        int sure;
        if (SayiOku(YI_Yazdir(dizi, sizeof(dizi), "1Sure_%d", i), &sure)) 
        {
            Ayarlar.Program.Tumu[_1No].Gunler[i].CalismaSuresi_Saat = (uint8_t)sure;
        }
        
        String basla = server.arg(YI_Yazdir(dizi, sizeof(dizi), "1Basla_%d", i));
        if (!basla.isEmpty() && basla.length() == 5) 
        {
            Ayarlar.Program.Tumu[_1No].Gunler[i].Baslama_Saati = (uint8_t)basla.toInt();
            basla.remove(0, 3);
            Ayarlar.Program.Tumu[_1No].Gunler[i].Baslama_Dakika = (uint8_t)basla.toInt();
            basla.clear();
        }
    }

    Ayarlar.Program.Tumu[_1No].OnIsitma.Isitici_Sicakligi = (uint8_t)_1oi_is;
    Ayarlar.Program.Tumu[_1No].OnIsitma.Karistirma_Sicakligi = (uint8_t)_1oi_ks;
    Ayarlar.Program.Tumu[_1No].OnIsitma.Karistirma_CalismaSuresi_Dk = (uint8_t)_1oi_kc;
    Ayarlar.Program.Tumu[_1No].OnIsitma.Karistirma_DurmaSuresi_Dk = (uint8_t)_1oi_kd;
    
    Ayarlar.Program.Tumu[_1No].Kullanim.Isitici_Sicakligi = (uint8_t)_1k_is;
    Ayarlar.Program.Tumu[_1No].Kullanim.Karistirma_Sicakligi = (uint8_t)_1k_ks;
    Ayarlar.Program.Tumu[_1No].Kullanim.Karistirma_CalismaSuresi_Dk = (uint8_t)_1k_kc;
    Ayarlar.Program.Tumu[_1No].Kullanim.Karistirma_DurmaSuresi_Dk = (uint8_t)_1k_kd;

    if (!Hafiza_Kaydet())
    {
        hata_msj = "Kaydedilemedi";
        goto Hata;
    }

    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "BASARILI");
    return;

    Hata:
    Hafiza_Baslat();
    Gunluk_Hata("%s", hata_msj.c_str());
    server.send(400, "text/plain", hata_msj);
}
void Gonder_WifiAyarlari()
{
    Led_Calistir(Led_Durum_Http_Istegi);
    Gunluk("WifiAyarlari");

    if (server.arg("2adi").isEmpty() || server.arg("2parola").isEmpty())
    {
        String msj = "Parametreler uygun değil";
        Gunluk_Hata("%s", msj.c_str());
        server.send(400, "text/plain", msj);
        return;
    }

    strcpy(Ayarlar.Wifi.ErisimNoktasi, server.arg("2adi").c_str());
    strcpy(Ayarlar.Wifi.Parola, server.arg("2parola").c_str());
    if (!Hafiza_Kaydet())
    {
        String msj = "Kaydedilemedi";
        Gunluk_Hata("%s", msj.c_str());
        server.send(400, "text/plain", msj);
        return;
    }

    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "BASARILI");
}
void Gonder_Kalibrasyon()
{
    Led_Calistir(Led_Durum_Http_Istegi);
    Gunluk("Kalibrasyon");

    int KazanSicakligi, KazanHassasiyeti;
    if (!SayiOku("3KazanSicakligi", &KazanSicakligi) || !SayiOku("3KazanHassasiyeti", &KazanHassasiyeti))
    {
        String msj = "Parametreler uygun değil";
        Gunluk_Hata("%s", msj.c_str());
        server.send(400, "text/plain", msj);
        return;
    }

    Ayarlar.Cihaz.KazanIsiOlcer.Duzelt = KazanSicakligi;
    Ayarlar.Cihaz.KazanIsiOlcer.Hassasiyet = KazanHassasiyeti;
    if (!Hafiza_Kaydet())
    {
        String msj = "Kaydedilemedi";
        Gunluk_Hata("%s", msj.c_str());
        server.send(400, "text/plain", msj);
        return;
    }

    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "BASARILI");
}
void Gonder_HataAyiklama()
{
    Led_Calistir(Led_Durum_Http_Istegi);
    Gunluk("HataAyiklama");

    int BaglantiNoktasi, Durum;
    if (!SayiOku("_A", &BaglantiNoktasi) || !SayiOku("_B", &Durum) || BaglantiNoktasi < 0 || BaglantiNoktasi > 4)
    {
        String msj = "Parametreler uygun değil";
        Gunluk_Hata("%s", msj.c_str());
        server.send(400, "text/plain", msj);
        return;
    }

    switch (BaglantiNoktasi)
    {
    case 1: //Karistirici
        digitalWrite(Bacak_Karistirici, Durum == 0 ? LOW : HIGH);
        break;
    
    case 2: //Sogutucu
        digitalWrite(Bacak_Sogutucu, Durum == 0 ? LOW : HIGH);
        break;

    case 3: //Isitici 1
        digitalWrite(Bacak_Isitici1, Durum == 0 ? LOW : HIGH);
        break;

    case 4: //Isitici 2
        digitalWrite(Bacak_Isitici2, Durum == 0 ? LOW : HIGH);
        break;
    }

    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "BASARILI");
}
void Gonder_YazilimGuncelleme_Once()
{
    Led_Calistir(Led_Durum_Http_Istegi);
    AnaDonguDahaHizliCalissin_BitisAni = millis() + 5000;

    HTTPUpload& upload = server.upload();

    if (upload.status == UPLOAD_FILE_START) 
    {
        char bin_dsy_adi[32];
        sprintf(bin_dsy_adi, "%s_%d_%d.bin", Uygulama_Adi, Surum_Yuksek, Surum_Dusuk);

        Gunluk_Bilgi("Guncelleme: Mevcut %s Gelen %s", bin_dsy_adi, upload.filename.c_str());

        #ifndef DEBUG
            if (!upload.filename.startsWith(Uygulama_Adi) ||
                upload.filename == bin_dsy_adi) //aynı dosya
            {
                Gunluk_Hata("%s", "Uygun degil");
                return; //uygun degil
            }
        #endif

        if (!Update.begin(UPDATE_SIZE_UNKNOWN))
        { //start with max available size
            Gunluk_Hata("%s", Update.errorString());
        }
    } 
    else if (upload.status == UPLOAD_FILE_WRITE) 
    {
        /* flashing firmware to ESP*/
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) 
        {
            Gunluk_Hata("%s", Update.errorString());
        }
    } 
    else if (upload.status == UPLOAD_FILE_END) 
    {
        Gunluk("UPLOAD_FILE_WRITE");

        if (Update.end(true)) 
        { //true to set the size to the current progress
            Gunluk_Bilgi("Guncelleme Basarili: %u %d", upload.totalSize, Update.isFinished());
        } 
        else 
        {
            Gunluk_Hata("%s", Update.errorString());
        }
    }
}
void Gonder_YazilimGuncelleme_Sonra()
{
    Led_Calistir(Led_Durum_Http_Istegi);
    strcpy(Ayarlar.Cihaz.SonYazilimYuklemeZamani, SntpIstemci_Yazdir().c_str());
    Hafiza_Kaydet();

    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? Update.errorString() : "BASARILI");
    delay(1000);
    ESP.restart();
}
void Gonder_SayfaBulunamadi() 
{
    server.send(404, "text/plain", "Sayfa bulunamadı\n" + BasliklariYazdir());
}

void HttpSunucu_Baslat()
{
    server.on("/", Gonder_AnaSayfa);
    
    //AnaSayfa
    server.on("/AnaSayfa_Durum_Sec", HTTP_POST, Gonder_AnaSayfa_Durum_Sec);
    server.on("/AnaSayfa_Program_Sec", HTTP_POST, Gonder_AnaSayfa_Program_Sec);
    server.on("/AnaSayfa_OnIsitmayiAtla", HTTP_POST, Gonder_AnaSayfa_OnIsitmayiAtla);

    //Ayarlar/Programlar
    server.on("/Ayarlar", HTTP_GET, Gonder_Ayarlar);
    server.on("/Ayarlar_Program_Sec", HTTP_GET, Gonder_Ayarlar_Program_Sec);
    server.on("/Ayarlar_Program_Kaydet", HTTP_POST, Gonder_Ayarlar_Program_Kaydet);
    server.on("/Ayarlar_Wifi_Kaydet", HTTP_POST, Gonder_WifiAyarlari);
    server.on("/Ayarlar_Kalibrasyon_Kaydet", HTTP_POST, Gonder_Kalibrasyon);
    server.on("/Ayarlar_YazilimGuncelle", HTTP_POST, Gonder_YazilimGuncelleme_Sonra, Gonder_YazilimGuncelleme_Once);

    #ifdef DEBUG
        server.on("/HataAyiklama", HTTP_GET, Gonder_HataAyiklama);
    #endif

    server.onNotFound(Gonder_SayfaBulunamadi);
    server.begin();
}

void HttpSunucu_Calistir()
{
  server.handleClient();
}
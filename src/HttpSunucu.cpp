#include <WebServer.h>
#include <Update.h>

#include "HttpSunucu.h"
#include "SntpIstemci.h"
#include "Ortak.h"

extern "C"
{
    ////////////////////////////////////////////////////////////////////////////////
    #define _Gunluk_Baslik "HttpSunucu"	//Gunluk ciktilarini tum dosyada kapatmak icin NULL olmali
    #include "Gunluk.h"					//Kaynak kod icinde tanimlanmali
    ////////////////////////////////////////////////////////////////////////////////
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

void Gonder_AnaSayfa() 
{
    String sayfa = Html_Ayarlar;
    char bin_dsy_adi[32];
    sprintf(bin_dsy_adi, "%s_%d_%d", Uygulama_Adi, Surum_Yuksek, Surum_Dusuk);
    sayfa.replace("??? 3 Surum ???", bin_dsy_adi);
    sayfa.replace("??? 3 Saat ???", SntpIstemci_Yazdir());
    sayfa.replace("??? 3 Kalibrasyon ???", 
        SayiGirisi("3KazanSicakligi", "Kazan sıcaklığını düzelt (32 °C -> 35 °C)", "3", "-15", "15") + 
        SayiGirisi("3KazanHassasiyeti", "Kazan sıcaklığı hata payı (48 °C - 52 °C)", "2", "1", "15"));

    server.send(200, "text/html", sayfa);
}
void Gonder_Kalibrasyon()
{
    BasliklariYazdir();
    Gunluk("Kalibrasyon");
    server.send(200, "text/plain", "BASARILI");
}
void Gonder_YazilimGuncelleme_Once()
{
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
            Gunluk_Bilgi("Guncelleme Basarili: %u", upload.totalSize);
        } 
        else 
        {
            Gunluk_Hata("%s", Update.errorString());
        }
    }
}
void Gonder_YazilimGuncelleme_Sonra()
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? Update.errorString() : "BASARILI");
    delay(1000);
    ESP.restart();
}
void Gonder_SayfaBulunamadi() 
{
    BasliklariYazdir();

    server.send(404, "text/plain", "Sayfa bulunamadı");
}

void HttpSunucu_Baslat()
{
    server.on("/", Gonder_AnaSayfa);
    

    //Ayarlar/Cihaz
    server.on("/Kalibrasyon", HTTP_POST, Gonder_Kalibrasyon);
    server.on("/YazilimGuncelle", HTTP_POST, Gonder_YazilimGuncelleme_Sonra, Gonder_YazilimGuncelleme_Once);

    server.onNotFound(Gonder_SayfaBulunamadi);
    server.begin();
}

void HttpSunucu_Calistir()
{
  server.handleClient();
}
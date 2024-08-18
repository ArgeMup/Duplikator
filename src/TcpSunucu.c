#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "TcpSunucu.h"
////////////////////////////////////////////////////////////////////////////////
#define _Gunluk_Baslik "TcpSunucu"	//Gunluk ciktilarini tum dosyada kapatmak icin NULL olmali
#include "Gunluk.h"					//Kaynak kod icinde tanimlanmali
////////////////////////////////////////////////////////////////////////////////

#define ErisimNoktasi 10000

int Soket_Sunucu = -1, Soket_Istemci = -1;

void TcpSunucu_Baslat()
{
    Soket_Sunucu = -1; 
    Soket_Istemci = -1;

    Soket_Sunucu = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (Soket_Sunucu < 0) {
        Gunluk_Hata("Soket olusturulamadi: %d", errno);
        return;
    }

    int opt = 1;
    setsockopt(Soket_Sunucu, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    Gunluk("Soket olusturuldu");

    struct sockaddr_storage dest_addr;
    struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
    dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
    dest_addr_ip4->sin_family = AF_INET;
    dest_addr_ip4->sin_port = htons(ErisimNoktasi);
    int err = bind(Soket_Sunucu, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err != 0) {
        Gunluk_Hata("Soket dinleyici acilamadi: %d", errno);
        Gunluk("IPPROTO: %d", AF_INET);
        TcpSunucu_Durdur();
        return;
    }
    Gunluk("Soket erisim noktasi: %d", ErisimNoktasi);

    err = listen(Soket_Sunucu, 1);
    if (err != 0) {
        Gunluk_Hata("Sunucu acilirken hata oldu: %d", errno);
        TcpSunucu_Durdur();
        return;
    }

    int flags = fcntl(Soket_Sunucu, F_GETFL); 
    if (fcntl(Soket_Sunucu, F_SETFL, flags | O_NONBLOCK) == -1) { 
        Gunluk_Hata("Sunucu bekletmeyen soket olarak ayarlanamadi: %d", errno);
        TcpSunucu_Durdur();
    }
}
void TcpSunucu_Calistir()
{
    if (Soket_Sunucu < 0) 
    {  
        TcpSunucu_Baslat();
        return;
    }

    if (Soket_Istemci < 0)
    {
        struct sockaddr_storage source_addr;
        socklen_t addr_len = sizeof(source_addr);
        Soket_Istemci = accept(Soket_Sunucu, (struct sockaddr *)&source_addr, &addr_len);
        if (Soket_Istemci < 0) {
            // errno == 11 bekleyen istemci yok
            if (errno != 11) Gunluk_Hata("Yeni baglanti beklerken hata: %d", errno);
            return;
        }

        // Set tcp keepalive option
        struct timeval to;
        to.tv_sec = 1;
        to.tv_usec = 0;
        setsockopt(Soket_Istemci,SOL_SOCKET,SO_SNDTIMEO,&to,sizeof(to));
        int keepAlive = 1;
        setsockopt(Soket_Istemci, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(int));
        int keepIdle = 5;
        setsockopt(Soket_Istemci, IPPROTO_TCP, TCP_KEEPIDLE, &keepIdle, sizeof(int));
         int keepInterval = 5;
        setsockopt(Soket_Istemci, IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(int));
        int keepCount = 3;
        setsockopt(Soket_Istemci, IPPROTO_TCP, TCP_KEEPCNT, &keepCount, sizeof(int));

        // Convert ip address to string
        char addr_str[128];
        if (source_addr.ss_family == PF_INET) {
            inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addr_str, sizeof(addr_str) - 1);
        }
        Gunluk("Soket baglandi, adresi: %s", addr_str);
    } 
}

void TcpSunucu_Gonder(void* Tampon, uint32_t Adet)
{
    if (Soket_Istemci < 0 || Adet < 1 || Tampon == NULL) return;

    int to_write = Adet;

    while (to_write > 0) 
    {
        int written = send(Soket_Istemci, Tampon + (Adet - to_write), to_write, 0);
        if (written < 0) 
        {
            shutdown(Soket_Istemci, 0);
            close(Soket_Istemci);
            Soket_Istemci = -1;

            Gunluk_Hata("Gonderme hatasi: %d", errno);
            return;
        }

        to_write -= written;
    }
}

void TcpSunucu_Durdur()
{
    if (Soket_Istemci > 0)
    {
        shutdown(Soket_Istemci, 0);
        close(Soket_Istemci);
        Gunluk("Soket_Istemci Kapatildi");
    }
    Soket_Istemci = -1;

    if (Soket_Sunucu > 0)
    {
        close(Soket_Sunucu);
        Gunluk("Soket_Sunucu Kapatildi");
    }
    Soket_Sunucu = -1;
}
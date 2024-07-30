// Copyright ArgeMup GNU GENERAL PUBLIC LICENSE Version 3 <http://www.gnu.org/licenses/> <https://github.com/ArgeMup/HazirKod_C>
// V1.16

#ifndef __HazirKod_C_Ayarlar_H__
#define __HazirKod_C_Ayarlar_H__

	#ifdef DEBUG
		#warning "!!! HATA AYIKLAMA ICIN DERLENEN KOD CALISIYOR !!!"
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//HazirKod_C_Ayarlar.h
	////////////////////////////////////////////////////////////////////////////////
	#include <stdbool.h>
	#include <stdint.h>
	#include <stdlib.h>
	#include <string.h>

	typedef uint8_t 															Tip_u8;
	typedef int8_t																Tip_i8;
	typedef uint16_t															Tip_u16;
	typedef int16_t 															Tip_i16;
	typedef uint32_t															Tip_u32;
	typedef int32_t 															Tip_i32;
	typedef uint64_t 															Tip_u64;
	typedef int64_t 															Tip_i64;
	typedef bool																Tip_bool;
	typedef char																Tip_char;
	typedef float 																Tip_float;
	typedef void *																Tip_Isaretci;
	typedef size_t																Tip_Isaretci_SayiKarsiligi;
	#define Tip_void															void
	#define Tip_null															NULL
	#define Tip_time															time_t

	#define _Yazdirma_Sablon_TamSayi_i											"%d"				//%d, %ld, %lld
	#define _Yazdirma_Sablon_TamSayi_u											"%u"				//%u, %lu, %llu
	#define _Yazdirma_Sablon_TarihSaat											"%Y-%m-%d %X %Z"	//1881-05-19 23:59:59 GMT
	#define _Yazdirma_Sablon_NoktaliSayi										"%.2f"				//0.99
	#define _Yazdirma_Sablon_Yazi												"%s"				//ArGeMuP
	#define _Yazdirma_Sablon_SatirSonu											"\r\n"				//CRLF
	#define _Yazdirma_Sablon_Hex												"%02X"				//AA
	#define _Yazdirma_Sablon_Hex_Tip_8											"0x%02X"			//0xAA
	#define _Yazdirma_Sablon_Hex_Tip_16											"0x%04X"			//0xAA11
	#define _Yazdirma_Sablon_Hex_Tip_32											"0x%08X"			//0xAA11BB22
	#define _Yazdirma_Sablon_Tip_u8												_Yazdirma_Sablon_TamSayi_u
	#define _Yazdirma_Sablon_Tip_i8												_Yazdirma_Sablon_TamSayi_i
	#define _Yazdirma_Sablon_Tip_u16											_Yazdirma_Sablon_TamSayi_u
	#define _Yazdirma_Sablon_Tip_i16											_Yazdirma_Sablon_TamSayi_i
	#define _Yazdirma_Sablon_Tip_u32											_Yazdirma_Sablon_TamSayi_u
	#define _Yazdirma_Sablon_Tip_i32											_Yazdirma_Sablon_TamSayi_i
	#define _Yazdirma_Sablon_Tip_u64											_Yazdirma_Sablon_TamSayi_u
	#define _Yazdirma_Sablon_Tip_i64											_Yazdirma_Sablon_TamSayi_i
	#define _Yazdirma_Sablon_Tip_bool											_Yazdirma_Sablon_TamSayi_u
	#define _Yazdirma_Sablon_Tip_char											"%c"				//A
	#define _Yazdirma_Sablon_Tip_float											"%f"				//NOKTALI.SAYI
	#define _Yazdirma_Sablon_Tip_Isaretci										"%p"				//99AABBCC
	#define _Yazdirma_Sablon_Tip_Isaretci_SayiKarsiligi							_Yazdirma_Sablon_TamSayi_u

	#define _Islem_memcpy_(x,y,z)												memcpy( ( x ), ( y ), ( z ) )
	#define _Islem_memset_(x,y,z)												memset( ( x ), ( y ), ( z ) )
	#define _Islem_memcmp_(x,y,z)												memcmp( ( x ), ( y ), ( z ) )
	#define _Islem_strlen_(x)													strlen( x )
	#define _Islem_strtol_(x,y,z)												strtol( ( x ), ( y ), ( z ) )
	#define _Islem_strtoul_(x,y,z)												strtoul( ( x ), ( y ), ( z ) )

	#define Isaretci_Konumlandir(Isaretci, Konum, Arttirma_Tipi, Cikti_Tipi)	( (Cikti_Tipi *)( ( (Arttirma_Tipi *)( Isaretci ) ) + ( Konum ) ) )
	#define Isaretci_Konumlandir_u8(Isaretci, Konum)							Isaretci_Konumlandir( Isaretci, Konum, Tip_u8, Tip_u8 )
	#define Isaretci_Konumlandir_i8(Isaretci, Konum)							Isaretci_Konumlandir( Isaretci, Konum, Tip_u8, Tip_i8 )
	#define Isaretci_Konumlandir_u16(Isaretci, Konum)							Isaretci_Konumlandir( Isaretci, Konum, Tip_u8, Tip_u16 )
	#define Isaretci_Konumlandir_i16(Isaretci, Konum)							Isaretci_Konumlandir( Isaretci, Konum, Tip_u8, Tip_i16 )
	#define Isaretci_Konumlandir_u32(Isaretci, Konum)							Isaretci_Konumlandir( Isaretci, Konum, Tip_u8, Tip_u32 )
	#define Isaretci_Konumlandir_i32(Isaretci, Konum)							Isaretci_Konumlandir( Isaretci, Konum, Tip_u8, Tip_i32 )
	#define Isaretci_Konumlandir_u64(Isaretci, Konum)							Isaretci_Konumlandir( Isaretci, Konum, Tip_u8, Tip_u64 )
	#define Isaretci_Konumlandir_i64(Isaretci, Konum)							Isaretci_Konumlandir( Isaretci, Konum, Tip_u8, Tip_i64 )
	#define Isaretci_Konumlandir_float(Isaretci, Konum)							Isaretci_Konumlandir( Isaretci, Konum, Tip_u8, Tip_float )
	#define Isaretci_Icerigi(Isaretci, Konum, Arttirma_Tipi, Cikti_Tipi)		( *Isaretci_Konumlandir( ( Isaretci ), ( Konum ), Arttirma_Tipi, Cikti_Tipi ) )
	#define Isaretci_Icerigi_u8(Isaretci, Konum)								Isaretci_Icerigi( Isaretci, Konum, Tip_u8, Tip_u8 )
	#define Isaretci_Icerigi_i8(Isaretci, Konum)								Isaretci_Icerigi( Isaretci, Konum, Tip_u8, Tip_i8 )
	#define Isaretci_Icerigi_u16(Isaretci, Konum)								Isaretci_Icerigi( Isaretci, Konum, Tip_u8, Tip_u16 )
	#define Isaretci_Icerigi_i16(Isaretci, Konum)								Isaretci_Icerigi( Isaretci, Konum, Tip_u8, Tip_i16 )
	#define Isaretci_Icerigi_u32(Isaretci, Konum)								Isaretci_Icerigi( Isaretci, Konum, Tip_u8, Tip_u32 )
	#define Isaretci_Icerigi_i32(Isaretci, Konum)								Isaretci_Icerigi( Isaretci, Konum, Tip_u8, Tip_i32 )
	#define Isaretci_Icerigi_u64(Isaretci, Konum)								Isaretci_Icerigi( Isaretci, Konum, Tip_u8, Tip_u64 )
	#define Isaretci_Icerigi_i64(Isaretci, Konum)								Isaretci_Icerigi( Isaretci, Konum, Tip_u8, Tip_i64 )
	#define Isaretci_Icerigi_float(Isaretci, Konum)								Isaretci_Icerigi( Isaretci, Konum, Tip_u8, Tip_float )
	#define Isaretci_KapladigiAlan_Bayt											( sizeof(Tip_Isaretci_SayiKarsiligi) )

	#define Bit_Uret_Ters(Bit)													( !( Bit ) )
	#define BitDizisi_Uret_Ters(Degisken) 										( ~( Degisken ) )
	#define BitDizisi_Yaz_Ters(Degisken) 										Degisken = BitDizisi_Uret_Ters( Degisken )
	#define Bit_SolaKaydir_1(Adet)												( 1 << ( Adet ) )
	#define Bit_SolaKaydir_0(Adet)												( BitDizisi_Uret_Ters( Bit_SolaKaydir_1( Adet ) ) )
	#define Bit_Oku(Degisken, No)												( ( ( Degisken ) & Bit_SolaKaydir_1( No ) ) > 0 )
	#define BitDizisi_Uret_Bit_1(Degisken, No)									Degisken | Bit_SolaKaydir_1( No )
	#define BitDizisi_Uret_Bit_0(Degisken, No)									Degisken & Bit_SolaKaydir_0( No )
	#define BitDizisi_Uret_Bit_Ters(Degisken, No)								( Bit_Oku( ( Degisken ), ( No ) ) ? BitDizisi_Uret_Bit_0( ( Degisken ), ( No ) ) : BitDizisi_Uret_Bit_1( ( Degisken ), ( No ) ) )
	#define Bit_Yaz_1(Degisken, No)												Degisken = BitDizisi_Uret_Bit_1( ( Degisken ), ( No ) )
	#define Bit_Yaz_0(Degisken, No)												Degisken = BitDizisi_Uret_Bit_0( ( Degisken ), ( No ) )
	#define Bit_Yaz_Ters(Degisken, No)											Degisken = BitDizisi_Uret_Bit_Ters( ( Degisken ), ( No ) )
	#define BaytDizisi_Yaz_Ters(Isaretci_Hedef, Isaretci_Kaynak, Adet)  		for (Tip_u8 i = 0; i < Adet; i++) { Isaretci_Icerigi_u8(Isaretci_Hedef, i) = Isaretci_Icerigi_u8(Isaretci_Kaynak, Adet - 1 - i); }

	//BaytDizisinin Hafizadaki Yerlesimi
	//Bilgi 0x11223344 Hafiza Adresi 0x00 0x01 0x02 0x03
	//Yuksekten Dusuge				 0x11 0x22 0x33 0x44 Big endian
	//Dusukten Yuksege				 0x44 0x33 0x22 0x11 Little endian
	#define BaytDizisi_HafizaYerlesimi_YuksektenDusugeMi(CevabinYazilacagiBoolDegiskeni) { Tip_u32 Gecici = 0x44332211; CevabinYazilacagiBoolDegiskeni = Isaretci_Icerigi_u8(&Gecici, 0) == 0x44; }
	#define BaytDizisi_HafizaYerlesimi_DusuktenYuksegeMi(CevabinYazilacagiBoolDegiskeni) { Tip_u32 Gecici = 0x44332211; CevabinYazilacagiBoolDegiskeni = Isaretci_Icerigi_u8(&Gecici, 0) == 0x11; }
	#define BaytDizisi_HafizaYerlesimi_YuksektenDusugeMi_2()					( __BYTE_ORDER == __BIG_ENDIAN )
	#define BaytDizisi_HafizaYerlesimi_DusuktenYuksegeMi_2()					( __BYTE_ORDER == __LITTLE_ENDIAN )

	#define Hesapla_Yuzde(Kullanim, Butun)										( ( ( Kullanim ) * 100 ) / ( Butun ) )
	#define Hesapla_Dolgu(Kullanim, Butun)										( ( Butun ) - ( ( Kullanim ) & ( ( Butun ) - 1 ) ) )
	#define Hesapla_EnKucuk(x, y)												( ( x ) < ( y ) ? ( x ) : ( y ) )
	#define Hesapla_EnBuyuk(x, y)												( ( x ) > ( y ) ? ( x ) : ( y ) )

	////Hazir atamalar
	//#define YenidenBaslat(Sebep)												abort()
	//#define Bekle_MiliSaniye(Sure)											Sleep(Sure)
	//#define Bacak_Yaz_1(Bacak)
	//#define Bacak_Yaz_0(Bacak)
	//#define Bacak_Oku(Bacak)

	#define _Hataliysa_(Islem, KarsilastirmaIslemi, BeklenenSonuc, SonucunYazilacagiDegisken, Hataliysa_SonIslemler) if ( Bit_Uret_Ters( ( SonucunYazilacagiDegisken = ( Islem ) ) KarsilastirmaIslemi ( BeklenenSonuc ) ) ) { Hataliysa_SonIslemler }
	#define Hataliysa_YenidenBaslat(Islem, KarsilastirmaIslemi, BeklenenSonuc, SonucunYazilacagiDegisken) _Hataliysa_(Islem, KarsilastirmaIslemi, BeklenenSonuc, SonucunYazilacagiDegisken, Gunluk_BeklenmeyenDurum("Satir : " _Yazdirma_Sablon_TamSayi_i ", Sebep : " _Yazdirma_Sablon_Tip_Isaretci_SayiKarsiligi, __LINE__, (Tip_Isaretci_SayiKarsiligi)SonucunYazilacagiDegisken); YenidenBaslat((Tip_Isaretci_SayiKarsiligi)SonucunYazilacagiDegisken); )
	#define Hataliysa_GeriDon(Islem, KarsilastirmaIslemi, BeklenenSonuc, SonucunYazilacagiDegisken) _Hataliysa_(Islem, KarsilastirmaIslemi, BeklenenSonuc, SonucunYazilacagiDegisken, Gunluk_Hata("Satir : " _Yazdirma_Sablon_TamSayi_i ", Sebep : " _Yazdirma_Sablon_Tip_Isaretci_SayiKarsiligi, __LINE__, (Tip_Isaretci_SayiKarsiligi)SonucunYazilacagiDegisken); return; )
	#define Hataliysa_EtiketeGit(Islem, KarsilastirmaIslemi, BeklenenSonuc, SonucunYazilacagiDegisken, Etiket) _Hataliysa_(Islem, KarsilastirmaIslemi, BeklenenSonuc, SonucunYazilacagiDegisken, Gunluk_Hata("Satir : " _Yazdirma_Sablon_TamSayi_i ", Sebep : " _Yazdirma_Sablon_Tip_Isaretci_SayiKarsiligi, __LINE__, (Tip_Isaretci_SayiKarsiligi)SonucunYazilacagiDegisken); goto Etiket; )

	////////////////////////////////////////////////////////////////////////////////
	//Kullanilmayan Kutuphanelerin Kapatilabilmesi icin Anahtarlar // Acik Birakildiginda ihtiyac Duyulan Diger Kutuphaneler
	////////////////////////////////////////////////////////////////////////////////
	#define HazirKod_C_Kullan_AramaIslemleri	//
	#define HazirKod_C_Kullan_Depo				//Gunluk IlkGirenIlkCikar
	#define HazirKod_C_Kullan_Dizi				//YerTahsisati
	#define HazirKod_C_Kullan_Gorev				//Zamanlama Liste
	#define HazirKod_C_Kullan_Gunluk			//Zamanlama
	#define HazirKod_C_Kullan_IlkGirenIlkCikar	//Gunluk YerTahsisati
	#define HazirKod_C_Kullan_KomutSatiri		//Tampon AramaIslemleri YaziIslemleri
	#define HazirKod_C_Kullan_LedKontrol		//Gorev
	#define HazirKod_C_Kullan_Liste				//YerTahsisati
	#define HazirKod_C_Kullan_Tampon			//YerTahsisati
	#define HazirKod_C_Kullan_YaziIslemleri		//AramaIslemleri
	#define HazirKod_C_Kullan_YerTahsisati		//Gunluk
	#define HazirKod_C_Kullan_Zamanlama			//
	//#define HazirKod_C_Kullan_DeneyselEklentiler

	////////////////////////////////////////////////////////////////////////////////
	//AramaIslemleri.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_AramaIslemleri
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//Depo.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_Depo
		//#define _Depo_Sablon_KullaniciNesnesi	//KullaniciNesnesini kapatmak icin bu satiri kaldir
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//Dizi.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_Dizi
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//Gorev.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_Gorev
		typedef Tip_u8 							_Tip_Gorev_CalistirilacakAdim;
		//#define _Gorev_Sablon_KullaniciNesnesi	//KullaniciNesnesini kapatmak icin bu satiri kaldir
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//Gunluk.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_Gunluk
		#define _Gunluk_Cikti_Onem_Seviyesi 					_Gunluk_Cikti_Onem_Seviye_Geveze
		#define _Gunluk_Renkli_Cikti_Uretsin
		#define _Gunluk_Sablon_Satir_Numarasi					":" _Yazdirma_Sablon_TamSayi_i //Satir numarasini kapatmak icin bu satiri kaldir
		
		#define _Gunluk_Renk_DerleyiciHataGiderici				( enum e_Gunluk_Gorunum_ ) //error: invalid conversion from 'int' to 'e_Gunluk_Gorunum_'
		#define _Gunluk_Renk_BeklenmeyenDurum					( _Gunluk_Renk_DerleyiciHataGiderici( e_Gunluk_Gorunum_Yazi_Beyaz | e_Gunluk_Gorunum_Yuzey_Kirmizi ) )
		#define _Gunluk_Renk_Hata								( _Gunluk_Renk_DerleyiciHataGiderici( e_Gunluk_Gorunum_Yazi_Kirmizi | e_Gunluk_Gorunum_Yuzey_Siyah ) )
		#define _Gunluk_Renk_Uyari								( _Gunluk_Renk_DerleyiciHataGiderici( e_Gunluk_Gorunum_Yazi_Sari | e_Gunluk_Gorunum_Yuzey_Siyah ) )
		#define _Gunluk_Renk_Bilgi								( _Gunluk_Renk_DerleyiciHataGiderici( e_Gunluk_Gorunum_Yazi_Yesil | e_Gunluk_Gorunum_Yuzey_Siyah ) )
		#define _Gunluk_Renk_Geveze								( _Gunluk_Renk_DerleyiciHataGiderici( e_Gunluk_Gorunum_Duzyazi ) )
		#define _Gunluk_Hex_BirSatirdakiBilgiSayisi				( 16 )
		#define _Gunluk_Tampon_Kapasitesi_Sabit					( 256 ) //Sabit miktarda stack dan temin edilen alan icin bu satiri ac
		#ifndef _Gunluk_Tampon_Kapasitesi_Sabit
			#define _Gunluk_Tampon_Azami_Kapasitesi				( 2048 ) //Degisken miktarda heap den temin edilen alan icin usttekini kapat
		#endif
	
		//Tip_void Gunluk_Disari_Aktarma_Islemi(Tip_Isaretci Tampon, Tip_u32 Adet)
		//{
		//	printf(_Yazdirma_Sablon_Yazi, (const Tip_char*)Tampon);
		//	fflush(stdout);
		//  veya
		//  fwrite ((const Tip_void*)Tampon, sizeof(Tip_u8), Adet, stdout);
		//}

		////////////////////////////////////////////////////////////////////////////////
		//#define _Gunluk_Baslik "KaynakKod"	//Gunluk ciktilarini tum dosyada kapatmak i�in NULL olmali
		//#include "Gunluk.h"					//Kaynak kod i�inde tanimlanmali
		////////////////////////////////////////////////////////////////////////////////
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//HataKontrol
	////////////////////////////////////////////////////////////////////////////////
	enum e_HataDurumu_Hatalar_
	{
		//Uygulama Hatalari
		e_HataDurumu_Hata_Hata1,
		e_HataDurumu_Hata_Hata2,

		//Sabit
		e_HataDurumu_Hata_SonEleman //Ilk eleman en onemli hatadir
	};
	#define HataDurumu_Baslat(Degisken)									Degisken = 0 //senaryo olarak, cihaz ilk kez calistiginda herseyin hatali oldugunu varsayip kontrol ede ede hatalari silmesi icin 0 yazildi
	#define HataDurumu_HataDevamEdiyorMu(Degisken, e_HataDurumu_Hatalar_)	( !Bit_Oku(Degisken, e_HataDurumu_Hatalar_) )
	#define	HataDurumu_Hatasiz(Degisken, e_HataDurumu_Hatalar_)			Bit_Yaz_1(Degisken, e_HataDurumu_Hatalar_)
	#define	HataDurumu_Hatali(Degisken, e_HataDurumu_Hatalar_)			Bit_Yaz_0(Degisken, e_HataDurumu_Hatalar_)

	////////////////////////////////////////////////////////////////////////////////
	//IlkGirenIlkCikar.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_IlkGirenIlkCikar
		//#define _IGIC_Sablon_KullaniciNesnesi	//KullaniciNesnesini kapatmak icin bu satiri kaldir
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//KomutSatiri.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_KomutSatiri
		#define _KomutSatiri_Yazi_Ayiracsiz_TekParca_Olabilir
		#define _KomutSatiri_Yazi_Icinde_OzelKarakter_Olabilir
		#define _KomutSatiri_UzunKomut_Baslangici				"Kart"
		#define _KomutSatiri_Komut_Bitisi						_Yazdirma_Sablon_SatirSonu
		#define _KomutSatiri_Cevap_Baslangici					">>"
		#define _KomutSatiri_Cevap_Bitisi						_KomutSatiri_Komut_Bitisi
		#define _KomutSatiri_Ayirac			 					' '
		#define _KomutSatiri_Ayirac_Yazi			 			'"'
		#define _KomutSatiri_Ayirac_Yazi_OzelKarakter 			'|'
		#define _KomutSatiri_DonanimAdresi_GenelCagri			( 0 )
		#define _KomutSatiri_DonanimAdresi_Kendisi				( 1 ) //( Ayarlar.Cihaz.DonanimAdresi )
		#define _KomutSatiri_KisaKomut_EnAzKaSa					( (1 /*Komut*/) + (sizeof(_KomutSatiri_Komut_Bitisi) - 1) )
		#define _KomutSatiri_UzunKomut_EnAzKaSa					( (sizeof(_KomutSatiri_UzunKomut_Baslangici) - 1) + (1 /*Ayirac*/) + (1 /*Adres*/) + (1 /*Ayirac*/) + (1 /*Komut*/) + (sizeof(_KomutSatiri_Komut_Bitisi) - 1) )
		#define _KomutSatiri_Cevap_Onay							"Tamam"
		#define _KomutSatiri_Cevap_Ret							"Hata"
		//Ornek Tamsayi				-> 1 VEYA -1 VEYA +1
		//Ornek Hex					-> 0xAA VEYA 0x112233445566778899AABBCCDDEEFF
		//Ornek Yazi				-> "Ornek Yazi"										Alisildik bicim
		//Ornek Yazi				-> OrnekYazi										_KomutSatiri_Yazi_Ayiracsiz_TekParca_Olabilir
		//Ornek Yazi				-> "Yazi|13||10|" -> "Yazi+CR+LF"					_KomutSatiri_Yazi_Icinde_OzelKarakter_Olabilir
		//Ornek Kisa Komut 			-> Komut1\r\n Cevap -> >>Tamam\r\n 					Genel cagri olarak degerlendirilip calistirilir
		//Ornek Uzun Komut 			-> Kart 0 Komut1\r\n Cevap -> >>Tamam\r\n 			Genel cagri olarak degerlendirilip calistirilir
		//Ornek Uzun Komut 			-> Kart 1 Komut1\r\n Cevap -> >>Tamam\r\n 			DonanimAdresi uygun oldugu icin calistirilir
		//Ornek Uzun Komut 			-> Kart 2 Komut1\r\n Cevap -> Gonderilmez			DonanimAdresi uygun olmad?gi icin calistirilmaz
		//Ornek Uzun Hatali Komut	-> Kart 1 KoXYZ\r\n  Cevap -> >>Hata PARAMETRE\r\n	Calistirilir, fazladan sebep gonderilir
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//LedKontrol.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_LedKontrol
		#define _LedKontrol_HataDurumuDegiskeni					( 0xFFFFFFFF ) // ( Ayarlar.Cihaz.HataDurumu ) Bu degiskeni kullanici tanimlar
		#define _LedKontrol_GosterilebilecekHataSayisi			( 2 ) // ornegin e_HataDurumu_Hatalar_ eleman sayisi kadar
		#define _LedKontrol_AnlikBildirim_Bekleme				( 50 )
		#define _LedKontrol_AnlikBildirim_Adet					( 5 )
		#define _LedKontrol_HerseyYolunda_Bekleme_Kisa			( 150 )
		#define _LedKontrol_HerseyYolunda_Bekleme_Uzun			( 1500 )
		#define _LedKontrol_HataVar_Bekleme_Kisa				( 500 )
		#define _LedKontrol_HataVar_Bekleme_Uzun				( 1500 - _LedKontrol_HerseyYolunda_Bekleme_Kisa )
		
		//Tip_void LedKontrol_YakSondur_Islemi(Tip_bool Yak)
		//{
		//	...
		//}	
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//Liste.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_Liste
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//Tampon.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_Tampon
		typedef struct
		{
			bool IsiBitinceSil;
			Tip_Isaretci Nesne;
		} Tip_s_Tampon_KullaniciNesnesi;
		//#define _Tampon_Sablon_KullaniciNesnesi					Tip_s_Tampon_KullaniciNesnesi //KullaniciNesnesini kapatmak icin bu satiri kaldir
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//YaziIslemleri.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_YaziIslemleri
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//YerTahsisati.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_YerTahsisati
		//#define _YT_Tanimli_HEAP_Kutuphanesini_kullanMA
		#ifndef _YT_Tanimli_HEAP_Kutuphanesini_kullanMA
			#define _YT_Islem_malloc_(x)						malloc(x)
			#define _YT_Islem_free_(x)							free(x)

			//#define _YT_Tahsis_Edilen_Alani_Kontrol_Et
			#ifdef _YT_Tahsis_Edilen_Alani_Kontrol_Et
				#define _YT_Ram_Baslangic 						( (Tip_u32)0 )							//(Tip_u32)&__heap_start__
				#define _YT_Ram_Bitis							( (Tip_u32)( _YT_Ram_Baslangic - 1 ) )	//(Tip_u32)&__heap_end__
			#endif
		#else
			////////////////////////////////////////////////////////////////////////////////
			//Heap_4.h
			////////////////////////////////////////////////////////////////////////////////
			#define configTOTAL_HEAP_SIZE 						( 5 * 1024 )
			#define portBYTE_ALIGNMENT 							( 8 )
		#endif
	#endif

	////////////////////////////////////////////////////////////////////////////////
	//Zamanlama.h
	////////////////////////////////////////////////////////////////////////////////
	#ifdef HazirKod_C_Kullan_Zamanlama
		#define _Zamanlama_An_Aralik_Msn_								( 1 ) // !!! �nlemleri silme
		#define _Zamanlama_Yazdirma_Sablon								"%llu" //%u, %lu, %llu

		#define _Zamanlama_An_Okuma_Islemi_8bayt_Deger_Uretiyor		//Kullanilan donanima ait tick islemi 8 bayt deger donduruyorsa bu anahtar� ac
		#ifndef _Zamanlama_An_Okuma_Islemi_8bayt_Deger_Uretiyor			//4 baytlik deger dondugunden calisma seklini secmek gerekiyor
			#define _Zamanlama_Tasmayan_Yontemi_Kullan					//Tasmaz fakat daha fazla ram kullanir ve farkli THREAD lerden cagirilacak ise Tip_Islem_Zamanlama_Kilit doldurulmali
		#endif															//Di�er her halukarda -> _Zamanlama_An_Aralik_Msn_ 1 olarak yaz�l�r ise kabaca 44 gun sonra sayac tasar

		//_Tip_Sure_Islem Zamanlama_An_Okuma_Islemi()
		//{
		//	return GetTickCount(); !!! 1 LSB nin degeri _Zamanlama_An_Aralik_Msn_ kadar olmali
		//}
	#endif

#endif /*__HazirKod_C_Ayarlar_H__ */

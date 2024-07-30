#include "Ortak.h"

const char *Uygulama_Adi = "Duplikator";
const char *Wifi_ErisimNoktasi_Adi = "Duplikator";
const char *Wifi_ErisimNoktasi_Parolasi = "19051881";
unsigned long AnaDonguDahaHizliCalissin_BitisAni = 0; 

const char * Gunler[] =
{
    "Pazar", "Pazartesi", "Salı", "Çarşamba", "Perşembe", "Cuma", "Cumartesi"
};

struct Cihaz_ Cihaz;

#pragma region Html_SayiGirisi
const char Html_SayiGirisi[] = R"rawliteral(
<div>
    <label for="??? Sayi Girisi Adi ???">??? Sayi Girisi Aciklama ???</label>
    <input type="number" ??? Sayi Girisi Aralik ??? id="??? Sayi Girisi Adi ???" name="??? Sayi Girisi Adi ???" value="??? Sayi Girisi Degeri ???" required>
</div> 
)rawliteral";
#pragma endregion

#pragma region Html_Ayarlar_Tablo
const char Html_Ayarlar_Tablo[] = R"rawliteral(
<tr>
    <td><input type="checkbox" name="1Gun_??? 1 Gun No ???" value="E" ??? 1 Onay ???></td>
    <td>??? 1 Gun ???</td>
    <td><input type="time" name="1Basla_??? 1 Gun No ???" value="??? 1 Saat ???" required></td>
    <td><input type="number" name="1Sure_??? 1 Gun No ???" min="0" max="24" value="??? 1 Sure ???" required></td>
</tr> 
)rawliteral";
#pragma endregion
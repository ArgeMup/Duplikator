#include "Ortak.h"

const char *Uygulama_Adi = "Duplikator";
const char *Wifi_ErisimNoktasi_Adi = "Duplikator";
const char *Wifi_ErisimNoktasi_Parolasi = "19051881";
const char *Wifi_Istasyon_Ilk_Adi = "_test_";
const char *Wifi_Istasyon_Ilk_Parolasi = "11233455667889";
unsigned long AnaDonguDahaHizliCalissin_BitisAni = 0; 

#pragma region Html_SayiGirisi
const char Html_SayiGirisi[] = R"rawliteral(
<div>
    <label for="??? Sayi Girisi Adi ???">??? Sayi Girisi Aciklama ???</label>
    <input type="number" ??? Sayi Girisi Aralik ??? id="??? Sayi Girisi Adi ???" name="??? Sayi Girisi Adi ???" value="??? Sayi Girisi Degeri ???" required>
</div> 
)rawliteral";
#pragma endregion

#pragma region Html_AnaSayfa
const char Html_AnaSayfa[] = R"rawliteral(
<!DOCTYPE html>
<html lang="tr">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="refresh" content="5">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>??? Uygulama ???</title>
    <style>
        body {
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }

        .kaydirici-container {
            width: 400px;
            height: 50px;
            position: relative;
            border-radius: 25px;
            cursor: pointer;
            display: flex;
        }

        .kaydirici {
            width: 133px;
            height: 50px;
            background-color: #00a000;
            position: absolute;
            border-radius: 25px;
            transition: left 1s, background-color 1s;
            display: flex;
            justify-content: center;
            align-items: center;
            color: white;
            font-weight: bold;
            font-size: 18px;
        }

        .region {
            flex: 1;
            display: flex;
            justify-content: center;
            align-items: center;
            color: #666;
            font-weight: bold;
            font-size: 18px;
            text-align: center;
            border-radius: 25px 25px 25px 25px;
        }

        .region:nth-child(1) {
            background-color: rgba(187, 187, 187, 0.8); /* Transparan gri */
        }

        .region:nth-child(2) {
            background-color: rgba(136, 136, 136, 0.8); /* Transparan koyu gri */
        }

        .region:nth-child(3) {
            background-color: rgba(187, 187, 187, 0.8); /* Transparan gri */
        }

        .info-table {
            width: 400px;
            border-collapse: collapse;
        }

        .info-table th, .info-table td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: center;
        }

        .info-table th {
            background-color: #f4f4f4;
        }

        .info-table td {
            background-color: #fff;
        }

        .button-container {
            text-align: center;
        }

        .button {
            background-color: #00a000; /* Yeşil arka plan rengi */
            color: white;
            padding: 10px 20px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 18px;
            font-weight: bold;
            border-radius: 5px; /* Köşe yuvarlatma */
        }

        select {
            width: 100%; /* Tam genişlik */
            padding: 8px;
            border: 1px solid #ddd;
            border-radius: 15px; /* Köşe yuvarlatma */
            font-size: 16px;
        }

        #toast {
            visibility: hidden;
            min-width: 250px;
            margin-left: -125px;
            background-color: #00a000;
            color: #fff;
            text-align: center;
            padding: 16px;
            position: fixed;
            z-index: 1;
            left: 50%;
            bottom: 30px;
            font-size: 18px;
            font-weight: bold;
            border-radius: 15px;
            border-style: solid;
            border-width: 2px;
            border-color: black;
        }

        #toast.show {
            visibility: visible;
            -webkit-animation: fadein 0.5s, fadeout 5s 1s;
            animation: fadein 0.5s, fadeout 5s 1s;
        }
    </style>
</head>
<body>
    <div id="toast"></div>
    <label style="font-size: xx-large;">??? Uygulama ???</label>
    <br>
    <div class="kaydirici-container" id="kaydiriciContainer">
        <div class="region">Kontrollü</div>
        <div class="region">Kapalı</div>
        <div class="region">Programlı</div>
        <div class="kaydirici" id="kaydirici">Kontrollü</div>
    </div>
    <br>??? Aciklama Asama ???<br><br>
    <table class="info-table">
        <tr>
            <th>Seçili Program</th>
            <th>
                <select>
                    <!--??? Programlar ve isimleri  
                        <option value="1" selected>1 : Program 1</option>
                    ???--> 
                </select>
            </th>
        </tr>
        <tr>
            <!--🔴🟢-->
            <td>Karıştırıcı</td>
            <td>??? Karistirici ???</td>
        </tr>
        <tr>
            <td>Soğutucu</td>
            <td>??? Sogutucu ???</td>
        </tr>
        <tr>
            <td>Isıtıcı 1</td>
            <td>??? Isitici 1 ???</td>
        </tr>
        <tr>
            <td>Isıtıcı 2</td>
            <td>??? Isitici 2 ???</td>
        </tr>
        <tr>
            <td>Kazan Sıcaklığı</td>
            <td>??? Kazan ??? °C</td>
        </tr>
        <tr>
            <td>Çevre Sıcaklığı</td>
            <td>??? Cevre ??? °C</td>
        </tr>
        <tr>
            <td>İşlemci Sıcaklığı</td>
            <td>??? Islemci ??? °C</td>
        </tr>
        <tr>
            <td>Akım Tüketimi</td>
            <td>??? Akim ??? A</td>
        </tr>
    </table>
    <br>
    <div class="button-container">
        <a href="/Ayarlar" class="button">Ayarlar</a>
    </div>

    <script>
        document.addEventListener('DOMContentLoaded', function () {
            const kaydirici = document.getElementById('kaydirici');
            const kaydiriciContainer = document.getElementById('kaydiriciContainer');

            kaydiriciContainer.addEventListener('click', function (event) {
                const containerWidth = kaydiriciContainer.offsetWidth;
                const clickX = event.clientX - kaydiriciContainer.getBoundingClientRect().left;
 
                let value;
                if (clickX < containerWidth / 3) {
                    value = 1;
                } else if (clickX < 2 * containerWidth / 3) {
                    value = 2;
                } else {
                    value = 3;
                }

                updateKaydiriciPosition(value);
                //Durum değişikliğini buradan gönder
            });

            function updateKaydiriciPosition(value) {
                switch (value) {
                    case 1:
                        kaydirici.style.left = '0';
                        kaydirici.style.backgroundColor = '#4caf50';
                        kaydirici.textContent = 'Kontrollü';
                        break;
                    case 2:
                        kaydirici.style.left = '133px';
                        kaydirici.style.backgroundColor = '#f44336';
                        kaydirici.textContent = 'Kapalı';
                        break;
                    case 3:
                        kaydirici.style.left = '267px';
                        kaydirici.style.backgroundColor = '#4caf50';
                        kaydirici.textContent = 'Programlı';
                        break;
                }
            }

            function GonderAl(Sayfa, Icerik) {
                fetch(Sayfa, {
                    method: 'POST',
                    headers: { 'Content-Type': 'text/plain' },
                    body: Icerik
                })
                .then(response => {
                    if (response.ok) {
                        var toast = document.getElementById("toast");
                        toast.innerHTML = "Başarılı";
                        toast.className = "show";
                        setTimeout(function() {
                            toast.className = toast.className.replace("show", "");
                        }, 3000);
                    }
                    else {
                        alert('Beklenmeyen bir durum oluştu A: ' + response.body);
                    }
                })
                .catch(error => {
                    alert('Beklenmeyen bir durum oluştu B: ' + error.message);
                });
            }

            // İlk pozisyonu ayarlama
            updateKaydiriciPosition(0/*??? Ilk Acilacak Sayfa No ???*/);
        });
    </script>
</body>
</html>
)rawliteral";
#pragma endregion

#pragma region Html_Ayarlar
const char Html_Ayarlar[] = R"rawliteral(
<!DOCTYPE html>
<html lang="tr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ayarlar Sayfası</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
        }
        .container {
            padding: 20px;
            background-color: #fff;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }
        .nav button {
            background-color: #007bff;
            color: #fff;
            border: none;
            padding: 10px 20px;
            margin-right: 10px;
            cursor: pointer;
            font-size: 18px;
            font-weight: bold;
        }
        .page {
            display: none;
        }
        .page.active {
            display: block;
        }
        .form-container div {
            display: table-row;
        }
        .form-container div label,
        .form-container div input,
        .form-container div select {
            display: table-cell;
            padding: 10px;
            border: 1px solid #ddd;
            vertical-align: middle; /* Dikey hizalama */
        }
        .form-container div label {
            text-align: right;
            font-weight: bold;
        }
        .form-container div input,
        .form-container div select {
            width: 100%;
            box-sizing: border-box; /* İçerik ve kenarlık toplam genişliği */
        }
        .file-upload input[type="file"] {
            display: none;
        }
        .file-upload label {
            background-color: #007bff;
            color: #fff;
            padding: 10px 20px;
            cursor: pointer;
            border-radius: 5px;
            font-size: 16px;
        }
        .button-container button {
            background-color: #28a745;
            color: #fff;
            border: none;
            padding: 10px 20px;
            cursor: pointer;
            font-size: 16px;
            border-radius: 5px;
        }
        table {
            width: 100%;
            border-collapse: collapse;
        }
        table, th, td {
            border: 1px solid #ddd;
        }
        th, td {
            padding: 10px;
            text-align: center;
        }
        th {
            background-color: #007bff;
            color: #fff;
        }
        input[type="time"],
        input[type="number"] {
            width: 100%;
            box-sizing: border-box;
        }
        .program-list {
            width: 100%;
        }
        .program-list select {
            width: 100%;
            padding: 10px;
            font-size: 16px;
            border-radius: 15px;
        }
        /* Ön Isıtma Sırasında alan stili */
        .preheating-settings {
            width: 100%;
        }
        .preheating-settings h3 {
            padding: 10px 0;
            border-bottom: 2px solid #007bff;
        }
        
        #toast {
            visibility: hidden;
            min-width: 250px;
            margin-left: -125px;
            background-color: #00a000;
            color: #fff;
            text-align: center;
            padding: 16px;
            position: fixed;
            z-index: 1;
            left: 50%;
            bottom: 30px;
            font-size: 18px;
            font-weight: bold;
            border-radius: 15px;
            border-style: solid;
            border-width: 2px;
            border-color: black;
        }

        #toast.show {
            visibility: visible;
            -webkit-animation: fadein 0.5s, fadeout 5s 1s;
            animation: fadein 0.5s, fadeout 5s 1s;
        }

        @-webkit-keyframes fadein {
            from {bottom: 0; opacity: 0;}
            to {bottom: 30px; opacity: 1;}
        }

        @keyframes fadein {
            from {bottom: 0; opacity: 0;}
            to {bottom: 30px; opacity: 1;}
        }

        @-webkit-keyframes fadeout {
            from {bottom: 30px; opacity: 1;}
            to {bottom: 0; opacity: 0;}
        }

        @keyframes fadeout {
            from {bottom: 30px; opacity: 1;}
            to {bottom: 0; opacity: 0;}
        }
    </style>
</head>
<body>
    <div id="toast"></div>
    <div class="container">
        <div class="nav">
            <button onclick="showPage('programs')">Programlar</button>
            <button onclick="showPage('wifi')">Wifi</button>
            <button onclick="showPage('devices')">Cihaz</button>
        </div>
        <div id="programs" class="page active">
            <h2>Programlar</h2> 
            <p>Program ayarlarını buradan yapabilirsiniz.</p>
            <div class="program-list">
                <label style="font-size: large;" for="program-select">Program Seç:</label>
                <select id="program-select">
                    <!--??? Programlar ve isimleri  
                        <option value="1" selected>1 : Program 1</option>
                    ???--> 
                </select>
            </div>
            <br>
            <form id="program-settings-form" action="/Programlar" method="post">
                <div>
                    <label style="font-size: large;" for="ProgramAdi">Program Adı:</label>
                    <input value="??? 1 Program Adi ???" style="width: 100%;" type="text" id="ProgramAdi" name="ProgramAdi" required>
                </div>
                <br>
                <div class="form-container">    
                    <!-- Haftanın günleri tablosu -->
                    <table>
                        <thead>
                            <tr>
                                <th>Etkin</th>
                                <th>Gün</th>
                                <th>Başlangıç Zamanı</th>
                                <th>Çalışma Süresi (Saat)</th>
                            </tr>
                        </thead>
                        <tbody>
                            <!-- 
                            <tr>
                                <td><input type="checkbox" name="weekdays" value="pzt" ??? 1 Onay ???></td>
                                <td>??? 1 Gun ???</td>
                                <td><input type="time" name="pzt-start" value="??? 1 Saat ???" required></td>
                                <td><input type="number" name="pzt-duration" min="0" value="??? 1 Sure ???" required></td>
                            </tr> 
                            -->
                            ??? 1 Tablo ???
                        </tbody>
                    </table>
                    <!-- Ön Isıtma Sırasında alanı -->
                    <div class="preheating-settings">
                        <h3>Ön Isıtma Sırasında</h3>
                        <div>
                            <!-- 
                            <div>
                                <label for="??? Sayi Girisi Adi ???">??? Sayi Girisi Aciklama ???</label>
                                <input type="number" ??? Sayi Girisi Aralik ??? id="??? Sayi Girisi Adi ???" name="??? Sayi Girisi Adi ???" value="??? Sayi Girisi Degeri ???" required>
                            </div> 
                            -->
                            ??? 1 OnIsitma ???
                        </div>
                    </div>
                    <!-- Ön Isıtma Sırasında alanı -->
                    <div class="preheating-settings">
                        <h3>Kullanım Sırasında</h3>
                        <div>
                            ??? 1 Kullanım ???
                        </div>
                    </div>
                </div>
                <br>
                <div class="button-container">
                    <button type="submit">Kaydet</button>
                </div>
            </form>    
        </div>
        <div id="wifi" class="page">
            <h2>Wifi</h2>
            <p>Wifi ayarlarını buradan yapabilirsiniz.</p>
            <form id="wifi-settings-form" action="/WifiAyarlar" method="post">
                <div class="form-container">
                    <div>
                        <label for="wifi-name">Erişim Noktası</label>
                        <input id="wifi-name" name="wifi-name" required maxlength="63">
                    </div>
                    <div>
                        <label for="wifi-password">Parola</label>
                        <input type="password" id="wifi-password" name="wifi-password" required maxlength="63">
                    </div>
                </div>
                <br>
                <div class="button-container">
                    <button type="submit">Kaydet</button>
                </div>
            </form>
        </div>
        <div id="devices" class="page">
            <h2>Cihaz</h2>
            <p>Cihaz ayarlarını buradan yapabilirsiniz.</p>
            <div class="preheating-settings form-container">
                <h3>Kalibrasyon</h3>
                <div>
                    ??? 3 Kalibrasyon ???
                    <br>
                    <div class="button-container">
                        <button onclick="GonderAl('/Kalibrasyon', '?3KazanSicakligi=' + document.getElementById('3KazanSicakligi').value + '&3KazanHassasiyeti=' + document.getElementById('3KazanHassasiyeti').value)">Kaydet</button>
                    </div>
                </div>
            </div>
            <div class="preheating-settings">
                <h3>Yazılım Güncelleme</h3>
                <p>Yazılım : ??? 3 Surum ???</p>
                <p>Dahili Saat : ??? 3 Saat ???</p>
                <br>
                <form id="file-upload-form" action="/YazilimGuncelle" method="post" enctype="multipart/form-data">
                    <div class="file-upload">
                        <input type="file" id="dfu-file" name="dfu-file" onchange="displayFileName()">
                        <label for="dfu-file">DFU Dosyası Seç</label>
                        <p id="file-name">Seçilen dosya yok</p>
                    </div>
                    <!-- Gizli alan dosya adını tutar -->
                    <input type="hidden" id="file-name-hidden" name="file-name">
                    <div class="button-container">
                        <button type="submit">Gönder</button>
                    </div>
                </form>
            </div>
        </div>
    </div>
    <script>
        function showPage(pageId) {
            // Tüm sayfaları gizle
            const pages = document.querySelectorAll('.page');
            pages.forEach(page => page.classList.remove('active'));
            
            // Aktif butonu güncelle
            const buttons = document.querySelectorAll('.nav button');
            buttons.forEach(button => button.classList.remove('active'));
            
            // Seçilen sayfayı göster
            document.getElementById(pageId).classList.add('active');
            
            // Aktif butonu güncelle
            const activeButton = [...buttons].find(button => button.textContent.toLowerCase() === pageId);
            if (activeButton) {
                activeButton.classList.add('active');
            }
        }

        function displayFileName() {
            const fileInput = document.getElementById('dfu-file');
            const fileName = fileInput.files.length > 0 ? fileInput.files[0].name : 'Seçilen dosya yok';
            document.getElementById('file-name').textContent = fileName;
            document.getElementById('file-name-hidden').value = fileName; // Gizli alana dosya adını ekler
        }

        function GonderAl(Sayfa, Icerik) {
            fetch(Sayfa, {
                method: 'POST',
                headers: { 'Content-Type': 'text/plain' },
                body: Icerik
            })
            .then(response => {
                if (response.ok) {
                    var toast = document.getElementById("toast");
                    toast.innerHTML = "Başarılı";
                    toast.className = "show";
                    setTimeout(function() {
                        toast.className = toast.className.replace("show", "");
                    }, 3000);
                }
                else {
                    alert('Beklenmeyen bir durum oluştu A: ' + response.body);
                }
            })
            .catch(error => {
                alert('Beklenmeyen bir durum oluştu B: ' + error.message);
            });
        }

        showPage('devices');
    </script>
</body>
</html>
)rawliteral";
#pragma endregion
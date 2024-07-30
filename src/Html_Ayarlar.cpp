#include "Html_Ayarlar.h"

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
                <select id="program-select" onchange="window.location.href='/Ayarlar_Program_Sec?Secim=' + this.value">
                    <!-- <option value="1" selected>1 : Program 1</option> -->
                    ??? 1 Programlar ??? 
                </select>
            </div>
            <br>
            <form id="program-settings-form" name="Programlar">
                <div>
                    <label style="font-size: large;" for="1Adi">Program Adı:</label>
                    <input value="??? 1 Program Adi ???" style="width: 100%;" type="text" id="1Adi" name="1Adi" maxlength="30" required>
                    <input type="hidden" name="1No" value="??? 1 Program No ???">
                </div>
                <br>
                <div class="form-container">    
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
                                <td><input type="checkbox" name="1Gun_??? 1 Gun No ???" value="E" ??? 1 Onay ???></td>
                                <td>??? 1 Gun ???</td>
                                <td><input type="time" name="1Basla_??? 1 Gun No ???" value="??? 1 Saat ???" required></td>
                                <td><input type="number" name="1Sure_??? 1 Gun No ???" min="0" max="24" value="??? 1 Sure ???" required></td>
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
                            ??? 1 Kullanim ???
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
            <div class="form-container">
                <div>
                    <label for="2adi">Erişim Noktası</label>
                    <input id="2adi" value="??? 2 Adi ???" name="2adi" required maxlength="62">
                </div>
                <div>
                    <label for="2parola">Parola</label>
                    <input type="password" id="2parola" name="2parola" required maxlength="62">
                </div>
            </div>
            <br>
            <div class="button-container">
                <button onclick="GonderAl('/WifiAyarlari', '2adi=' + document.getElementById('2adi').value + '&2parola=' + document.getElementById('2parola').value)">Kaydet</button>
            </div>
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
                        <button onclick="GonderAl('/Kalibrasyon', '3KazanSicakligi=' + document.getElementById('3KazanSicakligi').value + '&3KazanHassasiyeti=' + document.getElementById('3KazanHassasiyeti').value)">Kaydet</button>
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
                        <label for="dfu-file">Yazılım Dosyasını Seç</label>
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
                headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
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
    
        function FormGonder_Programlar(event) {
            event.preventDefault();
            const form = event.target;
            const formData = new FormData(form);

            let formContent = '';
            for (const [key, value] of formData.entries()) {
                formContent += `${key}=${value}&`;
            }

            GonderAl('/Ayarlar_Program_Kaydet', formContent);
        }

        document.addEventListener("DOMContentLoaded", function() {
            const form = document.querySelector('form[name="Programlar"]');
            if (form) {
                form.addEventListener('submit', FormGonder_Programlar);
            }
        });
    </script>
</body>
</html>)rawliteral";
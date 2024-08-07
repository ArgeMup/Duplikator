#include "Html_Ana_Sayfa.h"

const char Html_Ana_Sayfa[] = R"rawliteral(
<!DOCTYPE html>
<html lang="tr">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="refresh" content="15">
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
            height: 50px;
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
    <label style="font-size: xx-large;">??? Uygulama ???</label>
    <br>
    <div class="kaydirici-container" id="kaydiriciContainer">
        <div class="region">Kontrollü</div>
        <div class="region">Kapalı</div>
        <div class="region">Programlı</div>
        <div class="kaydirici" id="kaydirici">Kontrollü</div>
    </div>
    <br>??? Aciklama ???<br><br>
    <table class="info-table">
        <tr>
            <th>Seçili Program</th>
            <th>
                <select onchange="GonderAl('/AnaSayfa_Program_Sec', 'Secim=' + this.value)">
                    <!-- <option value="1" selected>1 : Program 1</option> --> 
                    ??? Programlar ???
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
            <td>??? Kazan ???</td>
        </tr>
        <tr>
            <td>Akım Tüketimi</td>
            <td>??? Akim ???</td>
        </tr>
        <tr>
            <td>Çevre</td>
            <td>??? Cevre ???</td>
        </tr>
    </table>

    <div class="button-container">
        <div id="OnIsitma" style="display:??? OnIsitmayiAtla ???">
            <br>
            <button style="background-color: rgb(237, 113, 52);color: black; padding: 5px;font-weight: bold;" onclick="OnIsitmayiAtla()">Ön Isıtmayı Atla</a>
            <br>
        </div>
        <br>
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
                    value = 2;
                } else if (clickX < 2 * containerWidth / 3) {
                    value = 1;
                } else {
                    value = 0;
                }

                updateKaydiriciPosition(value, true);
            });

            function updateKaydiriciPosition(value, Gonder) {
                switch (value) {
                    case 1:
                        kaydirici.style.left = '133px';
                        kaydirici.style.backgroundColor = '#f44336';
                        kaydirici.textContent = 'Kapalı';
                        break;
                    case 0:
                        kaydirici.style.left = '267px';
                        kaydirici.style.backgroundColor = '#00a000';
                        kaydirici.textContent = 'Programlı';
                        break;
                    case 2:
                        kaydirici.style.left = '0';
                        kaydirici.style.backgroundColor = '#005000';
                        kaydirici.textContent = 'Kontrollü';
                        break;
                }

                if (Gonder) GonderAl("/AnaSayfa_Durum_Sec", "Secim=" + value);
            }

            updateKaydiriciPosition(0/*??? Durum ???*/, false);
        });

        function OnIsitmayiAtla()
        {
            GonderAl("/AnaSayfa_OnIsitmayiAtla", "");

            var OnIsitma = document.getElementById("OnIsitma");
            OnIsitma.style.display = "none";
        }

        function GonderAl(Sayfa, Icerik, retries = 3, delay = 1000) {
            function tryFetch(attempt, errorMessages = []) {
                fetch(Sayfa, {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
                    body: Icerik
                })
                .then(response => {
                    if (response.status === 200) {
                        var toast = document.getElementById("toast");
                        toast.innerHTML = "Başarılı";
                        toast.className = "show";
                        setTimeout(function() {
                            toast.className = toast.className.replace("show", "");
                        }, 3000);
                    } else {
                        response.text().then(function (text) {
                            errorMessages.push(text);
                            if (attempt < retries) {
                                setTimeout(() => tryFetch(attempt + 1, errorMessages), delay);
                            } else {
                                throw new Error(text);
                            }
                        });
                    }
                })
                .catch(error => {
                    errorMessages.push(error.message);
                    if (attempt < retries) {
                        setTimeout(() => tryFetch(attempt + 1, errorMessages), delay);
                    } else {
                        alert('Beklenmeyen bir durum oluştu B:\n' + errorMessages.join('\n'));
                    }
                });
            }

            tryFetch(1);
        }
    </script>
</body>
</html>
)rawliteral";
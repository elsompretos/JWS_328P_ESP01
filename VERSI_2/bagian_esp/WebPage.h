String message;

char setwaktu[] PROGMEM = R"=====(

<!DOCTYPE HTML>
<html>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<head> <title>JWS NodeMCU</title> 
<style>
html { 
font-family: Helvetica; display: inline-block; margin: 0px auto;
}
input[type=text], select {
  width: 100%;
  padding: 8px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
  font-size: 20px; 
}
input[type=time], select {
  width: 100%;
  padding: 8px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
  font-size: 16px; 
}
input[type=date], select {
  width: 100%;
  padding: 8px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
  font-size: 16px; 
}
input[type=number], select {
  width: 100%;
  padding: 8px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
  font-size: 16px; 
}
input[type=submit] {
  width: 100%;
  background-color: #28a745;
  color: white;
  padding: 8px 15px;
  margin: 0px 0;
  border: none;
  border-radius: 4px;
  cursor: pointer;
  font-size: 16px;
}
input[type=submit]:hover {
  background-color: #0077a9;
}
input[type=button] {
  width: 100%;
  background-color: #28a745;
  color: white;
  padding: 8px 15px;
  margin: 0px 0;
  border: none;
  border-radius: 4px;
  cursor: pointer;
  font-size: 16px;
}
.div_isi {
  border-radius: 0px;
  background-color: #f2f2f2;
  padding: 20px;
}
.div_header {
  border-radius: 0px;
  background-color: #0199d9;
  padding: 1px;
  color: white;
}
.font_isi {
  color: #0199d9;
  font-family: Arial, Helvetica, sans-serif;
  font-size: 17px;
}
.font_header {
  color: white;
  font-family: Arial, Helvetica, sans-serif;
  font-size: 20px;
}
a:link, a:visited {
  text-decoration: none;
  font-family: Arial, Helvetica, sans-serif;
  font-size: 20px;
  color: #0199d9;
}
a:hover, a:active {
  text-decoration: none;
  font-family: Arial, Helvetica, sans-serif;
  font-size: 20px;
  color: #0199d9;
}
table, th, td {
  border: 0px solid black;
}
</style>
</head>
<body>
<div style='text-align:center' onclick='func_t4_waktu()'>
    <p style='background-color: #0199d9;padding: 5px;font-size: 22px;color: rgb(255,255,255);'>Waktu</p>
</div>
<div id='t4_waktu' style='display:none'>
<div style='text-align:center'>
  <span >Adjust Hijriyah : </span><span id='adhijrii'></span>
</div>
<table width='100%'>
  <tbody>
    <tr>
      <td >Tanggal</td>
      <td ><form onsubmit='setWaktu()'><input style='text-align:center' min='24-06-2020' name='date' type='date' ></td>
    </tr>
    <tr>
      <td >Jam</td>
      <td ><input style='text-align:center' name='time' type='time' ></td>
    </tr>
    <tr> 
      <td >Hijriyah</td>
      <td ><input style='text-align:center' type='number' name='adjhijr' id='adjhijr' value='1'></td> 
    </tr>
    <tr> 
      <td >Kecerahan</td>
      <td ><input style='text-align:center' type='number' name='adjcerah' id='adjcerah' value='10'></td> 
    </tr>
    <tr> 
      <td >Volume</td>
      <td ><input style='text-align:center' type='number' name='adjvolume' id='adjvolume' value='15'></td> 
    </tr>
    <tr>
    <td style='text-align:center' colspan='2'><input type='submit' value='Kirim'></form></td>
   </tr>
  </tbody>
</table>
</div>
<div style='text-align:center' onclick='t4_koordinat()'>
    <p style='background-color: #0199d9;padding: 5px;font-size: 22px;color: rgb(255,255,255);'>Koordinat</p>
</div>
<div id='t4_koordinat' style='display:none'>
<table width='100%'>
  <tbody>
    <tr>
      <td >Latitude</td>
      <td ><form onsubmit='setKoordinat()'><input style='text-align:center' type='text' name='latitude' id='latitude'></td>
    </tr>
    <tr>
      <td >Longitude</td>
      <td ><input style='text-align:center' type='text' name='longitude' id='longitude'></td>
    </tr>
    <tr>
      <td >TimeZone</td>
      <td ><input style='text-align:center' type='number' name='timezone' id='timezone'></td>
    </tr>
    <tr>
      <td style='text-align:center' colspan='2'><input type='submit' value='Kirim'></form> </td>
    </tr>
  </tbody>
</table>
</div>
<div style='text-align:center' onclick='t4_info()'>
    <p style='background-color: #0199d9;padding: 5px;font-size: 22px;color: rgb(255,255,255);'>Info</p>
</div>
<div id='t4_info' style='display:none'>
<table width='100%'>
  <tbody>
    <tr>
      <td >Masjid</td>
      <td ><form onsubmit='setNamamasjid()'><input style='text-align:center' type='text' name='namamasjid' id='namamasjid' value='Masjid Akbar Maulana'></td>
    </tr>
    <tr>
      <td style='text-align:center' colspan='2'><input type='submit' value='Kirim'></form></td>
    </tr>
    <tr>
      <td >Info</td>
      <td ><form onsubmit='setNamamasjid()'><input style='text-align:center' type='text' name='info1' id='info1' value='Sudahkah Anda Sholat'></td>
    </tr>
    <tr>
      <td style='text-align:center' colspan='2'><input type='submit' value='Kirim'></form></td>
    </tr>
  </tbody>
</table>
</div>
<div style='text-align:center' onclick='t4_adzan()'>
    <p style='background-color: #0199d9;padding: 5px;font-size: 22px;color: rgb(255,255,255);'>Adzan & Iqomah</p>
</div>
<div id='t4_adzan' style='display:none'>
<table width='100%'>
  <tbody>
    <tr>
      <td >Adzan</td>
      <td ><form onsubmit='setIqomah()'><input style='text-align:center' type='number' name='lamaadzan' id='lamaadzan' value='4'></td>
      <td ></td>
      <td ></td>
    </tr>
    <tr>
      <td >Subuh</td>
      <td ><input style='text-align:center' type='number' name='iqomahsubuh' id='iqomahsubuh' value='1'></td>
      <td >Dzuhur</td>
      <td ><input style='text-align:center' type='number' name='iqomahdzuhur' id='iqomahdzuhur' value='1'></td>
    </tr>
    <tr>
      <td >Ashar</td>
      <td ><input style='text-align:center' type='number' name='iqomahashar' id='iqomahashar' value='1'></td>
      <td >Maghrib</td>
      <td ><input style='text-align:center' type='number' name='iqomahmaghrib' id='iqomahmaghrib' value='1'></td>
    </tr>
    <tr>
      <td >Isya</td>
      <td ><input style='text-align:center' type='number' name='iqomahisya' id='iqomahisya' value='1'></td>
      <td ></td>
      <td ></td>
    </tr>
    <tr>
      <td style='text-align:center' colspan='4'><input type='submit' value='Kirim'></form></td>
    </tr>
    
  </tbody>
</table>
</div>
<div style='text-align:center' onclick='t4_koreksi()'>
    <p style='background-color: #0199d9;padding: 5px;font-size: 22px;color: rgb(255,255,255);'>Koreksi Waktu</p>
</div>
<div id='t4_koreksi' style='display:none'>
<table width='100%'>
  <tbody>
    <tr>
      <td >Imsak</td>
      <td ><form onsubmit='setKoreksi()'><input style='text-align:center' type='number' name='korimsak' id='korimsak' value='2'></td>
      <td >Subuh</td>
      <td ><input style='text-align:center' type='number' name='korsubuh' id='korsubuh' value='2'></td>
    </tr>
    <tr>
      <td >Terbit</td>
      <td ><input style='text-align:center' type='number' name='korterbit' id='korterbit' value='2'></td>
      <td >Dhuha</td>
      <td ><input style='text-align:center' type='number' name='kordhuha' id='kordhuha' value='2'></td>
    </tr>
    <tr>
      <td >Dzuhur</td>
      <td ><input style='text-align:center' type='number' name='kordzuhur' id='kordzuhur' value='2'></td>
      <td >Ashar</td>
      <td ><input style='text-align:center' type='number' name='korashar' id='korashar' value='2'></td>
    </tr>
    <tr>
      <td >Maghrib</td>
      <td ><input style='text-align:center' type='number' name='kormaghrib' id='kormaghrib' value='2'></td>
      <td >Isya</td>
      <td ><input style='text-align:center' type='number' name='korisya' id='korisya' value='2'></td>
    </tr>
    <tr>
      <td style='text-align:center' colspan='4'><input type='submit' value='Kirim'></form></td>
    </tr>
    
  </tbody>
</table>
</div>
</body>
</html>

<script>

var xmlHttp=createXmlHttpObject();

function createXmlHttpObject(){
 if(window.XMLHttpRequest){
    xmlHttp=new XMLHttpRequest();
 }else{
    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');// code for IE6, IE5
 }
 return xmlHttp;
}
function process(){
 if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
   xmlHttp.open('PUT','xmlwaktu',true);
   xmlHttp.onreadystatechange=handleServerResponse;
   xmlHttp.send(null);
 }
}
function handleServerResponse(){
 if(xmlHttp.readyState==4 && xmlHttp.status==200){
   xmlResponse=xmlHttp.responseXML;
   
   xmldoc = xmlResponse.getElementsByTagName('Hijriyah');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('adhijrii').innerHTML=message;
   document.getElementById('adjhijr').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Kecerahan');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('adjcerah').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Volume');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('adjvolume').value=message
 }
}
function proseskoordinat(){
 if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
   xmlHttp.open('PUT','xmlkoordinat',true);
   xmlHttp.onreadystatechange=handleKoordinat;
   xmlHttp.send(null);
 }
}
function handleKoordinat(){
 if(xmlHttp.readyState==4 && xmlHttp.status==200){
   xmlResponse=xmlHttp.responseXML;
   
   xmldoc = xmlResponse.getElementsByTagName('Latitude');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('latitude').value=message;
   xmldoc = xmlResponse.getElementsByTagName('Longitude');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('longitude').value=message;
   xmldoc = xmlResponse.getElementsByTagName('Timezone');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('timezone').value=message;
   
 }
}
function prosesinfomasjid(){
 if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
   xmlHttp.open('PUT','xmlinfomasjid',true);
   xmlHttp.onreadystatechange=handleInfoMasjid;
   xmlHttp.send(null);
 }
}
function handleInfoMasjid(){
 if(xmlHttp.readyState==4 && xmlHttp.status==200){
   xmlResponse=xmlHttp.responseXML;
   
   xmldoc = xmlResponse.getElementsByTagName('NamaMasjid');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('namamasjid').value=message;
   xmldoc = xmlResponse.getElementsByTagName('InfoSatu');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('info1').value=message;
   xmldoc = xmlResponse.getElementsByTagName('InfoDua');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('info2').value=message;
   xmldoc = xmlResponse.getElementsByTagName('InfoTiga');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('info3').value=message;
   
 }
}
function prosesKoreksi(){
 if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
   xmlHttp.open('PUT','xmlkoreksi',true);
   xmlHttp.onreadystatechange=handleKoreksi;
   xmlHttp.send(null);
 }
}
function handleKoreksi(){
 if(xmlHttp.readyState==4 && xmlHttp.status==200){
   xmlResponse=xmlHttp.responseXML;
   
   xmldoc = xmlResponse.getElementsByTagName('KorImsak');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('korimsak').value=message;
   xmldoc = xmlResponse.getElementsByTagName('KorSubuh');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('korsubuh').value=message;
   xmldoc = xmlResponse.getElementsByTagName('KorTerbit');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('korterbit').value=message;
   xmldoc = xmlResponse.getElementsByTagName('KorDhuha');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('kordhuha').value=message;
   xmldoc = xmlResponse.getElementsByTagName('KorDzuhur');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('kordzuhur').value=message;
   xmldoc = xmlResponse.getElementsByTagName('KorAshar');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('korashar').value=message;
   xmldoc = xmlResponse.getElementsByTagName('KorMaghrib');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('kormaghrib').value=message;
   xmldoc = xmlResponse.getElementsByTagName('KorIsya');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('korisya').value=message;
   
 }
}
function prosesIqomah(){
 if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
   xmlHttp.open('PUT','xmliqomah',true);
   xmlHttp.onreadystatechange=handleIqomah;
   xmlHttp.send(null);
 }
}
function handleIqomah(){
 if(xmlHttp.readyState==4 && xmlHttp.status==200){
   xmlResponse=xmlHttp.responseXML;
   
   xmldoc = xmlResponse.getElementsByTagName('LamZan');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('lamaadzan').value=message;
//   xmldoc = xmlResponse.getElementsByTagName('LamSak');
//   message = xmldoc[0].firstChild.nodeValue;
//   document.getElementById('lamaimsak').value=message;
   xmldoc = xmlResponse.getElementsByTagName('ISub');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('iqomahsubuh').value=message;
   xmldoc = xmlResponse.getElementsByTagName('IDzu');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('iqomahdzuhur').value=message;
   xmldoc = xmlResponse.getElementsByTagName('IAshr');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('iqomahashar').value=message;
   xmldoc = xmlResponse.getElementsByTagName('IMgr');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('iqomahmaghrib').value=message;
   xmldoc = xmlResponse.getElementsByTagName('IIsy');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('iqomahisya').value=message;
   
 }
}
function func_t4_waktu() {
  process();
  var x = document.getElementById('t4_waktu');
  var y = document.getElementById('t4_adzan');
  var z = document.getElementById('t4_koordinat');
  var h = document.getElementById('t4_info');
  var t = document.getElementById('t4_koreksi');
  if (x.style.display === 'none') {
    x.style.display = 'block';
    y.style.display = 'none';
    z.style.display = 'none';
    h.style.display = 'none';
    t.style.display = 'none';
  } else {
    x.style.display = 'none';
  }
}
function t4_adzan() {
  prosesIqomah();
  var x = document.getElementById('t4_adzan');
  var y = document.getElementById('t4_waktu');
  var z = document.getElementById('t4_koordinat');
  var h = document.getElementById('t4_info');
  var t = document.getElementById('t4_koreksi');
  if (x.style.display === 'none') {
    x.style.display = 'block';
    y.style.display = 'none';
    z.style.display = 'none';
    h.style.display = 'none';
    t.style.display = 'none';
  } else {
    x.style.display = 'none';
  }
}
function t4_koordinat() {
  proseskoordinat();
  var y = document.getElementById('t4_waktu');
  var x = document.getElementById('t4_adzan');
  var z = document.getElementById('t4_koordinat');
  var h = document.getElementById('t4_info');
  var t = document.getElementById('t4_koreksi');
  if (z.style.display === 'none') {
    z.style.display = 'block';
    x.style.display = 'none';
    y.style.display = 'none';
    h.style.display = 'none';
    t.style.display = 'none';
  } else {
    z.style.display = 'none';
  }
}
function t4_info() {
  prosesinfomasjid();
  var y = document.getElementById('t4_waktu');
  var x = document.getElementById('t4_adzan');
  var z = document.getElementById('t4_koordinat');
  var h = document.getElementById('t4_info');
  var t = document.getElementById('t4_koreksi');
  if (h.style.display === 'none') {
    h.style.display = 'block';
    x.style.display = 'none';
    y.style.display = 'none';
    z.style.display = 'none';
    t.style.display = 'none';
  } else {
    h.style.display = 'none';
  }
}
function t4_koreksi() {
  prosesKoreksi();
  var y = document.getElementById('t4_waktu');
  var x = document.getElementById('t4_adzan');
  var z = document.getElementById('t4_koordinat');
  var h = document.getElementById('t4_info');
  var t = document.getElementById('t4_koreksi');
  if (t.style.display === 'none') {
    t.style.display = 'block';
    x.style.display = 'none';
    y.style.display = 'none';
    z.style.display = 'none';
    h.style.display = 'none';
  } else {
    t.style.display = 'none';
  }
}

function setInfo() {
  var namamasjid = document.getElementById('namamasjid').value;
  var info1 = document.getElementById('info1').value;
  var info2 = document.getElementById('info2').value;
  var info3 = document.getElementById('info3').value;
  var datainfo = {namamasjid:namamasjid, info1:info1, info2:info2, info3:info3};
  var xhr = new XMLHttpRequest();
  var url = '/simpaninfo';
  xhr.onreadystatechange = function() {
    if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
    }
  };
  xhr.open('POST', url, true);
  xhr.send(JSON.stringify(datainfo));
};
function setWaktu() {

 
  
  var adjhijr = document.getElementById('adjhijr').value;
  var adjcerah = document.getElementById('adjcerah').value;
  var adjvolume = document.getElementById('adjvolume').value;

  var datainfoWaktu = {adjhijr:adjhijr, adjcerah:adjcerah, adjvolume:adjvolume};
  
  var xhr = new XMLHttpRequest();
  var url = '/simpanWaktu';
  xhr.onreadystatechange = function() {
    if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
    }
  };
  xhr.open('POST', url, true);
  xhr.send(JSON.stringify(datainfoWaktu));
   
  alert("Data Waktu, Kecerahan Dan Volume Berhasil Diubah");
};
function setKoordinat() {

  var latitude = document.getElementById('latitude').value;
  var longitude = document.getElementById('longitude').value;
  var zonawaktu = document.getElementById('timezone').value;

  var datainfoKoordinat = {latitude:latitude, longitude:longitude, zonawaktu:zonawaktu};
  
  var xhr = new XMLHttpRequest();
  var url = '/simpanKoordinat';
  xhr.onreadystatechange = function() {
    if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
    }
  };
  xhr.open('POST', url, true);
  xhr.send(JSON.stringify(datainfoKoordinat));
   
  alert("Data Lokasi Berhasil Diubah");
};
function setNamamasjid() {

  var namamasjid = document.getElementById('namamasjid').value;
  var info1 = document.getElementById('info1').value;

  var dataNamaMasjid = {namamasjid:namamasjid, info1:info1};
  
  var xhr = new XMLHttpRequest();
  var url = '/simpanNamamasjid';
  xhr.onreadystatechange = function() {
    if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
    }
  };
  xhr.open('POST', url, true);
  xhr.send(JSON.stringify(dataNamaMasjid));
   
  alert("Data Nama Masjid dan Informasi Berhasil Diubah");
};
function setIqomah() {

  var lamaadzan = document.getElementById('lamaadzan').value;
  var lamaimsak = "0";
  var iqomahsubuh = document.getElementById('iqomahsubuh').value;
  var iqomahdzuhur = document.getElementById('iqomahdzuhur').value;
  var iqomahashar = document.getElementById('iqomahashar').value;
  var iqomahmaghrib = document.getElementById('iqomahmaghrib').value;
  var iqomahisya = document.getElementById('iqomahisya').value;

  var dataIqomah = {lamaadzan:lamaadzan, lamaimsak:lamaimsak, iqomahsubuh:iqomahsubuh, iqomahdzuhur:iqomahdzuhur, iqomahashar:iqomahashar, iqomahmaghrib:iqomahmaghrib, iqomahisya:iqomahisya};
  
  var xhr = new XMLHttpRequest();
  var url = '/simpanIqomah';
  xhr.onreadystatechange = function() {
    if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
    }
  };
  xhr.open('POST', url, true);
  xhr.send(JSON.stringify(dataIqomah));
   
  alert("Data Adzan dan Iqomah Berhasil Diubah");
};
function setKoreksi() {

  var korimsak = document.getElementById('korimsak').value;
  var korsubuh = document.getElementById('korsubuh').value;
  var korterbit = document.getElementById('korterbit').value;
  var kordhuha = document.getElementById('kordhuha').value;
  var kordzuhur = document.getElementById('kordzuhur').value;
  var korashar = document.getElementById('korashar').value;
  var kormaghrib = document.getElementById('kormaghrib').value;
  var korisya = document.getElementById('korisya').value;

  var dataKoreksi = {korimsak:korimsak, korsubuh:korsubuh, korterbit:korterbit, kordhuha:kordhuha, kordzuhur:kordzuhur, korashar:korashar, kormaghrib:kormaghrib, korisya:korisya};
  
  var xhr = new XMLHttpRequest();
  var url = '/simpanKoreksi';
  xhr.onreadystatechange = function() {
    if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
    }
  };
  xhr.open('POST', url, true);
  xhr.send(JSON.stringify(dataKoreksi));
   
  alert("Data Koreksi Waktu Berhasil Diubah");
};


</script>
</html>

)=====";

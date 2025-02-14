/*
Perbaikan Tanggal 30 Juni 2020
Menggunakan Librray EEPROM bawaan Arduino IDE

0 Latitude : -6.21
5 Longitude : 106.85
10 Timezone : 7.00

15 adj_subuh : 2
17 adj_dzuhur : 2
19 adj_ashar : 2
21 adj_maghrib : 2
23 adj_isya : 2
25 adj_imsak : 0
27 adj_terbit : 0
29 adj_dhuha : 2

32 tpl_subuh : 1
34 tpl_dzuhur : 1
36 tpl_ashar : 1
38 tpl_maghrib : 1
40 tpl_isya : 1
42 tpl_imsak : 1
44 tpl_terbit : 1
46 tpl_dhuha : 1

49 iqm_subuh : 2
51 iqm_dzuhur : 2
53 iqm_ashar : 2
55 iqm_maghrib : 2
57 iqm_isya : 2
59 lama_adzan : 4

61 lama_imsak : 5

63 sesuaikan_tgl_hijriyah : 1
65 sesuaikan_bright : 10
67 sesuaikan_volume : 20

69 Nama Masjid  : Masjid Raya Akbar Maulana - Ampera Raya
119 Informasi 1 : Jadikan Sabar dan Sholat Sebagai Penolongmu
169 Informasi 2 : Sedekah Melancarkan Rezekimu
219 Informasi 3 : Subhanallah Walhamdulillah Laailahaillalhah
269 Informasi 4 : Selamat Hari Raya Idul Fitri 1 Syawal 1441 H

*/
 
#include <DMD3asis.h>
#include <Wire.h>
#include "RTClib.h"
#include "SholahTimeCalulation.h"
#include "tangal_hijriyah.h"

#include <DFPlayer_Mini_Mp3.h>
#include <EEPROM.h>

DMD3 display(1,1);

#include <SystemFont5x7.h>
#include <angka6x13.h>
#include <Font5x7.h>
#include <font/Font4x6.h>

RTC_DS3231 rtc;

unsigned long p_e_0_names=0, p_e_1_jam=0, p_e_2_hjry=0, p_e_4_jmsk=0, p_e_3_wksol=0, p_e_5_iqomah=0, p_e_6_lurus=0;
byte evt_0 = 0, evt_1 = 0, evt_2 = 1, evt_3 = 1, evt_4 = 1, evt_5 = 1, evt_6 = 1;
int iqm_ee, sis_wkt_iqo, du_iq, iqm_menit, iqm_menit_sisa, iqm_detik;

int b_a[8];
int b_t[8];
// String bnm_mesjid;
  
int Tahun;
byte Bulan, Tanggal, Jam, Menit, Detik, hariIni;

int mode = 1;

int ash, bsh;

String txhh, txmm, txss, tx_hh_mm, tx_hh_mm_ss, namaHarimasehi ;
String waktu_tbt, waktu_dhu, waktu_sbh, waktu_dzr, waktu_ims, waktu_asr, waktu_mgr, waktu_isy; //, jss;
String wkt_iqomah, tpl_iqo_ss, namaMasukWkt, textIqohitmun, wkt_ims_sat;

int b_bright, b_volume;

int dur_tpl_tx_sol;
String slt_sek;
String cck;
int  j_s_s = 0;
String tx_ser;
byte wkt_msk_skrg;

const char namaBulanMasehi[12][12] PROGMEM = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
const char namaHariMasehi[7][7] PROGMEM = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
const char namaWaktuSholat[8][12] PROGMEM = {"IMSAK ", " SUBUH ", " TERBIT ", " DHUHA ", " DZUHUR ", " ASHAR ", " MAGHRIB ", " ISYA "};
const char pesan[][60] PROGMEM = {"Matikan HP - Luruskan Shaf - Matikan HP - Luruskan Shaf"};

void scan(){
  display.refresh();
}
void setup(){

  Serial.begin (9600);
  mp3_set_serial (Serial); 
  
  EEPROM.get(67, b_volume); 
  mp3_set_volume (b_volume);

  DDRD |= (1<<DDD2) ;//pin 2 is in output mode

 for (int dd = 0; dd < 6; dd++){
    if (dd % 2 == 0){
      //digitalWrite(buzzer,HIGH);
      PORTD |=(1<< PORTD2);
    }
    else 
    {
      //digitalWrite(buzzer,LOW);
      PORTD &= ~(1<<PORTD2);
    }
    delay(250);
 }

  EEPROM.get(65, b_bright); // Baca EEPROM kecerahan
  
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan);
  Timer1.pwm(9,b_bright);
  display.setDoubleBuffer(1);
  // Wire.begin();
  rtc.begin();
  display.clear();

   // rtc.adjust(DateTime(2019, 11, 11, 17, 49, 50)); 
   // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}
void loop(){
switch (mode) {
    case 0: 
      // evt_0 = 0; evt_1 = 1; evt_2 = 1; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      // TPL_NM();
      evt_0 = 1; evt_1 = 1; evt_2 = 0; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      TPL_HH_TGL(3);
    break;
    case 1: 
      evt_0 = 1; evt_1 = 0; evt_2 = 1; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      TPL_HH();
    break;
    case 2: 
      evt_0 = 1; evt_1 = 1; evt_2 = 0; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      TPL_HH_TGL(1);
    break;
    case 3: 
      evt_0 = 1; evt_1 = 0; evt_2 = 1; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      TPL_HH();
    break;
    case 4: 
      evt_0 = 1; evt_1 = 1; evt_2 = 0; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      TPL_HH_TGL(5);
    break;
    case 5: 
      evt_0 = 1; evt_1 = 1; evt_2 = 1; evt_3 = 1; evt_4 = 0; evt_5 = 1; evt_6 = 1;
      TPL_HH_WKT_MSK();
    break;
    case 6: 
      evt_0 = 1; evt_1 = 1; evt_2 = 1; evt_3 = 1; evt_4 = 1; evt_5 = 0; evt_6 = 1;
      TPL_QD_IQM();  
    break;
    case 7: 
      evt_0 = 1; evt_1 = 1; evt_2 = 0; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      TPL_HH_TGL(4); 
    break;
    case 8: 
      evt_0 = 1; evt_1 = 0; evt_2 = 1; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      TPL_HH();
    break;
    case 9: 
      evt_0 = 1; evt_1 = 1; evt_2 = 0; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      TPL_HH_TGL(2);
    break;
    case 10: 
      evt_0 = 1; evt_1 = 1; evt_2 = 0; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      TPL_HH_TGL(6);
    break;

    }

    while (Serial.available() > 0 ) {

    tx_ser  = Serial.readStringUntil('\r\n');
    //tx_ser  = Serial.readString();
    
    }
    
    if (tx_ser.length() > 0){
        // Setting Jam === SJ=12-11-20-01-07-2020-01-15-20 4 digit terakhir (10-15) = brightness-volume
        if(tx_ser.substring(0,2) == "SJ"){
          Serial.println(tx_ser);

          String bnm_mesjid = readString(69);

          rtc.adjust(DateTime(tx_ser.substring(18,22).toInt(), tx_ser.substring(15,17).toInt(), tx_ser.substring(12,14).toInt(), tx_ser.substring(3,5).toInt(), tx_ser.substring(6,8).toInt(), tx_ser.substring(9,11).toInt())); 
          EEPROM.put(63, tx_ser.substring(23,25).toInt()); // Adj Hijriyah
          EEPROM.put(65, tx_ser.substring(26,28).toInt()); // Adj Kecerahan
          EEPROM.put(67, tx_ser.substring(29,31).toInt()); // Adj Volume

          writeString(69, bnm_mesjid);

          
          
          CERAH_VOLUME();
          
          BUZZ();
       }

       // Setting lama Iqomah === IQ=02-02-02-02-02-04 === IQ=03-03-03-03-03-05
       else if(tx_ser.substring(0,2) == "IQ"){ 
          Serial.println(tx_ser);

          byte blama_imsak;

          EEPROM.get(61, blama_imsak);
          
          EEPROM.put(49, tx_ser.substring(3,5).toInt());
          EEPROM.put(51, tx_ser.substring(6,8).toInt());
          EEPROM.put(53, tx_ser.substring(9,11).toInt());
          EEPROM.put(55, tx_ser.substring(12,14).toInt());
          EEPROM.put(57, tx_ser.substring(15,17).toInt());
          EEPROM.put(59, tx_ser.substring(18,20).toInt());

          EEPROM.put(61, blama_imsak);
   
          // for(int pp = 2; pp < 15; pp=pp+2){
          //    EEPROM.writeInt(66+pp, tx_ser.substring(pp,pp+2).toInt());
          // }
          
        BUZZ();
         
       }
       
       // Setting Koreksi waktu sholat === KR=02-02-02-02-02-02-00-00 == 02-00-02 imsak dan dhuha
       else if(tx_ser.substring(0,2) == "KR"){
         Serial.println(tx_ser);

         byte btpl_subuh;

         EEPROM.get(32, btpl_subuh);
         
         EEPROM.put(15, tx_ser.substring(3,5).toInt());
         EEPROM.put(17, tx_ser.substring(6,8).toInt());
         EEPROM.put(19, tx_ser.substring(9,11).toInt());
         EEPROM.put(21, tx_ser.substring(12,14).toInt());
         EEPROM.put(23, tx_ser.substring(15,17).toInt());
         EEPROM.put(25, tx_ser.substring(18,20).toInt());
         EEPROM.put(27, tx_ser.substring(21,23).toInt());
         EEPROM.put(29, tx_ser.substring(24,26).toInt());

         EEPROM.put(32, btpl_subuh);

         
          
         BUZZ();
       }

       // Setting Tampil waktu sholat === TP=01-01-01-01-01-01-01-01
       else if(tx_ser.substring(0,2) == "TP"){
         Serial.println(tx_ser);

         byte biqo_subuh;

         EEPROM.get(49, biqo_subuh);

         EEPROM.put(32, tx_ser.substring(6,8).toInt());
         EEPROM.put(34, tx_ser.substring(15,17).toInt());
         EEPROM.put(36, tx_ser.substring(18,20).toInt());
         EEPROM.put(38, tx_ser.substring(21,23).toInt());
         EEPROM.put(40, tx_ser.substring(24,26).toInt());
         EEPROM.put(42, tx_ser.substring(3,5).toInt());
         EEPROM.put(44, tx_ser.substring(9,11).toInt());
         EEPROM.put(46, tx_ser.substring(12,14).toInt());
         
         EEPROM.put(49, biqo_subuh);
          
         BUZZ();
       }

       // Setting Nama masjid === NM=Masjid Raya Akbar Maulana - Ampera Raya
       else if(tx_ser.substring(0,2) == "NM"){
         Serial.println(tx_ser);
         
         String isi_namamasjid = tx_ser.substring(3,tx_ser.length());
         writeString(69, isi_namamasjid);
          
         BUZZ();
       }
       
       // Setting Info === IN=Sudahkan Anda Sholat ??
       else if(tx_ser.substring(0,2) == "IN"){
         Serial.println(tx_ser);

         String isi_info = tx_ser.substring(3,tx_ser.length());
         writeString(119, isi_info);
         
         BUZZ();
       }
       
       // Setting Lokasi === LL=-6.287617|106.821189|7 === LL=-3.3186|114.5944|8
       else if(tx_ser.substring(0,2) == "LL"){
         Serial.println(tx_ser);
        
         for (int i = 0; i < tx_ser.length(); i++) {
            if (tx_ser.substring(i, i+1) == "|") {

              EEPROM.put(0, (tx_ser.substring(3, i)).toDouble());
              EEPROM.put(5, (tx_ser.substring(i+1, tx_ser.length()-3)).toDouble());
              EEPROM.put(10, (tx_ser.substring(tx_ser.length()-2, tx_ser.length())).toDouble());
              
              break;
            } 
          }

         BUZZ();
       }
              
        tx_ser = ""; 
      } // akhir serial lenght

       
}
void BUZZ(){
  PORTD |=(1<< PORTD2);
  delay(200);
  PORTD &= ~(1<<PORTD2);
}
String Konversi(int sInput) {
  if (sInput < 10)
  { return"0" + String(sInput); }
  else
  { return String(sInput); }
}
void WAKTU(){                         // AMBIL WAKTU
  DateTime now = rtc.now(); 
  Tahun = now.year();
  Bulan = now.month();
  Tanggal = now.day();
  Jam = now.hour();
  Menit = now.minute();
  Detik = now.second();
  hariIni = now.dayOfTheWeek();

  txhh = Konversi(Jam);
  txmm = Konversi(Menit);
  txss = Konversi(Detik);
     
  if(Detik % 2 == 0){
    tx_hh_mm = txhh + ":" + txmm;
  } 
  else
  {
    tx_hh_mm = txhh + " " + txmm;
  }
 
   cck = txhh + ":" + txmm; 
}
void TPL_HH (){                       // MENAMPILKAN JAM BESAR
  
  WAKTU();
  j_s_s = 0;

if ( !evt_1 && (millis()-p_e_1_jam) > 50) {
      p_e_1_jam = millis();
      
   if(ash < 240){ // if(ash < 240){ 
    ash++;
   
    display.clear();
    display.setFont(angka6x13);
    
    if(ash<17){
      display.drawText(1, ash-16, txhh);
      display.drawText(18, ash-16, txmm); 
    }
    else if (ash>16 && ash<223)
    {
      display.drawText(1, 0, txhh);
      display.drawText(18, 0, txmm); 
     
    }
     else if(ash>222) //else if(ash>142)
    {
      display.drawText(1, (-1*(-222+ash)), txhh);
      display.drawText(18, (-1*(-222+ash)), txmm); 
    }
    
    
    display.setFont(Font5x7);

  
   if(Detik % 2 == 0)
                {
                  // display.drawChar(14, 4, ':');
                  display.drawFilledRect(15, 4, 16, 5, 1);
                  display.drawFilledRect(15, 10, 16, 11, 1);
                }
                else
                {
                  //display.drawChar(14, 4, ' ');
                  display.drawFilledRect(15, 4, 16, 5, 0);
                  display.drawFilledRect(15, 10, 16, 11, 0);
                }
          display.swapBuffers();
          AMBIL_WAKTU_SHOLAT(); 
  if(ash % 20 == 0)
      {
          Serial.print(txhh); Serial.print(":"); Serial.print(txmm);Serial.print(":"); Serial.println(txss);
      }  
      }
   else
      {
        if(mode == 1)
        { mode = 0;} // NAMA MASJID
        else if(mode == 3) 
        { mode = 2; } // TANGGAL HIJRIYAH
        else if(mode == 8) 
        { mode = 4; } // WAKTU SHOLAT
       ash=0;
       Serial.println();
      }
 }
}
void TPL_HH_TGL(int pilih){           // MENAMPILKAN TANGGAL HIJRIYAH
  j_s_s = 0;
  WAKTU();
  AMBIL_WAKTU_SHOLAT();
  
  String str_tanggal_hijriyah;
  

       if(pilih == 1){ // ============= TANGGAL HIJRIYAH
    int b_ses_hijriyah;
    
    EEPROM.get(63, b_ses_hijriyah); 
    str_tanggal_hijriyah = Kuwaiti_algorithm(Tanggal, Bulan, Tahun, hariIni, b_ses_hijriyah);
     
  }
  else if(pilih == 2){ // ============= TANGGAL MASEHI
    // Hari Masehi
    char DayName[7];
    memset(DayName, 0, 7);
    strcpy_P(DayName, namaHariMasehi[hariIni]);

    // Bulan Masehi
    char BulanName[12];
    memset(BulanName, 0, 12);
    strcpy_P(BulanName, namaBulanMasehi[Bulan-1]);
    
    str_tanggal_hijriyah =  String(DayName) + ", " + String(Tanggal) + " " + String(BulanName) + " " + String(Tahun); 
  }
  else if(pilih == 3){ // ============= NAMA MASJID
    str_tanggal_hijriyah = readString(69);
  }
  else if(pilih == 4){ // ============= LURUSKAN

    char isiPesan[60];
    memset(isiPesan, 0, 60);
    strcpy_P(isiPesan, pesan[0]);

    str_tanggal_hijriyah = isiPesan;
  }
  else if(pilih == 5){ // ============= JWS

    // Imsak 04:32 Subuh 04:42 Terbit 06:05 Dhuha 06:27 Dzuhur 11:58 Ashar 15:20 Maghrib 17:51 Isya 19:06
    // Imsak 04:32 Terbit 06:03 Dhuha 06:25 Dzuhur 11:58 Ashar 15:20 Maghrib 17:51 Isya 19:06
    
    EEPROM.get(42, b_t[0]); //imsak
    EEPROM.get(32, b_t[1]); //subuh
    EEPROM.get(44, b_t[2]); //terbit
    EEPROM.get(46, b_t[3]); //dhuha
    EEPROM.get(34, b_t[4]); //dzuhur
    EEPROM.get(36, b_t[5]); //ashar
    EEPROM.get(38, b_t[6]); //maghrib
    EEPROM.get(40, b_t[7]); //isya

    str_tanggal_hijriyah = "";

    if(b_t[0] == 1){ 
      char nama_waktu[8];
      memset(nama_waktu, 0, 8);
      strcpy_P(nama_waktu, namaWaktuSholat[0]);
      
      str_tanggal_hijriyah = str_tanggal_hijriyah + nama_waktu + waktu_ims; 
     } 
      else 
     {  str_tanggal_hijriyah = str_tanggal_hijriyah;  }
     
    if(b_t[1] == 1){ 
      char nama_waktu[8];
      memset(nama_waktu, 0, 8);
      strcpy_P(nama_waktu, namaWaktuSholat[1]);
      
      str_tanggal_hijriyah = str_tanggal_hijriyah + nama_waktu + waktu_sbh; 
      } 
      else 
      {  str_tanggal_hijriyah = str_tanggal_hijriyah;  }
      
    if(b_t[2] == 1){ 
      char nama_waktu[8];
      memset(nama_waktu, 0, 8);
      strcpy_P(nama_waktu, namaWaktuSholat[2]);
      
      str_tanggal_hijriyah = str_tanggal_hijriyah + nama_waktu + waktu_tbt; 
      } 
      else 
      {  str_tanggal_hijriyah = str_tanggal_hijriyah;  }

    if(b_t[3] == 1){ 
      char nama_waktu[8];
      memset(nama_waktu, 0, 8);
      strcpy_P(nama_waktu, namaWaktuSholat[3]);
      
      str_tanggal_hijriyah = str_tanggal_hijriyah + nama_waktu + waktu_dhu;
    } 
    else 
    {  str_tanggal_hijriyah = str_tanggal_hijriyah;  }
    
    if(b_t[4] == 1){ 
      char nama_waktu[8];
      memset(nama_waktu, 0, 8);
      strcpy_P(nama_waktu, namaWaktuSholat[4]);

      str_tanggal_hijriyah = str_tanggal_hijriyah + nama_waktu + waktu_dzr; 
    } 
    else 
    {  str_tanggal_hijriyah = str_tanggal_hijriyah;  }
    
    if(b_t[5] == 1){ 
      char nama_waktu[8];
      memset(nama_waktu, 0, 8);
      strcpy_P(nama_waktu, namaWaktuSholat[5]);
      
      str_tanggal_hijriyah = str_tanggal_hijriyah + nama_waktu + waktu_asr; 
    } else { str_tanggal_hijriyah = str_tanggal_hijriyah; }

    if(b_t[6] == 1){ 
      char nama_waktu[8];
      memset(nama_waktu, 0, 8);
      strcpy_P(nama_waktu, namaWaktuSholat[6]);
      
      str_tanggal_hijriyah = str_tanggal_hijriyah + nama_waktu + waktu_mgr; 
     } else { str_tanggal_hijriyah = str_tanggal_hijriyah; }
     
    if(b_t[7] == 1){ 
      char nama_waktu[8];
      memset(nama_waktu, 0, 8);
      strcpy_P(nama_waktu, namaWaktuSholat[7]);
      
      str_tanggal_hijriyah = str_tanggal_hijriyah + nama_waktu + waktu_isy; 
    } else { str_tanggal_hijriyah = str_tanggal_hijriyah; }
    
    
    //str_tanggal_hijriyah = "Imsak " + waktu_ims + " Subuh " + waktu_sbh + " Dzuhur " + waktu_dzr + " Ashar " + waktu_asr + " Maghrib " + waktu_mgr + " Isya " + waktu_isy;    
    //str_tanggal_hijriyah = "IMSAK " + waktu_ims + "SUBUH " + waktu_sbh + "TERBIT " + waktu_tbt + " DHUHA " + waktu_dhu + "DZUHUR " + waktu_dzr + "ASHAR " + waktu_asr + "MAGHRIB " + waktu_mgr + "ISYA " + waktu_isy;    
  
  }
  else if(pilih == 6){ // ============= INFO 1
    str_tanggal_hijriyah = readString(119); 
  }
  
  
     
  if ( !evt_2 && (millis()-p_e_2_hjry) > 75) {
    
    p_e_2_hjry = millis();
    display.setFont(System5x7);
    if(bsh >(-1*(display.width()+display.textWidth(str_tanggal_hijriyah)))){
      display.clear();

      // MASUK JAM DARI ATAS //
      if(bsh>-8){ // -1,-2,-3...-7
        display.drawText((display.width()-display.textWidth(tx_hh_mm))/2, (-8+(-1*bsh)), tx_hh_mm);
      }
      else if(bsh < (-1*(display.width()+display.textWidth(str_tanggal_hijriyah))) + 8){
        display.drawText((display.width()-display.textWidth(tx_hh_mm))/2, ((-1*((-1*(display.width()+display.textWidth(str_tanggal_hijriyah))) + 8)) + bsh ), tx_hh_mm);
      }
      else if ((bsh < -7) && (bsh > (-1*(display.width()+display.textWidth(str_tanggal_hijriyah))) + 7))
      { 
        display.drawText((display.width()-display.textWidth(tx_hh_mm))/2,0,tx_hh_mm);
      }

      display.drawText((bsh+32),8,str_tanggal_hijriyah);   
      display.swapBuffers();
       bsh--;
     // Serial Print
       if(bsh % 24 == 0)
          {
            //Serial.print(bsh); Serial.print(" "); Serial.println(str_tanggal_hijriyah);
            Serial.println(str_tanggal_hijriyah);
          } 
       // AMBIL_WAKTU_SHOLAT();
    
    }
    else
    {
      if(pilih == 1){  mode = 9; }        // TANGGAL HIJRIYAH >> TANGGAL MASEHI
      else if(pilih == 2){  mode = 8; }   // TANGGAL MASEHI >> JAM BESAR
      else if(pilih == 3){  mode = 10; }  // NAMA MASJID >> INFO
   // else if(pilih == 3){  mode = 3; }   // NAMA MASJID >> JAM BESAR
      else if(pilih == 4){  mode = 1; }   // INFO >> JAM BESAR
      else if(pilih == 5){  mode = 1; }   // JWS >> JAM BESAR
      else if(pilih == 6){  mode = 3; }   // NAMA MASJID >> JAM BESAR
      bsh=0;
      Serial.println();
    }
  }
}
void TPL_HH_WKT_MSK(){                // MENAMPILKAN WAKTU MASUK ADZAN
  
    WAKTU();
    int b_lama_adzan;
    EEPROM.get(59, b_lama_adzan);
    int b_lama_imsak;
    EEPROM.get(61, b_lama_imsak); // harus 0
    int b_lama;

    // Membedakan waktu masuk Imsak dan Jadwal sholat

    if(slt_sek=="IMSAK"){
      b_lama = b_lama_imsak + 1;
    }
    else
    {
      b_lama = b_lama_adzan;
    }

    
    if (!evt_4 && (millis()-p_e_4_jmsk) > 1000) { 
    p_e_4_jmsk = millis();

      if (dur_tpl_tx_sol <= (60 * b_lama)){
        
// ==== TEMPAT BUAT BUZZER 10 DETIK PERTAMA ADZAN ==== //
//      if(dur_tpl_tx_sol < 10){
//
//         PORTD &= ~(1<<PORTD2); // pin 2 low
//         delay(500);
//         PORTD |=(1<< PORTD2); // pin 2 high
//         delay(500);
//         PORTD &= ~(1<<PORTD2); // pin 2 low    
//      }

      if(dur_tpl_tx_sol < 10){
        if(wkt_msk_skrg==1){
          mp3_play (3); // Beep
        }
        else if (wkt_msk_skrg==2){
          if(dur_tpl_tx_sol == 1){mp3_play (2);} // Play Adzan Subuh 
        }
        else if (wkt_msk_skrg==3 || wkt_msk_skrg==4 || wkt_msk_skrg==5 || wkt_msk_skrg==6){
          if(dur_tpl_tx_sol == 1){ mp3_play (1); } // Play Adzan Biasa 
        }
      }
  
        display.clear();
        
        
        if (dur_tpl_tx_sol % 2 == 0){
          display.setFont(System5x7);
          display.drawText((display.width()-display.textWidth(tx_hh_mm))/2,0,tx_hh_mm); // baris 1 : JAM
          if(slt_sek=="IMSAK"){
            display.setFont(Font4x6);
            namaMasukWkt = slt_sek;
            //namaMasukWkt = "WAKTU " + slt_sek;
            display.drawText((display.width()-display.textWidth(namaMasukWkt))/2,8,namaMasukWkt); // baris  : IMSAK 
            // Serial.println("WAKTU");
          }
          else
          {
            display.setFont(Font4x6);
            namaMasukWkt = slt_sek;
            display.drawText((display.width()-display.textWidth(namaMasukWkt))/2,8,namaMasukWkt); // baris  : ADZAN 
            // Serial.println("ADZAN");
          } 
          display.swapBuffers();
        }
        else
        {
          display.setFont(System5x7);
          display.drawText((display.width()-display.textWidth(tx_hh_mm))/2,0,tx_hh_mm); // baris 1 :  JAM
          display.drawText((display.width()-display.textWidth(slt_sek))/2,8,"  "); // baris  : JADWAL
          display.swapBuffers();
        }
        Serial.print(mode);  Serial.print(" ");
        Serial.print("WAKTU ");
        Serial.println(slt_sek);
        dur_tpl_tx_sol++;
      }
      else
      {
        if(slt_sek=="IMSAK"){
        j_s_s = 0;
        dur_tpl_tx_sol = 0;
        mode = 1; //  memanggil JAM
        
        }
        else
        {
        j_s_s = 1;
        dur_tpl_tx_sol = 0;
        mode = 6; //  memanggil IQOMAH
        }
        
      }
    } 
}
void TPL_QD_IQM(){                    // MENAMPILKAN IQOMAH
  WAKTU();
    j_s_s = 0;

    int b_iqm_sbh, b_iqm_dzr, b_iqm_asr, b_iqm_mgr, b_iqm_isy;
    
    // Baca EEPROM tampil lama iqomah
    EEPROM.get(49, b_iqm_sbh);
    EEPROM.get(51, b_iqm_dzr);
    EEPROM.get(53, b_iqm_asr); 
    EEPROM.get(55, b_iqm_mgr); 
    EEPROM.get(57, b_iqm_isy); 

    if (slt_sek == "SUBUH")
    { iqm_ee = (b_iqm_sbh*60); }
    if (slt_sek == "DZUHUR" || slt_sek == "JUMAT")
    { iqm_ee = (b_iqm_dzr*60); }
    if (slt_sek == "ASHAR")
    { iqm_ee = (b_iqm_asr*60); }
    if (slt_sek == "MAGRIB")
    { iqm_ee = (b_iqm_mgr*60); }
    if (slt_sek == "ISYA")
    { iqm_ee = (b_iqm_isy*60); }

    if (!evt_5 && (millis()-p_e_5_iqomah) > 1000) {  
      p_e_5_iqomah = millis();
      
      
      display.clear(); 
      if (du_iq <= iqm_ee){

        // Buzzer pengingat akhir iqomah
      if(du_iq > (iqm_ee-10) && du_iq < iqm_ee){
         PORTD &= ~(1<<PORTD2);
         delay(500);
         PORTD |=(1<< PORTD2);
         delay(500);
         PORTD &= ~(1<<PORTD2);
      }
      // Buzzer pengingat akhir iqomah detik terakhir
      if(du_iq == iqm_ee){
         PORTD &= ~(1<<PORTD2);
         delay(500);
         PORTD |=(1<< PORTD2);
         delay(2000);
         PORTD &= ~(1<<PORTD2);
      }
        
          sis_wkt_iqo = iqm_ee - du_iq;

          iqm_detik = sis_wkt_iqo % 60;
          iqm_menit_sisa = (sis_wkt_iqo - iqm_detik) / 60;
          iqm_menit = iqm_menit_sisa % 60;
          if (iqm_detik<10){
            tpl_iqo_ss = "0" +  String(iqm_detik);
          }
          else
          {
            tpl_iqo_ss = String(iqm_detik);
          }
    
          if(iqm_detik % 2 ==0){
            wkt_iqomah = "-" + String(iqm_menit) + ":" + tpl_iqo_ss;
          }
          else
          {
            wkt_iqomah = " " + String(iqm_menit) + ":" + tpl_iqo_ss;
          }
        
        // ==== TEMPAT BUAT BUZZER 10 DETIK TERAKHIR IQOMAH ==== //
        display.setFont(Font4x6);
        display.drawText((display.width()-display.textWidth("IQOMAH"))/2,0,"IQOMAH"); // JAM
        display.setFont(System5x7);
        textIqohitmun = wkt_iqomah;
        display.drawText((display.width()-display.textWidth(textIqohitmun))/2,8,textIqohitmun); // baris  : ADZAN 
        display.swapBuffers();
        
        Serial.print(mode);  Serial.print(" ");
        Serial.print("IQMAH ");
        Serial.println(wkt_iqomah);
        
        du_iq++;
        
      }
      else
    {
      mode = 7; 
      du_iq = 0;
    }  
      
    }
  
}
void AMBIL_WAKTU_SHOLAT(){            // AMBIL WAKTU SHOLAT

  DateTime now = rtc.now(); 
  int sekarang = now.dayOfTheWeek();
  double b_lati, b_longi, b_timezone;


      EEPROM.get(0, b_lati);
      EEPROM.get(5, b_longi);
      EEPROM.get(10, b_timezone); 
      
      EEPROM.get(25, b_a[0]); //imsak
      EEPROM.get(15, b_a[1]); //subuh
      EEPROM.get(27, b_a[2]); //terbit
      EEPROM.get(29, b_a[3]); //dhuha
      EEPROM.get(17, b_a[4]); //dzuhur
      EEPROM.get(19, b_a[5]); //ashar
      EEPROM.get(21, b_a[6]); //maghrib
      EEPROM.get(23, b_a[7]); //isya

        SholahTimeCalulation sholat;
        sholat.coordinatSet(b_lati, b_longi,b_timezone);
        sholat.dateSet(now.year(),now.month(),now.day());
        sholat.ihtiyatiSet(0);
        sholat.calculate();

      int hh_sol, mm_sol;
      int mm_ims, hh_ims;
      int hh_sol_res, mm_sol_res;

      for(int ws=0; ws < SholatCount; ws++){
        
        sholat.getTimePart(ws,hh_sol, mm_sol);

        if(ws==3){ // Dhuha
           // mm_sol = mm_sol + b_a[ws]-2;
           mm_sol = mm_sol + b_a[ws]; // Normal Dulu ya...
        }
        
        else if(ws==2){ // Terbit
           // mm_sol = mm_sol + b_a[ws]-2;
           mm_sol = mm_sol + b_a[ws]; // Normal Dulu ya...
        }
        else 
        {
          mm_sol = mm_sol + b_a[ws];
        }
        
        if (mm_sol >= 60) {
          mm_sol = mm_sol - 60;
          hh_sol ++;   
        }
        
        String wkt_sol_sat =  String(hh_sol / 10) + String(hh_sol % 10) + ":" + String(mm_sol / 10) + String(mm_sol % 10);

        //  Imsak:4:27|Subuh:4:37|Terbit:5:56|Dhuha:6:18|Dzuhur:12:9|Ashar:15:27|Maghrib:18:19|Isya:19:32

        if(ws==0){ waktu_ims = wkt_sol_sat;} // jss = jss + waktu_ims;}
        if(ws==1){ waktu_sbh = wkt_sol_sat;} // jss = jss + " " + waktu_sbh;}
        if(ws==2){ waktu_tbt = wkt_sol_sat;} // jss = jss + " " + waktu_tbt;}
        if(ws==3){ waktu_dhu = wkt_sol_sat;} // jss = jss + " " + waktu_dhu;}
        if(ws==4){ waktu_dzr = wkt_sol_sat;} // jss = jss + " " + waktu_dzr;}
        if(ws==5){ waktu_asr = wkt_sol_sat;} // jss = jss + " " + waktu_asr;}
        if(ws==6){ waktu_mgr = wkt_sol_sat;} // jss = jss + " " + waktu_mgr;}
        if(ws==7){ waktu_isy = wkt_sol_sat;} // jss = jss + " " + waktu_isy;}

      }

       // jss = "IMSAK " + waktu_ims + "SUBUH " + waktu_sbh + "DZUHUR " + waktu_dzr + "ASHAR " + waktu_asr + "MAGHRIB " + waktu_mgr + "ISYA " + waktu_isy;
     
    
      // =====================================================================================
      // CEK APAKAH SUDAH MASUK WAKTU SHOLAT //
      if (cck == waktu_ims && j_s_s == 0){
        wkt_msk_skrg = 1;
        slt_sek = "IMSAK";
        bsh=0; ash=0;
        mode=5;
      }
      
      if (cck == waktu_sbh && j_s_s == 0){
        wkt_msk_skrg = 2;
        slt_sek = "SUBUH";
        bsh=0; ash=0;
        mode=5;
      }
      if (cck == waktu_dzr && j_s_s == 0){
        wkt_msk_skrg = 3;
        if(sekarang==5){
          slt_sek = "JUMAT";
        bsh=0; ash=0; 
          mode=5;
        }
        else
        {
         slt_sek = "DZUHUR";
         bsh=0; ash=0;
          mode=5;
        }
      }
      
      if (cck == waktu_asr && j_s_s == 0){
        wkt_msk_skrg = 4;
        slt_sek = "ASHAR";
        bsh=0; ash=0; mode=5;
      }
      if (cck == waktu_mgr && j_s_s == 0){
        wkt_msk_skrg = 5;
        slt_sek = "MAGRIB";
        bsh=0; ash=0; 
        mode=5;
      }
      if (cck == waktu_isy && j_s_s == 0){
        wkt_msk_skrg = 6;
        slt_sek = "ISYA";
        bsh=0; ash=0;
        mode=5;
      }
      
      if(Menit == 0 && Detik == 0){
        if (Jam == 1 || Jam == 13){ mp3_play (21); }
        if (Jam == 2 || Jam == 14){ mp3_play (22); }
        if (Jam == 3 || Jam == 15){ mp3_play (23); }
        if (Jam == 4 || Jam == 16){ mp3_play (24); }
        if (Jam == 5 || Jam == 17){ mp3_play (25); }
        if (Jam == 6 || Jam == 18){ mp3_play (26); }
        if (Jam == 7 || Jam == 19){ mp3_play (27); }
        if (Jam == 8 || Jam == 20){ mp3_play (28); }
        if (Jam == 9 || Jam == 21){ mp3_play (29); }
        if (Jam == 10 || Jam == 22){ mp3_play (30); }
        if (Jam == 11 || Jam == 23){ mp3_play (31); }
        if (Jam == 12 || Jam == 0){ mp3_play (32); } 
      }
}
void CERAH_VOLUME(){
  EEPROM.get(65, b_bright); // Baca EEPROM kecerahan
  Timer1.pwm(9,b_bright);
  EEPROM.get(67, b_volume); // Baca EEPROM volume
  mp3_set_volume (b_volume);
}

void writeString(int address, String data){
  int stringSize = data.length();
  
  for(int i=0;i<stringSize;i++)
  {
    EEPROM.write(address+i, data[i]);
  }
  EEPROM.write(address + stringSize,'\0');   //Add termination null character
}
String readString(int address){
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k = EEPROM.read(address);
  while(k != '\0' && len < 100)   //Read until null character
  {
    k = EEPROM.read(address + len);
    data[len] = k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

/*
Lat  : -6.21
16 Long  : 106.85
30 Timezone  : 7.00
 
36 Adj SUBUH  : 2
38 Adj ZUHUR  : 2
40 Adj ASHAR  : 2
42 Adj MAGHRIB  : 2
44 Adj ISYA  : 2
46 Adj IMSAK  : 2
48 Adj TERBIT  : 2
50 Adj DHUHA  : 2
 
52 Tpl SUBUH  : 1
54 Tpl DZUHUR  : 0
56 Tpl ASHAR  : 1
58 Tpl MAGHRIB  : 0
60 Tpl ISYA : 1
62 Tpl IMSAK  : 0
64 Tpl TERBIT  : 1
66 Tpl DHUHA : 0
 
68 Iqo SUBUH  : 2
70 Iqo ZUHUR  : 2
72 Iqo ASHAR  : 2
74 Iqo MAGHRIB  : 2
76 Iqo ISYA  : 2
78 Lama Adzan : 4
80 Lama Imsak : 0
 
82 Adjust Hij : 1
84 Adjust Kecerahan : 10
86 Adjust Volume : 20
 
90 Panjang Nama Masjid : 40
93 Nama Masjid : Masjid Raya Akbar Maulana - Ampera Raya
 
140 Panjang info2 : 24
143 info 2 : Sudahkah Anda Sholat ??

 */
 
#include <DMD3asis.h>
#include <Wire.h>
#include "RTClib.h"
#include "SholahTimeCalulation.h"
#include "tangal_hijriyah.h"

#include <DFPlayer_Mini_Mp3.h>
#include <EEPROMex.h>

DMD3 display(1,1);

// #include <Arial_Black_16.h>
#include <SystemFont5x7.h>
#include <angka6x13.h>
#include <Font5x7.h>
// #include <Arial14.h>
#include <font/Font4x6.h>

RTC_DS3231 rtc;

unsigned long p_e_0_names=0, p_e_1_jam=0, p_e_2_hjry=0, p_e_4_jmsk=0, p_e_3_wksol=0, p_e_5_iqomah=0, p_e_6_lurus=0;
byte evt_0 = 0, evt_1 = 0, evt_2 = 1, evt_3 = 1, evt_4 = 1, evt_5 = 1, evt_6 = 1;
int iqm_ee, sis_wkt_iqo, du_iq, iqm_menit, iqm_menit_sisa, iqm_detik;

int b_a[8];
  
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
int j_s_s = 0;
String tx_ser;
byte wkt_msk_skrg;

const char namaBulanMasehi[12][12] PROGMEM = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
const char namaHariMasehi[7][7] PROGMEM = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
const char pesan[][60] PROGMEM = {"Matikan HP - Luruskan Shaf - Matikan HP - Luruskan Shaf"};

void scan(){
  display.refresh();
}
void setup(){
 
  EEPROM.setMaxAllowedWrites(10000);

  Serial.begin (9600);
  mp3_set_serial (Serial); 
  
  b_volume = EEPROM.readInt(86); 
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

  b_bright = EEPROM.readInt(84); // Baca EEPROM kecerahan
  
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
      // evt_0 = 1; evt_1 = 1; evt_2 = 1; evt_3 = 0; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      // TPL_HH_JWS();
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
       // evt_0 = 1; evt_1 = 1; evt_2 = 1; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 0;
       // TPL_LURUS(); 
      evt_0 = 1; evt_1 = 1; evt_2 = 0; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      TPL_HH_TGL(4); 
    break;
    case 8: 
      evt_0 = 1; evt_1 = 0; evt_2 = 1; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      TPL_HH();
    break;
    case 9: 
      // evt_0 = 1; evt_1 = 1; evt_2 = 0; evt_3 = 1; evt_4 = 1; evt_5 = 1; evt_6 = 1;
      // TPL_HH_TGL1();
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
    
    if (tx_ser.length() > 0)
      {
        // Setting Jam === SJ=04-29-55-23-06-2020-01-10-15 4 digit terakhir (10-15) = brightness-volume
        if(tx_ser.substring(0,2) == "SJ"){
          Serial.println(tx_ser);

          rtc.adjust(DateTime(tx_ser.substring(18,22).toInt(), tx_ser.substring(15,17).toInt(), tx_ser.substring(12,14).toInt(), tx_ser.substring(3,5).toInt(), tx_ser.substring(6,8).toInt(), tx_ser.substring(9,11).toInt())); 
          EEPROM.writeInt(82, tx_ser.substring(23,25).toInt()); // Adj Hijriyah
          EEPROM.writeInt(84, tx_ser.substring(26,28).toInt()); // Adj Kecerahan
          EEPROM.writeInt(86, tx_ser.substring(29,31).toInt()); // Adj Volume
          
          CERAH_VOLUME();
          
          BUZZ();
       }

       // Setting lama Iqomah === IQ=02-02-02-02-02-04 === IQ=01-01-01-01-01-02
       else if(tx_ser.substring(0,2) == "IQ"){ 
          Serial.println(tx_ser);
          EEPROM.writeInt(68, tx_ser.substring(3,5).toInt());
          EEPROM.writeInt(70, tx_ser.substring(6,8).toInt());
          EEPROM.writeInt(72, tx_ser.substring(9,11).toInt());
          EEPROM.writeInt(74, tx_ser.substring(12,14).toInt());
          EEPROM.writeInt(76, tx_ser.substring(15,17).toInt());
          EEPROM.writeInt(78, tx_ser.substring(18,20).toInt());
   
          // for(int pp = 2; pp < 15; pp=pp+2){
          //    EEPROM.writeInt(66+pp, tx_ser.substring(pp,pp+2).toInt());
          // }
          
        BUZZ();
         
       }
       
       // Setting Koreksi waktu sholat === KR=02-02-02-02-02-02-00-02 == 02-00-02 imsak dan dhuha
       else if(tx_ser.substring(0,2) == "KR"){
         Serial.println(tx_ser);
         
         EEPROM.writeInt(36, tx_ser.substring(3,5).toInt());
         EEPROM.writeInt(38, tx_ser.substring(6,8).toInt());
         EEPROM.writeInt(40, tx_ser.substring(9,11).toInt());
         EEPROM.writeInt(42, tx_ser.substring(12,14).toInt());
         EEPROM.writeInt(44, tx_ser.substring(15,17).toInt());
         EEPROM.writeInt(46, tx_ser.substring(18,20).toInt());
         EEPROM.writeInt(48, tx_ser.substring(21,23).toInt());
         EEPROM.writeInt(50, tx_ser.substring(24,26).toInt());
          
         BUZZ();
       }

       // Setting Nama masjid === NM=Masjid Raya Akbar Maulana - Ampera Raya
       else if(tx_ser.substring(0,2) == "NM"){
         Serial.println(tx_ser);
         
         byte panjang_nama_masjid = tx_ser.length()-3;
         EEPROM.write(90, panjang_nama_masjid);
         
         String isi_namamasjid = tx_ser.substring(3,tx_ser.length());
         
         char charbuf[panjang_nama_masjid];
         String s = tx_ser.substring(3,tx_ser.length());
         s.toCharArray(charbuf, panjang_nama_masjid);
         EEPROM.writeBlock<char>(93, charbuf, panjang_nama_masjid);
          
         BUZZ();
       }
       
       // Setting Info === IN=Sudahkan Anda Sholat ??
       else if(tx_ser.substring(0,2) == "IN"){
         Serial.println(tx_ser);
         
         byte panjang_info = tx_ser.length()-3;
         EEPROM.write(140, panjang_info);

         String isi_info = tx_ser.substring(3,tx_ser.length());
         
         char charbuf1[panjang_info];
         String s = tx_ser.substring(3,tx_ser.length());
         s.toCharArray(charbuf1, panjang_info);
         EEPROM.writeBlock<char>(143, charbuf1, panjang_info);
         
         BUZZ();
       }
       
       // Setting Lokasi === LL=-6.21462|106.84513|7 === LL=-1.26753|116.82887|8
       else if(tx_ser.substring(0,2) == "LL"){
         Serial.println(tx_ser);
        
         for (int i = 0; i < tx_ser.length(); i++) {
            if (tx_ser.substring(i, i+1) == "|") {

              EEPROM.writeDouble(0, (tx_ser.substring(3, i)).toDouble());
              EEPROM.writeDouble(16, (tx_ser.substring(i+1, tx_ser.length()-3)).toDouble());
              EEPROM.writeDouble(32, (tx_ser.substring(tx_ser.length()-2, tx_ser.length())).toDouble());
              
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
  

  if(pilih == 1){      // ============= TANGGAL HIJRIYAH
    int b_ses_hijriyah;
    b_ses_hijriyah=EEPROM.readInt(82); 
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

    byte panjang_nama_masjid;
    panjang_nama_masjid = EEPROM.read(90); 

    char output[panjang_nama_masjid];
    EEPROM.readBlock<char>(93, output, panjang_nama_masjid);
    str_tanggal_hijriyah = output;
    
  }
  else if(pilih == 4){ // ============= LURUSKAN

    char isiPesan[60];
    memset(isiPesan, 0, 60);
    strcpy_P(isiPesan, pesan[0]);

    str_tanggal_hijriyah = isiPesan;
  }
  else if(pilih == 5){ // ============= JWS
    str_tanggal_hijriyah = "Imsak " + waktu_ims + " Subuh " + waktu_sbh + " Dzuhur " + waktu_dzr + " Ashar " + waktu_asr + " Maghrib " + waktu_mgr + " Isya " + waktu_isy;    
    //str_tanggal_hijriyah = "IMSAK " + waktu_ims + "SUBUH " + waktu_sbh + "TERBIT " + waktu_tbt + "DHUHA " + waktu_dhu + "DZUHUR " + waktu_dzr + "ASHAR " + waktu_asr + "MAGHRIB " + waktu_mgr + "ISYA " + waktu_isy;    
  
  }
  else if(pilih == 6){ // ============= INFO 1

    byte panjang_info;
    panjang_info = EEPROM.read(140); 

    char output1[panjang_info];
    EEPROM.readBlock<char>(143, output1, panjang_info);
    str_tanggal_hijriyah = output1;
    
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
    b_lama_adzan = EEPROM.readInt(78);
    int b_lama_imsak;
    b_lama_imsak =  EEPROM.readInt(80); // harus 0
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
    b_iqm_sbh = EEPROM.readInt(68);
    b_iqm_dzr = EEPROM.readInt(70);
    b_iqm_asr = EEPROM.readInt(72); 
    b_iqm_mgr = EEPROM.readInt(74); 
    b_iqm_isy = EEPROM.readInt(76); 

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


      b_lati=EEPROM.readDouble(0);
      b_longi=EEPROM.readDouble(16);
      b_timezone=EEPROM.readDouble(32); 
      
      b_a[0]=EEPROM.readInt(46); //imsak
      b_a[1]=EEPROM.readInt(36); //subuh
      b_a[2]=EEPROM.readInt(48); //terbit
      b_a[3]=EEPROM.readInt(50); //dhuha
      b_a[4]=EEPROM.readInt(38); //dzuhur
      b_a[5]=EEPROM.readInt(40); //ashar
      b_a[6]=EEPROM.readInt(42); //maghrib
      b_a[7]=EEPROM.readInt(44); //isya



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

        if(ws==3){
           mm_sol = mm_sol + b_a[ws]-2;
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
  b_bright = EEPROM.readInt(84); // Baca EEPROM kecerahan
  Timer1.pwm(9,b_bright);
  b_volume = EEPROM.readInt(86); // Baca EEPROM volume
  mp3_set_volume (b_volume);
}

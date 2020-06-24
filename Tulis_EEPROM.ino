#include <EEPROMex.h>

String namamasjid = "Masjid Raya Akbar Maulana"; // Max 50
String info1 = "Matikan HP - Luruskan Shaf - Matikan HP - Luruskan Shaf"; // Max 60
String info2 = "Sudahkah Anda Sholat"; // Max 60
String info3 = "Selamat Memunaikan Ibadah Puasa"; // Max 60



void setup() {

  Serial.begin(115200);

//
//  
//  for (int i = 0 ; i < EEPROM.length() ; i++) {
//    EEPROM.write(i, 0);
//  }
  
//  
//  LATITUDE DAN LONGITUDE
//  ======================
//
  double lati = -6.21462;
  EEPROM.writeDouble(0, lati);
  double longi = 106.84513;
  EEPROM.writeDouble(16, longi);
  double timezone = 7;
  EEPROM.writeDouble(32, timezone);
//
//  ADJUST WAKTU SHOLAT
//  ===================
//
  int adj_subuh = 2;
  EEPROM.writeInt(36, adj_subuh);
  int adj_dzuhur = 2;
  EEPROM.writeInt(38, adj_dzuhur);
  int adj_ashar = 2;
  EEPROM.writeInt(40, adj_ashar);
  int adj_maghrib = 2;
  EEPROM.writeInt(42, adj_maghrib);
  int adj_isya = 2;
  EEPROM.writeInt(44, adj_isya);
  int adj_imsak = 2;
  EEPROM.writeInt(46, adj_imsak);
  int adj_terbit = 2;
  EEPROM.writeInt(48, adj_terbit);
  int adj_dhuha = 2;
  EEPROM.writeInt(50, adj_dhuha);
//
//  TAMPILKAN WAKTU SHOLAT
//  ======================
//
  int tpl_subuh = 1;
  EEPROM.writeInt(52, tpl_subuh);
  int tpl_dzuhur = 0;
  EEPROM.writeInt(54, tpl_dzuhur);
  int tpl_ashar = 1;
  EEPROM.writeInt(56, tpl_ashar);
  int tpl_maghrib = 0;
  EEPROM.writeInt(58, tpl_maghrib);
  int tpl_isya = 1;
  EEPROM.writeInt(60, tpl_isya);

  int tpl_imsak = 0;
  EEPROM.writeInt(62, tpl_imsak);
  int tpl_terbit = 1;
  EEPROM.writeInt(64, tpl_terbit);
  int tpl_dhuha = 0;
  EEPROM.writeInt(66, tpl_dhuha);
//
//  LAMA IQOMAH
//  ===========
//
  int iqm_subuh = 2;
  EEPROM.writeInt(68, iqm_subuh);
  int iqm_dzuhur = 2;
  EEPROM.writeInt(70, iqm_dzuhur);
  int iqm_ashar = 2;
  EEPROM.writeInt(72, iqm_ashar);
  int iqm_maghrib = 2;
  EEPROM.writeInt(74, iqm_maghrib);
  int iqm_isya = 2;
  EEPROM.writeInt(76, iqm_isya);
//
//  LAMA ADZAN
//  ===========
//
  int lama_adzan = 4;
  EEPROM.writeInt(78, lama_adzan);
  
//  LAMA IMSAK
//  ================
//
  int lama_imsak = 0;
  EEPROM.writeInt(80, lama_imsak);
//  
//  KOREKSI HIJRIYAH
//  ================
//
  int sesuaikan_tgl_hijriyah = 1;
  EEPROM.writeInt(82, sesuaikan_tgl_hijriyah);

  int sesuaikan_bright = 10;
  EEPROM.writeInt(84, sesuaikan_bright);

  int sesuaikan_volume = 20;
  EEPROM.writeInt(86, sesuaikan_volume);


//for(int pp = 2; pp < 15; pp=pp+2){
//  EEPROM.put(66+pp, 8);
//}
//
//for(int pp = 2; pp < 17; pp=pp+2){
//   EEPROM.put(34+pp, 2);
//}
  
//  

 
//  NAMA MASJID
//  ================

  byte panjang_nama_masjid = namamasjid.length() + 1; // buat nano, buat uno hilangin + 1;
  EEPROM.write(90, panjang_nama_masjid);

  char charbuf[panjang_nama_masjid];
  namamasjid.toCharArray(charbuf, panjang_nama_masjid);
  EEPROM.writeBlock<char>(93, charbuf, panjang_nama_masjid);

  
//  INFO 2 Max 60
//  ================

  byte panjang_info_2 = info2.length() + 1; // buat nano, buat uno hilangin + 1;
  EEPROM.write(140, panjang_info_2);

  char charbuf1[panjang_info_2];
  info2.toCharArray(charbuf1, panjang_info_2);
  EEPROM.writeBlock<char>(143, charbuf1, panjang_info_2);

  
  
//  INFO 2 Max 60
//  ================

//  int panjang_info_2 = info2.length();
//  EEPROM.put(176, panjang_info_1);
//
//  byte size_info2_1 = info2.length();
//  for (byte i = 178 ; i < (178 + info2.length()); i++) {
//    EEPROM.write(0x0F+i, info2[i-178]);
//  }

 
}

void loop() {
  // put your main code here, to run repeatedly:

}

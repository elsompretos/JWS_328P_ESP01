#include <EEPROM.h>
//double  blatitude, blongitude, btz;
//int badj_subuh, badj_dzuhur, badj_ashar, badj_maghrib, badj_isya, badj_imsak, badj_terbit, badj_dhuha;
//int btpl_subuh, btpl_dzuhur, btpl_ashar, btpl_maghrib, btpl_isya, btpl_imsak, btpl_terbit, btpl_dhuha;
//int biqm_subuh, biqm_dzuhur, biqm_ashar, biqm_maghrib, biqm_isya, blam_zan, blama_imsak;
//int bsesuaikan_tgl_hijriyah, bsesuaikan_bright, bsesuaikan_volume;
//  
//
//String nama;
//String info1, info2, info3, info4;


void setup() {

  Serial.begin(9600);

  //  LATITUDE DAN LONGITUDE
  //  ======================

  double latitude = -6.21462;
  EEPROM.put(0, latitude);
  double longitude = 106.84513;
  EEPROM.put(5, longitude);
  double tz = 7;
  EEPROM.put(10, tz);

//  EEPROM.get(0, blatitude);
//  Serial.print("0 Latitude : "); Serial.println(blatitude);
//  EEPROM.get(5, blongitude);
//  Serial.print("5 Longitude : "); Serial.println(blongitude);
//  EEPROM.get(10, btz);
//  Serial.print("10 Timezone : "); Serial.println(btz); Serial.println();
 
  //  ADJUST WAKTU SHOLAT
  //  ===================

  int adj_subuh = 2; EEPROM.put(15, adj_subuh);
  int adj_dzuhur = 2; EEPROM.put(17, adj_dzuhur);
  int adj_ashar = 2; EEPROM.put(19, adj_ashar);
  int adj_maghrib = 2; EEPROM.put(21, adj_maghrib);
  int adj_isya = 2; EEPROM.put(23, adj_isya);
  int adj_imsak = 2; EEPROM.put(25, adj_imsak);
  int adj_terbit = 2; EEPROM.put(27, adj_terbit);
  int adj_dhuha = 2; EEPROM.put(29, adj_dhuha);
  
//  EEPROM.get(15, badj_subuh); Serial.print("15 adj_subuh : "); Serial.println(badj_subuh);
//  EEPROM.get(17, badj_dzuhur); Serial.print("17 adj_dzuhur : "); Serial.println(badj_dzuhur);
//  EEPROM.get(19, badj_ashar); Serial.print("19 adj_ashar : "); Serial.println(badj_ashar);
//  EEPROM.get(21, badj_maghrib); Serial.print("21 adj_maghrib : "); Serial.println(badj_maghrib); 
//  EEPROM.get(23, badj_isya); Serial.print("23 adj_isya : "); Serial.println(badj_isya);
//  EEPROM.get(25, badj_imsak); Serial.print("25 adj_imsak : "); Serial.println(badj_imsak);
//  EEPROM.get(27, badj_terbit); Serial.print("27 adj_terbit : "); Serial.println(badj_terbit);
//  EEPROM.get(29, badj_dhuha); Serial.print("29 adj_dhuha : "); Serial.println(badj_dhuha);
//  Serial.println();

  //  TAMPILKAN WAKTU SHOLAT
  //  ======================

  int tpl_subuh = 1; EEPROM.put(31, tpl_subuh);
  int tpl_dzuhur = 1; EEPROM.put(33, tpl_dzuhur);
  int tpl_ashar = 1; EEPROM.put(35, tpl_ashar);
  int tpl_maghrib = 1; EEPROM.put(37, tpl_maghrib);
  int tpl_isya = 1; EEPROM.put(39, tpl_isya);
  int tpl_imsak = 1; EEPROM.put(41, tpl_imsak);
  int tpl_terbit = 1; EEPROM.put(43, tpl_terbit);
  int tpl_dhuha = 1; EEPROM.put(45, tpl_dhuha);

//  EEPROM.get(31, btpl_subuh); Serial.print("31 tpl_subuh : "); Serial.println(btpl_subuh);
//  EEPROM.get(33, btpl_dzuhur); Serial.print("33 tpl_dzuhur : "); Serial.println(btpl_dzuhur);
//  EEPROM.get(35, btpl_ashar); Serial.print("35 tpl_ashar : "); Serial.println(btpl_ashar);
//  EEPROM.get(37, btpl_maghrib); Serial.print("37 tpl_maghrib : "); Serial.println(btpl_maghrib); 
//  EEPROM.get(39, btpl_isya); Serial.print("39 tpl_isya : "); Serial.println(btpl_isya);
//  EEPROM.get(41, btpl_imsak); Serial.print("41 tpl_imsak : "); Serial.println(btpl_imsak);
//  EEPROM.get(43, btpl_terbit); Serial.print("43 tpl_terbit : "); Serial.println(btpl_terbit);
//  EEPROM.get(45, btpl_dhuha); Serial.print("45 tpl_dhuha : "); Serial.println(btpl_dhuha);
//  Serial.println();

  //  LAMA IQOMAH
  //  ===========

  int iqm_subuh = 2; EEPROM.put(47, iqm_subuh);
  int iqm_dzuhur = 2; EEPROM.put(49, iqm_dzuhur);
  int iqm_ashar = 2; EEPROM.put(51, iqm_ashar);
  int iqm_maghrib = 2; EEPROM.put(53, iqm_maghrib);
  int iqm_isya = 2; EEPROM.put(55, iqm_isya);
  int lama_adzan = 4; EEPROM.put(57, lama_adzan);

//  EEPROM.get(47, biqm_subuh); Serial.print("47 iqm_subuh : "); Serial.println(biqm_subuh); 
//  EEPROM.get(49, biqm_dzuhur); Serial.print("49 iqm_dzuhur : "); Serial.println(biqm_dzuhur);
//  EEPROM.get(51, biqm_ashar); Serial.print("51 iqm_ashar : "); Serial.println(biqm_ashar);
//  EEPROM.get(53, biqm_maghrib); Serial.print("53 iqm_maghrib : "); Serial.println(biqm_maghrib);
//  EEPROM.get(55, biqm_isya); Serial.print("55 iqm_isya : "); Serial.println(biqm_isya);
//  EEPROM.get(57, blam_zan); Serial.print("57 lama_adzan : "); Serial.println(blam_zan);
//  Serial.println();

  //  LAMA IMSAK
  //  ================

  int lama_imsak = 5; EEPROM.put(59, lama_imsak);
//  EEPROM.get(57, blama_imsak); Serial.print("57 lama_imsak : "); Serial.println(blama_imsak);
//  Serial.println(); 
   
  //  KOREKSI HIJRIYAH
  //  ================

  int sesuaikan_tgl_hijriyah = 1; EEPROM.put(61, sesuaikan_tgl_hijriyah); 
  int sesuaikan_bright = 10; EEPROM.put(63, sesuaikan_bright);
  int sesuaikan_volume = 20; EEPROM.put(65, sesuaikan_volume);

//  EEPROM.get(59, bsesuaikan_tgl_hijriyah); Serial.print("59 sesuaikan_tgl_hijriyah : "); Serial.println(bsesuaikan_tgl_hijriyah);
//  EEPROM.get(61, bsesuaikan_bright); Serial.print("61 sesuaikan_bright : "); Serial.println(bsesuaikan_bright);
//  EEPROM.get(63, bsesuaikan_volume); Serial.print("63 sesuaikan_volume : "); Serial.println(bsesuaikan_volume);
//  Serial.println();

  writeString(67, "Masjid Raya Akbar Maulana - Ampera Raya");
  writeString(117, "Jadikan Sabar dan Sholat Sebagai Penolongmu");
  writeString(167, "Sedekah Melancarkan Rezekimu");
  writeString(217, "Subhanallah Walhamdulillah Laailahaillalhah");
  writeString(267, "Selamat Hari Raya Idul Fitri 1 Syawal 1441 H");

//  nama = readString(65);
//  Serial.print("65 Nama Masjid  : "); Serial.println(nama);
//  info1 = readString(115);
//  Serial.print("115 Informasi 1 : "); Serial.println(info1);
//  info2 = readString(165);
//  Serial.print("165 Informasi 2 : "); Serial.println(info2);
//  info3 = readString(215);
//  Serial.print("215 Informasi 3 : "); Serial.println(info3);
//  info4 = readString(265);
//  Serial.print("265 Informasi 4 : "); Serial.println(info4);
//  Serial.println();


  
}

void loop() {
  

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

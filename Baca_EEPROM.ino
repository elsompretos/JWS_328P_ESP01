// #include <EEPROM.h>
#include <EEPROMex.h>

double b_lati;
double b_longi;
double b_timezone;

int b_adj_sbh;
int b_adj_dzr;
int b_adj_asr;
int b_adj_mgr;
int b_adj_isy;

int b_adj_ims;
int b_adj_ter;
int b_adj_dhu;

int tpl_subuh;
int tpl_dzuhur;
int tpl_ashar;
int tpl_maghrib;
int tpl_isya;

int tpl_ims;
int tpl_ter;
int tpl_dhu;

int blaza;
int lama_imsak;

int adj_bright;
int adj_volume;

int panjang_nama_masjid;
int panjang_info1;
int panjang_info2;

int bhijadj;

int b_iqm_sbh, b_iqm_dzr, b_iqm_asr, b_iqm_mgr, b_iqm_isy;


void setup() {
Serial.begin(115200);

    // EEPROM.writeInt(32, 8);
        

    // 0 - 30 LOKASI
    b_lati = EEPROM.readDouble(0);
    b_longi = EEPROM.readDouble(16);
    b_timezone = EEPROM.readDouble(32); 

    Serial.print("0 Lat  : ");
    Serial.println(b_lati);
    Serial.print("16 Long  : ");
    Serial.println(b_longi);
    Serial.print("32 Timezone  : ");
    Serial.println(b_timezone);

    Serial.println(" ");

    // 36 - 43 ADJUST
    b_adj_sbh = EEPROM.readInt(36);
    b_adj_dzr = EEPROM.readInt(38);
    b_adj_asr = EEPROM.readInt(40); 
    b_adj_mgr = EEPROM.readInt(42); 
    b_adj_isy = EEPROM.readInt(44);
    b_adj_ims = EEPROM.readInt(46); 
    b_adj_ter = EEPROM.readInt(48); 
    b_adj_dhu = EEPROM.readInt(50);
    
    Serial.print("36 Adj SUBUH  : ");
    Serial.println(b_adj_sbh);
    Serial.print("38 Adj ZUHUR  : ");
    Serial.println(b_adj_dzr);
    Serial.print("40 Adj ASHAR  : ");
    Serial.println(b_adj_asr);
    Serial.print("42 Adj MAGHRIB  : ");
    Serial.println(b_adj_mgr);
    Serial.print("44 Adj ISYA  : ");
    Serial.println(b_adj_isy);
    Serial.print("46 Adj IMSAK  : ");
    Serial.println(b_adj_ims);
    Serial.print("48 Adj TERBIT  : ");
    Serial.println(b_adj_ter);
    Serial.print("50 Adj DHUHA  : ");
    Serial.println(b_adj_dhu);

    Serial.println(" ");

    // 44 - 51 TAMPIL
    tpl_subuh = EEPROM.readInt(52);
    tpl_dzuhur = EEPROM.readInt(54);
    tpl_ashar = EEPROM.readInt(56); 
    tpl_maghrib = EEPROM.readInt(58); 
    tpl_isya = EEPROM.readInt(60); 
    tpl_ims = EEPROM.readInt(62); 
    tpl_ter = EEPROM.readInt(64); 
    tpl_dhu = EEPROM.readInt(66); 

    Serial.print("52 Tpl SUBUH  : ");
    Serial.println(tpl_subuh);
    Serial.print("54 Tpl DZUHUR  : ");
    Serial.println(tpl_dzuhur);
    Serial.print("56 Tpl ASHAR  : ");
    Serial.println(tpl_ashar);
    Serial.print("58 Tpl MAGHRIB  : ");
    Serial.println(tpl_maghrib);
    Serial.print("60 Tpl ISYA : ");
    Serial.println(tpl_isya);
    Serial.print("62 Tpl IMSAK  : ");
    Serial.println(tpl_ims);
    Serial.print("64 Tpl TERBIT  : ");
    Serial.println(tpl_ter);
    Serial.print("66 Tpl DHUHA : ");
    Serial.println(tpl_dhu);

    Serial.println(" ");

    // 52 - 65 IQOMAH & ADZAN
    b_iqm_sbh = EEPROM.readInt(68);
    b_iqm_dzr = EEPROM.readInt(70);
    b_iqm_asr = EEPROM.readInt(72); 
    b_iqm_mgr = EEPROM.readInt(74); 
    b_iqm_isy = EEPROM.readInt(76); 
    blaza = EEPROM.readInt(78); 
    lama_imsak = EEPROM.readInt(80); 

    Serial.print("68 Iqo SUBUH  : ");
    Serial.println(b_iqm_sbh);
    Serial.print("70 Iqo ZUHUR  : ");
    Serial.println(b_iqm_dzr);
    Serial.print("72 Iqo ASHAR  : ");
    Serial.println(b_iqm_asr);
    Serial.print("74 Iqo MAGHRIB  : ");
    Serial.println(b_iqm_mgr);
    Serial.print("76 Iqo ISYA  : ");
    Serial.println(b_iqm_isy);
    Serial.print("78 Lama Adzan : ");
    Serial.println(blaza);
    Serial.print("80 Lama Imsak : ");
    Serial.println(lama_imsak);

    Serial.println(" ");

    // 66 ADJUST HIJRIYAH
    
    bhijadj = EEPROM.readInt(82); 
    Serial.print("82 Adjust Hij : ");
    Serial.println(bhijadj);

    adj_bright = EEPROM.readInt(84); 
    Serial.print("84 Adjust Kecerahan : ");
    Serial.println(adj_bright);

    adj_volume = EEPROM.readInt(86); 
    Serial.print("86 Adjust Volume : ");
    Serial.println(adj_volume);

    Serial.println(" ");

    panjang_nama_masjid = EEPROM.read(90); 
    Serial.print("90 Panjang Nama Masjid : ");
    Serial.println(panjang_nama_masjid);
    
    String isi_namamasjid;
    char output[panjang_nama_masjid];
    EEPROM.readBlock<char>(93, output, panjang_nama_masjid);
    isi_namamasjid = output;
    
    Serial.print("93 Nama Masjid : ");
    Serial.println(isi_namamasjid);

    Serial.println(" ");
    panjang_info2 = EEPROM.read(140); 
    Serial.print("140 Panjang info2 : ");
    Serial.println(panjang_info2);
  
    String isi_info2;
    char output1[panjang_info2];
    EEPROM.readBlock<char>(143, output1, panjang_info2);
    isi_info2 = output1;
    Serial.print("143 info 2 : ");
    Serial.println(isi_info2);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

/*
SJ=12:59-00-24-06-2020-01-10-15
LL=-6.21462|106.84513|7
NM=Masjid Akbar Maulana
IN=Sudahkah Anda Sholat
IQ=01-01-01-01-01-04
KR=02-02-02-02-02-02-02-02

 */

#include <Wire.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

#include "WebPage.h"

// ==== WIFI ====
const char* ssid = "JWSKU";
const char* password = "00000000";

IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

String kirim;
String bulan, tanggal, tahun, jam, menit, hijri, cerah, volume, adzan, iqosubuh, iqodzuhur, iqoashar, iqomaghrib, iqoisya;
String korimsak, korsubuh, korterbit, kordhuha, kordzuhur, korashar, kormaghrib, korisya;

void setup() {
  Serial.begin(115200);
  
  // ==============
  // ==== WIFI ====
  // ==============
  
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  delay(1000);

  Serial.println("Wifi ACCESS POINT");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, netmask);
  WiFi.softAP(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  server.on("/", []() {
     server.send_P(200, "text/html", setwaktu);

     if (server.hasArg("date")) {
       // date=2020-06-24&time=10%3A20&hijr=1&cerah=10&volume=15

       tanggal = (server.arg(0)).substring(8,10);
       bulan = (server.arg(0)).substring(5,7);
       tahun = (server.arg(0)).substring(0,4);
       
       if ((server.arg(2)).toInt() < 10){ hijri = "0" + server.arg(2);  } else { hijri = server.arg(2);  }
       if ((server.arg(3)).toInt() < 10){ cerah = "0" + server.arg(3);  } else { cerah = server.arg(3);  }
       if ((server.arg(4)).toInt() < 10){ volume = "0" + server.arg(4); } else { volume = server.arg(4); }
   
       kirim = "SJ=" + server.arg(1) + "-00-" + tanggal + "-" + bulan + "-" + tahun + "-" + hijri + "-" + cerah + "-" + volume;
  
       Serial.println(kirim);

    }  

    if (server.hasArg("namamasjid")) {
      // namamasjid=Masjid+Akbar+Maulana
      kirim = "NM=" + server.arg(0);
      Serial.println(kirim); 
    }

    if (server.hasArg("info1")) {
      // info1=Sudahkah+Anda+Sholat
      kirim = "IN=" + server.arg(0);
      Serial.println(kirim);
    }

    if (server.hasArg("latitude")) {
      // latitude=-6.21462&longitude=106.84513&timezone=7 
      kirim = "LL=" + server.arg(0) + "|" + server.arg(1) + "|" + server.arg(2);
      Serial.println(kirim);
    }

    if (server.hasArg("lamaadzan")) {
      // lamaadzan=4&iqomahsubuh=1&iqomahdzuhur=1&iqomahashar=1&iqomahmaghrib=1&iqomahisya=1
      
      if ((server.arg(0)).toInt() < 10){ adzan = "0" + server.arg(0);  } else { adzan = server.arg(0);  }
      if ((server.arg(1)).toInt() < 10){ iqosubuh = "0" + server.arg(1);  } else { iqosubuh = server.arg(1);  }
      if ((server.arg(2)).toInt() < 10){ iqodzuhur = "0" + server.arg(2); } else { iqodzuhur = server.arg(2); }
      if ((server.arg(3)).toInt() < 10){ iqoashar = "0" + server.arg(3);  } else { iqoashar = server.arg(3);  }
      if ((server.arg(4)).toInt() < 10){ iqomaghrib = "0" + server.arg(4);  } else { iqomaghrib = server.arg(4);  }
      if ((server.arg(5)).toInt() < 10){ iqoisya = "0" + server.arg(5); } else { iqoisya = server.arg(5); }
      
      kirim = "IQ=" + iqosubuh + "-" + iqodzuhur + "-" + iqoashar + "-" + iqomaghrib  + "-" + iqoisya + "-" + adzan;
      Serial.println(kirim);
    }

    if (server.hasArg("korimsak")) {
      // korimsak=2&korsubuh=2&korterbit=2&kordhuha=2&kordzuhur=2&korashar=2&kormaghrib=2&korisya=2
      // KR=02-02-02-02-02-02-00-02 == 02-00-02 imsak dan dhuha
      
      if ((server.arg(0)).toInt() < 10){ korimsak = "0" + server.arg(0);  } else { korimsak = server.arg(0);  }
      if ((server.arg(1)).toInt() < 10){ korsubuh = "0" + server.arg(1);  } else { korsubuh = server.arg(1);  }
      if ((server.arg(2)).toInt() < 10){ korterbit = "0" + server.arg(2); } else { korterbit = server.arg(2); }
      if ((server.arg(3)).toInt() < 10){ kordhuha = "0" + server.arg(3);  } else { kordhuha = server.arg(3);  }
      if ((server.arg(4)).toInt() < 10){ kordzuhur = "0" + server.arg(4);  } else { kordzuhur = server.arg(4);  }
      if ((server.arg(5)).toInt() < 10){ korashar = "0" + server.arg(5); } else { korashar = server.arg(5); }
      if ((server.arg(6)).toInt() < 10){ kormaghrib = "0" + server.arg(6);  } else { kormaghrib = server.arg(6);  }
      if ((server.arg(7)).toInt() < 10){ korisya = "0" + server.arg(7); } else { korisya = server.arg(7); }
      
      kirim = "KR=" + korsubuh + "-" + kordzuhur + "-" + korashar + "-" + kormaghrib  + "-" + korisya + "-" + korimsak + "-" + korterbit  + "-" + kordhuha;
      Serial.println(kirim);
    }
    
  });
  
  // ================
  // ==== SERVER ====
  // ================

  httpUpdater.setup(&server);
  server.begin();
  Serial.println("HTTP server started"); 

}

void loop() {
  server.handleClient();
}

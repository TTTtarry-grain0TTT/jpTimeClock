#include <M5Core2.h>
#include <WiFi.h>
#include "time.h"

//WiFi情報
const char* ssid       = "Your_wifi_SSID";
const char* password   = "Your_wifi_password";
//NTPサーバ
const char* ntpServer = "ntp.nict.jp";
const long  gmtOffset_sec = 9 * 3600; //GMTとローカル時刻との差（単位は秒）
const int   daylightOffset_sec = 0; //夏時間で進める時間（単位は秒）

void printLocalTime();

void setup(){
  M5.begin(); 
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("\nConnecting to %s", ssid);
  //wifiの接続
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500); //0.5秒の遅延
    M5.Lcd.print(".");
  }
  M5.Lcd.println("\nCONNECTED!");
  M5.Lcd.fillScreen(BLACK);

  //NTPサーバとローカルのタイムゾーンの設定
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop(){
  delay(1000); //1秒の遅延
  M5.Lcd.setCursor(0,0);
  //時刻を表示する関数の呼び出し
  printLocalTime();
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    M5.Lcd.println("Failed to obtain time");
    return;
  }
  //文字サイズの設定
  M5.Lcd.setTextSize(4);
  //日付表示
  M5.Lcd.setCursor(40,100);
  M5.Lcd.printf("%04d%/%02d%/%02d ", timeinfo.tm_year+1900, timeinfo.tm_mon+1, timeinfo.tm_mday);
  //時間表示
  M5.Lcd.setCursor(70,140);
  M5.Lcd.printf("%02d:%02d:%02d",timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec);
}

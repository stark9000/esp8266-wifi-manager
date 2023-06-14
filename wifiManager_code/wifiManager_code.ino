#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int BTN_1 = D0;

const char* ssid     = "SSID";
const char* password = "PASSWORD";

WiFiManager wifiManager;

void setup() {

  Serial.begin(9600);
  Serial.println("wifi manager test");

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("wifi manager");
  delay(2000);

  WiFi.mode(WIFI_STA);

  pinMode(BTN_1, INPUT);

  if (!digitalRead(BTN_1) == HIGH ) {

    wifiManager.setDebugOutput(false);
    wifiManager.setBreakAfterConfig(true);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("config mode ...");
    lcd.setCursor(0, 1);
    lcd.print("CPIP:192.168.4.1");

    Serial.println("config mode ...");
    Serial.println("CPIP : 192.168.4.1");


    if (!wifiManager.startConfigPortal("WiFi-Sockets-Config")) {
      Serial.println("failed to connect and hit timeout");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ERR conn :(");
      delay(2000);
      ESP.reset();
    } else {
      //Serial.println("connect from portal");
      //Serial.println(WiFi.localIP());

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("p connected!");
      Serial.println("p connected");

      //Serial.print(wifiManager.getWiFiSSID(true).c_str());
      //Serial.print(wifiManager.getWiFiPass(true).c_str());
    }

  } else {

    //Serial.println(wifiManager.getWiFiSSID(true).c_str());
    // Serial.println(wifiManager.getWiFiPass(true).c_str());
    //Serial.println("****");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("m connect :");
    Serial.println("m connect :");
    WiFi.begin(wifiManager.getWiFiSSID(true).c_str() , wifiManager.getWiFiPass(true).c_str());

    byte i = 0;
    while (WiFi.status() != WL_CONNECTED && i++ < 20) {
      // Serial.println(".");
      lcd.setCursor(0, 1);
      lcd.print("connecting...");
      delay(500);
    }

    if (WiFi.status() == WL_CONNECTED) {
      // Serial.println(WiFi.localIP());
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("connected!");
      Serial.println("connected");
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ERR conn :(");
      // Serial.println("ERR conn :(");
    }

  }
}


void loop() {

}

#include "config.h"
#include "secrets.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// --- Define Pins ---
#define DHTPIN 13
#define DHTTYPE DHT11
#define GAS_SENSOR_PIN 34
#define BUZZER 14
#define MODEM_TX 17
#define MODEM_RX 16

// --- Initialize Objects ---
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
HardwareSerial gsmSerial(1); // UART1 for GSM

// --- Variables ---
const int GAS_THRESHOLD = 2000; // Adjust if needed
bool alertSent = false;

void setup() {
  // --- Serial Communications ---
  Serial.begin(115200);
  gsmSerial.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);

  // --- Initialize LCD and Sensors ---
  lcd.init();
  lcd.backlight();
  dht.begin();
  pinMode(BUZZER, OUTPUT);
  pinMode(GAS_SENSOR_PIN, INPUT);

  // --- WiFi Connection ---
  WiFi.begin(ssid, pass);
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected");
    Blynk.begin(auth, ssid, pass);
    delay(2000);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Failed");
    lcd.setCursor(0, 1);
    lcd.print("Check Hotspot!");
    Serial.println("WiFi Connection Failed");
    delay(5000);
  }

  // --- Check GSM Module ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Checking SIM...");
  if (checkGSMRegistration()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SIM Ready ✅");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SIM Failed");
    lcd.setCursor(0, 1);
    lcd.print("Check SIM Card!");
  }
  delay(3000);

  // --- Welcome Message ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print("SMART LPG DETECT");
  delay(3000);
  lcd.clear();
}

void loop() {
  Blynk.run();

  int gasLevel = analogRead(GAS_SENSOR_PIN);
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    lcd.setCursor(0, 0);
    lcd.print("DHT Fail!");
    lcd.setCursor(0, 1);
    lcd.print("Check Sensor");
    delay(2000);
    return;
  }

  // --- Update Blynk ---
  Blynk.virtualWrite(V0, gasLevel);
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, hum);

  // --- Print to Serial ---
  Serial.print("Gas: ");
  Serial.print(gasLevel);
  Serial.print(" | Temp: ");
  Serial.print(temp);
  Serial.print("C | Hum: ");
  Serial.print(hum);
  Serial.println("%");

  // --- Show on LCD ---
  lcd.setCursor(0, 0);
  lcd.print("Gas:");
  lcd.print(gasLevel);
  lcd.print(" T:");
  lcd.print((int)temp);
  lcd.print(" ");

  lcd.setCursor(0, 1);
  lcd.print("Hum:");
  lcd.print((int)hum);
  lcd.print("%   ");

  // --- Gas Leak Detected ---
  if (gasLevel > GAS_THRESHOLD && !alertSent) {
    sendSMSAlert();    // GSM SMS
    makeTwilioCall();  // Twilio Voice Call
    Blynk.logEvent("gas_leak", "Gas Leak Detected!");
    alertSent = true;

    digitalWrite(BUZZER, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("!!Gas Leak Det!!");
    lcd.setCursor(0, 1);
    lcd.print("SMS+Call+Blynk ");
    delay(15000);
    digitalWrite(BUZZER, LOW);
  }
  else if (gasLevel <= GAS_THRESHOLD) {
    alertSent = false;
  }

  delay(1000);
}

// --- Send SMS using GSM ---
void sendSMSAlert() {
  gsmSerial.println("AT+CMGF=1");
  delay(500);
  gsmSerial.println("AT+CMGS=\"+919398852259\""); 
  delay(500);
  gsmSerial.println("ALERT: Gas Leak Detected! Please check!");
  gsmSerial.write(26); // CTRL+Z
  delay(3000);
}

// --- Make a Voice Call via Twilio ---
void makeTwilioCall() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClientSecure client;
    client.setInsecure();

    String url = "https://api.twilio.com/2010-04-01/Accounts/" + String(twilio_account_sid) + "/Calls.json";
    String data = "Url=" + String(twilio_voice_url) + 
                  "&To=" + urlencode(twilio_to_number) +
                  "&From=" + urlencode(twilio_from_number);

    http.begin(client, url);
    http.setAuthorization(twilio_account_sid, twilio_auth_token);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpResponseCode = http.POST(data);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Twilio Response: ");
      Serial.println(response);
    } else {
      Serial.print("Error in Twilio Call: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi not connected - Cannot make Twilio call");
  }
}

// --- Check GSM Network Registration ---
bool checkGSMRegistration() {
  gsmSerial.println("AT+CREG?");
  delay(500);
  String response = "";

  while (gsmSerial.available()) {
    response += char(gsmSerial.read());
  }

  Serial.println(response);

  return (response.indexOf("+CREG: 0,1") >= 0 || response.indexOf("+CREG: 0,5") >= 0);
}

// --- URL Encode Helper Function ---
String urlencode(const char* str) {
  String encoded = "";
  char c;
  while ((c = *str++)) {
    if (isalnum(c)) {
      encoded += c;
    } else {
      encoded += '%';
      char buf[3];
      sprintf(buf, "%02X", c);
      encoded += buf;
    }
  }
  return encoded;
}
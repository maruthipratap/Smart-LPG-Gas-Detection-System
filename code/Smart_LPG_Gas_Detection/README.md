# Smart LPG Gas Detection System – Source Code

This folder contains the complete **embedded source code** for the **Smart LPG Gas Detection System** developed using **ESP32**, gas sensors, environmental sensors, GSM, and cloud services.

The code is modular, secure, and structured following **industry best practices** for IoT projects.

---

## 📁 Folder Structure

Smart_LPG_Gas_Detection/
├── Smart_LPG_Gas_Detection.ino # Main ESP32 application
├── config.h # Hardware pins & constants
├── secrets.h # Declarations for credentials
├── secrets.cpp # Actual credentials (ignored by Git)
├── README.md # This file

---

## 📌 File Description

### 🔹 `Smart_LPG_Gas_Detection.ino`
- Main program executed on ESP32
- Handles:
  - LPG gas detection (MQ series sensor)
  - Temperature & humidity monitoring (DHT11)
  - LCD display updates (I2C)
  - Buzzer alert
  - GSM-based SMS alerts
  - Cloud notifications via Blynk
  - Voice call alerts using Twilio API

---

### 🔹 `config.h`
Contains **non-sensitive configuration parameters**:
- Blynk template details
- Pin mappings
- Sensor configuration
- Threshold values

✅ Safe to upload to GitHub

---

### 🔹 `secrets.h`
Contains **declarations** for sensitive credentials:
- WiFi SSID & password
- Blynk authentication token
- Twilio account details

⚠️ This file is ignored using `.gitignore`

---

### 🔹 `secrets.cpp`
Contains the **actual secret values**:
- WiFi credentials
- Blynk auth token
- Twilio SID & Auth Token
- Phone numbers

🚫 **Never upload this file to GitHub**  
✔ Used only on the local development machine

---

## ⚙️ Hardware Used
- ESP32 Development Board
- MQ-series LPG Gas Sensor
- DHT11 Temperature & Humidity Sensor
- GSM Module (SIM800L)
- 16x2 LCD with I2C
- Buzzer
- External Power Supply

---

## ☁️ Cloud & Communication
- **Blynk** → Real-time monitoring & alerts
- **Twilio API** → Automated voice call alerts
- **GSM (SIM800L)** → SMS alerts without internet dependency

---

## 🔐 Security Design
- Credentials separated from logic
- Secrets excluded using `.gitignore`
- Safe for public GitHub repositories
- Follows professional IoT security practices

---

## 🚀 How to Use
1. Open the folder in **Arduino IDE**
2. Select:
   - Board: ESP32 Dev Module
   - Correct COM Port
3. Install required libraries:
   - Blynk
   - DHT Sensor Library
   - LiquidCrystal_I2C
4. Add your real credentials in `secrets.cpp`
5. Upload the code to ESP32

---

## 📈 Future Enhancements
- Relay-based automatic gas shutoff
- Mobile app integration
- Data logging to cloud database
- Machine-learning-based leak prediction

---

## 👨‍💻 Author
**Maruthi Pratap**

Smart LPG Gas Detection System  
IoT & Embedded Systems Project

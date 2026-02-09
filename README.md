# Smart LPG Gas Detection System 🔥

An **IoT-based Smart LPG Gas Leakage Detection System** designed to enhance household and industrial safety by detecting LPG gas leaks and providing **instant alerts** through **local alarms, GSM SMS, cloud notifications, and automated voice calls**.

This project uses **ESP32**, gas and environmental sensors, GSM communication, and cloud services to ensure reliable and real-time monitoring.

---

## 🚀 Features

- ✅ Real-time LPG gas leak detection  
- ✅ Temperature & humidity monitoring (DHT11)  
- ✅ Local alert using buzzer and LCD display  
- ✅ SMS alert using GSM module (SIM800L)  
- ✅ Voice call alert using **Twilio API**  
- ✅ Cloud monitoring & notifications via **Blynk**  
- ✅ Secure handling of credentials (GitHub-safe)  

---

## 🧠 System Overview

When the LPG gas concentration exceeds a predefined threshold:
1. The system triggers a **buzzer alert**
2. Displays warning on **LCD**
3. Sends **SMS alert** via GSM
4. Makes an **automated voice call** using Twilio
5. Pushes a **cloud notification** through Blynk

This multi-layer alert mechanism ensures **maximum safety** even if one communication method fails.

---

## 🗂️ Project Structure

Smart-LPG-Gas-Detection-System/
├── code/
│ └── Smart_LPG_Gas_Detection/
│ ├── Smart_LPG_Gas_Detection.ino
│ ├── config.h
│ ├── secrets.h
│ ├── secrets.cpp (ignored by Git)
│ └── README.md
├── circuit-diagram/
│ └── circuit-diagram.png
├── images/
│ ├── lcd.png
│ ├── lpg.png
│ └── demo-images
├── report/
│ └── Project_Report.pdf
├── .gitignore
└── README.md

---

## 🔧 Hardware Components

- ESP32 Development Board  
- MQ-series LPG Gas Sensor  
- DHT11 Temperature & Humidity Sensor  
- GSM Module (SIM800L)  
- 16x2 LCD with I2C  
- Buzzer  
- Power Supply & supporting components  

---

## ☁️ Software & Technologies

- **Arduino IDE**
- **ESP32 Core**
- **Blynk IoT Platform**
- **Twilio API**
- **GSM AT Commands**
- **Git & GitHub**

---

## 🔐 Security & Best Practices

- Sensitive credentials are stored in `secrets.cpp`
- Secrets are excluded from GitHub using `.gitignore`
- Configuration and logic are modularized
- Safe for public repositories

---

## ▶️ How to Run the Project

1. Open the `code/Smart_LPG_Gas_Detection` folder in **Arduino IDE**
2. Select:
   - Board: **ESP32 Dev Module**
   - Correct COM Port
3. Install required libraries:
   - Blynk
   - DHT Sensor Library
   - LiquidCrystal_I2C
4. Add your credentials in `secrets.cpp`
5. Upload the code to ESP32
6. Power the circuit and test using LPG source (safely)

---

## 📈 Future Scope

- 🔌 Relay-based automatic gas shutoff (solenoid valve)
- 📱 Dedicated mobile application
- ☁️ Cloud data logging and analytics
- 🤖 AI-based leak pattern detection

---

## 🎓 Academic Relevance

- Suitable for **Final Year Engineering Project**
- Covers **IoT, Embedded Systems, Cloud Integration, and Security**
- Demonstrates real-world safety application

---

## 👨‍💻 Author

**Maruthi Pratap**  
Smart LPG Gas Detection System  
IoT & Embedded Systems Project

---

## 📜 License
This project is intended for **educational and research purposes**.

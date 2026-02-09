#ifndef CONFIG_H
#define CONFIG_H

// --- Blynk Info (NON-SECRET) ---
#define BLYNK_TEMPLATE_ID "TMPL3XgGLFaR1"
#define BLYNK_TEMPLATE_NAME "Smart LPG Detection"

// --- Pin Definitions ---
#define DHTPIN 13
#define DHTTYPE DHT11
#define GAS_SENSOR_PIN 34
#define BUZZER 14
#define MODEM_TX 17
#define MODEM_RX 16

// --- Thresholds ---
#define GAS_THRESHOLD 2000

#endif

#include "BluetoothSerial.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ===================== CONFIGURATION ===================== */

// ---- LoRa RN2483 ----
#define RN_RESET 4
HardwareSerial lora(2);
unsigned long lastLoraSend = 0;
const unsigned long LORA_INTERVAL = 10000; // 10 s

// ---- Bluetooth ----
BluetoothSerial SerialBT;

// ---- ADC ----
#define ADC_PIN 36
unsigned long lastAdcRead = 0;
const unsigned long ADC_INTERVAL = 2000; //2s
int lastAdcValue = 0;

// ---- Ecran ----
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---- Bl ----
bool screenEnabled = true;

/* ===================== FONCTIONS ===================== */

void sendLoraCommand(String cmd, int delayMs = 1000) {
  lora.println(cmd);
  delay(delayMs);
  while (lora.available()) {
    Serial.write(lora.read());
  }
  Serial.println();
}

void updateScreenPower() {
  if (screenEnabled) {
    display.ssd1306_command(SSD1306_DISPLAYON);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Ecran ALLUME");
    display.display();
  } else {
    display.clearDisplay();
    display.display();
    display.ssd1306_command(SSD1306_DISPLAYOFF);
  }
}

void initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 non détecté");
    while (true);
  }

  updateScreenPower();
}


void initLora() {
  lora.begin(57600, SERIAL_8N1, 16, 17);

  pinMode(RN_RESET, OUTPUT);
  digitalWrite(RN_RESET, LOW);
  delay(200);
  digitalWrite(RN_RESET, HIGH);
  delay(2000);

  sendLoraCommand("sys reset");
  sendLoraCommand("sys get ver");

  sendLoraCommand("mac set deveui 70052e8f64964d6e");
  sendLoraCommand("mac set appeui 30e09b3545acb1ce");
  sendLoraCommand("mac set appkey 19011e234a8bf6c30854f0447b724c4d");

  sendLoraCommand("mac set pwridx 5");
  sendLoraCommand("mac join otaa");
  delay(5000);
}

void initADC() {
  analogReadResolution(12);
  analogSetPinAttenuation(ADC_PIN, ADC_11db);
}

void readADC() {
  lastAdcValue = analogRead(ADC_PIN);
  float tension = lastAdcValue * 3.3 / 4095.0;

  Serial.print("ADC = ");
  Serial.print(lastAdcValue);
  Serial.print(" | Tension = ");
  Serial.print(tension);
  Serial.println(" V");

  SerialBT.println(tension);

  if (screenEnabled){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Mesure ADC");

    display.setTextSize(2);
    display.print(tension, 2);
    display.println(" V");

    display.display();
  }
}


void sendLoraPayload() {
  char payload[5]; // 2 octets = 4 caractères hex
  sprintf(payload, "%04X", lastAdcValue);

  Serial.println(payload);

  String cmd = "mac tx uncnf 1 ";
  cmd += payload;

  sendLoraCommand(cmd);
}

void handleBluetooth() {
  if (SerialBT.available()) {
    int n = SerialBT.read();
    Serial.print("Bluetooth reçu : ");
    Serial.println(n);

    if (n == 1) {
      screenEnabled = !screenEnabled; 
      updateScreenPower();
      SerialBT.println(screenEnabled ? "SCREEN_ON" : "SCREEN_OFF");
    }
  }
}


/* ===================== SETUP ===================== */

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 démarrage...");

  SerialBT.begin("ESP32_LED");
  Serial.println("Bluetooth initialisé");

  initADC();

  Wire.begin(21, 22);   // SDA, SCL
  initDisplay();

  initLora();

  Serial.println("Système prêt !");
}

/* ===================== LOOP ===================== */

void loop() {
  unsigned long now = millis();

  handleBluetooth();

  if (now - lastAdcRead >= ADC_INTERVAL) {
    lastAdcRead = now;
    readADC();
  }

  if (now - lastLoraSend >= LORA_INTERVAL) {
    lastLoraSend = now;
    sendLoraPayload();
  }
}

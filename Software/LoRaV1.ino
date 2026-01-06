#define RN_RESET 4

HardwareSerial lora(2); // UART2

void sendCommand(String cmd, int delayMs = 1000) {
  lora.println(cmd);
  delay(delayMs);
  while (lora.available()) {
    Serial.write(lora.read());
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  
  lora.begin(57600, SERIAL_8N1, 16, 17); // RX, TX

  Serial2.begin(57600, SERIAL_8N1, 16, 17);

  pinMode(RN_RESET, OUTPUT);

  digitalWrite(RN_RESET, LOW);   // reset obligatoire sur notre carte !
  delay(200);
  digitalWrite(RN_RESET, HIGH);  // démarrage

  delay(2000);

  sendCommand("sys reset");
  sendCommand("sys get ver");

  // Configuration LoRaWAN (EXEMPLE)
  sendCommand("mac set deveui 70052e8f64964d6e");
  sendCommand("mac set appeui 30e09b3545acb1ce");
  sendCommand("mac set appkey 19011e234a8bf6c30854f0447b724c4d");

  delay(100);
  sendCommand("mac set pwridx 5");
  delay(100);
  sendCommand("mac join otaa");
  delay(5000);
}

void loop() {
  sendCommand("mac tx uncnf 1 48656C6C6F"); // "Hello" en HEX
  delay(10000);
}


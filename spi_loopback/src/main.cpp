#include <Arduino.h>
#include <SPI.h>

#define SCK_PIN  18
#define MISO_PIN 19
#define MOSI_PIN 23
#define CS_PIN   26 // Changed from 5 to 26 to avoid strapping pins!

void setup() {
  Serial.begin(115200);
  
  // Initialize SPI
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // CS is active LOW
  
  Serial.println("SPI Loopback Test Started");
}

void loop() {
  uint8_t sentByte = 0xA5;
  uint8_t receivedByte = 0x00;

  digitalWrite(CS_PIN, LOW); // Select slave
  
  // Lab requirement: 1 MHz, MSBFIRST, SPI_MODE0
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  receivedByte = SPI.transfer(sentByte);
  SPI.endTransaction();
  
  digitalWrite(CS_PIN, HIGH); // Deselect slave

  Serial.print("Sent 0x"); Serial.print(sentByte, HEX);
  Serial.print(", received 0x"); Serial.println(receivedByte, HEX);
  
  delay(1000);
}
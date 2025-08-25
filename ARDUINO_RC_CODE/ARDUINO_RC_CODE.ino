#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h> 

#define CE_PIN 2
#define CSN_PIN 3
#define VRx A0
#define VRy A1

RF24 radio(CE_PIN, CSN_PIN);

const byte address[5] = {'N','E','I','L','1'};

struct JoystickData {
  int16_t x;
  int16_t y;
};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!radio.begin()) {
    Serial.println("radio.begin() failed");
    while (1);
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(76);
  radio.setAutoAck(true);
  radio.enableDynamicPayloads();
  radio.stopListening();

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);

  Serial.println("Joystick transmitter ready");
}

void loop() {
  JoystickData data;
  data.x = analogRead(VRx);
  data.y = analogRead(VRy);

  Serial.print("Sending X: ");
  Serial.print(data.x);
  Serial.print(" Y: ");
  Serial.println(data.y);

  bool ok = radio.write(&data, sizeof(data));
  Serial.println(ok ? "✅ Sent!" : "❌ Failed to send");

  delay(100);
}

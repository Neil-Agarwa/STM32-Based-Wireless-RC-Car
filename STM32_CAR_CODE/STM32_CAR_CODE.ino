#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN D14
#define CSN_PIN D15
#define LED_PIN 13

// Motor driver pins
#define ENA1 D3   // D3 PWM capable
#define PF2 A3   // A4 pass front 
#define PF1 A2   // A2 pass front
#define PR1 A1   // A1 pass rear 
#define PR2 D2   // D2 pass rear

#define ENA2 A5   // A5 PWM capable
#define DR1 D4   // D4 Drive Rear
#define DR2 D5   // D5 Drive Rear
#define DP2 A0   // A0 Drive front
#define DP1 D6   // D6 Drive front




RF24 radio(CE_PIN, CSN_PIN);

const byte address[5] = {'N','E','I','L','1'};

struct JoystickData {
  int16_t x;
  int16_t y;
};

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for the serial connection to open
  Serial.println("STM32 Serial ready!");

  pinMode(LED_PIN, OUTPUT);

  //Motor driver pin setup
  pinMode(ENA1, OUTPUT);
  pinMode(PF1, OUTPUT);
  pinMode(PF2, OUTPUT);
  pinMode(PR1, OUTPUT);
  pinMode(PR2, OUTPUT);

  pinMode(ENA2, OUTPUT);
  pinMode(DR1, OUTPUT);
  pinMode(DR2, OUTPUT);
  pinMode(DP1, OUTPUT);
  pinMode(DP2, OUTPUT);

  digitalWrite(LED_PIN, HIGH);

  if (!radio.begin()) {
    Serial.println("radio.begin() failed");
    while (1);
  }

  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(76);
  radio.setAutoAck(true);
  radio.enableDynamicPayloads();
  radio.startListening(); 
  Serial.println("Joystick receiver ready and listening...");
}

void loop() {
  if (radio.available()) {
    JoystickData data;
    radio.read(&data, sizeof(data));

    Serial.print("X: ");
    Serial.print(data.x);
    Serial.print(" Y: ");
    Serial.println(data.y);

    digitalWrite(LED_PIN, LOW);
    delay(50);
    digitalWrite(LED_PIN, HIGH);

    // control logic
    //----FORWARD + RIGHT----
    if (data.y <= 300 && data.x <= 300){
      analogWrite(ENA2, 0);                       //maybe change to 150 
      digitalWrite(DP1, HIGH);
      digitalWrite(DP2, LOW);
      digitalWrite(DR1, HIGH);
      digitalWrite(DR2, LOW);

      analogWrite(ENA1, 255);
      digitalWrite(PF1, HIGH);
      digitalWrite(PF2, LOW);
      digitalWrite(PR1, HIGH);
      digitalWrite(PR2, LOW);
    }

//----FORWARD + LEFT----
    else if (data.y <= 300 && data.x >= 350){
      analogWrite(ENA2, 255);
      digitalWrite(DP1, HIGH);
      digitalWrite(DP2, LOW);
      digitalWrite(DR1, HIGH);
      digitalWrite(DR2, LOW);

      analogWrite(ENA1, 0);                      //maybe change to 150 
      digitalWrite(PF1, HIGH);
      digitalWrite(PF2, LOW);
      digitalWrite(PR1, HIGH);
      digitalWrite(PR2, LOW);
    }

//----BACKWARD + RIGHT----
    else if (data.y >= 350 && data.x <= 300){
      analogWrite(ENA2, 0);                       //maybe change to 150 
      digitalWrite(DP1, HIGH);
      digitalWrite(DP2, LOW);
      digitalWrite(DR1, HIGH);
      digitalWrite(DR2, LOW);

      analogWrite(ENA1, 255);
      digitalWrite(PF1, LOW);
      digitalWrite(PF2, HIGH);
      digitalWrite(PR1, LOW);
      digitalWrite(PR2, HIGH);
    }

  //----FORWARD + LEFT----
    else if (data.y >= 350 && data.x >= 350){
      analogWrite(ENA2, 255);
      digitalWrite(DP1, LOW);
      digitalWrite(DP2, HIGH);
      digitalWrite(DR1, LOW);
      digitalWrite(DR2, HIGH);

      analogWrite(ENA1, 0);                      //maybe change to 150 
      digitalWrite(PF1, HIGH);
      digitalWrite(PF2, LOW);
      digitalWrite(PR1, HIGH);
      digitalWrite(PR2, LOW);
    }
    
    //----FORWARD----
    else if (data.y <= 300){
      analogWrite(ENA2, 255);
      digitalWrite(DP1, HIGH);
      digitalWrite(DP2, LOW);
      digitalWrite(DR1, HIGH);
      digitalWrite(DR2, LOW);

      analogWrite(ENA1, 255);
      digitalWrite(PF1, HIGH);
      digitalWrite(PF2, LOW);
      digitalWrite(PR1, HIGH);
      digitalWrite(PR2, LOW);
    }

    //----BACKWARDS----
    else if (data.y >= 350){
      analogWrite(ENA2, 255);
      digitalWrite(DP1, LOW);
      digitalWrite(DP2, HIGH);
      digitalWrite(DR1, LOW);
      digitalWrite(DR2, HIGH);

      analogWrite(ENA1, 255);
      digitalWrite(PF1, LOW);
      digitalWrite(PF2, HIGH);
      digitalWrite(PR1, LOW);
      digitalWrite(PR2, HIGH);
    }

    //----SHARP_RIGHT----
    else if (data.x <= 300){
      analogWrite(ENA2, 255);
      digitalWrite(DP1, LOW);
      digitalWrite(DP2, HIGH);
      digitalWrite(DR1, LOW);
      digitalWrite(DR2, HIGH);

      analogWrite(ENA1, 255);
      digitalWrite(PF1, HIGH);
      digitalWrite(PF2, LOW);
      digitalWrite(PR1, HIGH);
      digitalWrite(PR2, LOW);
    }

        //----SHARP_LEF----
    else if (data.x >= 350){
      analogWrite(ENA2, 255);
      digitalWrite(DP1, HIGH);
      digitalWrite(DP2, LOW);
      digitalWrite(DR1, HIGH);
      digitalWrite(DR2, LOW);

      analogWrite(ENA1, 255);
      digitalWrite(PF1, LOW);
      digitalWrite(PF2, HIGH);
      digitalWrite(PR1, LOW);
      digitalWrite(PR2, HIGH);
    }
    else{
      analogWrite(ENA1, 0);
      analogWrite(ENA2, 0);
    }
	    
  }
}

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h> // Include the Servo library

#define RST_PIN     9
#define SS_PIN      10
#define LED_PIN     2         // Define LED pin
#define SERVO_PIN   5 // Use a digital pin for the servo motor
MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servoMotor; // Create a Servo instance

byte targetUID1[] = {0x46, 0xD6, 0xD4, 0x25}; // For turning the servo motor
byte targetUID2[] = {0xD4, 0x9F, 0x8C, 0x79}; // For blinking LED

void setup() {
   pinMode(LED_PIN, OUTPUT);    // Set LED pin as output
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  servoMotor.attach(SERVO_PIN); // Attach the servo motor to the specified pin
  servoMotor.write(0); // Initialize the servo motor position to 0 degrees
}

void loop() {
  
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    
    if (compareUID(mfrc522.uid.uidByte, mfrc522.uid.size, targetUID1, sizeof(targetUID1))) {
      // If the scanned UID matches the target UID 1, rotate the servo motor
      servoMotor.write(100); // Rotate to 90 degrees
      delay(5000); // Wait for 5 seconds
      servoMotor.write(0); // Rotate back to 0 degrees
    }
else {
      // Blink the LED for any other RFID card
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(500); // LED ON for 0.5 seconds
        digitalWrite(LED_PIN, LOW);
        delay(500); // LED OFF for 0.5 seconds
      }
    }
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
}

bool compareUID(byte* uid1, byte uid1Size, byte* uid2, byte uid2Size) {
  if (uid1Size != uid2Size) {
    return false;
  }

  for (byte i = 0; i < uid1Size; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }

  return true;
}

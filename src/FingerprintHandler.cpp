#include "FingerprintHandler.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

extern LiquidCrystal_I2C lcd;

FingerprintHandler::FingerprintHandler() : finger(SoftwareSerial(2, 3)), records(10), eepromBaseAddress(1000) {
  for (int i = 0; i < records; i++) {
    userIDs[i] = EEPROM.read(eepromBaseAddress + i);
  }
}

FingerprintHandler::~FingerprintHandler() {
}

void FingerprintHandler::begin() {
  finger.begin(57600);
}

void FingerprintHandler::enrollFingerprint() {
  // Implementation for enrolling a fingerprint goes here
  // You need to adapt the code based on your specific requirements
}

void FingerprintHandler::deleteFingerprint() {
  // Implementation for deleting a fingerprint goes here
  // You need to adapt the code based on your specific requirements
}

int FingerprintHandler::getFingerprintID() {
  int result = finger.getImage();

  if (result != FINGERPRINT_OK)
    return -1;

  result = finger.image2Tz();
  if (result != FINGERPRINT_OK)
    return -1;

  result = finger.fingerFastSearch();
  if (result != FINGERPRINT_OK) {
    lcd.clear();
    lcd.print("Finger Not Found");
    lcd.setCursor(0, 1);
    lcd.print("Try Later");
    delay(2000);
    return -1;
  }

  // found a match!
  Serial.print("Found ID #");
  Serial.print(finger.fingerID);
  return finger.fingerID;
}

void FingerprintHandler::download(int eepIndex) {
  // Implementation for downloading fingerprint data from EEPROM goes here
  // You need to adapt the code based on your specific requirements
}

void FingerprintHandler::upload(int eepIndex) {
  // Implementation for uploading fingerprint data to EEPROM goes here
  // You need to adapt the code based on your specific requirements
}

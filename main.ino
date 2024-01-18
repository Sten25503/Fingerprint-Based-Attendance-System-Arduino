#include <Wire.h>
#include <Adafruit_Fingerprint.h> // Fingerprint library header file
#include <EEPROM.h>               // Command for storing data
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <virtuabotixRTC.h> // Library used

// Other global variables or constants can be declared here

#define register_back 14
#define delete_ok 15
#define forward 16
#define reverse 17
#define match 5
#define indFinger 7
#define buzzer 5

#define records 10 // 10 for 10 users

int user1, user2, user3, user4, user5, user6, user7, user8, user9, user10;

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial fingerPrint(2, 3); // for tx/rx communication between Arduino & r305 fingerprint sensor
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);
virtuabotixRTC myRTC(6, 7, 8);

void setup() {
  delay(1000);
  lcd.begin();
  Serial.begin(9600); // try to get time sync from pc
  myRTC.setDS1302Time(15, 31, 9, 5, 01, 25, 2023);

  pinMode(register_back, INPUT_PULLUP);
  pinMode(forward, INPUT_PULLUP);
  pinMode(reverse, INPUT_PULLUP);
  pinMode(delete_ok, INPUT_PULLUP);
  pinMode(match, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(indFinger, OUTPUT);
  digitalWrite(buzzer, LOW);

  if (digitalRead(register_back) == 0) {
    // Code for downloading data
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    lcd.print("Please wait !");
    lcd.setCursor(0, 1);
    lcd.print("Downloading Data");

    Serial.println("Please wait");
    Serial.println("Downloading Data..");
    Serial.println();

    Serial.print("S.No. ");
    for (int i = 0; i < records; i++) {
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      Serial.print(" User ID");
      Serial.print(i + 1);
      Serial.print(" ");
    }
    Serial.println();

    int eepIndex = 0;
    for (int i = 0; i < 30; i++) {
      if (i + 1 < 10)
        Serial.print('0');
      Serial.print(i + 1);
      Serial.print(" ");
      eepIndex = (i * 7);
      download(eepIndex);
      eepIndex = (i * 7) + 210;
      download(eepIndex);
      eepIndex = (i * 7) + 420;
      download(eepIndex);
      eepIndex = (i * 7) + 630;
      download(eepIndex);
      eepIndex = (i * 7) + 840;
      download(eepIndex);
      eepIndex = (i * 7) + 1050;
      download(eepIndex);
      eepIndex = (i * 7) + 1260;
      download(eepIndex);
      eepIndex = (i * 7) + 1470;
      download(eepIndex);
      eepIndex = (i * 7) + 1680;
      download(eepIndex);
      Serial.println();
    }
  }

  // Other setup code goes here

  lcd.print("  Welcome! ");
  lcd.setCursor(0, 1);
  lcd.print("  Biometric ");
  delay(2000);
  lcd.clear();
  lcd.print("  Attendance");
  lcd.setCursor(0, 1);
  lcd.print("  System");
  delay(2000);
  lcd.clear();

  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);

  for (int i = 1000; i < 1000 + records; i++) {
    if (EEPROM.read(i) == 0xff)
      EEPROM.write(i, 0);
  }

  finger.begin(57600);
  Serial.begin(9600);
  lcd.clear();
  lcd.print(" Initializing...");
  lcd.setCursor(0, 1);
  delay(2000);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
    lcd.clear();
    lcd.print(" Initialized");
    delay(2000);
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    lcd.clear();
    lcd.print("Module Not Found");
    lcd.setCursor(0, 1);
    lcd.print("Check Connections");
    while (1);
  }

  lcd.setCursor(0, 0);
  lcd.print("Starting System ");
  lcd.setCursor(0, 1);
  lcd.print("Made by: Group 2-DSA");
  delay(3000);

  user1 = EEPROM.read(1000);
  user2 = EEPROM.read(1001);
  user3 = EEPROM.read(1002);
  user4 = EEPROM.read(1003);
  user5 = EEPROM.read(1004);
  lcd.clear();
  digitalWrite(indFinger, HIGH);
}

void loop() {
  // Loop code
  lcd.clear();
  myRTC.updateTime();
  lcd.setCursor(0, 0);
  lcd.print(myRTC.dayofmonth);
  lcd.setCursor(0, 0);
  lcd.print("DATE: ");
  lcd.print(myRTC.dayofmonth);
  lcd.print("/");
  lcd.print(myRTC.month);
  lcd.print("/");
  lcd.print(myRTC.year);
  lcd.setCursor(0, 1);
  lcd.print("TIME: ");
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
  lcd.print(myRTC.seconds);
  delay(1000);
  int result = getFingerprintIDez();
  if (result > 0) {
    digitalWrite(indFinger, LOW);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    lcd.print("ID:");
    lcd.print(result);
    lcd.setCursor(0, 1);
    lcd.print("Please Wait....");
    delay(1000);
    attendance(result);
    lcd.clear();
    lcd.print("Attendance ");
    lcd.setCursor(0, 1);
    lcd.print("Registered");
    delay(1000);
    digitalWrite(indFinger, HIGH);
    return;
  }
  checkKeys();
  delay(300);
}

// Other functions can go here

void download(int eepIndex) {
  if (EEPROM.read(eepIndex) != 0xff) {
    Serial.print("T->");
    if (EEPROM.read(eepIndex) < 10)
      Serial.print('0');
    Serial.print(EEPROM.read(eepIndex++));
    Serial.print(':');
    if (EEPROM.read(eepIndex) < 10)
      Serial.print('0');
    Serial.print(EEPROM.read(eepIndex++));
    Serial.print(':');
    if (EEPROM.read(eepIndex) < 10)
      Serial.print('0');
    Serial.print(EEPROM.read(eepIndex++));
    Serial.print(" D->");
    if (EEPROM.read(eepIndex) < 10)
      Serial.print('0');
    Serial.print(EEPROM.read(eepIndex++));
    Serial.print('/');
    if (EEPROM.read(eepIndex) < 10)
      Serial.print('0');
    Serial.print(EEPROM.read(eepIndex++));
    Serial.print('/');
    Serial.print(EEPROM.read(eepIndex++) << 8 | EEPROM.read(eepIndex++));
  } else {
    Serial.print("---------------------------");
  }

  Serial.print(" ");
}

#include "AttendanceHandler.h"

AttendanceHandler::AttendanceHandler(virtuabotixRTC& rtc, LiquidCrystal_I2C& lcd) : rtc(rtc), lcd(lcd) {
}

AttendanceHandler::~AttendanceHandler() {
}

void AttendanceHandler::updateTime() {
  rtc.updateTime();
}

void AttendanceHandler::recordAttendance(int id) {
  lcd.clear();
  displayDateTime();
  lcd.setCursor(0, 1);
  lcd.print("ID:");
  lcd.print(id);
  lcd.setCursor(0, 1);
  lcd.print("Please Wait....");
  delay(1000);

  storeAttendance(id);

  lcd.clear();
  lcd.print("Attendance ");
  lcd.setCursor(0, 1);
  lcd.print("Registered");
  delay(1000);
}

void AttendanceHandler::displayDateTime() {
  lcd.setCursor(0, 0);
  lcd.print("DATE: ");
  lcd.print(rtc.dayofmonth);
  lcd.print("/");
  lcd.print(rtc.month);
  lcd.print("/");
  lcd.print(rtc.year);
  lcd.setCursor(0, 1);
  lcd.print("TIME: ");
  lcd.print(rtc.hours);
  lcd.print(":");
  lcd.print(rtc.minutes);
  lcd.print(":");
  lcd.print(rtc.seconds);
  delay(1000);
}

void AttendanceHandler::storeAttendance(int id) {
  int user = 0;
  int eepLoc = 0;

  if (id >= 1 && id <= 10) {
    eepLoc = (id - 1) * 7;
    user = EEPROM.read(1000 + id - 1);
  } else {
    return;
  }

  int eepIndex = (user * 7) + eepLoc;
  EEPROM.write(eepIndex++, rtc.hours);
  EEPROM.write(eepIndex++, rtc.minutes);
  EEPROM.write(eepIndex++, rtc.seconds);
  EEPROM.write(eepIndex++, rtc.dayofmonth);
  EEPROM.write(eepIndex++, rtc.month);
  EEPROM.write(eepIndex++, rtc.year >> 8);
  EEPROM.write(eepIndex++, rtc.year);

  EEPROM.write(1000 + id - 1, user + 1);
}

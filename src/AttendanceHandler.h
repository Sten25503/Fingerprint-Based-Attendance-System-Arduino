#ifndef ATTENDANCE_HANDLER_H
#define ATTENDANCE_HANDLER_H

#include <virtuabotixRTC.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

class AttendanceHandler {
public:
  AttendanceHandler(virtuabotixRTC& rtc, LiquidCrystal_I2C& lcd);
  ~AttendanceHandler();

  void updateTime();
  void recordAttendance(int id);

private:
  virtuabotixRTC& rtc;
  LiquidCrystal_I2C& lcd;

  void displayDateTime();
  void storeAttendance(int id);
};

#endif // ATTENDANCE_HANDLER_H

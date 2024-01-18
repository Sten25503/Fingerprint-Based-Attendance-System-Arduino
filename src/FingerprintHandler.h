#ifndef FINGERPRINT_HANDLER_H
#define FINGERPRINT_HANDLER_H

#include "Adafruit_Fingerprint.h"
#include <EEPROM.h>

class FingerprintHandler {
public:
  FingerprintHandler();
  ~FingerprintHandler();

  void begin();
  void enrollFingerprint();
  void deleteFingerprint();
  int getFingerprintID();

private:
  Adafruit_Fingerprint finger;
  int records;
  int userIDs[10];
  int eepromBaseAddress;

  void download(int eepIndex);
  void upload(int eepIndex);
};

#endif // FINGERPRINT_HANDLER_H

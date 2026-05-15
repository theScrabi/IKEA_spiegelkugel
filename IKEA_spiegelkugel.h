
#pragma once
#include "wled.h"

class L298NMotor {
private:
  int16_t internal_speed;

  byte in1Pin, in2Pin;
  byte speedPin;
#ifdef ARDUINO_ARCH_ESP32
  byte pwmChannel;
#endif
public:
  L298NMotor(byte in1Pin, byte in2Pin, byte speedPin);

  void setSpeed(int8_t speed);
  int8_t speed;
};


class IKEA_spiegelkugel : public Usermod
{
private:
  L298NMotor* openCloseMotor = nullptr;
  L298NMotor* rotationMotor = nullptr;
public:
  void setup();
  void loop();
};

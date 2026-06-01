
#pragma once
#include "wled.h"

class L298NMotor {
private:
  int16_t internal_speed;

  byte in1Pin, in2Pin;

public:
  L298NMotor(byte in1Pin, byte in2Pin);

  void setSpeed(int8_t speed);
  int8_t getSpeed();
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

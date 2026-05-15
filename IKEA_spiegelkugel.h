
#pragma once
#include "wled.h"

class IKEA_spiegelkugel : public Usermod
{
private:
public:
  void setup();
  void loop();
};

class L298NMotor {
private:
  byte in1Pin, in2Pin;
  byte speedPin;
public:
  L298NMotor(byte in1Pin, byte in2Pin, byte speedPin);
};

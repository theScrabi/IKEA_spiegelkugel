
#pragma once
#include "wled.h"


namespace {
// Open/close motor wiring
constexpr byte OPEN_CLOSE_IN1_PIN = 25;
constexpr byte OPEN_CLOSE_IN2_PIN = 26;

// Rotation motor wiring
constexpr byte ROTATION_IN1_PIN = 32;
constexpr byte ROTATION_IN2_PIN = 33;
} // namespace



class L298NMotor {
private:
  int16_t internal_speed;

  byte in1Pin, in2Pin;

public:
  L298NMotor(byte in1Pin, byte in2Pin);

  void setup();

  void setSpeed(int8_t speed);
  int8_t getSpeed();
};


class IKEA_spiegelkugel : public Usermod
{
private:
  L298NMotor openCloseMotor = L298NMotor(OPEN_CLOSE_IN1_PIN, OPEN_CLOSE_IN2_PIN);
  L298NMotor rotationMotor = L298NMotor(ROTATION_IN1_PIN,   ROTATION_IN2_PIN);
public:
  void setup();
  void loop();
};

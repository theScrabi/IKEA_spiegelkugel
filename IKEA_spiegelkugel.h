
#pragma once
#include "wled.h"


namespace {
// Open/close motor wiring
constexpr byte OPEN_CLOSE_IN1_PIN = 17;
constexpr byte OPEN_CLOSE_IN2_PIN = 18;

// Rotation motor wiring
constexpr byte ROTATION_IN1_PIN = 19;
constexpr byte ROTATION_IN2_PIN = 21;
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

  void registerWebHandlers();
public:
  void setup();
  void loop();
};

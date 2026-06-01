
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
  String name;

public:
  L298NMotor(byte in1Pin, byte in2Pin, String name);

  void setup();

  void setSpeed(int8_t speed);
  int8_t getSpeed() { return internal_speed / 2; }
};

class IKEA_spiegelkugel : public Usermod {
private:
  L298NMotor openCloseMotor =
      L298NMotor(OPEN_CLOSE_IN1_PIN, OPEN_CLOSE_IN2_PIN, "OpenClose");
  L298NMotor rotationMotor =
      L298NMotor(ROTATION_IN1_PIN, ROTATION_IN2_PIN, "Rotation");

  bool ledControlEnabled = true;
  uint8_t segmentId = 0;
  uint16_t pixelIndex = 0;

  uint32_t lastPixelColor = 0xFFFFFFFF;

  void registerWebHandlers();

public:
  void setup() override;
  void loop() override;
  void addToConfig(JsonObject &root) override;
  bool readFromConfig(JsonObject &root) override;
};

#include "IKEA_spiegelkugel.h"
#include "wled.h"

namespace {
// Open/close motor wiring
constexpr byte OPEN_CLOSE_IN1_PIN = 25;
constexpr byte OPEN_CLOSE_IN2_PIN = 26;

// Rotation motor wiring
constexpr byte ROTATION_IN1_PIN = 32;
constexpr byte ROTATION_IN2_PIN = 33;
} // namespace

L298NMotor::L298NMotor(byte in1Pin, byte in2Pin)
    : in1Pin(in1Pin), in2Pin(in2Pin) {
  PinManager::allocatePin(in1Pin, true, PinOwner::UM_Unspecified);
  PinManager::allocatePin(in2Pin, true, PinOwner::UM_Unspecified);

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}

void L298NMotor::setSpeed(int8_t speed) {
  internal_speed = speed * 2;
  if(speed < 0) {
    internal_speed = -internal_speed;
  }

  if(internal_speed == 0) {
    digitalWrite(in1Pin, 0);
    digitalWrite(in2Pin, 0);
  } else if(0 < internal_speed) {
    digitalWrite(in2Pin, 0);
    analogWrite(in1Pin, internal_speed);
  } else if (internal_speed < 0) {
    digitalWrite(in1Pin, 0);
    analogWrite(in2Pin, -internal_speed);
  }
}

int8_t L298NMotor::getSpeed() {
  return internal_speed;
}

void IKEA_spiegelkugel::setup() {
  openCloseMotor = new L298NMotor(OPEN_CLOSE_IN1_PIN, OPEN_CLOSE_IN2_PIN);
  rotationMotor  = new L298NMotor(ROTATION_IN1_PIN,   ROTATION_IN2_PIN);
}

void IKEA_spiegelkugel::loop() { Serial.println("Hallo jan"); }

static IKEA_spiegelkugel ikea_spiegelkugel;
REGISTER_USERMOD(ikea_spiegelkugel);

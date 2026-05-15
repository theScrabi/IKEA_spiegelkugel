#include "IKEA_spiegelkugel.h"

namespace {
// Open/close motor wiring
constexpr byte OPEN_CLOSE_IN1_PIN = 25;
constexpr byte OPEN_CLOSE_IN2_PIN = 26;
constexpr byte OPEN_CLOSE_SPEED_PIN = 27;

// Rotation motor wiring
constexpr byte ROTATION_IN1_PIN = 32;
constexpr byte ROTATION_IN2_PIN = 33;
constexpr byte ROTATION_SPEED_PIN = 13;
} // namespace

L298NMotor::L298NMotor(byte in1Pin, byte in2Pin, byte speedPin)
    : in1Pin(in1Pin), in2Pin(in2Pin), speedPin(speedPin) {
  PinManager::allocatePin(in1Pin, true, PinOwner::UM_Unspecified);
  PinManager::allocatePin(in2Pin, true, PinOwner::UM_Unspecified);
  PinManager::allocatePin(speedPin, true, PinOwner::UM_Unspecified);

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

#ifdef ARDUINO_ARCH_ESP32
  pwmChannel = PinManager::allocateLedc(1);
  ledcSetup(pwmChannel, 20000, 8); // 20 kHz, 8-bit duty (0..255)
  ledcAttachPin(speedPin, pwmChannel);
#else
  analogWriteRange(255);
  analogWriteFreq(WLED_PWM_FREQ);
  pinMode(speedPin, OUTPUT);
#endif
}

void L298NMotor::setSpeed(int8_t speed) {
  internal_speed = speed * 2;
  if(speed < 0) {
    internal_speed = -internal_speed;
  }

  
}

void IKEA_spiegelkugel::setup() {
  openCloseMotor = new L298NMotor(OPEN_CLOSE_IN1_PIN, OPEN_CLOSE_IN2_PIN,
                                  OPEN_CLOSE_SPEED_PIN);
  rotationMotor =
      new L298NMotor(ROTATION_IN1_PIN, ROTATION_IN2_PIN, ROTATION_SPEED_PIN);
}

void IKEA_spiegelkugel::loop() { Serial.println("Hallo jan"); }

static IKEA_spiegelkugel ikea_spiegelkugel;
REGISTER_USERMOD(ikea_spiegelkugel);

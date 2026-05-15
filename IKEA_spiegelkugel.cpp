#include "IKEA_spiegelkugel.h"


L298NMotor::L298NMotor(byte in1Pin, byte in2Pin, byte speedPin)
  : in1Pin(in1Pin), in2Pin(in2Pin), speedPin(speedPin)
{
  PinManager::allocatePin(in1Pin, true, PinOwner::UM_Unspecified);
  PinManager::allocatePin(in2Pin, true, PinOwner::UM_Unspecified);
  PinManager::allocatePin(speedPin, true, PinOwner::UM_Unspecified);

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

#ifdef ARDUINO_ARCH_ESP32
  pwmChannel = PinManager::allocateLedc(1);
  ledcSetup(pwmChannel, 20000, 8);   // 20 kHz, 8-bit duty (0..255)
  ledcAttachPin(speedPin, pwmChannel);
#else
  analogWriteRange(255);
  analogWriteFreq(WLED_PWM_FREQ);
  pinMode(speedPin, OUTPUT);
#endif
}

void IKEA_spiegelkugel::setup()
{
  // TODO: replace placeholder GPIOs with the real wiring
  openCloseMotor = new L298NMotor(/*in1*/ 25, /*in2*/ 26, /*speed*/ 27);
  rotationMotor  = new L298NMotor(/*in1*/ 32, /*in2*/ 33, /*speed*/ 13);
}

void IKEA_spiegelkugel::loop()
{
  Serial.println("Hallo jan");
}


static IKEA_spiegelkugel ikea_spiegelkugel;
REGISTER_USERMOD(ikea_spiegelkugel);

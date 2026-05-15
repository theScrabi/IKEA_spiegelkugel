#include "IKEA_spiegelkugel.h"


L298NMotor::L298NMotor() {

}

void IKEA_spiegelkugel::setup()
{
}

void IKEA_spiegelkugel::loop()
{
  Serial.println("Hallo jan");
}


static IKEA_spiegelkugel ikea_spiegelkugel;
REGISTER_USERMOD(ikea_spiegelkugel);

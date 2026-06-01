#include "IKEA_spiegelkugel.h"
#include "wled.h"
#include <cstdint>

L298NMotor::L298NMotor(byte in1Pin, byte in2Pin)
    : in1Pin(in1Pin), in2Pin(in2Pin) {}

void L298NMotor::setup() {
  PinManager::allocatePin(in1Pin, true, PinOwner::UM_Unspecified);
  PinManager::allocatePin(in2Pin, true, PinOwner::UM_Unspecified);

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}

void L298NMotor::setSpeed(int8_t speed) {
  internal_speed = speed * 2;

  if (internal_speed == 0) {
    analogWrite(in1Pin, 0);
    analogWrite(in2Pin, 0);
  } else if (0 < internal_speed) {
    analogWrite(in2Pin, 0);
    analogWrite(in1Pin, internal_speed);
  } else if (internal_speed < 0) {
    analogWrite(in1Pin, 0);
    analogWrite(in2Pin, -internal_speed);
  }
}

int8_t L298NMotor::getSpeed() { return internal_speed; }

namespace {
const char IKEA_UI_HTML[] PROGMEM = R"=====(<!DOCTYPE html>
<html><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>IKEA Spiegelkugel</title>
<style>
  body{font-family:sans-serif;background:#222;color:#eee;margin:0;padding:1.5em;max-width:32em}
  h1{font-size:1.2em;margin-top:0}
  label{display:block;margin:1.2em 0 .3em}
  input[type=range]{width:100%}
  output{float:right;font-variant-numeric:tabular-nums}
</style></head><body>
<h1>IKEA Spiegelkugel</h1>
<label>Open/Close <output id="oo">0</output></label>
<input type="range" id="o" min="-127" max="127" value="0">
<label>Rotation <output id="ro">0</output></label>
<input type="range" id="r" min="-127" max="127" value="0">
<script>
const o=document.getElementById('o'),r=document.getElementById('r');
const oo=document.getElementById('oo'),ro=document.getElementById('ro');
function send(){oo.textContent=o.value;ro.textContent=r.value;
  fetch('/ikea/set?o='+o.value+'&r='+r.value);}
o.oninput=()=>oo.textContent=o.value;r.oninput=()=>ro.textContent=r.value;
o.onchange=send;r.onchange=send;
</script></body></html>)=====";
}

void IKEA_spiegelkugel::registerWebHandlers() {
  // More specific path first: AsyncWebServer's `on()` prefix-matches
  // `_uri+"/"`, so `/ikea` would otherwise swallow `/ikea/set`.
  server.on("/ikea/set", HTTP_GET, [this](AsyncWebServerRequest *req) {
    if (req->hasParam("o")) {
      String value = req->getParam("o")->value();
      Serial.println("OpenClose: " + value);
      openCloseMotor.setSpeed(value.toInt());
    }
    if (req->hasParam("r")) {
      String value = req->getParam("r")->value();
      Serial.println("Rotation: " + value);
      rotationMotor.setSpeed(value.toInt());
    }
    req->send(200, "text/plain", "ok");
  });
  server.on("/ikea", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send_P(200, "text/html", IKEA_UI_HTML);
  });
}

void IKEA_spiegelkugel::setup() {
  openCloseMotor.setup();
  rotationMotor.setup();
  registerWebHandlers();
}

void IKEA_spiegelkugel::loop() {}

static IKEA_spiegelkugel ikea_spiegelkugel;
REGISTER_USERMOD(ikea_spiegelkugel);

#include <HCSR04.h>
//#include <Bounce.h>
int blinkPin = 13;
float data;
byte current_value;
byte previous_value;
const int channel = 1;
const int controller = 22;

UltraSonicDistanceSensor distanceSensor(0, 1);

void setup () {
  pinMode(blinkPin, OUTPUT);
  digitalWrite(blinkPin, HIGH);

}

void loop () {
  blink();
  usbMIDI.read(); 
  
  data = distanceSensor.measureDistanceCm();

  if (data >= 2.0 && data <= 32.0) {

    current_value = map(data, 2.0, 32.0, 0, 127);

    Serial.println(current_value);

    if (current_value != previous_value) {
      previous_value = current_value;
      usbMIDI.sendControlChange(controller, current_value, channel);
    }

    delay(5);
  }
}


void blink() {
  if (millis() % 2000 < 1000) {
    digitalWrite(blinkPin, LOW);
  } else {
    digitalWrite(blinkPin, HIGH);
  }
}

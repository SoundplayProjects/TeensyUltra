#include <HCSR04.h>
//#include <Bounce.h>
//
//#include <MIDI.h>
//
//MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
const int channel = 1;

float data;
byte current_value;
byte previous_value;
//const int channel = 1;
const int controller = 22;

UltraSonicDistanceSensor distanceSensor(0, 1);

void setup () {

}

void loop () {
  usbMIDI.read(); 
  
  data = distanceSensor.measureDistanceCm();

  if (data >= 2.0 && data <= 70.0) {

    current_value = map(data, 2.0, 70.0, 30, 85);

    Serial.println(current_value);

    if (current_value != previous_value) {

      usbMIDI.sendNoteOn( current_value, 100, channel);
      delay(100);
      usbMIDI.sendNoteOff( current_value, 100, channel);
      
       while (usbMIDI.read()) {
  }
      
      //previous_value = current_value;
      //usbMIDI.sendControlChange(controller, current_value, channel);
    }

    delay(5);
  }
}

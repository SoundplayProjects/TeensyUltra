#include <HCSR04.h>
const int channel = 3; // change channel valure here

float data;

float minimumDistance = 2.0; //change minimum distance here (cm)
float maximumDistance = 70.0; //change maximum distance here (cm)
byte current_value;
byte previous_value;
const int controller = 24; // change controlller value here

UltraSonicDistanceSensor distanceSensor(0, 1);

void setup () {

}

void loop () {
  usbMIDI.read(); 
  
  data = distanceSensor.measureDistanceCm();

 Serial.println(data);

  if (data >= minimumDistance && data <= maximimDistance) {

    current_value = map(data, minimumDistance, maximimDistance, 30, 85);

    Serial.println(current_value);

    if (current_value != previous_value) {

      usbMIDI.sendNoteOn( current_value, 100, channel);
      delay(100);
      usbMIDI.sendNoteOff( current_value, 100, channel);
      
       while (usbMIDI.read()) {
  }
      
    }

    delay(5);
  }
}

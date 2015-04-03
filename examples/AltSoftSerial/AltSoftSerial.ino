/**
I found AltSoftSerial more reliable than SoftwareSerial (depends on the version).
https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html

AltSoftSerial pins

Board              Transmit Pin  Receive Pin Unusable PWM
Teensy 3.0 & 3.1              21          20           22
Teensy 2.0                    9           10           (none)
Teensy++ 2.0                  25           4           26, 27
Arduino Uno                   9            8           10
Arduino Leonardo              5            13          (none)
Arduino Mega                  46           48          44, 45
Wiring-S                      5            6           4
Sanguino                      13           14          12
*/

#include <AltSoftSerial.h>
#include <Mindwave.h>

AltSoftSerial bluetooth;
Mindwave mindwave;

void setup() {
  bluetooth.begin(MINDWAVE_BAUDRATE);
}
void onMindwaveData(){
  Serial.print("\tquality: ");
  Serial.print(mindwave.quality());
  Serial.print("\tattention: ");
  Serial.print(mindwave.attention());
  Serial.print("\tmeditation: ");
  Serial.print(mindwave.meditation());
  Serial.print("\tlast update: ");
  Serial.print(mindwave.lastUpdate());
  Serial.print("ms ago");
  Serial.println();
}
void loop() {
  mindwave.update(bluetooth,onMindwaveData);
}
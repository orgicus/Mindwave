#include <AltSoftSerial.h>
#include <Mindwave.h>

AltSoftSerial bluetooth;
Mindwave mindwave;

void setup() {
  bluetooth.begin(MINDWAVE_BAUDRATE);
  Serial.begin(MINDWAVE_BAUDRATE);
}
void headset1Event(){
  Serial.print("headset 1");
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
void headset2Event(){
  Serial.print("headset 2");
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
  mindwave.update(bluetooth,headset1Event);
  mindwave.update(Serial,headset2Event);
}

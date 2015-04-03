#include <Mindwave.h>

Mindwave mindwave;

void setup() {
  Serial.begin(MINDWAVE_BAUDRATE);
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
  mindwave.update(Serial,onMindwaveData);
}

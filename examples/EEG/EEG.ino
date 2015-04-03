#include <Mindwave.h>

Mindwave mindwave;
int*     eeg;

void setup() {
  Serial.begin(MINDWAVE_BAUDRATE);
  Serial.println("delta\ttheta\tlowAlpha\thighAlpha\tlowBeta\thightBeta\tlowGamma\thighGamma");
}
void onMindwaveData(){
  eeg = mindwave.eeg();
  for(int i = 0 ; i < MINDWAVE_EEG_SIZE; i++){
    Serial.print(eeg[i]);
    if(i < MINDWAVE_EEG_SIZE) Serial.print('\t');
  }
  Serial.println();
  //alternatively get individual value via delta(),theta() ,lowAlpha() ,highAlpha() ,lowBeta() ,highBeta() ,lowGamma() ,midGamma() functions
}
void loop() {
  mindwave.update(Serial,onMindwaveData);
}

Mindwave Mobile Parser
======================

Simple parser for Mindwave Mobile EEG headsets.

This is a fork from orgicus master branch: https://github.com/orgicus/Mindwave

The new version includes now also eye blink detection!

How to install the library
==========================

1. [Download the library](https://github.com/AK-Homberger/Mindwave/archive/master.zip)
2. Unzip **Mindwave-master.zip** and rename the **Mindwave-master** folder to the **Mindwave**
4. Move the freshly renamed **Mindwave** folder into the **Documents/Arduino/libraries** and restart Arduino

Alternatively, you can simply copy the two files "Mindwave.h" and "Mindwave.cpp" to your sketch folder.

How to use the library
==========================
If you're using the Serial class and simply want to get the attention/meditation values,
it's as simple as this.

The example includes also eye blink detection. Single and double blink detection.

In the example a HC-05 is connected to Serial2 on an ESP32. But it should work for all Arduino/ESP boards using the Serial Class.

``` cpp
#include "Arduino.h"
#include "Mindwave.h"

Mindwave mindwave;

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  Serial2.begin(MINDWAVE_BAUDRATE);
}

void onMindwaveBlink() {
 if (mindwave.blink() == 1) {
    Serial.println();
    Serial.println("Single Blink!");
    Serial.println();   
  }
  
  if (mindwave.blink() == 2) {
    Serial.println();
    Serial.println("Double Blink!");
    Serial.println();
  }
}

void onMindwaveData() {
  Serial.print("Quality: ");
  Serial.println(mindwave.quality());
  Serial.print("Attention: ");
  Serial.println(mindwave.attention());
  Serial.print("Meditation: ");
  Serial.println(mindwave.meditation());  
  Serial.println();
}

void loop() {
  mindwave.update(Serial2, onMindwaveData, onMindwaveBlink);
}
```

For more examples go to **Arduino > File > Examples > Mindwave**

Notes
=====

The code is mostly based on the [official NeuroSky wiki article](http://developer.neurosky.com

Blink detection is based on this work: https://github.com/sumitnathtiwari/Eye_Blink

/docs/doku.php?id=mindwave_mobile_and_arduino) and the [ThinkGear protocol specs](http://developer.neurosky.com/docs/doku.php?id=thinkgear_communications_protocol#bit_raw_wave_value)


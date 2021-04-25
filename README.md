Mindwave Mobile Parser
======================

Simple parser for [Mindwave Mobile](https://store.neurosky.com/pages/mindwave) EEG headsets.

![Headset](http://neurosky.com/wp-content/uploads/2018/04/mindwave-mobile-headset1-300x300.jpg)

This is a fork from orgicus master branch: https://github.com/orgicus/Mindwave

The new version includes now also eye blink detection!

How to install the library
==========================

1. [Download the library](https://github.com/AK-Homberger/Mindwave/archive/master.zip)
2. Unzip **Mindwave-master.zip** and rename the **Mindwave-master** folder to **Mindwave**
4. Move the freshly renamed **Mindwave** folder into the **Documents/Arduino/libraries** and restart Arduino

Alternatively, you can simply copy the two files "Mindwave.h" and "Mindwave.cpp" to your sketch folder.

How to use the library
==========================
If you're using the Serial class and simply want to get the attention/meditation values,
it's as simple as shown below.

The example includes also eye blink detection. Single and double blink detection.

In the example a HC-05 Bluetooth module is connected to Serial2 on an ESP32. But it should work for all Arduino/ESP boards using the Serial class.

[Here](https://github.com/Thought-Controlled-Machine/TCM-REP/wiki/Configuring-HC05-for-Mindwave-Mobile-&-Data-Transfer) is explained how to prepare the HC-05 for connecting to the headset.

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
  //mindwave.update(Serial2, onMindwaveData);    // This works without blink detection 
  mindwave.update(Serial2, onMindwaveData, onMindwaveBlink); // This with blink detection. onMindwaveBlink is an optional parameter.
}
```

For more examples go to **Arduino > File > Examples > Mindwave**

Notes
=====

The code is mostly based on the [official NeuroSky wiki article](http://developer.neurosky.com/docs/doku.php?id=mindwave_mobile_and_arduino) and the [ThinkGear protocol specs](http://developer.neurosky.com/docs/doku.php?id=thinkgear_communications_protocol#bit_raw_wave_value)

Blink detection is based on the code shown here: https://github.com/orgicus/Mindwave/issues/5


//
//  Mindwave Mobile parser
//  Based on the Mindwave Arduino sample: http://developer.neurosky.com/docs/doku.php?id=mindwave_mobile_and_arduino
//  and the ThinkGear Protocol specs: http://developer.neurosky.com/docs/doku.php?id=thinkgear_communications_protocol
//  Created by George Profenza on 03/04/2015.
//

#ifndef Mindwave_h
#define Mindwave_h

#include <inttypes.h>
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

//baud rate
#define MINDWAVE_BAUDRATE				 57600
//states
#define MINDWAVE_WAIT_FOR_FIRST_A        0
#define MINDWAVE_WAIT_FOR_SECOND_A       1
#define MINDWAVE_WAIT_FOR_PAYLOAD_LENGTH 2
#define MINDWAVE_WAIT_FOR_PAYLOAD        3
#define MINDWAVE_WAIT_FOR_CHECKSUM       4
//EEG
#define MINDWAVE_EEG_SIZE				 8
#define MINDWAVE_PACKET_MAX_SIZE		 173
#define MINDWAVE_PAYLOAD_MAX_SIZE		 169

typedef void (*MindwaveDataCallback) ();

class Mindwave
{


  public:

    Mindwave();
    void update(Stream &stream,MindwaveDataCallback onData);
    int  attention();
    int  meditation();
    int  quality();
    long lastUpdate();
    int* eeg();
    int  delta();
    int  theta();
    int  lowAlpha();
    int  highAlpha();
    int  lowBeta();
    int  highBeta();
    int  lowGamma();
    int  midGamma();
  private:
    // checksum variables
    byte _generatedChecksum = 0;
    byte _checksum = 0; 
    int  _payloadLength = 0;
    int  _payloadIndex;
    byte _payloadData[MINDWAVE_PACKET_MAX_SIZE] = {0};
    
    byte _poorQuality = 0;
    byte _attention;
    byte _meditation;
    int  _eeg[MINDWAVE_EEG_SIZE];
    // system variables
    long _lastReceivedPacket = 0, _lastUpdate = 0;
    boolean _bigPacket = false;
    int _state = 0;
    
    void parsePayload(MindwaveDataCallback onData);

};

#endif
#include "Mindwave.h"

Mindwave::Mindwave() {}

void Mindwave::update(Stream &stream, MindwaveDataCallback onData, MindwaveBlinkCallback onBlink) {

  if ((millis() - piekTime) > 450 && piekDetected == true) {
    if(onBlink != NULL) onBlink();
    piekDetected = false;
  }

  if (stream.available() > 0) {
    switch (_state) {
      case MINDWAVE_WAIT_FOR_FIRST_A:
        if (stream.read() == 0xAA) _state = MINDWAVE_WAIT_FOR_SECOND_A;
        break;
      case MINDWAVE_WAIT_FOR_SECOND_A:
        if (stream.read() == 0xAA) _state = MINDWAVE_WAIT_FOR_PAYLOAD_LENGTH;
        break;
      case MINDWAVE_WAIT_FOR_PAYLOAD_LENGTH:
        _payloadLength = stream.read();
        if (_payloadLength > MINDWAVE_PAYLOAD_MAX_SIZE) {
          _state = MINDWAVE_WAIT_FOR_FIRST_A;
          return;
        }
        _generatedChecksum = _payloadIndex = 0;
        _state = MINDWAVE_WAIT_FOR_PAYLOAD;
        break;
      case MINDWAVE_WAIT_FOR_PAYLOAD:
        if (_payloadIndex < _payloadLength) {
          _payloadData[_payloadIndex] = stream.read();
          _generatedChecksum += _payloadData[_payloadIndex];
          _payloadIndex++;
        } else {
          _state = MINDWAVE_WAIT_FOR_CHECKSUM;
        }
        break;
      case MINDWAVE_WAIT_FOR_CHECKSUM:
        _checksum = stream.read();
        _generatedChecksum = 255 - _generatedChecksum;
        if (_checksum == _generatedChecksum) {
          parsePayload(onData, onBlink);
          _state = MINDWAVE_WAIT_FOR_FIRST_A;
        } else {
          _state = MINDWAVE_WAIT_FOR_FIRST_A;
        }
        break;
    }
  }
}


void Mindwave::parsePayload(MindwaveDataCallback onData, MindwaveBlinkCallback onBlink) {
  _poorQuality = 200;
  _attention = 0;
  _meditation = 0;
  for (int j = 0; j < MINDWAVE_EEG_SIZE; j++) _eeg[j] = 0;

  for (int i = 0; i < _payloadLength; i++) {   // Parse the payload
    switch (_payloadData[i]) {
      case 2:
        i++;
        _poorQuality = _payloadData[i];
        _bigPacket = true;
        break;
      case 4:
        i++;
        _attention = _payloadData[i];
        break;
      case 5:
        i++;
        _meditation = _payloadData[i];
        break;

      case 0x80:   // Raw data for blink
        if (_payloadData[i + 1] == 2) {
          Hilf = ((long)_payloadData[i + 2] * 256 + (long)_payloadData[i + 3]); // read the most significant two bytes and form a signed number of it
          if (Hilf > 32767) Hilf -= (long)(65535);
          Data[_i] = (int)Hilf;

          // PiekP is a gliding sum over 50 values of Data 71 values of Data in the past, 71 values are reserved for the minus peak PiekM
          PiekP += Data[(512 + _i - 71) % 512];
          PiekP -= Data[(512 + _i - 50 - 71) % 512];

          // Test, if PiekP exceeds a certain value and the youngest value of PiekP is negative and it has no huge values
          if ((PiekP > 3000) && (Data[(512 + _i  - 70) % 512] < 0) && (PiekP < 13000)) { // The next eye blink detection is enabled only after a certain elapse time

            if (millis() - piekTime > 100) { //time
              PiekM = 0;
              // After detecting a positive peak PiekP the following 70 values are summed up and tested, if more negative than a certain value
              for (int j = 1; j <= 70; j++)
                PiekM +=  (int)(Data[(512 + _i  + j - 70) % 512]);

              //Sometimes big negative numbers appear, which are suppressed by a limit for the negative values, if they are to huge
              if (PiekM < -3000 && PiekM > -11000) {

                if ((millis() - piekTime) < 400)_n++; else _n = 1;
                piekTime = millis();  // piekTime is the time at which the eye blink has been detected
                piekDetected = true;  // piekDetected is set true, when an eye blink has been detected

              }// end if PiekM (eyeblink detected)
            }//end elapse time
          }// end PiekP detect
          _i++;
          if (_i >= 512) _i = 0;
        }
        i = i + 3;
        break;

      case 0x83:
        i++;
        for (int j = 0; j < MINDWAVE_EEG_SIZE; j++) {
          _eeg[j] = ((int)_payloadData[++i] << 16) | ((int)_payloadData[++i] << 8) | (int)_payloadData[++i];
        }
        break;
      default:
        break;
    } // switch
  } // for loop
  if (_bigPacket) {
    _lastUpdate = millis() - _lastReceivedPacket;
    _lastReceivedPacket = millis();

    onData();
  }
  _bigPacket = false;
}


int Mindwave::attention() {
  return _attention;
}

int Mindwave::meditation() {
  return _meditation;
}

int Mindwave::quality() {
  return (100 - (_poorQuality / 2));
}

long Mindwave::lastUpdate() {
  return _lastUpdate;
}

int* Mindwave::eeg() {
  return _eeg;
}

int Mindwave::delta() {
  return _eeg[0];
}

int Mindwave::theta() {
  return _eeg[1];
}

int Mindwave::lowAlpha() {
  return _eeg[2];
}

int Mindwave::highAlpha() {
  return _eeg[3];
}

int Mindwave::lowBeta() {
  return _eeg[4];
}

int Mindwave::highBeta() {
  return _eeg[5];
}

int Mindwave::lowGamma() {
  return _eeg[6];
}

int Mindwave::midGamma() {
  return _eeg[7];
}

int Mindwave::blink() {
  return _n;


}

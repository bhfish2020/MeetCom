#include "MeetCom.h"

MeetCom::MeetCom() {
  _buffer = "";
}

void MeetCom::begin(long baudRate) {
  Serial.begin(baudRate);
}

void MeetCom::sendMessage(String message) {
  Serial.println(message);
}

String MeetCom::receiveMessage() {
  if (Serial.available()) {
    _buffer = Serial.readStringUntil('\n');
    return _buffer;
  }
  return "";
}

bool MeetCom::isMessageAvailable() {
  return Serial.available() > 0;
}

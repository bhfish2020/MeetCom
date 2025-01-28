#ifndef MEETCOM_H
#define MEETCOM_H

#include <Arduino.h>

class MeetCom {
  public:
    MeetCom();
    void begin(long baudRate);
    void sendMessage(String message);
    String receiveMessage();
    bool isMessageAvailable();
  private:
    String _buffer;
};

#endif

#ifndef MEETCOM_H
#define MEETCOM_H

#include <Arduino.h>

class MeetCom {
  public:
    MeetCom();
    void begin(long baudRate = 9600);
    
    // Command Functions
    void assignAddress(byte moduleId);
    void sendCommand(byte moduleId, byte function);
    void queryData(byte moduleId, byte channel);
    void broadcastRequest();
    
    // Response Handlers
    bool isResponseAvailable();
    String getResponse();
    
    // Module-specific Functions
    void setMultimeterMode(byte mode);
    void setFunctionGeneratorMode(byte mode, float value);
    void setOscilloscopeSettings(byte setting, float value);
    
  private:
    String _buffer;
    byte _moduleId;
    void sendPacket(char cmdType, byte moduleId, byte function, byte payloadLen = 0, String payload = "");
    String formatResponse(char cmdType, byte moduleId, byte payloadLen, String payload);
};

#endif

#include "MeetCom.h"

MeetCom::MeetCom() {
    _buffer = "";
    _moduleId = 0;
}

void MeetCom::begin(long baudRate) {
    Serial.begin(baudRate);
}

void MeetCom::assignAddress(byte moduleId) {
    _moduleId = moduleId;
    sendPacket('A', moduleId, 0x00);
}

void MeetCom::sendCommand(byte moduleId, byte function) {
    sendPacket('C', moduleId, function);
}

void MeetCom::queryData(byte moduleId, byte channel) {
    sendPacket('Q', moduleId, channel);
}

void MeetCom::broadcastRequest() {
    sendPacket('B', 0xFF, 0x01);
}

bool MeetCom::isResponseAvailable() {
    return Serial.available() > 0;
}

String MeetCom::getResponse() {
    if (Serial.available()) {
        _buffer = Serial.readStringUntil('\n');
        return _buffer;
    }
    return "";
}

MeetComResponse MeetCom::parseResponse(String response) {
    MeetComResponse result;
    
    // Check minimum length for valid response
    if (response.length() < 4) {
        return result;
    }
    
    // Parse command type
    result.cmdType = response.charAt(0);
    
    // Parse module ID (assuming hex format)
    String moduleIdStr = response.substring(1, 3);
    result.moduleId = (byte)strtol(moduleIdStr.c_str(), NULL, 16);
    
    // Parse function code
    if (response.length() >= 5) {
        String functionStr = response.substring(3, 5);
        result.function = (byte)strtol(functionStr.c_str(), NULL, 16);
    }
    
    // Parse payload length and payload if present
    if (response.length() >= 7) {
        String payloadLenStr = response.substring(5, 7);
        result.payloadLen = (byte)strtol(payloadLenStr.c_str(), NULL, 16);
        
        if (response.length() >= 7 + result.payloadLen) {
            result.payload = response.substring(7, 7 + result.payloadLen);
            result.isValid = true;
        }
    }
    
    return result;
}


void MeetCom::sendPacket(char cmdType, byte moduleId, byte function, byte payloadLen, String payload) {
    String packet = String(cmdType);
    packet += String(moduleId, HEX);
    packet += String(function, HEX);
    if (payloadLen > 0) {
        packet += String(payloadLen, HEX);
        packet += payload;
    }
    Serial.println(packet);
}

String MeetCom::formatResponse(char cmdType, byte moduleId, byte payloadLen, String payload) {
    String response = String(cmdType);
    response += String(moduleId, HEX);
    response += String(payloadLen, HEX);
    response += payload;
    return response;
}

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

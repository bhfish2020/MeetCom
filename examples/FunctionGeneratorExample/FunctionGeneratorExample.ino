#include <MeetCom.h>

MeetCom comm;

void setup() {
    comm.begin(9600);
    
    // Initialize as function generator with address 0x03
    comm.assignAddress(0x03);
    delay(100);
    
    // Set sine wave mode
    comm.sendCommand(0x03, 0x01);
}

void loop() {
    if (comm.isResponseAvailable()) {
        String response = comm.getResponse();
        Serial.println("Received: " + response);
    }
    
    // Handle incoming broadcast requests
    static unsigned long lastBroadcast = 0;
    if (millis() - lastBroadcast > 5000) {
        comm.broadcastRequest();
        lastBroadcast = millis();
    }
}

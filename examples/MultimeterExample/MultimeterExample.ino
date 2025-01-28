#include <MeetCom.h>

MeetCom comm;

void setup() {
    comm.begin(9600);
    
    // Initialize as multimeter with address 0x02
    comm.assignAddress(0x02);
    delay(100);
    
    // Set DC Voltage mode
    comm.sendCommand(0x02, 0x01);
}

void loop() {
    if (comm.isResponseAvailable()) {
        String response = comm.getResponse();
        Serial.println("Received: " + response);
    }
    
    // Query voltage reading every second
    static unsigned long lastQuery = 0;
    if (millis() - lastQuery > 1000) {
        comm.queryData(0x02, 0x01);
        lastQuery = millis();
    }
}

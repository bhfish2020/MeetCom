#include <MeetCom.h>

MeetCom comm;

void setup() {
  comm.begin(9600);
  comm.sendMessage("MeetCom initialized!");
}

void loop() {
  if (comm.isMessageAvailable()) {
    String message = comm.receiveMessage();
    comm.sendMessage("Received: " + message);
  }
  
  // Send a heartbeat message every 5 seconds
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 5000) {
    comm.sendMessage("Heartbeat");
    lastSend = millis();
  }
}

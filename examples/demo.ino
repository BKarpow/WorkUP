#include <Arduino.h>
#include <WorkUP.h>

void setup() {
  Serial.begin(115200);
  WUP.begin();

}

void loop() {
  if (WUP.tick()) {
    // Serial.print(WUP.getSecunds());
    // Serial.print(":");
    // Serial.print(WUP.getMinutes());
    Serial.println(WUP.getUpString());
  }

}

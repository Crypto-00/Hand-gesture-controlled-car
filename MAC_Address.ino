#include "WiFi.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.print("MAC Address: ");
  Serial.print(WiFi.macAddress());
}

void loop() {
  // put your main code here, to run repeatedly:

}

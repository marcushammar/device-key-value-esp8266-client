#include "DeviceKeyValue.h"

void setup() {
  String wifi_ssid = "ssid";
  String wifi_password = "password";
  String server = "server";
  String device = "device-01";
  String key = "test";
  String value = "it_works";

  Serial.begin(115200);

  DeviceKeyValue deviceKeyValue;

  Serial.print("Connecting to WiFi...");
  deviceKeyValue.connect(wifi_ssid, wifi_password, server);
  Serial.println(" done");

  Serial.print("Set a value on the server...");
  deviceKeyValue.setString(device, key, value);
  Serial.println(" done");

  Serial.print("Get a value from the server...");
  String output = deviceKeyValue.getString(device, key);
  Serial.println(" done");

  Serial.println("The response from the server was: " + output);
}

void loop() {

}

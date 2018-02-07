/*
 * Copyright 2018 Marcus Hammar
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

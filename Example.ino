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
  String fingerprint = "XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX";

  Serial.begin(115200);

  DeviceKeyValue deviceKeyValue;

  Serial.print("Connecting to WiFi...");
  deviceKeyValue.connectToWiFi(wifi_ssid, wifi_password);
  Serial.println(" done");

  Serial.print("Set HTTPS server...");
  deviceKeyValue.setServerHTTPS(server, fingerprint);
  Serial.println(" done");

  Serial.print("Set a value on the HTTPS server...");
  deviceKeyValue.setString("device-01", "test_key_https", "https_works");
  Serial.println(" done");

  Serial.print("Get a value from the HTTPS server...");
  String outputHTTPSServer = deviceKeyValue.getString("device-01", "test_key_https");
  Serial.println(" done");

  Serial.println("The response from the HTTPS server was: " + outputHTTPSServer);

  Serial.print("Set HTTP server...");
  deviceKeyValue.setServerHTTP(server);
  Serial.println(" done");

  Serial.print("Set a value on the HTTP server...");
  deviceKeyValue.setString("device-01", "test_key_http", "http_works");
  Serial.println(" done");

  Serial.print("Get a value from the HTTP server...");
  String outputHTTPServer = deviceKeyValue.getString("device-01", "test_key_http");
  Serial.println(" done");

  Serial.println("The response from the HTTP server was: " + outputHTTPServer);
}

void loop() {

}

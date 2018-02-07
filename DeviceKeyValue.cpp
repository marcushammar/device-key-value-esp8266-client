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

void DeviceKeyValue::connect(String ssid, String password, String newServer) {
  server = newServer;
  port = 443;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void DeviceKeyValue::setString(String device, String key, String value) {
  request(device, key, value);
}

String DeviceKeyValue::getString(String device, String key) {
  return request(device, key, "");
}

String DeviceKeyValue::request(String device, String key, String value) {
  WiFiClientSecure wiFiClientSecure;
  if (!wiFiClientSecure.connect(server.c_str(), port)) {
    return "ERROR (Device could not connect)";
  }

  String url1 = "/?device=";
  String url2 = device;
  String url3 = "&key=";
  String url4 = key;
  String url5 = "&value=";
  String url6 = value;

  String url = url1 + url2 + url3 + url4 + url5 + url6;

  String request1 = "GET ";
  String request2 = url;
  String request3 = " HTTP/1.1\r\nHost: ";
  String request4 = server;
  String request5 = "\r\nUser-Agent: ESP8266\r\nConnection: close\r\n\r\n";

  String request = request1 + request2 + request3 + request4 + request5;

  wiFiClientSecure.print(request);

  while (wiFiClientSecure.connected()) {
    String response = wiFiClientSecure.readStringUntil('\n');
    if (response == "\r") {
      break;
    }
  }

  String response = wiFiClientSecure.readStringUntil('\n');

  return response;
}

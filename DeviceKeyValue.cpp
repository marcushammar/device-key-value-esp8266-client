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

void DeviceKeyValue::connectToWiFi(String ssid, String password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void DeviceKeyValue::setServerHTTPS(String newServer, String newFingerprint) {
  useHTTPS = true;
  server = newServer;
  fingerprint = newFingerprint;
}

void DeviceKeyValue::setServerHTTP(String newServer) {
  useHTTPS = false;
  server = newServer;
}

void DeviceKeyValue::setString(String device, String key, String value) {
  request(device, key, value);
}

String DeviceKeyValue::getString(String device, String key) {
  return request(device, key, "");
}

String DeviceKeyValue::request(String device, String key, String value) {
  if (WiFi.status() != WL_CONNECTED) {
    return "ERROR (WiFi not connected)";
  }

  HTTPClient httpClient;

  String url1 = (useHTTPS) ? "https://" : "http://";
  String url2 = server;
  String url3 = "/?device=";
  String url4 = device;
  String url5 = "&key=";
  String url6 = key;
  String url7 = "&value=";
  String url8 = value;

  String url = url1 + url2 + url3 + url4 + url5 + url6 + url7 + url8;

  if (useHTTPS) {
    httpClient.begin(url, fingerprint);
  } else {
    httpClient.begin(url);
  }
  
  int httpResponseCode = httpClient.GET();

  String response;

  if (httpResponseCode > 0) {
    response = httpClient.getString();
  } else {
    response = String("ERROR (Could not connect to the server. Response code ") + httpResponseCode + ")";
  }

  httpClient.end();

  return response;
}

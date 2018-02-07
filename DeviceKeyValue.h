#ifndef DEVICEKEYVALUE_H
#define DEVICEKEYVALUE_H

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

class DeviceKeyValue {
public:
  void connect(String ssid, String password, String newServer);
  void setString(String device, String key, String value);
  String getString(String device, String key);

private:
  String request(String device, String key, String value);
  String server;
  int port;
};

#endif

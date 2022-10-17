#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "CredentialManager.h"
//#include "WiFiManager.h"
#include "NTP.h"
#include "AXP192.h"
#include <BleKeyboard.h>
#include <Preferences.h>
#define LED G10

#include <WiFi.h>
#include <DNSServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <ArduinoJson.h>

extern String name;
extern String manufacturer;
extern DNSServer dnsServer;
extern AsyncWebServer server;

extern BleKeyboard bleKeyboard;

extern RTC_TimeTypeDef rtc_time;
extern RTC_DateTypeDef rtc_date;

extern Credential credentials[100];
extern NTP ntp;
extern Preferences preferences;
extern String secretCode;
extern unsigned long oldTimestamp;
extern unsigned long timer;
extern bool configModeEnabled;
extern unsigned long n_credentials;
extern Credential currentCredential;
extern uint8_t timezone;
extern bool rgbHudEnabled;

void startWiFi();
void stopWiFi();
void setupServer();
void loadCredentials();
void vibrate(int);
bool isCharging();
float getBatteryLevel();

#endif



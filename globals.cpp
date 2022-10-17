#include "globals.h"
#include "ui_helpers.h"


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
    <html>
    <head>
        <title>{{name}}</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
            * {
                padding: 0px;
                margin: 0px;
            }

            body {
                background-color: #111;
                color: white;
            }

            .header {
                background-color: #003e33;
                height: 3em;
                text-align: center;
                padding-top: 1em;
                border-bottom: 1px solid #006e62 
            }

            .json {
                font-size: 1em;
                padding: 2em;
                width: 85%;
                margin-top: 2em;
                height: 45vh;
            }

            .container {
                padding-left: 1em;
                padding-right: 1em;
            }

            .button {
                border-radius: 5px;
                border: 1px solid #003e33;
                background-color: #006856;
                color: white;
                padding: 2em;
                font-size: 1em;
                font-weight: bold;
                text-transform: uppercase;
                display: block;
                width: 100%;
                margin-top: 2em;
            }
        </style>
    </head>
    <body>
        <nav class="header">
            <h1>{{name}}</h1>
        </nav>

        <div class="container">
            <form action="/setRTC">
                <input id="timestamp" type="hidden" name="timestamp" value="">
                <input class="button" type="submit" value="Set RTC">
            </form>

            <form action="/resetSecrets">
                <input class="button"  type="submit" value="Reset Credentials">
            </form>

            <form action="/setSecrets">
                <textarea class="json" type="text" name="data">
{{jsonData}}
                </textarea>
                <input class="button"  type="submit" value="Set Credentials">
            </form>
        </div>

        <script>
            function setTimestamp() {
                document.getElementById('timestamp').value = Math.floor(new Date().getTime()/1000);
            }

            setInterval(setTimestamp, 100);
            setTimestamp();
        </script>
    </body>
</html>)rawliteral";

String name = "CryptoCore";
String manufacturer = "localghost";
DNSServer dnsServer;
AsyncWebServer server(80);

BleKeyboard bleKeyboard(name.c_str(), manufacturer.c_str(), 100);

RTC_TimeTypeDef rtc_time;
RTC_DateTypeDef rtc_date;

Credential credentials[100];
NTP ntp;
Preferences preferences;
String secretCode = String("");
unsigned long oldTimestamp = 0;
unsigned long timer = 0;
bool configModeEnabled = false;
unsigned long n_credentials = 0;
uint8_t timezone = 1;
Credential currentCredential;
bool rgbHudEnabled = false;

class CaptiveRequestHandler : public AsyncWebHandler {
  public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}

    bool canHandle(AsyncWebServerRequest *request){
      //request->addInterestingHeader("ANY");
      return true;
    }

    void handleRequest(AsyncWebServerRequest *request) {
      String jsonData = preferences.getString("data", "{\"count\":0,\"list\":[]}");
      String renderedHTML = String(index_html);
      renderedHTML.replace("{{jsonData}}", jsonData);
      renderedHTML.replace("{{name}}", name);
      request->send_P(200, "text/html", renderedHTML.c_str()); 
    }
};

void startWiFi() {
  WiFi.mode(WIFI_AP); 
  WiFi.softAP(name.c_str());
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  setupServer();
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); //only when requested from AP
  server.begin();
}

void stopWiFi() {
  WiFi.softAPdisconnect(true);
  server.reset();
  dnsServer.stop();
}

void setupServer(){
  preferences.begin("storage", false);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      String jsonData = preferences.getString("data", "{\"count\":0,\"list\":[]}");
      String renderedHTML = String(index_html);
      renderedHTML.replace("{{jsonData}}", jsonData);
      renderedHTML.replace("{{name}}", name);
      request->send_P(200, "text/html", renderedHTML.c_str()); 
      Serial.println("Client Connected");
  });
    
  server.on("/setRTC", HTTP_GET, [] (AsyncWebServerRequest *request) {
      unsigned long timestamp;
      
      if (request->hasParam("timestamp")) {
        timestamp =  atol(String(request->getParam("timestamp")->value()).c_str())+1;
        ntp.setRTC(timestamp);
      }

      request->send(200, "text/html", "The Settings was successfully applied <br><a href=\"/\">Return to Home Page</a>");
      
      //configModeEnabled = false;
      delay(2000);
      M5.Axp.PowerOff();
  });

  server.on("/getSecrets", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String jsonData = preferences.getString("data", "{\"count\":0,\"list\":[]}");
    request->send(200, "text/html", jsonData);
  });

  
  server.on("/resetSecrets", HTTP_GET, [] (AsyncWebServerRequest *request) {
    preferences.putString("data", String("{\"count\":0,\"list\":[]}"));
    request->send(200, "text/html", "Ok");
    delay(2000);
    M5.Axp.PowerOff();
  });
  
  server.on("/setSecrets", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if (request->hasParam("data")) {        
      preferences.putString("data", String(request->getParam("data")->value()).c_str());
    }
    
    request->send(200, "text/html", "Ok");
    delay(2000);
    M5.Axp.PowerOff();
  });
}

void loadCredentials() {
  preferences.begin("storage", false);

  String json = preferences.getString("data", "{\"list\":[]}");
  DynamicJsonDocument doc(4096);
  deserializeJson(doc, json);
  JsonObject root = doc.as<JsonObject>();

  n_credentials = root["list"].size();

  String items = "";
  for(int i = 0; i < n_credentials; i++) {
    credentials[i] = Credential(root["list"][i]["name"].as<String>(), root["list"][i]["secret"].as<String>(), root["list"][i]["isOTP"].as<bool>());

    if(i == 0) {
      currentCredential = credentials[i];
      if(currentCredential.isOTP()) {
        lv_label_set_text(ui_Home_Label1, currentCredential.getSecret().c_str());
      }   
      else {
        lv_label_set_text(ui_Home_Label1, currentCredential.getName().c_str());
      }
    }

    if(i != 0) {
      items += "\n";
    }
    items += root["list"][i]["name"].as<String>();
  }

  lv_dropdown_set_options(ui_itemsDropdown, items.c_str());
}

float getBatteryCurrent() {
  M5.Axp.GetBatCurrent();
}

bool isCharging() {
  return M5.Axp.isCharging();
}

float getBatteryLevel() {
  float batVoltage = M5.Axp.GetBatVoltage();
  return ( batVoltage < 3.2 ) ? 0 : ( batVoltage - 3.2 ) * 100;
}

void vibrate(int ms) {
  M5.Axp.SetLDOEnable(3, true); 
  delay(ms);
  M5.Axp.SetLDOEnable(3, false);
}



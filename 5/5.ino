/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-async-web-server-espasyncwebserver-library/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char *ssid = "SeeMoo Master";
const char *password = "seemoo123";

const char *PARAM_INPUT_1 = "output";
const char *PARAM_INPUT_2 = "state";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
<h1>Async Webserver Test</h1>
13222046 - Nur Dawam Abdan Syakuro
13222067 - Goldwin Sonick Wijaya Thaha
</body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String &var)
{
    // Serial.println(var);
    return String();
}

String outputState(int output)
{
    if (digitalRead(output))
    {
        return "checked";
    }
    else
    {
        return "";
    }
}

void setup()
{
    // Serial port for debugging purposes
    Serial.begin(115200);

    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    pinMode(33, OUTPUT);
    digitalWrite(33, LOW);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }

    // Print ESP Local IP Address
    Serial.println(WiFi.localIP());

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", index_html, processor); });

    // // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    // server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request)
    //           {
    // String inputMessage1;
    // String inputMessage2;
    // // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    // if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
    //   inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
    //   inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
    //   digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    // }
    // else {
    //   inputMessage1 = "No message sent";
    //   inputMessage2 = "No message sent";
    // }
    // Serial.print("GPIO: ");
    // Serial.print(inputMessage1);
    // Serial.print(" - Set to: ");
    // Serial.println(inputMessage2);
    // request->send(200, "text/plain", "OK"); });

    // Start server
    server.begin();
}

void loop()
{
}
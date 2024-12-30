#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

#define LED_PIN 19

// WiFi Credentials
const char* ssid = "SeeMoo Master";
const char* password = "seemoo123";

WebServer server(80);
Preferences preferences;

// Variables for LED blinking
int onDuration = 500; // Default ON duration in ms
int offDuration = 500; // Default OFF duration in ms
bool ledState = false;

// HTML content
const char htmlPage[] = R"rawliteral(
<!DOCTYPE html>
<html>
<body style="display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100vh; margin: 0;">
<h1>LED Blink Configuration</h1>
<div style="text-align: center;">
  <label for="onDuration">ON Duration (ms):</label>
  <input type="number" id="onDuration" name="onDuration" value="%ON_DURATION%" style="margin: 10px;"><br>
  <label for="offDuration">OFF Duration (ms):</label>
  <input type="number" id="offDuration" name="offDuration" value="%OFF_DURATION%" style="margin: 10px;"><br>
  <button onclick="updateDurations()" style="margin-top: 20px; padding: 10px 20px;">Update</button>
</div>
<script>
function updateDurations() {
  const onDuration = document.getElementById('onDuration').value;
  const offDuration = document.getElementById('offDuration').value;
  fetch(`/update?onDuration=${onDuration}&offDuration=${offDuration}`)
    .then(response => response.text())
    .then(data => alert(data));
}
</script>
</body>
</html>
)rawliteral";

// Function prototypes
void setupWiFi();
void setupFlash();
void handleRoot();
void handleUpdate();
void handleLED();

void setup() {
  pinMode(LED_PIN, OUTPUT);
  setupWiFi();
  setupFlash();

  // Define web server routes
  server.on("/", handleRoot);
  server.on("/update", handleUpdate);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  handleLED();
}

void setupWiFi() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void setupFlash() {
  preferences.begin("led-config", false);
  onDuration = preferences.getInt("onDuration", 500);
  offDuration = preferences.getInt("offDuration", 500);

  Serial.print("Loaded ON duration: ");
  Serial.println(onDuration);
  Serial.print("Loaded OFF duration: ");
  Serial.println(offDuration);
}

void handleRoot() {
  String html = htmlPage;
  html.replace("%ON_DURATION%", String(onDuration));
  html.replace("%OFF_DURATION%", String(offDuration));
  server.send(200, "text/html", html);
}

void handleUpdate() {
  if (server.hasArg("onDuration") && server.hasArg("offDuration")) {
    onDuration = server.arg("onDuration").toInt();
    offDuration = server.arg("offDuration").toInt();

    preferences.putInt("onDuration", onDuration);
    preferences.putInt("offDuration", offDuration);

    Serial.print("Updated ON duration: ");
    Serial.println(onDuration);
    Serial.print("Updated OFF duration: ");
    Serial.println(offDuration);

    server.send(200, "text/plain", "Settings updated successfully!");
  } else {
    server.send(400, "text/plain", "Invalid input!");
  }
}

void handleLED() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  if (ledState && currentMillis - previousMillis >= onDuration) {
    ledState = false;
    digitalWrite(LED_PIN, LOW);
    previousMillis = currentMillis;
  } else if (!ledState && currentMillis - previousMillis >= offDuration) {
    ledState = true;
    digitalWrite(LED_PIN, HIGH);
    previousMillis = currentMillis;
  }
}

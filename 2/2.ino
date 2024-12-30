#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "SeeMoo Master";       // Masukkan SSID WiFi Anda
const char* password = "seemoo123"; // Masukkan password WiFi Anda

void setup() {
  Serial.begin(115200);

  // Hubungkan ke WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP Address: " + WiFi.localIP().toString());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { // Periksa koneksi WiFi
    HTTPClient http;

    // URL server tujuan
    http.begin("http://www.google.com"); // Bisa juga server lokal di jaringan Anda

    // Kirim permintaan GET
    int httpResponseCode = http.GET();

    // Baca respons server
    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println("Response:");
      Serial.println(payload);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    // Tutup koneksi
    http.end();
  }

  delay(10000); // Tunggu 10 detik sebelum mengulangi
}

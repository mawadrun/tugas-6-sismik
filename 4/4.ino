#include <WiFi.h>

// Konfigurasi WiFi
const char* ssid = "SeeMoo Master";
const char* password = "seemoo123";

// Inisialisasi WiFi server pada port 80
WiFiServer server(80);

void setup() {
    Serial.begin(115200);

    // --- Setup wifi ---
    // Menghubungkan ke WiFi
    Serial.print("Menghubungkan ke WiFi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi terhubung!");
    Serial.print("Alamat IP: ");
    Serial.println(WiFi.localIP());

    // Memulai server
    server.begin();
    Serial.println("Web server dimulai!");
}

const char index_html[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Kelompok</title>
</head>
<body style="display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; background-color: #f0f0f0;">
    <div style="text-align: center; font-size: 2em; color: #333;">
        <h1>Anggota Kelompok</h1>
        <p>Goldwin Sonick Wijaya Thaha / 13222067</p>
        <p>Nur Dawam Abdan Syakuro / 13222046</p>
    </div>
</body>
</html>
)rawliteral";

void loop() {
    // Cek jika ada client yang terhubung
    WiFiClient client = server.available();
    if (client) {
        Serial.println("Client terhubung.");
        String request = "";

        // Baca permintaan HTTP dari client
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                request += c;

                // Kirim respons
                if (request.endsWith("\r\n\r\n")) {
                // Header HTTP
                client.println("HTTP/1.1 200 OK");
                client.println("Content-Type: text/html");
                client.println("Connection: close");
                client.println();

                // Konten HTML
                client.println(index_html);
                break;
                }
            }
        }
        // Tunggu client memutuskan koneksi
        delay(10);
        client.stop();
        Serial.println("Client terputus.");
    }
}

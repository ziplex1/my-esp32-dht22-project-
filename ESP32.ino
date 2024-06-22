#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Konfigurasi WiFi
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// URL server lokal
const char* serverName = "http://192.168.1.2:5000/data";

// Konfigurasi sensor DHT
#define DHTPIN 15 // Pin yang terhubung dengan DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Menghubungkan ke WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Mengambil data dari sensor DHT
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Memastikan pembacaan berhasil
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Memastikan ESP32 terhubung ke WiFi
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Mengubah data ke format JSON
    String httpRequestData = "{\"temperature\": " + String(t) + ", \"humidity\": " + String(h) + "}";

    // Mengirimkan data POST
    int httpResponseCode = http.POST(httpRequestData);

    // Mencetak respons HTTP ke serial monitor
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    // Mengakhiri koneksi
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  // Delay sebelum pengulangan berikutnya
  delay(10000); // Mengirimkan data setiap 10 detik
}

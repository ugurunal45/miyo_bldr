#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// User configuration
const char *ssid = "YOUR_SSID"; // WiFi SSID
const char *password = "YOUR_PASSWORD"; // WiFi Password

// OpenWeatherMap API settings
const char *apiKey = "YOUR_API_KEY"; // API Key for OpenWeatherMap
const char *cityId = "city_id_for_manisa"; // City ID for Manisa

// OLED Display settings
Adafruit_SH110X display = Adafruit_SH110X(128, 64);

// NTP Client settings
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() {
  Serial.begin(115200);
  display.begin();
  display.clearDisplay();

  // Show boot screen
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("MIYO BLDR");
  display.display();
  delay(2000);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize NTP Client
  timeClient.begin();
  timeClient.setTimeOffset(10800);
  timeClient.update();

  // Retrieve weather data
  getWeatherData();
}

void loop() {
  // Update time
  timeClient.update();
  displayTime();
  checkButton();
  delay(1000);
}

void displayTime() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Time: ");
  display.print(timeClient.getFormattedTime());
  display.display();
}

void checkButton() {
  // Logic for button testing (short/long press)
  // Implement button debouncing and press detection logic here
}

void getWeatherData() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://api.openweathermap.org/data/2.5/weather?id=" + String(cityId) + "&appid=" + String(apiKey));
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
      // Parse JSON and display
    }
    http.end();
  }
}

// Function for simple eye animation
void simpleEyeAnimation() {
  // Implement eye animation logic here
}
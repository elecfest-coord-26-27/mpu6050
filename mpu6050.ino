#include <WiFi.h>
#include <WebServer.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

const char* ssid = "Excitel_Bharadwaj. 4G";
const char* password = "Pranavanath";

WebServer server(80);
MPU6050 mpu(Wire);

void handleRoot() {
  // Update the sensor values from the chip
  mpu.update();

  // Pure, basic HTML with standard layout boxes (Tables)
  String html = "<!DOCTYPE html><html>";
  html += "<head>";
  html += "<meta http-equiv=\"refresh\" content=\"0.33\">"; // Set to a stable 1 second refresh rate
  html += "<title>MPU6050 Data</title>";
  html += "</head>";
  html += "<body>";
  
  html += "<h2>ESP32 MPU-6050 Raw Telemetry</h2>";

  // Box 1: Accelerometer Data (Multiplied by 9.81 to match your original m/s² units)
  html += "<table border=\"1\" cellpadding=\"10\" style=\"margin-bottom: 20px; width: 300px;\">";
  html += "<tr><th><b>ACCELEROMETER (m/s&sup2;)</b></th></tr>";
  html += "<tr><td>X: " + String(mpu.getAccX() * 9.81, 2) + "</td></tr>";
  html += "<tr><td>Y: " + String(mpu.getAccY() * 9.81, 2) + "</td></tr>";
  html += "<tr><td>Z: " + String(mpu.getAccZ() * 9.81, 2) + "</td></tr>";
  html += "</table>";

  // Box 2: Gyroscope Data (Multiplied by 0.01745 to match your original rad/s units)
  html += "<table border=\"1\" cellpadding=\"10\" style=\"width: 300px;\">";
  html += "<tr><th><b>GYROSCOPE (rad/s)</b></th></tr>";
  html += "<tr><td>X: " + String(mpu.getGyroX() * 0.01745, 2) + "</td></tr>";
  html += "<tr><td>Y: " + String(mpu.getGyroY() * 0.01745, 2) + "</td></tr>";
  html += "<tr><td>Z: " + String(mpu.getGyroZ() * 0.01745, 2) + "</td></tr>";
  html += "</table>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}
void setup() {

  Wire.begin(21,22);
  Serial.begin(115200);

  mpu.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("wifi not connected");
  }
  Serial.println("\nConnected!");
  Serial.print("Go to this IP link on your laptop: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();


}



void loop() {
  server.handleClient();
}

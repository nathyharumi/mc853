// Import required libraries
#include <ESP8266WiFi.h>

WiFiClient client;

String ip = "";
int test = 1;
bool hostConnect(const char* host, int port) {
  Serial.print("Connecting to ");
  Serial.println(host);
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay (5000);
    return false;
  }
  return true;
}

String getWebpage() {
  String webpage = "";
  while (!client.available()) {
    delay(1);
  }
  while (client.available()) {
    String line = client.readStringUntil('\r');
    webpage += line;
  }
}

String getIp(String webpage) {
  return webpage;
}

void sendIP() {
  client.println(ip);
  Serial.println("Sent to Xaveco: " + client.readString());
}

void setup() {
  Serial.println(test);
  test += 1;
  Serial.println(test);
  // WiFi parameters
  const char* ssid = "aula-ic3";
  const char* password = "iotic@2019";

  // Start Serial
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  Serial.println(test);
  // Host to get the IP
  const char* identmeHost = "ident.me";
  const int identmePort = 80;

  // Host to send the IP
  const char* xavecoHost = "";
  const int xavecoPort = 50007;

  // Only connects to ident.me if it does not know the IP or if reseted
  if (ip.length() == 0) {
    // Connect to the ident.me
    if (!hostConnect(identmeHost, identmePort)) {
      return;
    }

    // Get the IP from the ident.me
    ip = getIp(getWebpage());

    // Close connection
    client.stop();
  }
  // Connect to Xaveco
  if (!hostConnect(xavecoHost, xavecoPort)) {
    return;
  }

  // Send IP to Xaveco
  sendIP();

  client.stop();

}

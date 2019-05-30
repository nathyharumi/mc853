// Import required libraries
#include <ESP8266WiFi.h>

WiFiClient client;

String ip = "";

String getIp(String webpage) {
  String webip = webpage.substring(webpage.lastIndexOf("."));
  Serial.println(webip);
  return webpage;
}

void setup() {
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
  // Host to get the IP
  const char* identmeHost = "ident.me";
  const int identmePort = 80;

  // Host to send the IP
  const char* xavecoHost = "";
  const int xavecoPort = 50007;

  // Only connects to ident.me if it does not know the IP or if reseted
  if (ip.length() == 0) {
    
    // Connect to the ident.me
    if (!client.connect(identmeHost, identmePort)) {
      Serial.println("connection failed");
      delay (5000);
      return;
    }
    // This will send the request to the server
    client.print(String("GET /") + " HTTP/1.1\r\n" +
                 "Host: " + identmeHost + "\r\n" +
                 "Connection: close\r\n\r\n");
    delay(10);

    // Get the all html content from the ident.me
    String webpage = "";
    while (!client.available()) {
      delay(1);
    }
    while (client.available()) {
      String line = client.readStringUntil('\r');
      webpage += line;
    }

    // Get the IP from the webpage content
    ip = getIp(webpage);

    // Close connection
    client.stop();
  }
  
    // Connect to the Xaveco Server
    if (!client.connect(xavecoHost, xavecoPort)) {
      Serial.println("connection failed");
      delay (5000);
      return;
    }

    // Send IP to Xaveco
    client.println(ip);

  client.stop();

}

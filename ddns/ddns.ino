// Import required libraries
#include <ESP8266WiFi.h>
#define MINUTES 60000000

WiFiClient client;

String ip = "";

inline void print_connection(const char* host, const int port){
  Serial.print("Conectando ao host ");
  Serial.print(host);
  Serial.print(", porta ");
  Serial.println(port); 
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
  Serial.print("WIFI conectando a");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
}

void loop() {
  // Host to get the IP
  const char* identmeHost = "ident.me";
  const int identmePort = 80;

  // Host to send the IP
  const char* xavecoHost = "143.106.16.163";
  const int xavecoPort = 50007;

  // Only connects to ident.me if it does not know the IP or if reseted
  if (ip.length() == 0) {

    // Connect to the ident.me
    print_connection(identmeHost, identmePort);
    if (!client.connect(identmeHost, identmePort)) {
      Serial.println("Falha de conexão.");
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
    String webpage_lines = webpage;
    int ip1 = 0, ip2 = 0, ip3 = 0, ip4 = 0;
    int index = 0;

    sscanf(webpage_lines.c_str(), "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);
    while (ip1 == 0 && ip2 == 0 && ip3 == 0 && ip4 == 0 && index > -1) {
      index = webpage_lines.indexOf("\n");
      webpage_lines = webpage_lines.substring(index + 1);
      sscanf(webpage_lines.c_str(), "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);
    }
    ip = String(ip1) + String('.') + String(ip2) + String('.') + String(ip3) + String('.') + String(ip4);
    Serial.print("IP obtido pelo host: ");
    Serial.println(ip);

    // Close connection
    client.stop();
  } else {
    Serial.print("IP obtido anteriormente: ");
    Serial.print(ip);
    Serial.println("; Sem necessidade de obtenção do IP novamente.");
  }

  // Connect to the Xaveco Server
  print_connection(xavecoHost, xavecoPort);
  if (!client.connect(xavecoHost, xavecoPort)) {
    Serial.println("Falha de conexão.");
    delay (5000);
    return;
  }

  // Send IP to Xaveco
  client.print(ip);
  client.stop();
  Serial.println("IP enviado com sucesso. Repouso de 15 minutos.");
  ESP.deepSleep(5*MINUTES/60,WAKE_NO_RFCAL);
  //ESP.deepSleep(15 * MINUTES,WAKE_NO_RFCAL); // convert to microsecs

}

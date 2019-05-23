#include <ESP8266WiFi.h>

// Luís Fernando V. Silva, 173170
// Nathália Harumi, 175188

#define Show(string,val)Serial.print(string);Serial.println(val); //macro for common print case
const char* ssid = "tropico-de-capricornio";     // WiFi parameters
const char* password = "elevador";

WiFiClient client;        // and one of client to talk to echoclient

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);    //WiFi connect
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Show("local IP= ",WiFi.localIP());

}

void loop() {
  Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect("192.168.43.85", 50007)) {
      Serial.println("connected");
      int count=0;
      for(int ct=0; ct < 8; ct++){
        client.println("Hello mc853 " + String(ct));
        //delay(1000);
        String req = client.readString(); //Until('\n'); in this call
        count++;
        Serial.print(req);
      }
      client.stop();
      Serial.println("Disconnected");
      Serial.println("Number of lines: " + String(count));
    }
    delay(4000);
}

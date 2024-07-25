#include <WiFi.h>
#include <PubSubClient.h>

// Replace with your network credentials
const char* ssid = "wifitiga";
const char* password = "sangatrahasia";

// Replace with your MQTT broker's credentials
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic = "/sic5/maalma/metal_detection";

#define SENSOR_PIN 4
#define OUTPUT_PIN 19

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
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

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("alatscanner123")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
     reconnect();
   }
   client.loop();

  int input = digitalRead(SENSOR_PIN);
  Serial.print("INPUT : ");
  Serial.println(input);
  if (input == LOW) {
    digitalWrite(OUTPUT_PIN, LOW);
     String payload = "detected";
     client.publish(mqtt_topic, (char*) payload.c_str());
  } else {
    digitalWrite(OUTPUT_PIN, HIGH);
  }
  delay(10);
}

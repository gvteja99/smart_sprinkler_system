#include <WiFi.h>
#include <PubSubClient.h>
/****************************************
* Define Constants
****************************************/
#define WIFISSID "Devilscore" // Put your WifiSSID here
#define PASSWORD "password" // Put your wifi password here
#define TOKEN "BBFF-IC2ALCb76kQ2K8ZpniTSj8AEBD1G14" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "zpjhAhxrOv" // MQTT client Name, please enter your own 8-12
alphanumeric character ASCII string;
//it should be a random and unique ascii string and different from all other devices
#define VARIABLE_LABEL "soil-sensor2" // Assign the variable label
#define VARIABLE_LABEL_SUBSCRIBE "relay2" // Assign the variable label
#define DEVICE_LABEL "esp32d2" // Assig the device label
#define RELAY 23 // Set the pin 23 as RELAY
#define SENSOR 35 // Set the pin 35 as SENSOR
char mqttBroker[] = "industrial.api.ubidots.com";
char payload[100];
char topic[150];
char topicSubscribe[100];
char str_sensor[10];
/****************************************
* Auxiliar Functions
****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);
void callback(char* topic, byte* payload, unsigned int length) {
char p[length + 1];
memcpy(p, payload, length);
p[length] = NULL;
String message(p);
// functioning of relay
//if msg is ‘0’ it means that there is very high moisture and relay is controlled accordingly
to our necessary.
if (message == "0") {
digitalWrite(RELAY, LOW);
} else {
digitalWrite(RELAY, HIGH);
}
Serial.write(payload, length);
Serial.println();
}
13
void reconnect() {
// Loop until we're reconnected
while (!client.connected()) {
Serial.println("Attempting MQTT connection...");
// Attemp to connect
if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
Serial.println("Connected");
client.subscribe(topicSubscribe);
} else {
Serial.print("Failed, rc=");
Serial.print(client.state());
Serial.println(" try again in 2 seconds");
// Wait 2 seconds before retrying
delay(2000);
}
}
}
/****************************************
* Main Functions
****************************************/
void setup() {
Serial.begin(115200);
WiFi.begin(WIFISSID, PASSWORD);
// Assign the pin as OUTPUT
pinMode(RELAY, OUTPUT);
pinMode(SENSOR, INPUT);
Serial.println();
Serial.print("Wait for WiFi...");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println("");
Serial.println("WiFi Connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
client.setServer(mqttBroker, 1883);
client.setCallback(callback);
sprintf(topicSubscribe, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE);
client.subscribe(topicSubscribe);
}
void loop() {
if (!client.connected()) {
reconnect();
client.subscribe(topicSubscribe);
}
sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
14
sprintf(payload, "%s", ""); // Cleans the payload
sprintf(payload, "{\"%s\":", VARIABLE_LABEL); // Adds the variable label
float sensor = analogRead(SENSOR);
/* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
dtostrf(sensor, 4, 2, str_sensor);
sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
Serial.println("Publishing data to Ubidots Cloud");
client.publish(topic, payload);
client.loop();
delay(1000);
}

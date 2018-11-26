#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

const size_t bufferSize = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3) + 60;
DynamicJsonBuffer jsonBuffer(bufferSize);

const char *json = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.75608,2.302038]}";

JsonObject &root = jsonBuffer.parseObject(json);

const char *ssid = "ramzes";
const char *password = "artemida131990";

String form = "<form action='led'><input type='radio' name='state' value='1' checked>On<input type='radio' name='state' value='0'>Off<input type='submit' value='Submit'></form>";

// HTTP server will listen at port 80
ESP8266WebServer server(80);

const int led = 13;

void handle_adc()
{
  float val = analogRead(0);
  server.send(200, "text/plain", String(val));
}

void handle_led()
{
  // get the value of request argument "state" and convert it to an int
  int state = server.arg("state").toInt();

  digitalWrite(led, state);
  server.send(200, "text/plain", String("LED is now ") + ((state) ? "on" : "off"));
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println("");
  pinMode(led, OUTPUT);

  // Connect to WiFi network
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up the endpoints for HTTP server
  //
  // Endpoints can be written as inline functions:
  server.on("/", []() {
    server.send(200, "text/html", form);
  });

  // And as regular external functions:
  server.on("/adc", handle_adc);
  server.on("/led", handle_led);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  // check for incomming client connections frequently in the main loop:
  server.handleClient();
}
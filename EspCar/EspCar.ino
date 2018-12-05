#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Car.h>

const char *ssid = "ramzes";
const char *password = "artemida131990";

MotorController *lMotor = new MotorController(4, 5, "lm");
MotorController *rMotor = new MotorController(12, 14, "rm");
Car *car = new Car(lMotor, rMotor);

// HTTP server will listen at port 80
ESP8266WebServer server(80);

const int led = 13;

void handle_move()
{
  int speed = server.arg("speed").toInt();
  int directionAngle = server.arg("angle").toInt();

  Serial.println(speed);
  Serial.println(directionAngle);
  car->move(speed, directionAngle);

  server.send(200, "text/plain", "ok");
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

  // And as regular external functions:
  server.on("/", handle_move);
  server.on("/move", handle_move);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  // Start the server
  server.begin();
  Serial.println("HTTP server started");

  car->setup(true);
}

void loop(void)
{
  // check for incomming client connections frequently in the main loop:
  server.handleClient();
}
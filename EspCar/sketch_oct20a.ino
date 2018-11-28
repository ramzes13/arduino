// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>

// const char *ssid = "ramzes";
// const char *password = "artemida131990";

// WiFiServer server(80);

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println();

//   Serial.printf("Connecting to %s ", ssid);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println(" connected");

//   server.begin();
//   Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
// }

// void loop()
// {
//   WiFiClient client = server.available();
//   // wait for a client (web browser) to connect
//   if (!client)
//   {
//     return;
//   }

//   Serial.println("\n[Client connected]");
//   while (client.connected())
//   {
//     // read line by line what the client (web browser) is requesting
//     if (client.available())
//     {
//       String line = client.readStringUntil('\r');
//       Serial.print(line);
//       // wait for end of client's request, that is marked with an empty line
//       if (line.length() == 1 && line[0] == '\n')
//       {
//         Serial.println("send data back!!");
//         //        Serial.println(prepareHtmlPage());
//         String response = "<!DOCTYPE HTML>\r\n<html><h1>Hello World!</h1></html>\r\n";
//         client.printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %u\r\n\r\n%s",
//                       response.length(), response.c_str());
//         client.flush();
//         break;
//       }
//     }
//   }
//   delay(1000); // give the web browser time to receive the data

//   // close the connection:
//   client.stop();
//   Serial.println("[Client disonnected]");
// }

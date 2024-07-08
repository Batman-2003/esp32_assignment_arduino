/*
  Written by Gaurav Khaire for Technical Assignment
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#define PORT 80

// TODO: 1. Don't HardCode WiFi Credentials
const char* SSID = "ABOIT_SSID";
const char* PASS = "ABOIT_PASS";

WiFiServer server(PORT);

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  if (!WiFi.softAP(SSID, PASS))
  {
    Serial.println("Error While Setting up Access Point");
    while (1) // Keep Blinking the Built-In Led to show Error
    {
      digitalWrite(BUILTIN_LED, HIGH);
      delay(100);
      digitalWrite(BUILTIN_LED, LOW);
      delay(100);
    }
    
  }
  IPAddress AP_IP = WiFi.softAPIP();
  Serial.print("Access Point IP Address is : ");
  Serial.println(AP_IP);

  // TODO: Experiment with different and no port numbers
  server.begin(PORT);

}

void loop()
{
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("New Client ");
    String currentLine = "";
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        currentLine += c;
        if (c == '\n')
        {
          if (currentLine.length() == 2)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type: text/html");
            client.println("Connection: close");
            client.println();

            client.println("<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
            client.println("<body><h1>Hello World</h1></body></html>");

            // Two Blank Lines Stop the HTTP Response
            client.println();

            break;
          }
          else 
          {
            // Only a Newline, therefore clear the currentLine buffer
            currentLine = "";
          }
        } 
        else if (c != '\r')
        {
          currentLine += c;
        }
      }

    }

    // Destroy the Server
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
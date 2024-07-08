#include "pgmspace.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#define contactMode 1
#define projectMode 2
#define educationMode 3

const char* SSID = "ABIOTS_TEST";
const char* PASS = "ABIOTS_PASSWORD";


IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80); //PORT = 80

String core PROGMEM = R"rawliteral(
<html lang="en">
<head><link href='https://fonts.googleapis.com/css?family=JetBrains Mono' rel='stylesheet'>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<style>html{font-family:'JetBrains Mono';padding-top:2cm;padding-left:20%;padding-right:20%;background-color:#071952;color:whitesmoke}header{text-align:center}aside{float:right}article{float:left}img{border-radius:50px}ul{line-height:32px}a{text-decoration:none}.button{font-size:24px;background-color:#088395;color:whitesmoke;cursor:pointer;text-decoration:none;border-radius:10px;padding:10px}</style></head>
<body><header><h2>Gaurav Khaire</h2>
<i><h2>Embedded Engineer</h2></i></header>
)rawliteral";

String contact PROGMEM = R"rawliteral(
<nav><a href="/EduBtn"><button class="button" id="EduBtn">Education</button></a>
<a href="/PrjBtn"><button class="button" id="PrjBtn" >Projects</button></a></nav>
<article><div id="Contact">
<h2>Contact &nbsp;: </h2> <br>
<ul><li>Email: <a style="color:aquamarine">g4ur4v03@gmail.com</a></li>
<li>Github: <a href="https://github.com/Batman-2003" style="color:aquamarine">https://github.com/Batman-2003</a></li>
<li>Youtube: <a href="https://youtube.com/@gauravkhaire56" style="color:aquamarine">https://youtube.com/@gauravkhaire56</a></li>
<li>Phone: +91 7498782508</li>
</ul></div></article></body></html>
)rawliteral";

String project PROGMEM = R"rawliteral(
<nav><a href="/EduBtn"><button class="button" id="EduBtn">Education</button></a>
<a href="/ContBtn"><button class="button" id="ContBtn">Contact</button></a></nav>
<article><div id="Prj"><h2>Projects : </h2> <br><ol>
<li>ESP32 Webserver (THIS PROJECT):
<ul><li>Code: <a href="https://github.com/Batman-2003/esp32_assignment_arduino" style="color:aquamarine">github.com/Batman-2003/esp32_assignment_arduino</a></li>
<li>Video: --</li>
<li>Description: A simple Webserver on ESP32 Running on PORT 80.</li>
<li>Hardware: ESP32</li>
<li>Software: Platformio, Framework: Arduino</li></ul></li></ol></div>
</article></body></html>
)rawliteral";

String education PROGMEM = R"rawliteral(
<nav><a href="/PrjBtn"><button class="button" id="PrjBtn">Projects</button></a>
<a href="/ContBtn"><button class="button" id="ContBtn">Contact</button></a></nav>
<article><div id="Edu"><h2>Education: </h2>
<ul><li>Till Std.X &nbsp;: Swami Muktanand English Medium, Yeola</li>
<ul><li>Percentage: 90.40%</li></ul>
<li>Till Std.XII: Swami Muktanand Jr. College, Yeola </li>
<ul><li>Percentage: 88.33%</li></ul>
<li>B.Tech METX : Sanjivani College of Engg, Kopargaon</li>
<ul><li>CGPA(Till Sem-V): 9.01</li></ul></ul></div></article></body></html>
)rawliteral";

void handleContact(void);
void handleProject(void);
void handleEducation(void);
void handleNotfound(void);

void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(BUILTIN_LED, OUTPUT);

  WiFi.softAP(SSID, PASS);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handleContact);
  server.on("/ContBtn", handleContact);
  server.on("/PrjBtn", handleProject);
  server.on("/EduBtn", handleEducation);
  server.onNotFound(handleNotfound);

  server.begin();
  delay(100);
  Serial.printf("IP ADD: %s", String(local_ip.toString()));
}

void loop()
{
  server.handleClient();
}

String sendHTML(uint8_t mode)
{
  if (mode == contactMode)
  {
    return core + contact;
  }
  else if (mode == projectMode)
  {
    return core + project;
  }
  else if (mode == educationMode)
  {
    return core + education;
  }
  else
  {
    Serial.println("Don't Know What Happend");
    return "\0";
  }
}

void handleContact(void)
{
  Serial.println("Contact Handler");
  server.send(200, "text/html", sendHTML(contactMode));
}

void handleProject(void)
{
  Serial.println("Project Handler");
  server.send(200, "text/html", sendHTML(projectMode));
}

void handleEducation(void)
{
  Serial.println("Education Handler");
  server.send(200, "text/html", sendHTML(educationMode));
}

void handleNotfound(void)
{
  Serial.println("Not Found");
}
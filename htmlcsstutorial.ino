/*
Creat by Fairy-Elab on 21-20-2021
*/
#include <WebServer.h>

WebServer webServer(80);

char *ssid = "non";
char *pass = "non";

char *apssid = "enter access point";
char *appass = "enter pass";

//=========Biến chứa mã HTLM Website==//
const char MainPage[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html>

  <head>
    <title>HOME PAGE</title>
    <style>
      body {
        text-align: center;
      }

      h1 {
        color: #003399;
      }

      a {
        text-decoration: none;
        color: #FFFFFF;
      }

      .bt_on {
        height: 50px;
        width: 100px;
        margin: 10px 0;
        background-color: #FF6600;
        border-radius: 5px;
      }

      .bt_off {
        height: 50px;
        width: 100px;
        margin: 10px 0;
        background-color: #00FF00;
        border-radius: 5px;
      }
    </style>
    <meta charset="UTF-8">
  </head>

  <body>
    <h1>ESP32 Web Server</h1>
    <div>Trạng thái trên chân D1: <b>OFF</b></div>
    <div>
      <button class="bt_on"><a href="/onD1">ON</a></button>
      <button class="bt_off"><a href="/offD1">OFF</a></button>
    </div>
    <div>Trạng thái trên chân D2: <b>OFF</b></div>
    <div>
      <button class="bt_on"><a href="/onD2">ON</a></button>
      <button class="bt_off"><a href="/offD2">OFF</a></button>
    </div>
  </body>

  </html>
  )=====";

//=========================================//
void setup()
{

  Serial.begin(115200);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting...");
  }
  Serial.print("Connecting...");
  Serial.println(WiFi.localIP());

  WiFi.softAP(apssid, appass);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  webServer.on("/", mainpage);
  webServer.on("/onD1", on_D1);
  webServer.on("/offD1", off_D1);
  webServer.on("/onD2", on_D2);
  webServer.on("/offD2", off_D2);
  webServer.begin();
  Serial.println("Server started");
}

void loop()
{
  webServer.handleClient();
}

//==========Chương trình con=================//
void mainpage()
{
  String s = FPSTR(MainPage);
  webServer.send(200, "text/html", s);
}

void on_D1()
{
  Serial.println("D1,LOW");
  String s = FPSTR(MainPage);
  webServer.send(200, "text/html", s);
}
void off_D1()
{
  Serial.println("D1,HIGH");
  String s = FPSTR(MainPage);
  webServer.send(200, "text/html", s);
}
void on_D2()
{
  Serial.println("D2,LOW");
  String s = FPSTR(MainPage);
  webServer.send(200, "text/html", s);
}
void off_D2()
{
  Serial.println("D2,HIGH");
  String s = FPSTR(MainPage);
  webServer.send(200, "text/html", s);
}
/*
 *  Contains code from Rui Santos of http://randomnerdtutorials.com
 * 
 * 
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

#define WLAN_SSID       "YourSSIDgoesHere"
#define WLAN_PASS       "YourWifiPassword"

MDNSResponder mdns;
ESP8266WebServer server(80);

Servo myservo;
int pos = 0;
int state = 0;
int prevstate = 0;
int dirc = 0;
int servoPin = D3; //CHANGE TO WHATEVER PIN YOUR USING

String webPage = "";

void setup(void) {
  webPage += "<h1>ESP8266 Web Server</h1><p>Blinds <a href=\"open\"><button>OPEN</button></a>&nbsp;<a href=\"close\"><button>CLOSE</button></a></p>";

  delay(1000);
  Serial.begin(9600);
  delay(500);
  Serial.println("Blind Startup Sequence");
  delay(500);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  // Set a static IP (optional)
  IPAddress ip(192, 168, 1, 142);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);
  // End of set a static IP (optional)
  delay(500);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    ESP.wdtFeed();
    if (i > 40)                                        // Try 40 times to connect to Wifi
      Serial.print("Restarting Wifi"); ESP.reset();    // Reset Wifi stack if more than 40 trys
    i++;
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    // Set a static IP retry (optional)
    IPAddress ip(192, 168, 1, 142);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.config(ip, gateway, subnet);
    // End of set a static IP retry (optional)
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", []() {
    server.send(200, "text/html", webPage);
  });
  server.on("/open", []() {
    server.send(200, "text/html", webPage);
    Serial.println("HTTP OPEN COMMAND RECEIVED");
    dirc = 0;  // direction for servo to run
    state = 2; // sets current state
  });
  server.on("/close", []() {
    server.send(200, "text/html", webPage);
    Serial.println("HTTP CLOSE COMMAND RECEIVED");
    dirc = 180; // direction for servo to run
    state = 1;  // sets current state
  });
  server.begin();
  Serial.println("HTTP server started");
}

void servo_move() {
  Serial.println("State Change. Rotating Servo");
  if ( dirc == 180) {
    myservo.attach(servoPin);              // energize servo
    delay(50);
    for (pos = 0; pos <= 90; pos += 1) {   // goes from 0 degrees to 90 degrees in steps of 1 degree CHANGE 90 TO MATCH ANGLE OF TILT DESIRED
      myservo.write(pos);                  // tell servo to go to position in variable 'pos'
      delay(30);                           // waits 30ms between each degree to slow rotation speed
    }
    delay(50);
    myservo.detach();                      // movement finished so detach servo to conserve power
  }
  else if (dirc == 0) {
    myservo.attach(servoPin);              // energize servo
    delay(50);
    for (pos = 90; pos >= 0; pos -= 1) {   // goes from 90 degrees to 0 degrees in steps of 1 degree CHANGE 90 TO MIRROR ANGLE OF TILT DESIRED ABOVE
      myservo.write(pos);                  // tell servo to go to position in variable 'pos'
      delay(30);                           // waits 30ms between each degree to slow rotation speed
    }
    delay(50);
    myservo.detach();                      // movement finished so detach servo to conserve power
  }

  Serial.println("Returning to main loop");
  return;
}

void loop(void) {
  if (state != prevstate) {
    Serial.println("State change!");
    servo_move();
  }
  prevstate = state;
  server.handleClient();
}

//Include Libraries
#include "esp_now.h"
#include "WiFi.h"

//Set Motor PINs
#define ENA 5
#define IN1 18
#define IN2 19
#define IN3 23
#define IN4 32
#define ENB 33
 
//Initialize global variables
bool front = 0;
bool back = 0;
bool left = 0;
bool right = 0;

//Struct to recieve data (same as on transmitter side)
typedef struct{
  bool f;
  bool b;
  bool l;
  bool r;
} message;
message data;

//Function to be called on callback
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len){
  memcpy(&data, incomingData, sizeof(data));
  front = data.f;
  back = data.b;
  left = data.l;
  right = data.r;
}

void setup() {
  //Initialize pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  WiFi.mode(WIFI_STA);

  //Initialize esp-now
  if (esp_now_init() != ESP_OK){
    return;
  }

  //Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  if (front == 1) {
    carforward();
  } 
  else if (back == 1) {
    carbackward();
  } 
  else if (left == 1) {
    carturnleft();
  } 
  else if (right == 1) {
    carturnright();
  } 
  else if (front == 0 && back == 0 && left == 0 && right == 0) {
    carStop();
  }
}
 
//Functions for specific movements
void carforward() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carbackward() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnleft() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnright() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
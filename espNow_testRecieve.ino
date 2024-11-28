//espNow recieve test code to flash on-board LED of peer while in range
//Code based on Random Nert Tutorials
//https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/
//NodeMCU #3 
#include <espnow.h>  //Libraries for esp8266
#include <ESP8266WiFi.h>
int ledPin = 2; //For NodeMCU blue LED on module
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int b;
    bool d;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.println("Int: ");
  Serial.println(myData.b);
  Serial.println(myData.d);
  digitalWrite(ledPin, myData.d);
}
 
void setup() {
  pinMode(ledPin, OUTPUT);
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ERR_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

}
 
void loop() {

}
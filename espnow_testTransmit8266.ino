//espNow transmit test code to flash on-board LED of peer while in range
//Comment/uncomment lines as required
//Code based on Random Nert Tutorials
//https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/
//==============================================
#include <ESP8266WiFi.h>
#include <espnow.h>  //Libraries for esp8266

int a = 0;
bool c = 0;
// REPLACE WITH YOUR OWN RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xC8, 0xC9, 0xA3, 0x6A, 0x9A, 0xA4};
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int b;  //Number of transmissions
  bool d; //Variable to flash LED on peer
} struct_message;
// Create a struct_message called myData
struct_message myData;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() 
{
  // Init Serial Monitor
  Serial.begin(115200); 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  
  // Init ESP-NOW   
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  
  
}
void loop() {
  // Set values to send
  c = !c; // To flash LED
  myData.b = a++; //Count for number of transmissions
  myData.d = c;   //Transmit LED flash signal
  
  Serial.println(myData.b);
  Serial.println(myData.d);
  // Send message via ESP-NOW
 esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
delay(1000);
}
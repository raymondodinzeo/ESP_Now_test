//espNow transmit test code to flash on-board LED of peer while in range
//Code based on Random Nert Tutorials
//https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/
//Peer = NodeMCU #3
#include <esp_now.h> //Libraries for esp32
#include <WiFi.h>
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
esp_now_peer_info_t peerInfo;
// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() 
{
  // Init Serial Monitor
  Serial.begin(115200); 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_MODE_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
void loop() {
  // Set values to send
  c = !c; // To flash LED
  myData.b = a++; //Count for number of transmissions
  myData.d = c;   //Transmit LED flash signal
  
  Serial.println(myData.b);
  Serial.println(myData.d);
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(1000);
}
#include <EEPROM.h>

extern const int eepromSize;
extern const int outputPinList[];
extern const int pullupPinList[];
extern const int outputPinListSize;
extern const int pullupPinListSize;

TaskHandle_t touchSensorTask;

void setup() {
  
  Serial.begin(115200);
  while (!Serial) {
    Serial.println("Error in setup");
    continue;
  }
  EEPROM.begin(eepromSize);

  //Set the pin mode of OUTPUT, INPUT, INPUT_PULLUP pins
  for(int i=0; i<outputPinListSize; i++){
      pinMode(outputPinList[i], OUTPUT); 
     } 
     
  for(int i=0; i<pullupPinListSize; i++){
       pinMode(pullupPinList[i], INPUT_PULLUP); 
     }
   
  connectToWifi();
  connectToMQTT(); 
  restore();
  xTaskCreatePinnedToCore(detectTouch, "touchSensorTask", 10000, NULL, 1, &touchSensorTask, 0);  //(function name, name, Stack size, parameter to function, priority, &Task handle, core no (0 or 1))                
  delay(500); 
}

void restore(){
// Serial.println("Main - restore");
  int pin;
  int state;
  
  for(int i=0; i<outputPinListSize; i++){
      pin = outputPinList[i];
      state = EEPROM.read(pin);
      digitalWrite(pin, state);
    }
}

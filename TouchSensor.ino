extern const int touchPinList[];
extern const int outputPinList[];
extern const int dimmerPinList[];
extern const int touchPinListSize;
extern const int outputPinListSize;
int *touchState = (int*)calloc(touchPinListSize, sizeof(int));

void loop(){
//  Serial.println("Touchsensor - loop");
      for(int i = 0; i < touchPinListSize; i++){
        int touch = digitalRead(touchPinList[i]);
        if(touch == 1){
             while( touch = digitalRead(touchPinList[i]) == 1){}                          //if someone press and hold the touch
             process(i);
          }
        }
}

void process(int index){
//  Serial.println("Touchsensor - process");
    if(index == 0){
       for(int i = 0; i < outputPinListSize; i++){
          digitalWrite(outputPinList[i], LOW);
          EEPROM.write(outputPinList[i], LOW);
       }
    }else{
          publish(topic, strcat(roomNo,strcat(seperator,strcat(patientNo,seperator)+index)));
          digitalWrite(outputPinList[index], HIGH);
          EEPROM.write(outputPinList[index], HIGH);
    }
    EEPROM.commit();
  }

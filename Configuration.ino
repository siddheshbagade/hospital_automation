// This file contains constants and function

const char* ssid = "WIFI ID";
const char* password = "WIFI PASWORD";
const int port = 1883;
const char* topic = "Hospital";
char* roomNo = "1";
char* patientNo = "1";
char* seperator = "-";
const char* server = "SEEVER IP";

const int outputPinList[] = {25, 32, 21, 12};    // Relay Pin     // index-0 will be "OK" button
const int pullupPinList[] = {27, 33, 34, 23};    // OPAMP use pin
const int touchPinList[] = {15, 2, 4};           // touchpin      // index-0 will be "OK" button
const int outputPinListSize = sizeof(outputPinList)/ sizeof(outputPinList[0]);
const int pullupPinListSize = sizeof(pullupPinList)/ sizeof(pullupPinList[0]);
const int touchPinListSize = sizeof(touchPinList)/ sizeof(touchPinList[0]);
const int eepromSize = 512;                      // size of EEPROM internal memory

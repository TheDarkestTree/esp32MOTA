#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <Wire.h>
#include <SparkFun_SCD30_Arduino_Library.h>
#include <BLEServer.h>
#include <BLE2902.h>

//Due to problems with libraries, all the code must be here. I don't really like it, but xD. For that reason, all the .c file must disappear.


//This pins are denifed as GPIO not like phisic number.
#define pinT 32
#define pinL 33
#define pinRX 16
#define pinTX 17
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"


int temperature = 30;
int lux = 2000;
uint16_t CO2value = 0xffff;
int personas = 0;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;
int scanTime = 5;
String option;


BLEScan* pBLEScan;
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;

SCD30 CO2sensor;

//Scanner

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

//Server

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      //BLEDevice::getPeerDevices();
      deviceConnected = true;
      Serial.println("Device Connected");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("Device Disconnected");
    }
};

//Temperature sensor control function

int getTemperature(){
  
  int valorSensor = 0;
  int voltajeSal = 0;

  //valorSensor = analogRead (pinT);      //pinT dependera del pin en el que se encuentre el sensor. analogRead funcion de la libreria de arduino.
  voltajeSal = (valorSensor * 5000)/ 1024;  // 5000 no comprendo de donde sale. 1024 es el correspondiente en arduino de 5v.
  temperature = 20;//voltajeSal / 10;        //en el caso del sensor LM35 son 10mV para convertirlo en ºC.

  return temperature;
}

//Fotoresistor control function

int getLux (){

 // int lux = 0;
  
 // lux = analogRead (pinL);      //In the case of this sensor, we don't need to use any formula. It's enough reading data of the pin.
  
  return lux;
}

//CO2 sensor function

uint16_t getCO2(){
    
 // uint16_t CO2value = 0x0000;   //son un total de 16 bits

  /*Wire.begin();
  if (CO2sensor.dataAvailable())
    CO2value = CO2sensor.getCO2();*/

  return CO2value;    
}

//Bluetooth scan

int getCount(){

  int cont = 0;

  //init ble scan
    Serial.println("Scanning...");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value

  //In this part we are going to put everything related with bluetooth scan using ble. 
  //Should confirm if We can do the scan usig classic bluetooth.

  //count = devices.found();    //devices.found is a function of the library related to ble.

  //Scan part

  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
    cont = foundDevices.getCount();
    pBLEScan->clearResults();
  return cont;
}

//Bluetooth sever to send data

void sendDataBLE(){

  String data;

  if (deviceConnected) {
        data = getTemperature();
        data = data + "/" + getLux();
        data = data + "/" + getCO2();
        data = data + "/" + getCount();
        Serial.println("Data: " + data);
        pCharacteristic->setValue(data.c_str());
        pCharacteristic->notify();
        delay(600); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
    }

    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }

    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}

void setup (){

  //parametros necesarios para inicializar esp32
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, pinRX, pinTX);
  // Create the BLE Device
  BLEDevice::init("ESP32");
  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);
  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);

  // Start the service
  pService->start();
  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
  
}

void loop (void){

    String prueba;
    int val = 0;
    if (Serial.available() > 0){
      option = Serial.readString();
      Serial.flush();
      Serial.println(option);
      //Serial.println("Option: " + option);
    }

    sendDataBLE();
    /*if (option != 48){
   		switch(option){
			  case 49: //dat = Serial.write(option);
                       delay(4000);
                       nuevo = Serial.read();
                       //Serial.println(dat);
                       if (Serial.available())
                          Serial.println(nuevo);
                       Serial.flush();
              
                       delay (400);
                /*if (Serial.available()){
                    Serial.read();
                    Serial.flush();
                    Serial.println(option, DEC);
                 }*/
	/*	  		break;
		  	case 50: Serial2.write(getLux());
		  		break;
		  	case 51: Serial2.write(getCO2());
		  		break;
		  	case 52: Serial2.write(getCount());
		  		break;
		  	case 53: //In this case we have two options. Send all the information in only one string or sending one by one
		  			prueba = "Personas: " + getCount();
		  			prueba = prueba + " CO2: " + getCO2();
		  			prueba = prueba + " Luz: " + getLux();
		  			prueba = prueba + " Temperature " + getTemperature();
		  			Serial2.write(prueba.c_str());
		  		break;
		  	case 54: prueba = "Temperatura: " + getTemperature();
		  			prueba = prueba + " Luz: " + getLux();
		  			Serial2.write(prueba.c_str());
		  		break;
		  	case 55: prueba = "Temperatura: " + getTemperature();
		  			prueba += " CO2: " + getCO2();
		  			Serial2.write(prueba.c_str());
		  		break;
   		}
   	}*/
    
    if (option == "t" || option == "T"){			//sending a t or T
    	//Serial2.write(getTemperature());
    	Serial.println("Temperatura");
    	val ++;
    }

    if (option == "l" || option == "L"){			//sending a l or L
    	//Serial2.write(getLux());
    	Serial.println("luz");
    	val ++;
    }

    if (option == "c" || option == "C"){			//sending a c or C
    	//Serial2.write(getCO2());
    	Serial.println("CO2");
    	val ++;
    }

    if (option == "p" || option == "P"){			//sending a p or P
    	//Serial2.write(getCount());
    	Serial.println("Personas");
    	val ++;
    }

    if ((option == "a" || option == "A") && val == 0){		//sending an a or A
    	prueba = "Personas: " + getCount();
		prueba = prueba +" CO2: " + getCO2();
		prueba = prueba + " Luz: " + getLux();
		prueba = prueba + " Temperature " + getTemperature();
		Serial.println(prueba);
		//Serial2.write(prueba.c_str());
    }


   	//delay(400);
}

//#include all the libraries that I wiil need to implement bluetooth
//All this code must go to the main function.
/*int getCount(){

	int cont = 0;

	//init ble scan

	Serial.begin(115200);
  	Serial.println("Scanning...");

	BLEDevice::init("");
	pBLEScan = BLEDevice::getScan(); //create new scan
	pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
	pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
	pBLEScan->setInterval(100);
	pBLEScan->setWindow(99);  // less or equal setInterval value

	//In this part we are going to put everything related with bluetooth scan using ble. 
	//Should confirm if We can do the scan usig classic bluetooth.

	//count = devices.found(); 		//devices.found is a function of the library related to ble.

	//Scan part

	BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  	cont = foundDevices.getCount();

	return cont;
}

/*n this case, we are going to use the esp32 as a server and the phone as client. The esp32 will send all the data to the client(phone)*/
/*
int connect(){

	//string UUID;					//this is the identifier of the service.
	int connected = 0;			//used as a control variable.

	//In this part, everything related to create a ble server. Probably, we should use characteristics or something like that.  rerturn connected;
}

//this function is used to send all the information take it by the sensors and send it to the phone.

//void sendData(int temperature, int lux, int count, uint16_t CO2){
/*
	send(temperature, lux, count, CO2);

	//or

	send (temperature);
	send (lux);
	send (count);
	send (CO2);*/

	//How to send data depends of how phone must recieve it.
//}
/*#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;
char hola = 'h';

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "62e0fa9c-7133-4027-ba76-181c47d64b23"
#define CHARACTERISTIC_UUID "525e57f2-eeed-4712-96c1-2a68c6248fc4"


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("Device connected");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("DEvice Disconnected");
    }
};

void setup() {
  Serial.begin(115200);

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
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

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

void loop() {
    // notify changed value
    if (deviceConnected) {
        //pCharacteristic->setValue((uint8_t*)&value, 5);
        //pCharacteristic->notify();
        //pCharacteristic->setValue((uint8_t*)&hola, 2);
        pCharacteristic->setValue("Hola mi amor");
        pCharacteristic->notify();
        Serial.println(hola);
        //value++;
        delay(200); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
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
}*/
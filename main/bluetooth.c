//#include all the libraries that I wiil need to implement bluetooth
//All this code must go to the main function.

int getCount(){

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

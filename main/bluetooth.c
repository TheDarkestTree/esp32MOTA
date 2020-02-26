//#include all the libraries that I wiil need to implement bluetooth


int getCount(){

	int count = 0;

	//In this part we are going to put everything related with bluetooth scan using ble. 
	//Should confirm if We can do the scan usig classic bluetooth.

	count = devices.found(); 		//devices.found is a function of the library related to ble.

	return count;
}

/*n this case, we are going to use the esp32 as a server and the phone as client. The esp32 will send all the data to the client(phone)*/

void connect(){

	string UUID;					//this is the identifier of the service.
	bool connected = false;			//used as a control variable.

	//In this part, everything related to create a ble server. Probably, we should use characteristics or something like that.

}

//this function is used to send all the information take it by the sensors and send it to the phone.

void sendData(int temperature, int lux, int count, uint16_t CO2){

	send(temperature, lux, count, CO2);

	//or

	send (temperature);
	send (lux);
	send (count);
	send (CO2);

	//How to send data depends of how phone must recieve it.
}
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <Wire.h>
#include <SparkFun_SCD30_Arduino_Library.h>


//Due to problems with libraries, all the code must be here. I don't really like it, but xD. For that reason, all the .c file must disappear.

#define pinT 6
#define pinL 7


BLEScan* pBLEScan;

SCD30 CO2sensor;


//Temperature sensor control function

float getTemperature(){

	float temperature = 0.0;
	float valorSensor = 0.0;
	float voltajeSal = 0.0;

	valorSensor = analogRead (pinT); 			//pinT dependera del pin en el que se encuentre el sensor. analogRead funcion de la libreria de arduino.
	voltajeSal = (valorSensor * 5000)/ 1024;	// 5000 no comprendo de donde sale. 1024 es el correspondiente en arduino de 5v.
	temperature = voltajeSal / 10;				//en el caso del sensor LM35 son 10mV para convertirlo en ºC.

	return temperature;
}


//Fotoresistor control function

int getLux (){

	int lux = 0;
	
	lux = analogRead (pinL);			//In the case of this sensor, we don't need to use any formula. It's enough reading data of the pin.
	
	return lux;
}

uint16_t getCO2(){
		
	uint16_t CO2value = 0x0000;		//son un total de 16 bits

	Wire.begin();

	if (CO2sensor.dataAvailable()){

		CO2value = CO2sensor.getCO2();
	}

	return CO2value;		
}



void Setup (){

	//parametros necesarios para inicializar esp32
	float temperatura = 0.0;
	int lux = 0;
	uint16_t C02 = 0x0000;
	int personas = 0;
}

void loop (){
      //por UART recibe la información del robot de gobierno 

    int orden = 0;
    orden = UARTGobierno();

    /*al tener un total de 4 clases sin contar micrófono podemos comprender entre 1 y 5 los valores siendo
      1) solicitud de temperatura
      2) Solicitud de luz
      3) solicitud de CO2
      4) solicitud de nuúmero de personas
      5) Todo
    */
    //en este punto podemos hacerlo con todo ifs o podemos considerar la opción de un switch dependiendo de lo más óptimo
    
    //opcion 1:
    if (orden != 0){
      if (orden == 1)
        temperatura = getTemperatura ();
      else if (orden == 2)
        lux = getLux();
      else if (orden == 3)
        CO2 = getCO2();
      else if (orden == 4)
        personas = count(MACs[][N]);
      else if (orden == 5){
        temperatura = getTemperatura();
        lux = getLux ();
        CO2 = getCO2();
        personas = count (MACs [][N]);
      }
    }

    //opcion 2
    if (orden != 0){
      do{
        switch(orden){
          case 1: temperatura = getTemperatura();
              break;
          case 2: lux = getLux();
              break;
          case 3: CO2 = getCO2();
              break;
          case 4: personas = count (MACs[][N]);
              break;
          case 5: temperatura = getTemperatura();
              lux = getLux();
              CO2 = getCO2();
              personas = count (MACs[][N]); 
              break;
        }
      }while (orden != 6);
    }

    UARTGobierno ("Temperatura: %f ºC", temperatura);
    UARTGobierno ("Luz: %d lux", lux);
    UARTGobierno ("CO2: %d ppm", CO2);
    UARTGobierno ("Numero de personas: %d personas", personas);
}

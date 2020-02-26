#include <Wire.h>
#include <SparkFun_SCD30_Arduino_Library.h>


/*Con este sensor tenemos dos opoiones de porgramación. Como utiliza el protolo I2C podemos resumir el código
a estas lineas de código incluyendo las dos librerias que también estan preparadas para que el sensor reciba
los valores de humedad y temperatura. Sin embargo, podemos evitar introducir esa libreria y meternos 
en código I2C usando la libreria wire.h para llevar a cabo toda la comunicación y controlarla. Utilizando de 
esta manera solo una parte enfocada al CO2. Tengo que hablar con Norberto para ello.*/

uint16_t getCO2(){

  SCD30 C02sensor;
	uint16_t CO2value = 0x0000;		//son un total de 16 bits

	Wire.begin();
	if (CO2sensor.dataAvailable())
	{
		CO2value = CO2sensor.getCO2();
	}

	return CO2value;
		
}

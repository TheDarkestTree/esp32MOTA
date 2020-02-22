
#include //librerias necesarias

//se debe indicar el pin en el que se encuentra situado el sensor.

//funcion encargada de devolver los valores de la temperatura ya convertidos.
float getTemperature(){

	float temperatura = 0.0;
	float valorSensor = 0.0;
	float voltajeSal = 0.0;

	valorSensor = analogRead (sensorPIN); 		//sensorPIN dependera del pin en el que se encuentre el sensor. analogRead funcion de la libreria de arduino.
	voltajeSal = (valorSensor * 5000)/ 1024;	// 5000 no comprendo de donde sale. 1024 es el correspondiente en arduino de 5v.
	temperatura = voltajeSal / 10;				//en el caso del sensor LM35 son 10mV para convertirlo en ºC.

	return temperatura;
}
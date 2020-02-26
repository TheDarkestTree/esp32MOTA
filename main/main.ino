#include "temperatura.c"
#include "luz.c"
#include "CO2.c"
#include "bluetooth.c"

#define N 12

void main (){

	//parametros necesarios para inicializar esp32
	int orden = 0;
	float temperatura = 0.0;
	int lux = 0;
	uint16_t C02 = 0x0000;
	int personas = 0;
	char MACs [][N];				//el valor de la x debería ser variable (necesario ver como se hace) OJO AL STACK

	while (1){

		//por UART recibe la información del robot de gobierno 

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
}

//En este código no necesito el uso de ninguna libreria (Pendiente de prueba)

//definir el pin del que se va a leer la luz. Debe tener un adc.

int getLux (){
	int Pin = 22;
	int lux = 0;
	
	lux = analogRead (Pin);			//no necesita ninguna formula de transformación. Con leer el valor del pin es suficiente.
	
	return lux;
}

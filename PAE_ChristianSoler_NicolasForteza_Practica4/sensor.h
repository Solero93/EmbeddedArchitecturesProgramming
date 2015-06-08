//RAM AREA
#define LEFT_IR_SENSOR_DATA 26
#define CENTER_IR_SENSOR_DATA 27
#define RIGHT_IR_SENSOR_DATA 28
#define OBSTACLE_DETECTION_FLAG 32
#define OBSTACLE_DETECTED_COMPARE 52

#define SENSOR_ID 100
#define OBSTACLE_VALUE 0x50
#define VALUE_DISTANT 0x0F

/**
 * Inicializacion del sensor
 *
 */
void init_sensor(){
	//set OBSTACLE_DETECTION_FLAG to 0
	gbpParameter[0] = OBSTACLE_DETECTION_FLAG;
	gbpParameter[1] = 0;
	TxPacket(SENSOR_ID,2,INST_WRITE);
	
	//set OBSTACLE_DETECTED_COMPARE to a specific value (needs to be tried out)
	gbpParameter[0] = OBSTACLE_DETECTED_COMPARE;
	gbpParameter[1] = OBSTACLE_VALUE; // Value from which something is considered an obstacle
	TxPacket(SENSOR_ID,2,INST_WRITE);	
}

/**
 * Retorna si hay algun obstaculo ceca
 *
 */
int obstacle_detection(){
	//read OBSTACLE_DETECTION_FLAG
	gbpParameter[0] = OBSTACLE_DETECTION_FLAG;
	gbpParameter[1] = 1; // Length of the data to be read
	TxPacket(SENSOR_ID,2,INST_READ);
	struct RxReturn respuesta= RxPacket();
	//escribirRxSensor(4, respuesta);
	return respuesta.StatusPacket[5]; // The data read is PARAMETER 1
	/**
	 * BIT 2 - Obstacle detected by Right sensor 
	 * BIT 1 - Obstacle detected by Center sensor
	 * BIT 0 - Obstacle detected by Left sensor
	 */
}


/**
 * lectura del sensor izquierdo
 *
 */
int read_left(){
	gbpParameter[0] = LEFT_IR_SENSOR_DATA;
	gbpParameter[1] = 1; // Length of the data to be read

	TxPacket(SENSOR_ID,2,INST_READ);

	return RxPacket().StatusPacket[5];

}

/**
 * lectura del sensor delantero
 *
 */
int read_center(){
	gbpParameter[0] = CENTER_IR_SENSOR_DATA;
	gbpParameter[1] = 1; // Length of the data to be read

	TxPacket(SENSOR_ID,2,INST_READ);

	return RxPacket().StatusPacket[5];

}

/**
 * lectura del sensor derecho
 *
 */
int read_right(){
	gbpParameter[0] = RIGHT_IR_SENSOR_DATA;
	gbpParameter[1] = 1; // Length of the data to be read

	TxPacket(SENSOR_ID,2,INST_READ);

	return RxPacket().StatusPacket[5];

}

/**
 *comprueba si esta mas lejos el sensor  izquierdo
 *
 */
int lejos_izquierda(){
	if(read_left()< VALUE_DISTANT){
		return 1;
	}else{
		return 0;
	}
}

/**
 * comprueba si estamas lejos el sensor derecho
 *
 */
int lejos_derecha(){
	if(read_right()< VALUE_DISTANT){
		return 1;
	}else{
		return 0;
	}
}


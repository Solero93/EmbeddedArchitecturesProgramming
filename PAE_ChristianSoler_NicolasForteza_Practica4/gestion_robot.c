#include "constants.h"
#include "fisica.h"
#include "gestion_robot.h"

volatile byte gbpRxInterruptBuffer[256];
byte gbpParameter[128];
byte gbpTxBuffer[32];

/**
 * MOTORES
 */

void angulo_a0(byte bID){
	gbpParameter[0] = P_CW_ANGLE_LIMIT_L; //high de Speed de 0 a 3
	gbpParameter[1] = 0x00;
	gbpParameter[2] = 0x00; //
	gbpParameter[3] = 0x00; //
	gbpParameter[4] = 0x00; //
	TxPacket(bID,5,INST_WRITE);
	escribirRx(RxPacket());
}

void change_velocidad(byte bID, byte H, byte L){
	gbpParameter[0] = P_GOAL_SPEED_L; //high de Speed de 0 a 3
	gbpParameter[1] = L; //
	gbpParameter[2] = H; //
	TxPacket(bID,3,INST_WRITE);
}

void init_motor(byte bID){
	angulo_a0(bID);
	change_velocidad(bID, 0, 0);
}

void mover_delante(){
	change_velocidad(MOTOR_DEL_DERECHO, 5 & FORWARD_MOTOR_DEL_DERECHO, 0);
	change_velocidad(MOTOR_DEL_IZQUIERDO,  5 & FORWARD_MOTOR_DEL_IZQUIERDO, 0);
	change_velocidad(MOTOR_TRAS_DERECHO,  5 & FORWARD_MOTOR_TRAS_DERECHO, 0);
	change_velocidad(MOTOR_TRAS_IZQUIERDO,  5 & FORWARD_MOTOR_TRAS_IZQUIERDO, 0);
}


void parar(){
	change_velocidad(MOTOR_DEL_DERECHO,0, 0);
	change_velocidad(MOTOR_DEL_IZQUIERDO, 0, 0);
	change_velocidad(MOTOR_TRAS_DERECHO, 0, 0);
	change_velocidad(MOTOR_TRAS_IZQUIERDO, 0, 0);
}


void mover_atras(){
	change_velocidad(MOTOR_DEL_DERECHO,  5 & BACKWARD_MOTOR_DEL_DERECHO, 0);
	change_velocidad(MOTOR_DEL_IZQUIERDO,  5 & BACKWARD_MOTOR_DEL_IZQUIERDO, 0);
	change_velocidad(MOTOR_TRAS_DERECHO,  5 & BACKWARD_MOTOR_TRAS_DERECHO, 0);
	change_velocidad(MOTOR_TRAS_IZQUIERDO,  5 & BACKWARD_MOTOR_TRAS_IZQUIERDO, 0);
}

void girar_derecha(){
	change_velocidad(MOTOR_DEL_DERECHO,  5 & BACKWARD_MOTOR_DEL_DERECHO, 0);
	change_velocidad(MOTOR_DEL_IZQUIERDO,  5 & FORWARD_MOTOR_DEL_IZQUIERDO, 0);
	change_velocidad(MOTOR_TRAS_DERECHO,  5 & BACKWARD_MOTOR_TRAS_DERECHO, 0);
	change_velocidad(MOTOR_TRAS_IZQUIERDO,  5 & FORWARD_MOTOR_TRAS_IZQUIERDO, 0);
}

void girar_izquierda(){
	change_velocidad(MOTOR_DEL_DERECHO,  5 & FORWARD_MOTOR_DEL_DERECHO, 0);
	change_velocidad(MOTOR_DEL_IZQUIERDO,  5 & BACKWARD_MOTOR_DEL_IZQUIERDO, 0);
	change_velocidad(MOTOR_TRAS_DERECHO,  5 & FORWARD_MOTOR_TRAS_DERECHO, 0);
	change_velocidad(MOTOR_TRAS_IZQUIERDO,  5 & BACKWARD_MOTOR_TRAS_IZQUIERDO, 0);
}


void mandar_a_todos_motores(byte numParam, byte instruction){

}

void ping(byte bID){
	TxPacket(bID,0,INST_PING);
	escribirRx(RxPacket());
}

void encender_LED(byte bID){
	gbpParameter[0] = P_LED; //Address of LED
	gbpParameter[1] = 1; //Writing Data encender
	TxPacket(bID,2,INST_WRITE);
	escribirRx(RxPacket());

}

void apagar_LED(byte bID){
	gbpParameter[0] = P_LED; //Address of LED
	gbpParameter[1] = 0; //Writing Data apagar
	TxPacket(bID,2,INST_WRITE);

}

/**
 *
 * SENSORES
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

int obstacle_detection(){
	//read OBSTACLE_DETECTION_FLAG
	gbpParameter[0] = OBSTACLE_DETECTION_FLAG;
	gbpParameter[1] = 1; // Length of the data to be read
	TxPacket(SENSOR_ID,2,INST_READ);

	struct RxReturn respuesta = RxPacket();
	//escribirRxSensor(4, respuesta);
	return respuesta.StatusPacket[5]; // The data read is PARAMETER 1
	/**
	 * BIT 2 - Obstacle detected by Right sensor
	 * BIT 1 - Obstacle detected by Center sensor
	 * BIT 0 - Obstacle detected by Left sensor
	 */
}

int read_left(){
	gbpParameter[0] = LEFT_IR_SENSOR_DATA;
	gbpParameter[1] = 1; // Length of the data to be read

	TxPacket(SENSOR_ID,2,INST_READ);

	//TODO escribirRxSensor(1,RxPacket()); => cambiarlo por un return

}

int read_center(){
	gbpParameter[0] = CENTER_IR_SENSOR_DATA;
	gbpParameter[1] = 1; // Length of the data to be read

	TxPacket(SENSOR_ID,2,INST_READ);

	//TODO escribirRxSensor(2, RxPacket()); => cambiarlo por un return

}

int read_right(){
	gbpParameter[0] = RIGHT_IR_SENSOR_DATA;
	gbpParameter[1] = 1; // Length of the data to be read

	TxPacket(SENSOR_ID,2,INST_READ);

	//TODO escribirRxSensor(3, RxPacket()); => cambiarlo por un return

}

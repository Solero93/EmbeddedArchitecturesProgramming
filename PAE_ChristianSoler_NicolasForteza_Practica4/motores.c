#include <motores.h>

/*
* La part del codi que no ens va
*/
void angulo_a0(byte bID){
        gbpParameter[0] = P_CW_ANGLE_LIMIT_H; //high de Speed de 0 a 3
        gbpParameter[1] = 0x00;
        TxPacket(bID,2,INST_WRITE);

        gbpParameter[0] = P_CW_ANGLE_LIMIT_L; //low de speed de 0 a ff
        gbpParameter[1] = 0x00; //
        TxPacket(bID,2,INST_WRITE);

        gbpParameter[0] = P_CCW_ANGLE_LIMIT_H; //high de Speed de 0 a 3
        gbpParameter[1] = 0x00; //
        TxPacket(bID,2,INST_WRITE);

        gbpParameter[0] = P_CCW_ANGLE_LIMIT_L; //low de speed de 0 a ff
        gbpParameter[1] = 0x00; //
        TxPacket(bID,2,INST_WRITE);

        gbpParameter[0] = P_GOAL_POSITION_H; //high de Speed de 0 a 3
        gbpParameter[1] = 0x00; //
        TxPacket(bID,2,INST_WRITE);

        gbpParameter[0] = P_GOAL_POSITION_L; //low de speed de 0 a ff
        gbpParameter[1] = 0x00; //
        TxPacket(bID,2,INST_WRITE);

}

void change_velocidad(byte bID, byte H, byte L){
	gbpParameter[0] = P_MOVING_SPEED_H; //high de Speed de 0 a 3
	gbpParameter[1] = H; //
	TxPacket(bID,2,INST_WRITE);

	gbpParameter[0] = P_MOVING_SPEED_L; //low de speed de 0 a ff
	gbpParameter[1] = L; //
	TxPacket(bID,2,INST_WRITE);
}

void init_motor(byte bID){
	angulo_a0(bID);
	change_velocidad(bID, 0, 0);
}

void ping(byte bID){
	TxPacket(bID,0,INST_PING);
	escribirRx(RxPacket());
}

void encender_LED(byte bID){
	gbpParameter[0] = P_LED; //Address of LED
	gbpParameter[1] = 1; //Writing Data encender
	TxPacket(bID,2,INST_WRITE);
}

void apagar_LED(byte bID){
	gbpParameter[0] = P_LED; //Address of LED
	gbpParameter[1] = 0; //Writing Data apagar
	TxPacket(bID,2,INST_WRITE);
}

/*
 *Encara no está implementat

void mover_delante(){
	change_velocidad(1, 1 | FORWARD_MOTOR_DEL_DERECHO, 0);
	change_velocidad(2, 1 | FORWARD_MOTOR_DEL_IZQUIERDO, 0);
	change_velocidad(3, 1 | BACKWARD_MOTOR_TRAS_DERECHO, 0);
	change_velocidad(4, 1 | BACKWARD_MOTOR_TRAS_IZQUIERDO, 0);
}

void mover_atras(){
	change_velocidad(1, 1 | BACKWARD_MOTOR_DEL_DERECHO, 0);
	change_velocidad(2, 1 | BACKWARD_MOTOR_DEL_IZQUIERDO, 0);
	change_velocidad(3, 1 | FORWARD_MOTOR_TRAS_DERECHO, 0);
	change_velocidad(4, 1 | FORWARD_MOTOR_TRAS_IZQUIERDO, 0);
}

void girar_derecha(){
	change_velocidad(1, 1 | FORWARD_MOTOR_DEL_DERECHO, 0);
	change_velocidad(2, 1 | FORWARD_MOTOR_DEL_IZQUIERDO, 0);
	change_velocidad(3, 1 | FORWARD_MOTOR_TRAS_DERECHO, 0);
	change_velocidad(4, 1 | FORWARD_MOTOR_TRAS_IZQUIERDO, 0);
}

void girar_izquierda(){
	change_velocidad(1, 1 | BACKWARD_MOTOR_DEL_DERECHO, 0);
	change_velocidad(2, 1 | BACKWARD_MOTOR_DEL_IZQUIERDO, 0);
	change_velocidad(3, 1 | BACKWARD_MOTOR_TRAS_DERECHO, 0);
	change_velocidad(4, 1 | BACKWARD_MOTOR_TRAS_IZQUIERDO, 0);
}


void mandar_a_todos_motores(byte numParam, byte instruction){

}
*/
/******************************
 *
 * PRÁCTICA 4_PIH Programació de Ports i pràctica de: "do-while" "case" "if" i "for"
 *
 *****************************/

#include "constants.h"
#include "hal_lcd.h"
#include "control_pantalla.h"
#include "fisica.h"
#include "gestion_robot.h"

long int i;

byte referencia;

void tratarRespuesta(byte respuesta) {
	// Por la nuevo estructura no va

	//sprintf(cadena," %x ", respuesta);
	//escribir(cadena, 1);
	if((respuesta & 2 ) | (respuesta) == 2){

	}
	else if (respuesta & referencia != referencia){
		if(referencia)
		girar_izquierda();
	}
	/*
	else if((respuesta & 1) == 1){//
		girar_derecha();
	}

	else if((respuesta & 4) == 4){//
		girar_izquierda();
	}

	*/
	else{
		mover_delante();
	}
}

/************
 * MAIN
 ************
 */
void main(void)
{
	init_UCS();
	init_UART();
   	WDTCTL = WDTPW+WDTHOLD;       	// Paramos el watchdog timer

  	init_botons();					// Iniciamos los botones y Leds.

    init_LCD();						// Inicializamos la pantalla
    _enable_interrupt();
//  	linea++; 					//Aumentamos el valor de linea y con ello pasamos a la linea siguiente

  	referencia=1;

  	P4OUT = 0x01;


  	//AQUI------Nuevo--------------------------
/*
  	init_motor(1);
  	init_motor(2);
  	init_motor(3);
  	init_motor(4);
*/
//  	angulo_a0(1);
//  	escribirRx(RxPacket());
 // 	change_velocidad(1, 1, 0);
 // 	escribirRx(RxPacket());

  	//gbpParameter[0] = P_LED; //Address of LED
  	//gbpParameter[1] = 1; //Writing Data encender
  	/*bTxPacketLength =*/
  	//TxPacket(4,0,INST_PING);
  	//escribirRx(RxPacket());
  	//TxPacket(4,2,INST_WRITE);
  	//gbpParameter[1] = 0;//apagar
  	//TxPacket(1,2,INST_WRITE);
  	//bRxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);



  	//-----------------------




  	do//do While de todo el programa
   	{
  		//el programa espera a una interrupcion

  		read_left();
  		read_center();
  		read_right();

  		tratarRespuesta(obstacle_detection());
   	}while(1);
}

/******************************
 *
 * PRÁCTICA 4_PIH Programació de Ports i pràctica de: "do-while" "case" "if" i "for"
 *
 *****************************/

#include <msp430x54xA.h>
#include <stdio.h>
#include "hal_lcd.h"
#include "envio_recibir_instruc.h"
#include "control_pantalla.h"

#include "motores.h"
#include "sensor.h"
volatile long int delay_cont;
long int i;

byte referencia;




/**************************************************************************
 * INICIALIZACIÓN DE LOS BOTONES.
 * Configuramos botones y leds:
 *
 * Sin datos de entrada
 *
 * Sin datos de salida
 *
 **************************************************************************/

void init_botons(void)
{
  //Configuramos botones y leds:
  P1DIR |= 0x03;	//Puertos P1.0 y P1.1 como salidas (Leds)
  P1OUT |= 0x01;	//Inicializamos puerto P1.0 a 1,
  P1OUT &= 0xFD;	// y P1.1 a 0, para leds en alternancia


  P2DIR &= ~0xC0;	//Puertos P2.6 y P2.7 como entradas (botones S1 y S2)
  P2SEL &= ~0xC0;	//Puertos P2.6 y P2.7 como I/O digitales,
  P2REN |= 0xC0;	//con resistencia activada
  P2OUT |= 0xC0;	// de pull-up
  P2IE |= 0xC0; 	//Interrupciones activadas en P2.6 y P2.7,
  P2IES &= ~0xC0;	// con transicion L->H


  //Configuramos el joystick:
  P2DIR &= ~0x3E;	//Puertos P2.1 a P2.5 como entradas (joystick)
  P2SEL &= ~0x3E;	//Puertos P2.1 y P2.5 como I/O digitales,
  P2REN |= 0x3E;	//con resistencia activada
  P2OUT |= 0x3E;	// de pull-up
  P2IE |= 0x3E; 	//Interrupciones activadas en P2.1 a P2.5,
  P2IES &= ~0x3E;	// con transicion L->H

}

void init_B0(void){
	TB0CTL= 0x0110;//ACLK y UP
	TB0CCR0 = 0x20;//MILISEGUNDO
	TB0CCTL0 = CCIE;//enable interrupt
}


void escribirRx(struct RxReturn respuesta ){
	byte bCount;
    for(bCount = 0; bCount < respuesta.StatusPacket[3]; bCount++){

    sprintf(cadena," %x ", respuesta.StatusPacket[bCount+4]);
    escribir(cadena, bCount+1);
    }
}

void escribirRxSensor(int linea, struct RxReturn respuesta ,char on){

    sprintf(cadena," %x ", respuesta.StatusPacket[5]);
    escribir(cadena, linea);
}

void tratarRespuesta(byte respuesta) {
	sprintf(cadena," %x ", respuesta);
	escribir(cadena, 1);
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

void delay(long int algo){
	delay_cont=algo;
	while(delay_cont>0);
	delay_cont=-1;
}

void circular_ref_derecha(){
	int arreglaProblemas=0;
	while(1){
		if(arreglaProblemas>=5){
			mover_delante();
			delay(500);
			arreglaProblemas=0;
		}
		if((obstacle_detection() & 2) == 2){//MIRAR DELANTE

			girar_izquierda();
			delay(1000);

		}else if((obstacle_detection() & 4) == 4){//CERCA derecha?

			girar_izquierda();
			delay(500);

		}else if(lejos_derecha()){

			girar_derecha();
			delay(500);


		}else{
			arreglaProblemas=0;
			mover_delante();
			delay(500);
		}
		arreglaProblemas++;
	}
}


void circular_ref_izquierda(){
	int arreglaProblemas=0;
	while(1){
		if(arreglaProblemas>=5){
			mover_delante();
			delay(500);
			arreglaProblemas=0;
		}
		if((obstacle_detection() & 2) == 2){//MIRAR DELANTE

			girar_derecha();
			delay(1000);

		}else if((obstacle_detection() & 1) == 1){//CERCA izquierda?

			girar_derecha();
			delay(500);
		}else if(lejos_izquierda()){

			girar_izquierda();
			delay(500);
		}else{
			arreglaProblemas=0;
			mover_delante();
			delay(500);
		}
		arreglaProblemas++;
	}

}

void init_lado(){
	int respuesta;
	while(!referencia){

		respuesta=obstacle_detection();

		if((respuesta & 2 )  == 2){
			girar_derecha();
			delay(1000);

			referencia=1; //referencia izquierda
		}


		else if((respuesta & 1) == 1){//
			referencia=1; //referencia izquierda
		}

		else if((respuesta & 4) == 4){//
			referencia=2; //referencia derecha
		}else{
			mover_delante();
			delay(500);
		}
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
  	init_B0();

    init_LCD();						// Inicializamos la pantalla
    _enable_interrupt();
  	linea++; 					//Aumentamos el valor de linea y con ello pasamos a la linea siguiente

  	referencia=0;

  	P4OUT = 0x01;




  	do//do While de todo el programa
   	{
  		//el programa espera a una interrupcion
  		referencia=0;
  		init_lado();
  		if(referencia==1){
  			circular_ref_izquierda();
  		}else if(referencia == 2){
  			circular_ref_derecha();
  		}
   	}while(1);
}


/**************************************************************************
 * MINIPROGRAMA DE LOS BOTONES:
 * Mediante este programa, se detectará que botón se ha pulsado
 *
 * Sin Datos de entrada
 *
 * Sin datos de salida
 *
 * Actualiza el valor estado
 *
 **************************************************************************/

#pragma vector=PORT2_VECTOR  //interrupción de los botones. Actualiza el valor de la variable global estado.
__interrupt void Port2_ISR(void)
{
	P2IE &= 0xC0; 	//interrupciones botones S1 y S2 (P2.6 y P2.7) desactivadas
	P2IE &= 0x3E;   //interrupciones joystick (2.1-2.5) desactivadas

	/**********************************************************+
		A RELLENAR POR EL ALUMNO BLOQUE CASE

	Boton S1, estado =1 y editar horas(del reloj o la alarma)
	Boton S2, estado =2 y editar minutos(del reloj o la alrma)
	Joystick left, estado =3 y los LEDs rotan a la izquierda
	Joystick right, estado =4 y los LEDs rotan a la derecha
	Joystick center, estado = 5 y Canvia Modo a Editar Reloj/Alarma
	Joystick up, estado =6 y disminuye el timer y van mas rapidos los LEDs
	Joystick down, estado =7 y aumenta el timer y van mas lentos los LEDs
	 * *********************************************************/

	switch(P2IFG){

	case 2://Joystick a la izquierda
		girar_izquierda();
		break;
	case 4:// Joystick a l derecha
		girar_derecha();
		break;
	case 8://Joystick centro

		break;
	case 16://Joystick Arriba
		mover_delante();
		break;
	case 32://Joystick abajo
		mover_atras();
		break;
	case 64://Boton S1
		parar();
		break;
	case 128://boton S2

		break;
	}

	/***********************************************
   	 * HASTA AQUI BLOQUE CASE
   	 ***********************************************/
	
	P2IFG = 0;		//limpiamos todas las interrupciones
	P2IE |= 0xC0; 	//interrupciones botones S1 y S2 (P2.6 y P2.7) reactivadas
	P2IE |= 0x3E;  //interrupciones joystick (2.1-2.5) reactivadas
 return;
}





#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
//interrupcion de recepcion en la uart A0
UCA0IE &= ~UCRXIE; //Interrupciones desactivadas en RX
DatoLeido_UART = UCA0RXBUF;
Byte_Recibido=1;

UCA0IE |= UCRXIE; //Interrupciones reactivadas en RX
}

#pragma vector=TIMERB0_VECTOR
__interrupt void Interrupcion_B0(void){

	if(delay_cont>= 0){
		delay_cont--;
	}
}

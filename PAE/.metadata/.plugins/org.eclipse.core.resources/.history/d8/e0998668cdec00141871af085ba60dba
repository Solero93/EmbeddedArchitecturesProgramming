/*
 * envio_recibir_instruc.h
 *
 *  Created on: 26/4/2015
 *      Author: Administrador
 */

byte DatoLeido_UART;
int Byte_Recibido;//1=si 0=no


volatile byte gbpRxInterruptBuffer[256];
byte gbpParameter[128];
byte gbpTxBuffer[32];






void Sentit_Dades_Rx(void)
{
		//Configuració del Half Duplex dels motors: Recepció
P3OUT &= ~0x80;	//El pin P3.7 (DIRECTION_PORT) el posem a0 (Rx)
}




void Sentit_Dades_Tx(void)
{
		//Configuració del Half Duplex dels motors: Transmissió
	P3OUT |= 0x80;	//El pin P3.7(DIRECTION_PORT) el posem a 1 (Tx)
}


void init_UCS(void)
{
    //inicialització de les freqüències de rellotge del microcontrolador
    unsigned long DCORSEL = DCORSEL_7;	//DCORSEL_6 selecciona rango de DCO de 7 a 60 MHz
    unsigned short FLLN = 487;		//Parametro N
    __bis_SR_register(SCG0);		// Desactiva el FLL control loop
    UCSCTL0 = 0x00;			// Posa DCOx, MODx al mínim possible
    UCSCTL1 = DCORSEL;			// Seleccionem el rang de DCO 16 MHz
    UCSCTL2 = FLLN + FLLD_1;		//Selecciona el factor multiplicador del DCO
    UCSCTL3 = 0;			//Referència FLL SELREF = XT1, divisor =1;
    /* Selecció de la font de rellotge: ACLK el Clock extern de 2^015, SMCLK i MCLK el DCO intern de 16MHz */
    UCSCTL4 = SELA__XT1CLK | SELS__DCOCLKDIV | SELM__DCOCLKDIV ;
    UCSCTL5 = DIVA__1 | DIVS__1;	//Divisor per SMCLK: f(SMCLK)/1 i ACLK: f(ACLK)/1
    __bic_SR_register(SCG0);		// Enable the FLL control loop
    P11DIR = 0x07;			//Configurem els pins 11.0, 11.1 y 11.2 com sortida
    P11SEL = 0x07;			//ACLK, MCLK y SMCLK; activem els pins de test
}



void init_UART(void)
{
UCA0CTL1 |= UCSWRST; 		//Fem un reset de la USCI i es desactiva
UCA0CTL0 = 0x00;		//UCSYNC=0 mode asíncron
				//UCMODEx=0 seleccionem mode UART
				//UCSPB=0 nomes 1 stop bit
				//UC7BIT=0 8 bits de dades
				//UCMSB=0 bit de menys pes primer
				//UCPAR=x no es fa servir bit de paritat
				//UCPEN=0 sense bit de paritat
UCA0CTL1 |= UCSSEL__SMCLK;	//Triem SMCLK (16MHz) com a font del clock BRCLK
UCA0BR0 = 1; 			//Prescaler de BRCLK fixat a 1 (LO byte = 1, ...
UCA0BR1 = 0;			//... HI byte = 0).
UCA0MCTL = UCOS16;		// No necessitem modulació (divisió entera), però
				// si oversampling => bit 0 = UCOS16 = 1.
				// El Baud rate és BRCLK/16=1MBps
P3SEL |= 0x30;			//I/O funcion: P3.4 = UART0TX, P3.5 = UART0RX
P3REN |= 0x20;			//amb resistència activada de pull-up l’entrada P3.5
P3OUT |= 0x20;			//
P3DIR |= 0x80;			//Port P3.7 com sortida (Data Direction: selector Tx/Rx)
P3SEL &= ~0x80;			//Port 3.7 com I/O digital
P3OUT &= ~0x80;			//Inicialitzem el port P3.7 a 0 (Rx)
UCA0CTL1 &= ~UCSWRST;		//Reactivem la línia de comunicacions sèrie
UCA0IE |= UCRXIE;		//Això s’ha d’activà només quan fem la recepció
}


/*
 * funció TxUAC0(byte): envia un byte de dades per la UART 0
 * */
void TxUAC0(byte bTxdData)
{
	while(!TXD0_READY); // Espera a que estigui preparat el buffer de transmissió
	UCA0TXBUF = bTxdData;
}







/*
TxPacket() necessita 3 paràmetr es; ID del Dynamixel, Instruction byte, Mida dels paràmetres.
TxPacket() torna la mida del "Return packet" des del Dynamixel.
*/

byte TxPacket(byte bID, byte bParameterLength, byte bInstruction)
{
	byte bCount,bCheckSum,bPacketLength;
	//byte gbpTxBuffer[32];
	Sentit_Dades_Tx(); //El pin P3.7(DIRECTION_PORT) el posem a 1 (Tx)
	gbpTxBuffer[0] = 0xff;//Primers 2 bytes que indiquen inici de trama FF, FF.
	gbpTxBuffer[1] = 0xff;
	gbpTxBuffer[2] = bID; //ID del mòdul al que volem enviar el missatge
	gbpTxBuffer[3] = bParameterLength+2;//Length(Parameter,Instruction,Checksum)
	gbpTxBuffer[4] = bInstruction;//Instrucció que enviem al mòdul

	for(bCount = 0; bCount < bParameterLength; bCount++)//Comencem a generar la trama
	{
		gbpTxBuffer[bCount+5] = gbpParameter[bCount];
	}

	bCheckSum = 0;
	bPacketLength = bParameterLength+4+2;

	for(bCount = 2; bCount <bPacketLength-1; bCount++)//Càlcul del Checksum
	{
		bCheckSum += gbpTxBuffer[bCount];
	}


	gbpTxBuffer[bCount] = ~bCheckSum;//Escriu el Checksum(complement a 1)
	for(bCount = 0; bCount < bPacketLength; bCount++)//Aquest bucle és el que enviala trama
	{
		TxUAC0(gbpTxBuffer[bCount]);
	}

	while((UCA0STAT & UCBUSY));//Espera fins s’ha transmès el últim byte

	Sentit_Dades_Rx();//Posem la línia de dades en Rx perquè el mòdul Dynamixel envia resposta


	return (bPacketLength);
}





struct RxReturn RxPacket(void) {
        struct RxReturn respuesta;
        byte bCount, bLenght, bChecksum;
        byte Rx_time_out=0;
        Sentit_Dades_Rx(); //Ponemos la linea half duplex en Rx
        //init_A1();
        long int delay;
        respuesta.time_out=0;
        for(bCount = 0; bCount < 4; bCount++) //bRxPacketLength; bCount++)
        {
                delay=125000;
                Byte_Recibido=0; //No_se_ha_recibido_Byte();
                while (Byte_Recibido==0) //Se_ha_recibido_Byte())
                {
                         // tiempo en decenas de microsegundos
                		delay--;
                		if (delay<=0){
                			Rx_time_out=1;
                		}
                        if (Rx_time_out)break;//sale del while
                }
                if (Rx_time_out)break; //sale del for si ha habido Timeout
                        //Si no, es que todo ha ido bien, y leemos un dato:
                        respuesta.StatusPacket[bCount] = DatoLeido_UART; //Get_Byte_Leido_UART();
        }//fin del for
        if (!Rx_time_out)
        	respuesta.time_out=1;
        // Continua llegint la resta de bytes del Status Packet
        return respuesta;
}


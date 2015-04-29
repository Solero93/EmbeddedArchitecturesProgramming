//Defines
 typedef static unsigned char byte;
#ifndef TXD0_READY
#define TXD0_READY (UCA0IFG & UCTXIFG)
#define RXD0_READY (UCA0IFG & UCRXIFG)
#endif

//--- Instruction ---
#ifndef INST_PING
#define INST_PING 0x01

#define INST_READ 0x02

#define INST_WRITE 0x03
#define INST_REG_WRITE 0x04
#define INST_ACTION 0x05
#define INST_RESET 0x06
#define INST_DIGITAL_RESET 0x07
#define INST_SYSTEM_READ 0x0C
#define INST_SYSTEM_WRITE 0x0D
#define INST_SYNC_WRITE 0x83
#define INST_SYNC_REG_WRITE 0x84
#endif



byte DatoLeido_UART;
static int Byte_Recibido;//1 = si 0 = no


volatile byte gbpRxInterruptBuffer[256];
byte gbpParameter[128];
byte gbpTxBuffer[32];



//Estructura de el retorn
 typedef static struct RxReturn{
        byte StatusPacket[32];
        byte time_out;
} RxReturn;


//Variable PantallaLCD
static char cadena[17];
static char borrado[] = "                 ";
static unsigned char contraste   = 0x64;
static unsigned char iluminacion  = 30;
static unsigned char linea = 1;

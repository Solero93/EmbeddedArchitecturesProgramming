//Defines
typedef unsigned char byte;
#define TXD0_READY (UCA0IFG & UCTXIFG)
#define RXD0_READY (UCA0IFG & UCRXIFG)


//--- Instruction ---
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


//Defines de la comunicacion con motores
#define P_LED 0x19

//Estructura de el retorn
typedef struct RxReturn{
        byte StatusPacket[32];
        byte time_out;
} RxReturn;


//Variable PantallaLCD
char cadena[17];
char borrado[] = "                 ";
unsigned char contraste   = 0x64;
unsigned char iluminacion  = 30;
unsigned char linea = 1;

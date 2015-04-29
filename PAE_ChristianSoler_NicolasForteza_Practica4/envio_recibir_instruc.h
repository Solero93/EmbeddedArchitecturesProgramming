


void Sentit_Dades_Rx(void);

void Sentit_Dades_Tx(void);

void init_UCS(void);

void init_UART(void);

void TxUAC0(byte bTxdData);

byte TxPacket(byte bID, byte bParameterLength, byte bInstruction);

struct RxReturn RxPacket(void);

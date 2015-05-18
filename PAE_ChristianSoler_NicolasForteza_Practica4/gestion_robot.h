// MOTORES

void angulo_a0(byte bID);

void change_velocidad(byte bID, byte H, byte L);

void init_motor(byte bID);

void mover_delante();

void parar();

void mover_atras();

void girar_derecha();

void girar_izquierda();

void mandar_a_todos_motores(byte numParam, byte instruction);

void ping(byte bID);

void encender_LED(byte bID);

void apagar_LED(byte bID);

// SENSORES

void init_sensor();

int obstacle_detection();

int read_left();

int read_center();

int read_right();

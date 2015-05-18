//Defines
#include <msp430x54xA.h>
#include <stdio.h>

typedef unsigned char byte;

typedef struct RxReturn{
        byte StatusPacket[32];
        byte time_out;
} RxReturn;

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

//DEFINE DE MOTORES
//--- Control Table Address ---
//EEPROM AREA
#define P_CW_ANGLE_LIMIT_L 0x06
#define P_CW_ANGLE_LIMIT_H 0x07
#define P_CCW_ANGLE_LIMIT_L 0x08
#define P_CCW_ANGLE_LIMIT_H 0x09
#define P_GOAL_POSITION_L 0x1E
#define P_GOAL_POSITION_H 0x1F
#define P_GOAL_SPEED_L 0x20
#define P_GOAL_SPEED_H 0x21

#define MOTOR_DEL_DERECHO 0x02
#define FORWARD_MOTOR_DEL_DERECHO 0x05
#define BACKWARD_MOTOR_DEL_DERECHO 0x01

#define MOTOR_DEL_IZQUIERDO 0x03
#define FORWARD_MOTOR_DEL_IZQUIERDO 0x01
#define BACKWARD_MOTOR_DEL_IZQUIERDO 0x05

#define MOTOR_TRAS_DERECHO 0x01
#define FORWARD_MOTOR_TRAS_DERECHO 0x05
#define BACKWARD_MOTOR_TRAS_DERECHO 0x01

#define MOTOR_TRAS_IZQUIERDO 0x04
#define FORWARD_MOTOR_TRAS_IZQUIERDO 0x01
#define BACKWARD_MOTOR_TRAS_IZQUIERDO 0x05

//DEFINES DE SENSORES
#define LEFT_IR_SENSOR_DATA 26
#define CENTER_IR_SENSOR_DATA 27
#define RIGHT_IR_SENSOR_DATA 28
#define OBSTACLE_DETECTION_FLAG 32
#define OBSTACLE_DETECTED_COMPARE 52

#define SENSOR_ID 100
#define OBSTACLE_VALUE 0x0F // Needs to be changed and tried out

//DEFINES DE PANTALLA
#define OVERWRITE_TEXT BIT2

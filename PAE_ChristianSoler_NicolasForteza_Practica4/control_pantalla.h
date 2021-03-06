/*
 * control_pantalla.h
 *
 *  Created on: 20/04/2015
 *      Author: mat.aules
 */
//Variable PantallaLCD
char cadena[17];
char borrado[] = "                 ";
unsigned char contraste   = 0x64;
unsigned char iluminacion  = 30;
unsigned char linea = 1;


/**************************************************************************
 * BORRAR LINEA
 *
 * Datos de entrada: Linea, indica la linea a borrar
 *
 * Sin datos de salida
 *
 **************************************************************************/

void borrar(unsigned char Linea)
{
	halLcdPrintLine(borrado, Linea, OVERWRITE_TEXT); //incluimos una linea en blanco
}


/**************************************************************************
 * ESCRIBIR LINEA
 *
 * Datos de entrada: Linea, indica la linea a escribir
 * 					 String, cadena de caracteres que vamos a introducir
 *
 * Sin datos de salida
 *
 **************************************************************************/

void escribir(char String[], unsigned char Linea)

{
	halLcdPrintLine(String, Linea, OVERWRITE_TEXT); //superponemos la nueva palabra introducida, haya o no algo.
}

/***********************************************************
 * Inicializa la pantalla
 *
 * Sin Datos de entrada
 *
 * Sin Datos de salida
 * *******************************************************
 */
void init_LCD(void)
{

  halLcdInit();  //Programa interno para iniciar la pantalla
  halLcdBackLightInit(); // Inicio de Iluminación posterior de la pantalla
  halLcdSetBackLight(iluminacion); // Determinación de la Iluminación posterior de la pantalla
  halLcdSetContrast(contraste);//Establecimiento del contraste
  halLcdClearScreen();  //Limpiar (borrar) la pantalla
}

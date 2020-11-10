#ifndef VIAJE_H_INCLUDED
#define VIAJE_H_INCLUDED
#include <string>
#include <iostream>

using namespace std;

struct Esquema{
	char fila1[23] = "           11111111112";
	char fila2[23] = " |12345678901234567890";
	char fila3[23] = "----------------------";
	char fila4[23] = "A|OOOOOOOOOOOOOOOOOOOO";
	char fila5[23] = "B|OOOOOOOOOOOOOOOOOOOO";
	char fila6[23] = "======================";
	char fila7[23] = "C|OOOOOOOOOOOOOOOOOOOO";
};

struct Viaje{
	char destino[20];
	char turno[20];
	char fecha[20];
	Esquema esquema;
};

/*****************************************************************************///CONSTRUCTOR

Viaje crearViaje(char destino[20], char fecha[20], char turno[20]);

/*****************************************************************************///SETTERS

void setDestino(Viaje &viaje, char destino[20]);
void setFecha(Viaje &viaje, char fecha[20]);
void setTurno(Viaje &viaje, char turno[20]);
void setEsquema(Viaje &viaje, Esquema &esquema);

void setFilaA(Viaje &viaje, char fila[23]);
void setFilaB(Viaje &viaje, char fila[23]);
void setFilaC(Viaje &viaje, char fila[23]);

void setFila2(Viaje &viaje, char fila[23]);

/*****************************************************************************///GETTERS

char* getDestino(Viaje &viaje);
char* getFecha(Viaje &viaje);
char* getTurno(Viaje &viaje);
char* getFila1(Viaje &viaje);
char* getFila2(Viaje &viaje);
char* getFila3(Viaje &viaje);
char* getFila6(Viaje &viaje);
char* getFilaA(Viaje &viaje);
char* getFilaB(Viaje &viaje);
char* getFilaC(Viaje &viaje);


/*****************************************************************************///METODOS

void mostrarEsquema(Viaje &viaje);
void asignarAsiento(Viaje &viaje,char fila, int columna);
void liberarAsiento(Viaje &viaje,char fila, int columna);
bool validarAsientoVacio(Viaje &viaje,char fila, int columna);

/*****************************************************************************///FICHERO

void escribirFichero(Viaje &viaje);
void escribirFicheroDestino(Viaje &viaje);
void escribirFicheroFecha(Viaje &viaje);
void escribirFicheroTurno(Viaje &viaje);
void escribirFicheroDestinoFechaTurno(Viaje &viaje);
void leerFichero();
void modificacionFicheroAsignar(char destino[20], char fecha[20], char turno[20], char fila, int columna );
void modificacionFicheroLiberar(char destino[20], char fecha[20], char turno[20], char fila, int columna );

/*****************************************************************************///CONSULTAS
/*
void consultaPorDestino(char destino[20]);
void consultaPorFecha(char fecha[20]);
void consultaPorTurno(char turno[20]);
void consultaPorDestinoFecha(char destino[20], char fecha[20]);
void consultaPorDestinoTurno(char destino[20], char turno[20]);
void consultaPorFechaTurno( char fecha[20], char turno[20]);
void consultaPorServicio(char destino[20], char fecha[20], char turno[20]);
*/

#endif

#ifndef BINARIO_H_INCLUDED

struct Esquema{
	char fila1[23];
	char fila2[23];
	char fila3[23];
	char fila4[23];
	char fila5[23];
	char fila6[23];
	char fila7[23];
};

struct Viaje{
	char destino[20];
	char turno[20];
	char fecha[20];
	Esquema esquema;
};

#define BINARIO_H_INCLUDED

void leerFichero();
void leerFicheroDestino();
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

void mostrarEsquema(Viaje &viaje);

#endif // BINARIO_H_INCLUDED

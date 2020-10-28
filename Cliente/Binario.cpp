#include <iostream>
#include <cstdlib>
#include "Binario.h"

using namespace std;


void leerFichero(){			//lee el fichero completo

	FILE *fichero;
	FILE *fichero_txt;
	Viaje viaje;

	char* salto_linea ="\n";
	fichero = fopen("Servicios.bin","rb");
	fichero_txt = fopen("Servicios.txt","wt");

	if(fichero == NULL){									//verifica si fichero existe
		cout<<"no existe fichero"<<endl;					//imprime error en pantalla
	}else{
		fread(&viaje, sizeof(Viaje),1,fichero);
		while(! feof(fichero)){
			cout<<"------------------------"<<endl;
			cout<< getDestino(viaje)<<endl;
			cout<< getFecha(viaje)<<endl;
			cout<< getTurno(viaje)<<endl;
			cout<<endl;
			mostrarEsquema(viaje);
			cout<<endl;
			cout<<"------------------------"<<endl;


			fputs(salto_linea,fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs("******************************",fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(getDestino(viaje),fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(getFecha(viaje),fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(getTurno(viaje),fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(getFila1(viaje),fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(getFila2(viaje),fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(getFila3(viaje),fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(getFilaA(viaje),fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(getFilaB(viaje),fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(getFila6(viaje),fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(getFilaC(viaje),fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs("******************************",fichero_txt);
			fputs(salto_linea,fichero_txt);
			fputs(salto_linea,fichero_txt);

			fread(&viaje, sizeof(Viaje), 1,fichero);
		}
	}
	fclose(fichero);
	fclose(fichero_txt);

}


char* getDestino(Viaje &viaje){
	return viaje.destino;
};
char* getFecha(Viaje &viaje){
	return viaje.fecha;
};
char* getTurno(Viaje &viaje){
	return viaje.turno;
};
char* getFila1(Viaje &viaje){
	return viaje.esquema.fila1;
};
char* getFila2(Viaje &viaje){
	return viaje.esquema.fila2;
};
char* getFila3(Viaje &viaje){
	return viaje.esquema.fila3;
};
char* getFilaA(Viaje &viaje){
	return viaje.esquema.fila4;
};
char* getFilaB(Viaje &viaje){
	return viaje.esquema.fila5;
};
char* getFila6(Viaje &viaje){
	return viaje.esquema.fila6;
};
char* getFilaC(Viaje &viaje){
	return viaje.esquema.fila7;
};

/*******************************************************///METODOS

void mostrarEsquema(Viaje &viaje){
	cout<< getFila1(viaje)<<endl;			//TRAE LA FILA 1 DEL ESQUEMA Y LA IMPRIME
	cout<< getFila2(viaje)<<endl;			//TRAE LA FILA 2 DEL ESQUEMA Y LA IMPRIME
	cout<< getFila3(viaje)<<endl;			//ASI HASTA COMPLETAR TODAS LAS FILAS DEL ESQUEMA
	cout<< getFilaA(viaje)<<endl;
	cout<< getFilaB(viaje)<<endl;
	cout<< getFila6(viaje)<<endl;
	cout<< getFilaC(viaje)<<endl;
	cout<<endl;
};

#include "Viaje.h"
#include <string.h>



Viaje crearViaje(char destino[20], char fecha[20], char turno[20]){

	Viaje viaje;			//CREA VARIABLE TIPO VIAJE
	Esquema esquema;		//CREA VARIABLE TIPO ESQUEMA
	setDestino(viaje, destino);
	setFecha(viaje, fecha);
	setTurno(viaje, turno);
	setEsquema(viaje, esquema);		// EL ESQUEMA YA SE SETEA DESDE SU DECLARACION VACIO, ES DECIR, CON O'S EN TODOS LOS ASIENTOS.
	escribirFichero(viaje);			// guarda en el fichero el viaje creado
	return viaje;					//DEVUELVE EL VIAJE CON LOS DATOS SETEADOS POR PARAMETRO Y UN ESQUEMA DE BUS VACIO
}

/*******************************************************///SETTERS

void setDestino(Viaje &viaje, char destino[20]){
	strcpy(viaje.destino, destino);
}

void setFecha(Viaje &viaje, char fecha[20]){
	strcpy(viaje.fecha, fecha);
}

void setTurno(Viaje &viaje, char turno[20]){
	strcpy(viaje.turno, turno);
}

void setEsquema(Viaje &viaje, Esquema &esquema){
	viaje.esquema = esquema;
}

//SOLO NECESITO TRABAJAR SOBRE LAS FILAS A, B Y C QUEDANDO EL RESTO DE LAS FILAS ESTATICAS COMO SE DECLARARON EN UN PRINCIPIO.
void setFilaA(Viaje &viaje, char fila[23]){
	strcpy(viaje.esquema.fila4, fila);
}
void setFilaB(Viaje &viaje, char fila[23]){
	strcpy(viaje.esquema.fila5, fila);
}
void setFilaC(Viaje &viaje, char fila[23]){
	strcpy(viaje.esquema.fila7, fila);
}


void setFila2(Viaje &viaje, char fila[23]){
	strcpy(viaje.esquema.fila2, fila);
}

/*******************************************************///GETTERS
char* getDestino(Viaje &viaje){
	return viaje.destino;
}

char* getFecha(Viaje &viaje){
	return viaje.fecha;
}

char* getTurno(Viaje &viaje){
	return viaje.turno;
}

char* getFila1(Viaje &viaje){
	return viaje.esquema.fila1;
}

char* getFila2(Viaje &viaje){
	return viaje.esquema.fila2;
}

char* getFila3(Viaje &viaje){
	return viaje.esquema.fila3;
}

char* getFilaA(Viaje &viaje){
	return viaje.esquema.fila4;
}

char* getFilaB(Viaje &viaje){
	return viaje.esquema.fila5;
}

char* getFila6(Viaje &viaje){
	return viaje.esquema.fila6;
}

char* getFilaC(Viaje &viaje){
	return viaje.esquema.fila7;
}

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
}


/*****************************************************************************///FICHERO


void escribirFichero(Viaje &viaje){			//escribe un registro al final del fichero.

	FILE *fichero;					//crea puntero a fichero
	fichero = fopen("Servicios.bin","ab");
	if(fichero ==NULL){			//verifica si fichero existe y lo crea añadiendo datos al final sin pisar los datos ya guardados
		cout<<"no existe fichero"<<endl;					//imprime error en pantalla
	}else{
		fwrite(&viaje,sizeof(viaje),1,fichero);				//sino, escribe toda la estructura en el fichero
		fclose(fichero);									//cierra fichero
	}
}



void escribirFicheroDestino(Viaje &viaje){			//escribe un registro al final del fichero.

	FILE *ficheroDestino;
	                         			//crea puntero a fichero
	ficheroDestino = fopen("Destino.bin","ab");
	if(ficheroDestino ==NULL){			//verifica si fichero existe y lo crea añadiendo datos al final sin pisar los datos ya guardados
		cout<<"no existe fichero"<<endl;					//imprime error en pantalla
	}else{
		fwrite(&viaje,sizeof(viaje),1,ficheroDestino);				//sino, escribe toda la estructura en el fichero
		fclose(ficheroDestino);
                                        //cierra fichero
	}
}


void escribirFicheroFecha(Viaje &viaje){			//escribe un registro al final del fichero.

	FILE *ficheroFecha;					//crea puntero a fichero
	ficheroFecha = fopen("Fecha.bin","ab");
	if(ficheroFecha ==NULL){			//verifica si fichero existe y lo crea añadiendo datos al final sin pisar los datos ya guardados
		cout<<"no existe fichero"<<endl;					//imprime error en pantalla
	}else{
		fwrite(&viaje,sizeof(viaje),1,ficheroFecha);				//sino, escribe toda la estructura en el fichero
		fclose(ficheroFecha);									//cierra fichero
	}
}

void escribirFicheroTurno(Viaje &viaje){			//escribe un registro al final del fichero.

	FILE *ficheroTurno;					//crea puntero a fichero
	ficheroTurno = fopen("Turno.bin","ab");
	if(ficheroTurno ==NULL){			//verifica si fichero existe y lo crea añadiendo datos al final sin pisar los datos ya guardados
		cout<<"no existe fichero"<<endl;					//imprime error en pantalla
	}else{
		fwrite(&viaje,sizeof(viaje),1,ficheroTurno);				//sino, escribe toda la estructura en el fichero
		fclose(ficheroTurno);									//cierra fichero
	}
}

void escribirFicheroDestinoFechaTurno(Viaje &viaje){			//escribe un registro al final del fichero.

	FILE *ficheroDestinoFechaTurno;					//crea puntero a fichero
	ficheroDestinoFechaTurno = fopen("ServicioCompleto.bin","ab");
	if(ficheroDestinoFechaTurno ==NULL){			//verifica si fichero existe y lo crea añadiendo datos al final sin pisar los datos ya guardados
		cout<<"no existe fichero"<<endl;					//imprime error en pantalla
	}else{
		fwrite(&viaje,sizeof(viaje),1,ficheroDestinoFechaTurno);				//sino, escribe toda la estructura en el fichero
		fclose(ficheroDestinoFechaTurno);									//cierra fichero
	}
}

void escribirFicheroDestinoFecha(Viaje &viaje){

	FILE *ficheroDestinoFecha;					//crea puntero a fichero
	ficheroDestinoFecha = fopen("ServicioDestinoFecha.bin","ab");
	if(ficheroDestinoFecha ==NULL){			//verifica si fichero existe y lo crea añadiendo datos al final sin pisar los datos ya guardados
		cout<<"no existe fichero"<<endl;					//imprime error en pantalla
	}else{
		fwrite(&viaje,sizeof(viaje),1,ficheroDestinoFecha);				//sino, escribe toda la estructura en el fichero
		fclose(ficheroDestinoFecha);									//cierra fichero
	}

}


void leerFichero(){			//lee el fichero completo

	FILE *fichero;
	Viaje viaje;
	int i=0;
	fichero = fopen("Servicios.bin","rb");
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
                    cout <<i++;
                    fread(&viaje, sizeof(Viaje), 1,fichero);
                    system("pause");
		}
	}
	fclose(fichero);

}

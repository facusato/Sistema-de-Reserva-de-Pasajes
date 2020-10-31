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
};

/*******************************************************///SETTERS

void setDestino(Viaje &viaje, char destino[20]){
	strcpy(viaje.destino, destino);
};

void setFecha(Viaje &viaje, char fecha[20]){
	strcpy(viaje.fecha, fecha);
};

void setTurno(Viaje &viaje, char turno[20]){
	strcpy(viaje.turno, turno);
};

void setEsquema(Viaje &viaje, Esquema &esquema){
	viaje.esquema = esquema;
};

//SOLO NECESITO TRABAJAR SOBRE LAS FILAS A, B Y C QUEDANDO EL RESTO DE LAS FILAS ESTATICAS COMO SE DECLARARON EN UN PRINCIPIO.
void setFilaA(Viaje &viaje, char fila[23]){
	strcpy(viaje.esquema.fila4, fila);
};
void setFilaB(Viaje &viaje, char fila[23]){
	strcpy(viaje.esquema.fila5, fila);
};
void setFilaC(Viaje &viaje, char fila[23]){
	strcpy(viaje.esquema.fila7, fila);
};


void setFila2(Viaje &viaje, char fila[23]){
	strcpy(viaje.esquema.fila2, fila);
};

/*******************************************************///GETTERS
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


void asignarAsiento(Viaje &viaje, char fila, int columna){

	int columna_aux = columna + 1;
	char* fila_temporal;
	char* fila_temporal1 = getFila2(viaje);		// pasa pisar la linea 2 del esquema (no encontre porque se setea mal dado que en ninguna parte del codigo se toca)

	if(true){			// validar si viaje existe (por ahora entra siempre)


		if(fila == 'A' ||fila == 'a'){
			fila_temporal = getFilaA(viaje);				//TRAE LA FILA A DEL ESQUEMA COMPLETA

				if(fila_temporal[columna_aux] == 'O'){					//verifica si esta libre el asiento, si esta libre entra
					fila_temporal[columna_aux] = 'X';

					strcpy(fila_temporal1," |12345678901234567890");
					setFila2(viaje, fila_temporal1);

					setFilaA(viaje, fila_temporal);					//SETEA EN EL VIAJE DEL PARAMETRO LA FILA COMPLETA YA MODIFICADA
					cout<<"Se asigno el asiento para dicho viaje."<<endl;
					system("cls");
					mostrarEsquema(viaje);
				}else{
					cout<<"asiento ocupado"<<endl;					// sino avisa error en pantalla
				}
		}

		if(fila == 'B' ||fila == 'b'){
			fila_temporal = getFilaB(viaje);

				if(fila_temporal[columna_aux] == 'O'){				//verifica si esta libre el asiento, si esta libre entra
					fila_temporal[columna_aux] = 'X';

					strcpy(fila_temporal1," |12345678901234567890");
					setFila2(viaje, fila_temporal1);

					setFilaB(viaje, fila_temporal);					//SETEA EN EL VIAJE DEL PARAMETRO LA FILA COMPLETA YA MODIFICADA
					cout<<"Se asigno el asiento para dicho viaje."<<endl;
					mostrarEsquema(viaje);
				}else{
					cout<<"asiento ocupado"<<endl;					// sino avisa error en pantalla
				}
		}
		if(fila == 'C' ||fila == 'c'){
			fila_temporal = getFilaC(viaje);

				if(fila_temporal[columna_aux] == 'O'){				//verifica si esta libre el asiento, si esta libre entra
					fila_temporal[columna_aux] = 'X';

					strcpy(fila_temporal1," |12345678901234567890");
					setFila2(viaje, fila_temporal1);

					setFilaC(viaje, fila_temporal);					//SETEA EN EL VIAJE DEL PARAMETRO LA FILA COMPLETA YA MODIFICADA
					cout<<"Se asigno el asiento para dicho viaje."<<endl;
					mostrarEsquema(viaje);
				}else{
					cout<<"asiento ocupado"<<endl;					// sino avisa error en pantalla
				}
		}
	}else{
		cout<<"No existe el viaje, proceda a dar de alta el servicio"<<endl;
	}

};


void liberarAsiento(Viaje &viaje, char fila, int columna){

	int columna_aux = columna + 1;
	char* fila_temporal;
	char* fila_temporal1 = getFila2(viaje);		// pasa pisar la linea 2 del esquema (no encontre porque se setea mal dado que en ninguna parte del codigo se toca)

	if(true){			// validar si viaje existe (por ahora entra siempre)


		if(fila == 'A' ||fila == 'a'){
			fila_temporal = getFilaA(viaje);				//TRAE LA FILA A DEL ESQUEMA COMPLETA

				if(fila_temporal[columna_aux] == 'X'){				//verifica si esta ocupado el asiento, si esta ocupado entra
					fila_temporal[columna_aux] = 'O';

					strcpy(fila_temporal1," |12345678901234567890");
					setFila2(viaje, fila_temporal1);

					setFilaA(viaje, fila_temporal);					//SETEA EN EL VIAJE DEL PARAMETRO LA FILA COMPLETA YA MODIFICADA
					cout<<"Se libero el asiento para dicho viaje."<<endl;
					mostrarEsquema(viaje);
				}

		}

		if(fila == 'B' ||fila == 'b'){
			fila_temporal = getFilaB(viaje);

				if(fila_temporal[columna_aux] == 'X'){				//verifica si esta ocupado el asiento, si esta ocupado entra
					fila_temporal[columna_aux] = 'O';

					strcpy(fila_temporal1," |12345678901234567890");
					setFila2(viaje, fila_temporal1);

					setFilaB(viaje, fila_temporal);					//SETEA EN EL VIAJE DEL PARAMETRO LA FILA COMPLETA YA MODIFICADA
					cout<<"Se libero el asiento para dicho viaje."<<endl;
					mostrarEsquema(viaje);
				}

		}
		if(fila == 'C' ||fila == 'c'){
			fila_temporal = getFilaC(viaje);

				if(fila_temporal[columna_aux] == 'X'){						//verifica si esta ocupado el asiento, si esta ocupado entra
					fila_temporal[columna_aux] = 'O';

					strcpy(fila_temporal1," |12345678901234567890");
					setFila2(viaje, fila_temporal1);

					setFilaC(viaje, fila_temporal);					//SETEA EN EL VIAJE DEL PARAMETRO LA FILA COMPLETA YA MODIFICADA
					cout<<"Se libero el asiento para dicho viaje."<<endl;
					mostrarEsquema(viaje);
				}
			//}
		}
	}else{
		cout<<"no existe viaje, favor de crearlo primero"<<endl;
	}

};

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
};



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
};


void escribirFicheroFecha(Viaje &viaje){			//escribe un registro al final del fichero.

	FILE *ficheroFecha;					//crea puntero a fichero
	ficheroFecha = fopen("Fecha.bin","ab");
	if(ficheroFecha ==NULL){			//verifica si fichero existe y lo crea añadiendo datos al final sin pisar los datos ya guardados
		cout<<"no existe fichero"<<endl;					//imprime error en pantalla
	}else{
		fwrite(&viaje,sizeof(viaje),1,ficheroFecha);				//sino, escribe toda la estructura en el fichero
		fclose(ficheroFecha);									//cierra fichero
	}
};

void escribirFicheroTurno(Viaje &viaje){			//escribe un registro al final del fichero.

	FILE *ficheroTurno;					//crea puntero a fichero
	ficheroTurno = fopen("Turno.bin","ab");
	if(ficheroTurno ==NULL){			//verifica si fichero existe y lo crea añadiendo datos al final sin pisar los datos ya guardados
		cout<<"no existe fichero"<<endl;					//imprime error en pantalla
	}else{
		fwrite(&viaje,sizeof(viaje),1,ficheroTurno);				//sino, escribe toda la estructura en el fichero
		fclose(ficheroTurno);									//cierra fichero
	}
};


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


void modificacionFicheroAsignar(char destino[20], char fecha[20], char turno[20], char fila, int columna ){

    FILE *fichero;
    fichero=fopen("Servicios.bin","r+b");
        if (fichero==NULL)
            exit(1);

    Viaje viaje;
    int existe=0;			//flag para comprobar si existe el registro buscado.

    fread(&viaje, sizeof(Viaje), 1,fichero);
        while(!feof(fichero))
        {
            if (strcmp(getDestino(viaje),destino) == 0 && strcmp(getFecha(viaje),fecha) == 0 && strcmp(getTurno(viaje),turno) == 0)			//compara si coinciden registro leido con parametro
            {
                asignarAsiento(viaje,fila,columna);				//asigna el asiento al registro leido
                int pos=ftell(fichero)-sizeof(Viaje);			//lee la posicion del cursor en el fichero
                fseek(fichero,pos,SEEK_SET);						//reacomoda cursor en fichero
                fwrite(&viaje, sizeof(Viaje), 1, fichero);		//reescribe fichero modificado, pisando el anterior.
                existe=1;
                break;
            }
         fread(&viaje, sizeof(Viaje), 1, fichero);
        }
    if (existe==0)
        cout<<"No existe un viaje con dichos parametros"<<endl;
    fclose(fichero);
}



void modificacionFicheroLiberar(char destino[20], char fecha[20], char turno[20], char fila, int columna ){

    FILE *fichero;
    fichero=fopen("Servicios.bin","r+b");
    if (fichero==NULL)
        exit(1);

    Viaje viaje;
    int existe=0;			//flag para comprobar si existe el registro buscado.

    fread(&viaje, sizeof(Viaje), 1,fichero);
        while(!feof(fichero))
        {
            if (strcmp(getDestino(viaje),destino) == 0 && strcmp(getFecha(viaje),fecha) == 0 && strcmp(getTurno(viaje),turno) == 0)			//compara si coinciden registro leido con parametro
            {
                liberarAsiento(viaje,fila,columna);				//asigna el asiento al registro leido
                int pos=ftell(fichero)-sizeof(Viaje);			//lee la posicion del cursor en el fichero
                fseek(fichero,pos,SEEK_SET);						//reacomoda cursor en fichero
                fwrite(&viaje, sizeof(Viaje), 1, fichero);		//reescribe fichero modificado, pisando el anterior.
                existe=1;
                break;
            }
         fread(&viaje, sizeof(Viaje), 1, fichero);
        }
    if (existe==0)
        cout<<"No existe un viaje con dichos parametros"<<endl;
    fclose(fichero);
}

/*****************************************************************************///CONSULTAS

void consultaPorDestino(char destino[20]){

    FILE *fichero;
    fichero=fopen("Servicios.bin","rb");
    if (fichero==NULL)
        exit(1);

    Viaje viaje;
    int existe=0;
    fread(&viaje, sizeof(Viaje), 1, fichero);
    while(!feof(fichero))
    {
        if (strcmp(getDestino(viaje),destino)==0)
        {
        	cout<<"------------------------"<<endl;
			cout<< getDestino(viaje)<<endl;
			cout<< getFecha(viaje)<<endl;
			cout<< getTurno(viaje)<<endl;
			cout<<endl;
			//sacar el mostrar esquema para que no se vea del lado del server 15:50
			mostrarEsquema(viaje);
			escribirFicheroDestino(viaje);
			cout<<endl;
			cout<<"------------------------"<<endl;
        	existe=1;
        }
        fread(&viaje, sizeof(Viaje), 1, fichero);
    }
    if (existe==0)
        cout<<"No existe servicio con dichos parametros"<<endl;
    fclose(fichero);
}

void consultaPorFecha(char fecha[20]){

    FILE *fichero;
    fichero=fopen("Servicios.bin","rb");
    if (fichero==NULL)
        exit(1);

    Viaje viaje;
    int existe=0;
    fread(&viaje, sizeof(Viaje), 1, fichero);
    while(!feof(fichero))
    {
        if (strcmp(getFecha(viaje),fecha) == 0)
        {
        	cout<<"------------------------"<<endl;
			cout<< getDestino(viaje)<<endl;
			cout<< getFecha(viaje)<<endl;
			cout<< getTurno(viaje)<<endl;
			cout<<endl;
			mostrarEsquema(viaje);
			escribirFicheroFecha(viaje);
			cout<<endl;
			cout<<"------------------------"<<endl;
        	existe=1;
        }
        fread(&viaje, sizeof(Viaje), 1, fichero);
    }
    if (existe==0)
        cout<<"No existe servicio con dichos parametros"<<endl;
    fclose(fichero);
}

void consultaPorTurno(char turno[20]){

    FILE *fichero;
    fichero=fopen("Servicios.bin","rb");
    if (fichero==NULL)
        exit(1);

    Viaje viaje;
    int existe=0;
    fread(&viaje, sizeof(Viaje), 1, fichero);
    while(!feof(fichero))
    {
        if (strcmp(getTurno(viaje),turno) == 0)
        {
        	cout<<"------------------------"<<endl;
			cout<< getDestino(viaje)<<endl;
			cout<< getFecha(viaje)<<endl;
			cout<< getTurno(viaje)<<endl;
			cout<<endl;
			mostrarEsquema(viaje);
			escribirFicheroTurno(viaje);
			cout<<endl;
			cout<<"------------------------"<<endl;
        	existe=1;
        }
        fread(&viaje, sizeof(Viaje), 1, fichero);
    }
    if (existe==0)
        cout<<"No existe servicio con dichos parametros"<<endl;
    fclose(fichero);
}



void consultaPorDestinoFecha(char destino[20], char fecha[20]){

    FILE *fichero;
    fichero=fopen("Servicios.bin","rb");
    if (fichero==NULL)
        exit(1);

    Viaje viaje;
    int existe=0;
    fread(&viaje, sizeof(Viaje), 1, fichero);
    while(!feof(fichero))
    {
        if (strcmp(getDestino(viaje),destino) == 0 && strcmp(getFecha(viaje),fecha) == 0)
        {
        	cout<<"------------------------"<<endl;
			cout<< getDestino(viaje)<<endl;
			cout<< getFecha(viaje)<<endl;
			cout<< getTurno(viaje)<<endl;
			cout<<endl;
			mostrarEsquema(viaje);
			cout<<endl;
			cout<<"------------------------"<<endl;
        	existe=1;
        }
        fread(&viaje, sizeof(Viaje), 1, fichero);
    }
    if (existe==0)
        cout<<"No existe servicio con dichos parametros"<<endl;
    fclose(fichero);
}


void consultaPorDestinoTurno(char destino[20], char turno[20]){

    FILE *fichero;
    fichero=fopen("Servicios.bin","rb");
    if (fichero==NULL)
        exit(1);

    Viaje viaje;
    int existe=0;
    fread(&viaje, sizeof(Viaje), 1, fichero);
    while(!feof(fichero))
    {
        if (strcmp(getDestino(viaje),destino) == 0 && strcmp(getTurno(viaje),turno) == 0)
        {
        	cout<<"------------------------"<<endl;
			cout<< getDestino(viaje)<<endl;
			cout<< getFecha(viaje)<<endl;
			cout<< getTurno(viaje)<<endl;
			cout<<endl;
			mostrarEsquema(viaje);
			cout<<endl;
			cout<<"------------------------"<<endl;
        	existe=1;
        }
        fread(&viaje, sizeof(Viaje), 1, fichero);
    }
    if (existe==0)
        cout<<"No existe servicio con dichos parametros"<<endl;
    fclose(fichero);
}

void consultaPorFechaTurno( char fecha[20], char turno[20]){

    FILE *fichero;
    fichero=fopen("Servicios.bin","rb");
    if (fichero==NULL)
        exit(1);

    Viaje viaje;
    int existe=0;
    fread(&viaje, sizeof(Viaje), 1, fichero);
    while(!feof(fichero))
    {
        if (strcmp(getFecha(viaje),fecha) == 0 && strcmp(getTurno(viaje),turno) == 0)
        {
        	cout<<"------------------------"<<endl;
			cout<< getDestino(viaje)<<endl;
			cout<< getFecha(viaje)<<endl;
			cout<< getTurno(viaje)<<endl;
			cout<<endl;
			mostrarEsquema(viaje);
			cout<<endl;
			cout<<"------------------------"<<endl;
        	existe=1;
        }
        fread(&viaje, sizeof(Viaje), 1, fichero);
    }
    if (existe==0)
        cout<<"No existe servicio con dichos parametros"<<endl;
    fclose(fichero);
}


void consultaPorServicio(char destino[20], char fecha[20], char turno[20]){

    FILE *fichero;
    fichero=fopen("Servicios.bin","rb");
    if (fichero==NULL)
        exit(1);

    Viaje viaje;
    int existe=0;
    fread(&viaje, sizeof(Viaje), 1, fichero);
    while(!feof(fichero))
    {
        if (strcmp(getDestino(viaje),destino) == 0 && strcmp(getFecha(viaje),fecha) == 0 && strcmp(getTurno(viaje),turno) == 0)
        {
        	cout<<"------------------------"<<endl;
			cout<< getDestino(viaje)<<endl;
			cout<< getFecha(viaje)<<endl;
			cout<< getTurno(viaje)<<endl;
			cout<<endl;
			mostrarEsquema(viaje);
			cout<<endl;
			cout<<"------------------------"<<endl;
        	existe=1;
        }
        fread(&viaje, sizeof(Viaje), 1, fichero);
    }
    if (existe==0)
        cout<<"No existe servicio con dichos parametros"<<endl;
    fclose(fichero);
}






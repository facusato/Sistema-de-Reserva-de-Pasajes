#include <iostream>
#include <cstdlib>
#include "Binario.h"

using namespace std;


void leerFichero(){			//lee el fichero completo

	FILE *fichero;
	Viaje viaje;
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
                    fread(&viaje, sizeof(Viaje), 1,fichero);
                }
            }
        fclose(fichero);
}

void leerFicheroDestino(){			//lee el fichero completo

	FILE *fichero;
	Viaje viaje;
	fichero = fopen("Destino.bin","rb");
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
                    fread(&viaje, sizeof(Viaje), 1,fichero);
                }
        }
        fclose(fichero);
}

void leerFicheroFecha(){			//lee el fichero completo

	FILE *fichero;
	Viaje viaje;
	fichero = fopen("Fecha.bin","rb");
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
                    fread(&viaje, sizeof(Viaje), 1,fichero);
                }
        }
        fclose(fichero);
}

void leerFicheroTurno(){			//lee el fichero completo

	FILE *fichero;
	Viaje viaje;
	fichero = fopen("Turno.bin","rb");
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
                    fread(&viaje, sizeof(Viaje), 1,fichero);
                }
        }
        fclose(fichero);
}


void leerFicheroDestinoFechaTurno(){			//lee el fichero completo

	FILE *fichero;
	Viaje viaje;
	fichero = fopen("ServicioCompleto.bin","rb");
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
                    fread(&viaje, sizeof(Viaje), 1,fichero);
                }
        }
        fclose(fichero);
}

void leerFicheroDestinoFecha(){
    FILE *fichero;
    Viaje viaje;
    fichero = fopen("ServicioDestinoFecha.bin","rb");
        if(fichero == NULL){                                    //verifica si fichero existe
            cout<<"no existe fichero"<<endl;                    //imprime error en pantalla
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
                    fread(&viaje, sizeof(Viaje), 1,fichero);
                }
        }
        fclose(fichero);
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

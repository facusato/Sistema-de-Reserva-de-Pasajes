#include <iostream>
#include <cstdlib>

using namespace std;


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

void leerFichero();

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

int main(int argc, char** argv) {

	leerFichero();
	system("pause");
	return 0;
}

void leerFichero(){			//lee el fichero completo

	FILE *fichero;
	Viaje viaje;
	fichero = fopen("C:\\Users\\Notebook\\Sistema-de-Reserva-de-Pasajes\\Servidor\\bin\\Debug\\Servicios.bin","rb");

        if(fichero == NULL){									//verifica si fichero existe
            cout<<"\nNo existe el fichero binario\n"<<endl;					//imprime error en pantalla
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

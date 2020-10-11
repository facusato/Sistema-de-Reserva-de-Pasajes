#include <iostream>
#include <winsock2.h>
#include "Server.h"
#include <sstream>
#include <fstream>
using namespace std;

int main()
{
    Servidor servidor;
    string mensaje = "";
    int respuesta=0;
    bool valido=false;
    int puerto;
    int i=0;
    barraCargando();
    system("cls");
    cout<< "...BIENVENIDO AL SERVIDOR..."<<endl;
    cout<< "Ingrese el puerto: ";
    cin>> puerto;
    crearServidor(servidor,puerto);
        while (i<3 && !valido){
            if(validarCredencial(servidor)==true){
                enviarMensaje(servidor,"Correcto.");
                valido=true;
            }
            else{
                enviarMensaje(servidor,"Incorrecto.");
            }
            i++;
        }

    respuesta=recibirMensaje(servidor);
        while(respuesta!=2){
                if(respuesta==1){
                    recibirArchivo(servidor);
                }
                else{
                    enviarMensaje(servidor,"ok");
                    Sleep(1000);
                }
                respuesta=recibirMensaje(servidor);
        }

     cout<<"Esperando"<<endl;
    volver(servidor);
    Sleep(2000);
    return 0;
}

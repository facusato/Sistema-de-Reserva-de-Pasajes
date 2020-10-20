#include <iostream>
#include <winsock2.h>
#include "Server.h"
#include <sstream>
#include <fstream>
#include <ctime>
using namespace std;

int main()
{
    ofstream archivo;
    Servidor servidor;
    string mensaje = "";
    int respuesta=0;
    bool valido=false;
    int puerto;
    int i=1;
    barraCargando();
    system("cls");
    archivo.open("serverLog.txt",ios::out);
    if(archivo.fail()){
        cout<<"error al abrir o crear el archivo"<<endl;
    }
    cout<< "...BIENVENIDO AL SERVIDOR..."<<endl;
    cout<< "Ingrese el puerto: ";
    cin>> puerto;
    crearServidor(servidor,puerto);

    //Probando escribir el archivo de actividad del server
    archivo<<"========================================================================="<<endl;
    archivo<<"Inicia Servidor"<<endl;
    archivo<<"Socket creado. Puerto de escucha:"<<puerto<<endl;
    //ver como poner la fecha hora del sistema operativo en una cadena para grabarla en el archivo
    fechaHora();

        while (i<=3 && !valido){
            if(validarCredencial(servidor)==true){
                enviarMensaje(servidor,"Correcto.");
                valido=true;
            }
            else{
                enviarMensaje(servidor,"Incorrecto.");
                archivo<<"El cliente fallo al logueo en el intento:"<<i<<endl;
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

    archivo<<"El cliente se retiro de la conexion"<<endl;
    archivo<<"Esperando a un nuevo cliente"<<endl;
    volver(servidor);
    Sleep(2000);
    archivo.close();
    return 0;
}

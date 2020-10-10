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


        /*while (comando[0] != 'F' && fLagConexion != -1 )
        {
            if (flagRecibir == 0)
            {
                menu();
                Sleep(400);
                cin >> ws;
                cin.getline(comando, sizeof(comando));
                Sleep(400);

                if(comando[0] != 'F')
                {
                    switch(comando[0])
                    {
                    case 'M':
                        mensaje = msj(comando);
                        enviarMensaje(servidor,mensaje);
                        flagRecibir = 1;
                        break;
                    case 'T':
                        ruta = msj(comando);
                        enviarArchivo(servidor,ruta);
                        flagRecibir = 1;
                        break;
                    default:
                        cout<<endl<<"Comando equivocado."<<endl;
                        break;
                    }
                }
            }

        else{
            cout<<"Esperando respuesta del cliente..."<<endl;
            respuesta =recibirMensaje(servidor);

            if(respuesta == 1){
                recibirArchivo(servidor);
            }
            else if (respuesta == 2){
                fLagConexion = -1;
            }
            flagRecibir = 0;
        }
    }*/
    respuesta=recibirMensaje(servidor);
        do{
                if(respuesta==1){
                    recibirArchivo(servidor);
                }
                else{
                    enviarMensaje(servidor,"ok");
                }
                respuesta=recibirMensaje(servidor);
        }while(respuesta==2);


    cout<<endl;
    enviarMensaje(servidor,"Se cerro el socket.");
    cout<<"El cliente cerro la sesion"<<endl;
    Sleep(1000);
    cout<<endl;
    enviarMensaje(servidor,"Se cerro el socket.");
    cout<<"El cliente cerro la sesion"<<endl;
    cerrarSocket(servidor);
    cout<<endl<<"Saliendo del sistema..."<<endl;
    Sleep(2000);
    return 0;
}

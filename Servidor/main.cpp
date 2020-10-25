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
    bool seguir=true;
    int opcion,i=0;
    barraCargando();
    system("cls");
    archivo.open("serverLog.txt",ios::app);
        if(archivo.fail()){
            cout<<"error al abrir o crear el archivo"<<endl;
        }
    cout<< "...BIENVENIDO AL SERVIDOR..."<<endl;
    cout<< "Ingrese el puerto: ";
    cin>> puerto;
    crearServidor(servidor,puerto);
    //Poner condicion para que si el cliente esta conectado y por 2 min no envia nada lo saque de la conexion
    //DWORD time_out=120*1000;
    //setsockopt(servidor.server,SOL_SOCKET,SO_RCVTIMEO,(const char *)&time_out,sizeof(time_out));
    archivo<<"========================================================================="<<endl;
    archivo<<fechaHora();
    archivo<<" Inicia Servidor"<<endl;
    archivo<<fechaHora();
    archivo<<" Socket creado. Puerto de escucha: "<<puerto<<endl;

        while(seguir){
            valido=false;
            i=0;

                while (i<3 && !valido){
                    if(validarCredencial(servidor)==true){
                        enviarMensaje(servidor,"Correcto.");
                        archivo<<fechaHora();
                        archivo<<" El cliente ingreso al sistema"<<endl;
                        valido=true;
                    }
                    else{
                        enviarMensaje(servidor,"Incorrecto.");
                        archivo<<fechaHora();
                        archivo<<" El cliente fallo al logueo en el intento:"<<i+1<<endl;
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

    archivo<<fechaHora();
    archivo<<" El cliente se retiro de la conexion"<<endl;
    Sleep(1000);

            //while(opcion!=2 && opcion!=1){
            system("cls");
            cout<<" 1- ESPERAR UN NUEVO CLIENTE \n"<<endl;
            cout<<" 2- CERRAR CONEXION \n"<<endl;
            cout << "\n INGRESE LA OPCION DESEADA: ";
            cin>>opcion;
                switch(opcion){
                    case 1:
                        archivo<<"========================================================================="<<endl;
                        archivo<<fechaHora();
                        archivo<<" Esperando a un nuevo cliente"<<endl;
                        barraCargando();
                        system("cls");
                        cout<<"\n"<<endl;
                        volver(servidor);
                        Sleep(1000);
                        break;
                    case 2:
                        seguir=false;
                        cout<<endl;
                        Sleep(2000);
                        cout<<endl;
                        enviarMensaje(servidor,"Se cerro el socket.");
                        archivo<<fechaHora();
                        archivo<<" El Servidor cerro la conexion"<<endl;
                        cerrarSocket(servidor);
                        cout<<endl<<"Saliendo del sistema..."<<endl;
                        Sleep(2000);
                        system("cls");
                        cout << "-----------------------------------------------" << endl;
                        cout << "-- CATEDRA REDES Y COMUNICACIONES --" << endl;
                        cout << "-------- TRABAJO PRACTICO CUATRIMESTRAL -------" << endl;
                        cout << "-----------------------------------------------\n" << endl;
                        cout << "MUCHAS GRACIAS POR UTILIZAR LA APLICACION" << endl;
                    break;
                    default:
                        system("cls");
                        cout << "----------------------------------" << endl;
                        cout << "-- OPCION INGRESADA INEXISTENTE --" << endl;
                        cout << "----------------------------------\n" << endl;
                        cout << "MENSAJE: LA OPCION INGRESADA ES INEXISTENTE, INTENTE NUEVAMENTE.\n";
                    break;
                }

        }
    archivo.close();
    return 0;
}

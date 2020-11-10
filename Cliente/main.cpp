#include "Client.h"
#include <iostream>
#include <winsock2.h>

using namespace std;


int main()
{
    Cliente cliente;
    string mensaje,ruta,usuario,password = "";
    char ip[16];
    int puerto;
    int respuesta=0;
    int intentos=0;
    int fLagConexion=0;
    int opcion=0;
        do{
            barraCargando();
            system("cls");
            cout<< "...BIENVENIDO AL CLIENTE..."<<endl;
            cout<< "INGRESE EL IP DEL SERVIDOR"<<endl;
            cout<< "IP: ";  cin>> ip; cout<< endl;
            cout<< "INGRESE EL PUERTO"<< endl;
            cout<< "PUERTO: "; cin>> puerto;
            crearCliente(cliente,ip,puerto);
            fLagConexion = cliente.conectado;
                if(fLagConexion != 0 ){
                    WSACleanup();
                    cout<<endl<<endl;
                }
        }while(fLagConexion != 0);

        while(intentos<3 && respuesta!=3){
            recibirMensaje(cliente);
            cin>>usuario;
            enviarMensaje(cliente,usuario);
            Sleep(1000);
            recibirMensaje(cliente);
            cin>>password;
            enviarMensaje(cliente,password);
            Sleep(1000);
            respuesta=recibirMensaje(cliente);
            intentos++;
        }

        if(respuesta==3){
                while(opcion!=4 || respuesta!=2){
                   opcion=menu(cliente,usuario);
                   respuesta=recibirMensaje(cliente);
                   Sleep(1000);
                }
        }
     enviarMensaje(cliente,"Se cerro el socket.");
     cerrarSocket(cliente);
    return 0;
}

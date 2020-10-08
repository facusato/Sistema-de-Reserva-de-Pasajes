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
    int fLagConexion=0;
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
    recibirMensaje(cliente);
    cout<<"Ingrese el nombre de usuario \n"<<endl;
    cin>>usuario;
    enviarMensaje(cliente,usuario);
    Sleep(1000);
    recibirMensaje(cliente);
    cout<<"Ingrese el password \n"<<endl;
    cin>>password;
    enviarMensaje(cliente,password);
    Sleep(1000);
    menu(cliente);
    cout<<endl;
    enviarMensaje(cliente,"Se cerro el socket.");
    cerrarSocket(cliente);
    cout<<endl<<"Saliendo del sistema..."<<endl;
    Sleep(2000);
    return 0;
}

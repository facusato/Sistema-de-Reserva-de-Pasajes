#include "Client.h"
#include <iostream>
#include <winsock2.h>

using namespace std;


int main()
{
    Cliente cliente;
    char comando[1024] = "\0";
    string ruta = "";
    string mensaje = "";
    int flagRecibir = 1;
    int fLagConexion;
    int respuesta;
    char ip[16];
    int puerto;

    do{
        barraCarga();
        system("cls");
        cout<< "...BIENVENIDO AL CLIENTE..."<<endl;
        cout<< "Ingrese el IP del servidor"<<endl;
        cout<< "IP: "; cin>>ws; cin>> ip; cout<< endl;
        cout<< "Ingrese el puerto"<< endl;
        cout<< "Puerto: "; cin>>ws; cin>> puerto;
        crearCliente(cliente,ip,puerto);
        fLagConexion = cliente.conectado;
            if(fLagConexion != 0 ){
                WSACleanup();
                cout<<endl<<endl;
            }
    }while(fLagConexion != 0);

    recibirMensaje(cliente);
    enviarMensaje(cliente,"Pablo");
    Sleep(1000);
    recibirMensaje(cliente);
    enviarMensaje(cliente,"1234");
    Sleep(1000);


    while (comando[0] != 'F' && fLagConexion != -1)
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
                        enviarMensaje(cliente,mensaje);
                        flagRecibir = 1;
                        break;
                    case 'T':
                        ruta = msj(comando);
                        enviarArchivo(cliente,ruta);
                        flagRecibir = 1;
                        break;
                    default:
                        cout<<endl<<"Comando equivocado."<<endl;
                        break;
                    }
                }
            }
        else
        {
            cout<<"Esperando respuesta del server..."<<endl;
            respuesta = recibirMensaje(cliente);
            if(respuesta == 1)
            {
                recibirArchivo(cliente);
            }
            else if (respuesta == 2)
            {
                fLagConexion = -1;
            }
            flagRecibir = 0;
        }
    }

    cout<<endl;
    enviarMensaje(cliente,"Se cerro el socket.");
    cerrarSocket(cliente);
    cout<<endl<<"Saliendo del sistema..."<<endl;
    Sleep(2000);
    return 0;
}

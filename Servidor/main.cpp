#include <iostream>
#include <winsock2.h>
#include "Server.h"
using namespace std;

int main()
{
    Servidor servidor;
    char comando[1024] = "\0";
    string ruta = "";
    string mensaje = "";
    int puerto;
    int flagRecibir = 0;
    int fLagConexion = 0;
    int respuesta;
    barraCarga();
    system("cls");
    cout<< "...BIENVENIDO AL SERVIDOR..."<<endl;
    cout<< "Ingrese el puerto: "; cin>>ws; cin>> puerto;
    crearServidor(servidor,puerto);

    enviarMensaje(servidor,"Ingrese usuario");
    Sleep(1000);
    recibirMensaje(servidor);
    enviarMensaje(servidor,"Ingrese password");
    Sleep(1000);
    recibirMensaje(servidor);



        while (comando[0] != 'F' && fLagConexion != -1)
        {
            if (flagRecibir == 0)
            {
                menu();
                Sleep(400);
                //ws guarda la opcion elegida en el menu
                cin >> ws;
                //Leemos la cadena ingresada por teclado
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
    }


    cout<<endl;
    enviarMensaje(servidor,"Se cerro el socket.");
    cerrarSocket(servidor);
    cout<<endl<<"Saliendo del sistema..."<<endl;
    Sleep(2000);
    return 0;
}

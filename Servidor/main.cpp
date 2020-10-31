#include <iostream>
#include <winsock2.h>
#include "Server.h"
#include <sstream>
#include <fstream>
#include <ctime>
#include "Viaje.h"
using namespace std;

int main()
{
    string servicios = "Servicios.bin";
    string destino= "Destino.bin";
    string fecha="Fecha.bin";
    string turno="Turno.bin";
    string usuario="usuario.txt";
    Viaje viaje;
    ofstream archivo;
    Servidor servidor;
    string mensaje = "";
    int respuesta=0;
    bool valido=false;
    int puerto;
    bool seguir=true;
    int opcion,intentos=0;
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
    //int tiempo=setsockopt(servidor.server,SOL_SOCKET,SO_RCVTIMEO,(const char *)&time_out,sizeof(time_out));
    archivo<<"========================================================================="<<endl;
    archivo<<fechaHora();
    archivo<<" Inicia Servidor"<<endl;
    archivo<<fechaHora();
    archivo<<" Socket creado. Puerto de escucha: "<<puerto<<endl;

        while(seguir){
            valido=false;
            intentos=0;

                while (intentos<3 && !valido){
                    if(validarCredencial(servidor)==true){
                        enviarMensaje(servidor,"Correcto.");
                        archivo<<fechaHora();
                        archivo<<" El cliente ingreso al sistema"<<endl;
                        valido=true;
                    }
                    else{
                        enviarMensaje(servidor,"Incorrecto.");
                        archivo<<fechaHora();
                        archivo<<" El cliente fallo al logueo en el intento:"<<intentos+1<<endl;
                    }
                    intentos++;
                }

    respuesta=recibirMensaje(servidor);
        while(respuesta!=2){
                    if(respuesta==1){
                        recibirArchivo(servidor);
                    }
                    else if(respuesta==3){
                        respuesta=menuCrearViaje(servidor,viaje);
                        enviarMensaje(servidor,"Alta correctamente");
                        Sleep(1000);
                    }
                    else if(respuesta==4){
                            system("cls");
                            enviarMensaje(servidor,"Entrando a otro menu");
                            Sleep(1000);
                            respuesta=menuAsignarAsiento(servidor,viaje);
                    }else if(respuesta==5){
                            system("cls");
                            respuesta=menuAsignarAsiento(servidor,viaje);
                            enviarMensaje(servidor,"Se asigno el asiento correctamente");
                            Sleep(1000);
                    }else if (respuesta==6){
                            system("cls");
                            respuesta=menuLiberarAsiento(servidor,viaje);
                            enviarMensaje(servidor,"Se libero el asiento correspondiente");
                            Sleep(1000);
                    }
                    else if (respuesta==7){
                            system("cls");
                            enviarArchivo(servidor,servicios);
                            Sleep(1000);
                            respuesta=80;
                    }
                    else if (respuesta==8){
                            system("cls");
                            respuesta=filtrarPorDestino(servidor,viaje);
                            enviarArchivo(servidor,destino);
                            Sleep(1000);
                            remove("Destino.bin");
                    }
                     else if (respuesta==9){
                            system("cls");
                            respuesta=filtrarPorFecha(servidor,viaje);
                            enviarArchivo(servidor,fecha);
                            Sleep(1000);
                            remove("Fecha.bin");
                    }
                    else if (respuesta==10){
                            system("cls");
                            respuesta=filtrarPorTurno(servidor,viaje);
                            enviarArchivo(servidor,turno);
                            Sleep(1000);
                            remove("Turno.bin");
                    }
                    else if (respuesta==11){
                            system("cls");
                            enviarArchivo(servidor,usuario);
                            Sleep(1000);
                            respuesta=90;
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
    enviarMensaje(servidor,"Se cerro el socket.");

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
                        escuchando(servidor);
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

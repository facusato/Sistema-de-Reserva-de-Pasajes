#include <iostream>
#include <string>
#include <winsock2.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>
#include <stdlib.h>
#ifndef SERVER_H_INCLUDED
#include "Viaje.h"

using namespace std;

typedef struct{
    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;
    char buffer[1024];
}Servidor;

#define SERVER_H_INCLUDED


void crearServidor(Servidor &servidor,int puerto);

int recibirMensaje(Servidor &servidor);

void escuchando(Servidor &servidor);

bool validarCredencial(Servidor &servidor);

void enviarMensaje(Servidor &servidor,string mensaje);

void enviarArchivo(Servidor &servidor,string ruta);

void recibirArchivo(Servidor &servidor);

int SafeSend(SOCKET s, char* buf, int buflen);

void cerrarSocket(Servidor &servidor);

string msj(char* grupo);

void barraCargando();

string fechaHora();

void recibirDestino(Servidor &servidor,Viaje &viaje);

void recibirFecha(Servidor &servidor,Viaje &viaje);

void recibirTurno(Servidor &servidor,Viaje &viaje);

int menuCrearViaje(Servidor &servidor,Viaje &viaje);

int menuAsignarAsiento(Servidor &servidor,Viaje &viaje);

int menuLiberarAsiento(Servidor &servidor, Viaje &viaje);

char recibirFila(Servidor &servidor);

int recibirColumna(Servidor &servidor);

#endif // SERVER_H_INCLUDED

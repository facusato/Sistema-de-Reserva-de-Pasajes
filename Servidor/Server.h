#include <iostream>
#include <string>
#include <winsock2.h>
#include <fstream>
#include <sstream>
#ifndef SERVER_H_INCLUDED

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

void volver(Servidor &servidor);

bool validarCredencial(Servidor &servidor);

void enviarMensaje(Servidor &servidor,string mensaje);

void enviarArchivo(Servidor &servidor,string ruta);

void recibirArchivo(Servidor &servidor);

int SafeSend(SOCKET s, char* buf, int buflen);

void cerrarSocket(Servidor &servidor);

string msj(char* grupo);

void barraCargando();

#endif // SERVER_H_INCLUDED

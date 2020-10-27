#include <iostream>
#include <string.h>
#include <winsock2.h>
#include <fstream>

using namespace std;

#ifndef CLIENT_H_INCLUDED

typedef struct{
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
    char buffer[1024];
    int conectado;
}Cliente;

#define CLIENT_H_INCLUDED

void crearCliente(Cliente &cliente,char *ip, int puerto);

void enviarMensaje(Cliente &cliente,string mensaje);

int recibirMensaje(Cliente &cliente);

void enviarArchivo(Cliente &cliente,string ruta);

void recibirArchivo(Cliente &cliente);

int SafeSend(SOCKET s, char* buf, int buflen);

void cerrarSocket(Cliente &cliente);

string msj(char* grupo);

void barraCargando();

int menu(Cliente &cliente);

int menu2(Cliente &cliente);

#endif // CLIENT_H_INCLUDED

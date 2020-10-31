#include <iostream>
#include <string.h>
#include <stdlib.h>
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

void validarDestinoFechaTurno(char destino[23], char fecha[23], char turno[23],Cliente &cliente);

void validarFilaColumna(char fila[5], char columna[5], Cliente &cliente);

int menu(Cliente &cliente);

int menuGestionarPasajes(Cliente &cliente);

int menuPorFiltros(Cliente &cliente);

void solicitarServiciosDisponibles(Cliente &cliente);

void servicioPorDestino(Cliente &cliente);

void servicioPorTurno(Cliente &cliente);

void servicioPorFecha(Cliente &cliente);

void lecturaRegistroActividades();

void registroDeActividades(Cliente &cliente);

#endif // CLIENT_H_INCLUDED

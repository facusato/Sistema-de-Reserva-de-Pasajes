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

void recibirArchivo(Cliente &cliente,string usuario);

int SafeSend(SOCKET s, char* buf, int buflen);

void cerrarSocket(Cliente &cliente);

string msj(char* grupo);

void barraCargando();

void validarDestinoFechaTurno(char destino[23], char fecha[23], char turno[23],Cliente &cliente);

void validarFilaColumna(char fila[5], char columna[5], Cliente &cliente);

int menu(Cliente &cliente,string usuario);

int menuGestionarPasajes(Cliente &cliente,string usuario);

int menuPorFiltros(Cliente &cliente,string usuario);

void solicitarServiciosDisponibles(Cliente &cliente,string usuario);

void servicioPorDestino(Cliente &cliente,string usuario);

void servicioPorTurno(Cliente &cliente,string usuario);

void servicioPorFecha(Cliente &cliente,string usuario);

void servicioPorDestinoFechaTurno(Cliente &cliente,string usuario);

void servicioPorDestinoFecha(Cliente &cliente,string usuario);

void lecturaRegistroActividades(string usuario);

void registroDeActividades(Cliente &cliente,string usuario);

bool verConectividad(Cliente &cliente);

#endif // CLIENT_H_INCLUDED

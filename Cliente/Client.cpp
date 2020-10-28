#include "Client.h"
#include "Binario.h"

void crearCliente(Cliente &cliente,char *ip, int puerto){
    system("cls");
    cout<<"Conectando al servidor..."<<endl<<endl;
    WSAStartup(MAKEWORD(2,2), &cliente.WSAData);
    cliente.server = socket(AF_INET, SOCK_STREAM, 0);
    cliente.addr.sin_addr.s_addr = inet_addr(ip);
    cliente.addr.sin_family = AF_INET;
    cliente.addr.sin_port = htons(puerto);
    /**  Establecer una conexión a otro socket,permitiendo que un protocolo TCP inicie una
    conexión en la capa de transporte para el servidor especificado*/
    cliente.conectado = connect(cliente.server, (SOCKADDR *)&cliente.addr, sizeof(cliente.addr));

        if(cliente.conectado == 0){
            cout << "Conectado al Servidor." << endl;
        }
        else{
            cout << "Error en la conexion." << endl;
            Sleep(2000);
        }
    }

void enviarMensaje(Cliente &cliente,string mensaje){
    strcpy(cliente.buffer, &mensaje[0]);
    send(cliente.server,cliente.buffer, sizeof(cliente.buffer), 0);
    memset(cliente.buffer, 0, sizeof(cliente.buffer));
        if(strcmp(cliente.buffer, "Enviando archivo.") && strcmp(cliente.buffer, "Se cerro el socket.")){
                cout << "Mensaje enviado." << endl << endl;
        }
    }

int recibirMensaje(Cliente &cliente){
    int retorno;
    recv(cliente.server, cliente.buffer, sizeof(cliente.buffer), 0);
        if(!strcmp(cliente.buffer, "Enviando archivo.")){
            memset(cliente.buffer, 0, sizeof(cliente.buffer));
            retorno=1;
        }
        else if(!strcmp(cliente.buffer, "Se cerro el socket.")){
            cout << "\n Cerrando conexion" << endl;
            memset(cliente.buffer, 0, sizeof(cliente.buffer));
            retorno= 2;
        }else if(!strcmp(cliente.buffer, "Correcto.")){
            cout << "\nEl servidor acepto el lngreso" << endl;
            memset(cliente.buffer, 0, sizeof(cliente.buffer));
            retorno=3;
              }
        else{
            cout << "\nEl servidor dice: " << cliente.buffer << endl;
            memset(cliente.buffer, 0, sizeof(cliente.buffer));
            retorno= 0;
        }
        return retorno;
}

void enviarArchivo(Cliente &cliente,string ruta){
    FILE *File;
    char *Buffer;
    unsigned long Size;
    char nombre[512]= "\0";
    char rutaChar[1024] = "\0";
    string mensaje = "Enviando archivo.";
    cout<<mensaje<<endl;
    enviarMensaje(cliente,mensaje);
    strcpy(nombre, &ruta[0]); //Ruta y nombre de archivo
    SafeSend(cliente.server, nombre, sizeof(nombre));
    strcpy(rutaChar, &ruta[0]);
    File = fopen(rutaChar, "rb");
        if(!File){
            cout<<"Error al leer archivo."<<endl;
            cin.ignore();
        }
        else{
            fseek(File, 0, SEEK_END);
            Size = ftell(File);
            fseek(File, 0, SEEK_SET);
            Buffer = new char[Size];
            fread(Buffer, Size, 1, File);
            char cSize[MAX_PATH];
            sprintf(cSize, "%lu", Size);
            fclose(File);
            Sleep(1000);
            SafeSend(cliente.server, cSize, MAX_PATH);
            Sleep(1000);
            SafeSend(cliente.server,Buffer,Size);
        }
    free(Buffer);
}


void recibirArchivo(Cliente &cliente){
    cout<<"Recibiendo archivo."<<endl;
    int Size;
    char Filesize[MAX_PATH] = "\0";
    char nombre[512] = "\0";
    recv(cliente.server, nombre, sizeof(nombre), 0);
        if(recv(cliente.server, Filesize, sizeof(Filesize), 0)){
            Size = atoi((const char*)Filesize);
            cout<< "Tamanio del archivo: "<< Size<<endl;
        }
        char *Buffer = new char[Size];
        recv(cliente.server, Buffer, Size, 0);
        cout<< "Se trajo el archivo: "<< nombre <<endl; // Guardo la ruta y el nombre y lo muestro
        char cmd[50];
        cout<<"Ingresar ruta y  nombre del archivo: "<<endl;
        cin>>ws; cin>>cmd;
        FILE* File;
        File = fopen(cmd, "wb");
        fwrite(Buffer, 1, Size, File);
        fclose(File);
        cout<<"Archivo recibido."<<endl;
        cout<<"Se recibieron " << Size << " bytes.";
        free(Buffer);
}


int SafeSend(SOCKET s, char* buf, int buflen){
	int sendlen = 0;
	int totalsend = 0;
	int remaining = buflen;
        while(sendlen != buflen){
            sendlen = send(s, &buf[totalsend], remaining, 0);
            if(sendlen == SOCKET_ERROR){
			return SOCKET_ERROR;
            }
          totalsend = totalsend + sendlen;
          remaining = sendlen - totalsend;
        }
    return 0;
}


void cerrarSocket(Cliente &cliente){
    closesocket(cliente.server);
    WSACleanup();
    cout << "Socket cerrado." << endl << endl;
}

string msj(char* grupo){
    string cadena = "";
        for(int i=2; grupo[i]!= '\0'; i++){
            cadena = cadena + grupo[i];
        }
    return cadena;
}

int menu(Cliente &cliente){
    char destino[23];
	char fecha[23];
	char turno[23];
    int opcion;
    system("cls");
    cout<< "\n\n";
    cout<<"---BIENVENIDOS AL SISTEMA DE VENTA DE PASAJES---"<<endl;
    cout<<"---DESTINO BUENOS AIRES - MAR DEL PLATA---"<<endl;
    cout<<"\n"<<endl;
    cout<<" 1- ALTA DE SERVICIO \n"<<endl;
    cout<<" 2- GESTIONAR PASAJES \n"<<endl;
    cout<<" 3- VER REGISTRO DE ACTIVIDADES \n"<<endl;
    cout<<" 4- CERRAR SESION \n"<<endl;
    cout << "\n INGRESE LA OPCION DESEADA: ";
    cin>>opcion;
    system("cls");
    switch(opcion){
               case 1:
                    enviarMensaje(cliente,"ALTA DE SERVICIO.");
                    Sleep(1000);
                    recibirMensaje(cliente);
                    cin >> destino;
                    enviarMensaje(cliente,destino);
                    Sleep(1000);
                    recibirMensaje(cliente);
                    cin >> fecha;
                    enviarMensaje(cliente,fecha);
                    Sleep(1000);
                    recibirMensaje(cliente);
                    cin >> turno;
                    enviarMensaje(cliente,turno);
                    Sleep(1000);
               break;
               case 2:
                    menu2(cliente);
                    Sleep(1000);
               break;
               case 3:
                    enviarMensaje(cliente,"VER REGISTRO DE ACTIVIDADES.");
                    Sleep(1000);
               break;
               case 4:
                   system("cls");
                   cout << "-----------------------------------------------" << endl;
                   cout << "-- CATEDRA REDES Y COMUNICACIONES --" << endl;
                   cout << "-------- TRABAJO PRACTICO CUATRIMESTRAL -------" << endl;
                   cout << "-----------------------------------------------\n" << endl;
                   cout << "MUCHAS GRACIAS POR UTILIZAR LA APLICACION" << endl;
                   enviarMensaje(cliente,"Se cerro el socket.");
               break;
               default:
                   system("cls");
                   cout << "----------------------------------" << endl;
                   cout << "-- OPCION INGRESADA INEXISTENTE --" << endl;
                   cout << "----------------------------------\n" << endl;
                   menu(cliente);
                   Sleep(1000);
               break;
    }
    return opcion;
}




int menu2(Cliente &cliente){
    char destino[23];
	char fecha[23];
	char turno[23];
	char fila[5];
	char columna[5];
    int opcion;
    system("cls");
    cout<<"\n"<<endl;
    cout<<" 1- RESERVAR UN ASIENTO \n"<<endl;
    cout<<" 2- LIBERAR UN ASIENTO \n"<<endl;
    cout<<" 3- ELEGIR OTRO SERVICIO \n"<<endl;
    cout<<" 4- VOLVER AL MENU ANTERIOR \n"<<endl;
    cout << "\n INGRESE LA OPCION DESEADA: ";
    cin>>opcion;
    system("cls");
    switch(opcion){
               case 1:
                     enviarMensaje(cliente,"RESERVAR UN ASIENTO.");
                     Sleep(1000);
                     recibirMensaje(cliente);
                     cin >> destino;
                     enviarMensaje(cliente,destino);
                     Sleep(1000);
                     recibirMensaje(cliente);
                     cin >> fecha;
                     enviarMensaje(cliente,fecha);
                     Sleep(1000);
                     recibirMensaje(cliente);
                     cin >> turno;
                     enviarMensaje(cliente,turno);
                     Sleep(1000);
                     recibirMensaje(cliente);
                     cin>>fila;
                     enviarMensaje(cliente,fila);
                     Sleep(1000);
                     recibirMensaje(cliente);
                     cin>>columna;
                     enviarMensaje(cliente,columna);
                     Sleep(1000);
               break;
               case 2:
               break;
               case 3:
               break;
               case 4:
                   system("cls");
                   cout<<endl;
                   Sleep(2000);
                   cout<<menu(cliente)<<endl;
               break;
               default:
                   system("cls");
                   cout << "----------------------------------" << endl;
                   cout << "-- OPCION INGRESADA INEXISTENTE --" << endl;
                   cout << "----------------------------------\n" << endl;
                   menu2(cliente);
                   Sleep(1000);
               break;
    }
    return opcion;
}




void barraCargando(){
    int segundos=2;
    cout << "\n";
    cout << "\t\t\t CARGANDO CLIENTE...\n";
        for(int i=0; i<=0; i++)
            cout << "_";
        for(int i=0; i<=70; i++){
            cout<<char(219);
            Sleep(segundos*1000/175);
        }
}

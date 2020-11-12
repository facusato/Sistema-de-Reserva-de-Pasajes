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
         }else if(!strcmp(cliente.buffer,"No existe ningun servicio, dar de alta.")|| !strcmp(cliente.buffer,"No existe el servicio filtrado.")){
            cout << "\nEl servidor no tiene servicio que cumpla los requisitos" << endl;
            memset(cliente.buffer, 0, sizeof(cliente.buffer));
            retorno=4;
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


void recibirArchivo(Cliente &cliente,string usuario){
        cout<<"Recibiendo archivo."<<endl;
        int Size;
        char Filesize[MAX_PATH] = "\0";
        char nombre[512] = "\0";
        string extension=".txt";
        string ruta=usuario+extension;
        char usuarios[12];
        strcpy(usuarios,ruta.c_str());
        recv(cliente.server, nombre, sizeof(nombre), 0);

        if(recv(cliente.server, Filesize, sizeof(Filesize), 0)) // Tamaño de archivo
        {
            Size = atoi((const char*)Filesize);
            cout<< "Tamanio del archivo: "<< Size<<endl;
        }

        char *Buffer = new char[Size];
        recv(cliente.server, Buffer, Size, 0);
        cout<< "Se trajo el archivo: "<< nombre <<endl; // Guardo la ruta y el nombre y lo muestro

        if(strcmp(nombre,"Servicios.bin")==0){
            FILE* File;
            File = fopen("Servicios.bin", "wb");
            fwrite(Buffer, 1, Size, File);
            fclose(File);
            cout<<"Archivo recibido."<<endl;
            cout<<"Se recibieron " << Size << " bytes.";
        }else if(strcmp(nombre,"Destino.bin")==0){
            FILE* File;
            File = fopen("Destino.bin", "wb");
            fwrite(Buffer, 1, Size, File);
            fclose(File);
            cout<<"Archivo recibido."<<endl;
            cout<<"Se recibieron " << Size << " bytes.";
        }else if(strcmp(nombre,"Fecha.bin")==0){
            FILE* File;
            File = fopen("Fecha.bin", "wb");
            fwrite(Buffer, 1, Size, File);
            fclose(File);
            cout<<"Archivo recibido."<<endl;
            cout<<"Se recibieron " << Size << " bytes.";
        }
        else if(strcmp(nombre,"Turno.bin")==0){
            FILE* File;
            File = fopen("Turno.bin", "wb");
            fwrite(Buffer, 1, Size, File);
            fclose(File);
            cout<<"Archivo recibido."<<endl;
            cout<<"Se recibieron " << Size << " bytes.";
        }
        else if(strcmp(nombre,"ServicioCompleto.bin")==0){
            FILE* File;
            File = fopen("ServicioCompleto.bin", "wb");
            fwrite(Buffer, 1, Size, File);
            fclose(File);
            cout<<"Archivo recibido."<<endl;
            cout<<"Se recibieron " << Size << " bytes.";
        }
        else if(strcmp(nombre,"ServicioDestinoFecha.bin")==0){
            FILE* File;
            File = fopen("ServicioDestinoFecha.bin", "wb");
            fwrite(Buffer, 1, Size, File);
            fclose(File);
            cout<<"Archivo recibido."<<endl;
            cout<<"Se recibieron " << Size << " bytes.";
        }
        else if(strcmp(nombre,usuarios)==0){
            FILE* File;
            File = fopen(usuarios, "wb");
            fwrite(Buffer, 1, Size, File);
            fclose(File);
            cout<<"Archivo recibido."<<endl;
            cout<<"Se recibieron " << Size << " bytes.";
        }
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

int menu(Cliente &cliente,string usuario){
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
    if(verConectividad(cliente)==false){
            cout<<"\n Cliente desconectado por inactividad\n"<<endl;
            system("pause");
            exit(EXIT_SUCCESS);
    }
    system("cls");
    switch(opcion){
               case 1:
                    enviarMensaje(cliente,"ALTA DE SERVICIO.");
                    validarDestinoFechaTurno(destino,fecha,turno,cliente);
               break;
               case 2:
                    menuGestionarPasajes(cliente,usuario);
               break;
               case 3:
                    enviarMensaje(cliente,"VER REGISTRO DE ACTIVIDADES.");
                    registroDeActividades(cliente,usuario);
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
                   menu(cliente,usuario);
                   Sleep(1000);
               break;
    }
    return opcion;
}




int menuGestionarPasajes(Cliente &cliente,string usuario){
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
    cout<<" 3- VER VIAJES DISPONIBLES \n"<<endl;
    cout<<" 4- RESERVAR PASAJES \n"<<endl;
    cout<<" 5- VOLVER AL MENU ANTERIOR \n"<<endl;
    cout << "\n INGRESE LA OPCION DESEADA: ";
    cin>>opcion;
    system("cls");
    switch(opcion){
               case 1:
                   enviarMensaje(cliente,"RESERVAR UN ASIENTO.");
                   validarDestinoFechaTurno(destino,fecha,turno,cliente);
                   validarFilaColumna(fila,columna,cliente);
               break;
               case 2:
                   enviarMensaje(cliente,"LIBERAR UN ASIENTO.");
                   validarDestinoFechaTurno(destino,fecha,turno,cliente);
                   validarFilaColumna(fila,columna,cliente);
               break;
               case 3:
                   enviarMensaje(cliente,"VER SERVICIOS DISPONIBLES.");
                   solicitarServiciosDisponibles(cliente,usuario);
               break;
               case 4:
                   system("cls");
                   menuPorFiltros(cliente,usuario);
               break;
               case 5:
                   system("cls");
                   menu(cliente,usuario);
               break;
               default:
               system("cls");
                   cout << "----------------------------------" << endl;
                   cout << "-- OPCION INGRESADA INEXISTENTE --" << endl;
                   cout << "----------------------------------\n" << endl;
                   menuGestionarPasajes(cliente,usuario);
                   Sleep(1000);
               break;
    }
    return opcion;
}


int menuPorFiltros(Cliente &cliente,string usuario){

    int opcion;
    system("cls");
    cout<<"\n"<<endl;
    cout<<" 1- VER VIAJES POR DESTINO \n"<<endl;
    cout<<" 2- VER VIAJES POR TURNO \n"<<endl;
    cout<<" 3- VER VIAJES POR FECHA \n"<<endl;
    cout<<" 4- VER VIAJE POR DESTINO-FECHA-TURNO \n"<<endl;
    cout<<" 5- VER VIAJE POR DESTINO-FECHA \n"<<endl;
    cout<<" 6- VOLVER AL MENU ANTERIOR \n"<<endl;
    cout << "\n INGRESE LA OPCION DESEADA: ";
    cin>>opcion;
    system("cls");
    switch(opcion){
               case 1:
                   servicioPorDestino(cliente,usuario);
               break;
               case 2:
                   servicioPorTurno(cliente,usuario);
               break;
               case 3:
                   servicioPorFecha(cliente,usuario);
               break;
               case 4:
                   servicioPorDestinoFechaTurno(cliente,usuario);
               break;
               case 5:
                   servicioPorDestinoFecha(cliente,usuario);
               break;
               case 6:
                   system("cls");
                   cout<<endl;
                   Sleep(1000);
                   cout<<menuGestionarPasajes(cliente,usuario)<<endl;
               break;
               default:
               system("cls");
                   cout << "----------------------------------" << endl;
                   cout << "-- OPCION INGRESADA INEXISTENTE --" << endl;
                   cout << "----------------------------------\n" << endl;
                   menuPorFiltros(cliente,usuario);
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

void solicitarServiciosDisponibles(Cliente &cliente,string usuario){

    Sleep(1000);
    int resp=recibirMensaje(cliente);
        if(resp==1){
            recibirArchivo(cliente,usuario);
            system("cls");
            leerFichero();
            Sleep(2000);
            system("pause");
            enviarMensaje(cliente,"RECIBIDO.");
            Sleep(1000);
        }
        else{
            enviarMensaje(cliente,"OK.");
            Sleep(1000);
        }
}


void servicioPorDestino(Cliente &cliente,string usuario){

    char destino[23];
    bool destinoCorrecto=false;
    system("cls");
    enviarMensaje(cliente,"VER POR DESTINO.");
    Sleep(1000);
    int resp=recibirMensaje(cliente);
      if(resp!=4){
            while(destinoCorrecto==false){
                cin >> destino;
                    if (strcmp(destino,"MDQ")==0||strcmp(destino,"BSAS")==0){
                        destinoCorrecto=true;
                    }else{
                        cout << "Destino Incorrecto. Por favor, vuelva a ingresarlo:" << endl;
                    }
            }
            enviarMensaje(cliente,destino);
            Sleep(1000);
            int resp2=recibirMensaje(cliente);
                if(resp2==1){
                    recibirArchivo(cliente,usuario);
                    system("cls");
                    leerFicheroDestino();
                    Sleep(2000);
                    system("pause");
                    enviarMensaje(cliente,"RECIBIDO.");
                    Sleep(1000);
                }
                else{
                   enviarMensaje(cliente,"OK.");
                   Sleep(1000);
                }
        }else{
                enviarMensaje(cliente,"OK.");
                Sleep(1000);
            }

}


void servicioPorFecha(Cliente &cliente,string usuario){
    char fecha[23];
    bool fechaCorrecta=false;
    system("cls");
    enviarMensaje(cliente,"VER POR FECHA.");
    Sleep(1000);
    int resp=recibirMensaje(cliente);
     if(resp!=4){
        while(fechaCorrecta==false){
            cin >> fecha;
                if(strlen(fecha)<=10){
                    fechaCorrecta=true;
                }else{
                    cout << "Fecha Incorrecta. Por favor, vuelva a ingresarla:" << endl;
                    }
            }
            enviarMensaje(cliente,fecha);
            Sleep(1000);
            int resp2= recibirMensaje(cliente);
                if(resp2==1){
                    recibirArchivo(cliente,usuario);
                    system("cls");
                    leerFicheroFecha();
                    Sleep(2000);
                    system("pause");
                    enviarMensaje(cliente,"RECIBIDO.");
                    Sleep(1000);
                }
                else{
                    enviarMensaje(cliente,"OK.");
                    Sleep(1000);
                }
        }
        else{
            enviarMensaje(cliente,"OK.");
            Sleep(1000);
        }
}


void servicioPorTurno(Cliente &cliente,string usuario){

    char turno[23];
    bool turnoCorrecto=false;
    system("cls");
    enviarMensaje(cliente,"VER POR TURNO.");
    Sleep(1000);
    int resp=recibirMensaje(cliente);
      if(resp!=4){
             while(turnoCorrecto==false){
                        cin >> turno;
                            if (strcmp(turno,"manana")==0||strcmp(turno,"tarde")==0||strcmp(turno,"noche")==0){
                                    turnoCorrecto=true;
                            }else{
                            cout << "Turno Incorrecto. Por favor, vuelva a ingresarlo:" << endl;}
                }
            enviarMensaje(cliente,turno);
            Sleep(1000);
            int resp2=recibirMensaje(cliente);
                if(resp2==1){
                    recibirArchivo(cliente,usuario);
                    system("cls");
                    leerFicheroTurno();
                    Sleep(2000);
                    system("pause");
                    enviarMensaje(cliente,"RECIBIDO.");
                    Sleep(1000);
                }
                else{
                    enviarMensaje(cliente,"OK.");
                    Sleep(1000);
                }

        }else{
            enviarMensaje(cliente,"OK.");
            Sleep(1000);
        }
}

void servicioPorDestinoFechaTurno(Cliente &cliente,string usuario){

    char destino[23];
    char turno[23];
    char fecha[23];
    bool turnoCorrecto=false;
    bool destinoCorrecto=false;
    bool fechaCorrecta=false;

    system("cls");
    enviarMensaje(cliente,"VER POR DESTINO FECHA TURNO.");
    Sleep(1000);
    int resp=recibirMensaje(cliente);
      if(resp!=4){
            while(destinoCorrecto==false){
                cin >> destino;
                        if (strcmp(destino,"MDQ")==0||strcmp(destino,"BSAS")==0){
                            destinoCorrecto=true;
                        }else{
                            cout << "Destino Incorrecto. Por favor, vuelva a ingresarlo:" << endl;
                        }
            }
            enviarMensaje(cliente,destino);
            Sleep(1000);
            recibirMensaje(cliente);
            //Fecha
                while(fechaCorrecta==false){
                    cin >> fecha;
                        if(strlen(fecha)<=10){
                            fechaCorrecta=true;
                        }else{
                        cout << "Fecha Incorrecta. Por favor, vuelva a ingresarla:" << endl;
                        }
                }
                enviarMensaje(cliente,fecha);
                Sleep(1000);
                recibirMensaje(cliente);
                //turno
                    while(turnoCorrecto==false){
                        cin >> turno;
                            if (strcmp(turno,"manana")==0||strcmp(turno,"tarde")==0||strcmp(turno,"noche")==0){
                                    turnoCorrecto=true;
                            }else{
                            cout << "Turno Incorrecto. Por favor, vuelva a ingresarlo:" << endl;
                            }
                    }
                    enviarMensaje(cliente,turno);
                    Sleep(1000);
                    int resp2=recibirMensaje(cliente);
                        if(resp2==1){
                        recibirArchivo(cliente,usuario);
                        system("cls");
                        leerFicheroDestinoFechaTurno();
                        Sleep(2000);
                        system("pause");
                        enviarMensaje(cliente,"RECIBIDO.");
                        Sleep(1000);
                        }
                        else{
                        enviarMensaje(cliente,"OK.");
                        Sleep(1000);
                        }
                }
                else{
                    enviarMensaje(cliente,"OK.");
                    Sleep(1000);
        }
}

void servicioPorDestinoFecha(Cliente &cliente,string usuario){

    char destino[23];
    char fecha[23];
    bool destinoCorrecto=false;
    bool fechaCorrecta=false;
    system("cls");
    enviarMensaje(cliente,"VER POR DESTINO FECHA.");
    Sleep(1000);
    int resp=recibirMensaje(cliente);
      if(resp!=4){
            while(destinoCorrecto==false){
                cin >> destino;
                        if (strcmp(destino,"MDQ")==0||strcmp(destino,"BSAS")==0){
                            destinoCorrecto=true;
                        }else{
                            cout << "Destino Incorrecto. Por favor, vuelva a ingresarlo:" << endl;
                        }
            }
            enviarMensaje(cliente,destino);
            Sleep(1000);
            recibirMensaje(cliente);
            //Fecha
                while(fechaCorrecta==false){
                    cin >> fecha;
                        if(strlen(fecha)<=10){
                            fechaCorrecta=true;
                        }else{
                        cout << "Fecha Incorrecta. Por favor, vuelva a ingresarla:" << endl;
                        }
                }
                enviarMensaje(cliente,fecha);
                Sleep(1000);
                    int resp2=recibirMensaje(cliente);
                        if(resp2==1){
                            recibirArchivo(cliente,usuario);
                            system("cls");
                            leerFicheroDestinoFecha();
                            Sleep(2000);
                            system("pause");
                            enviarMensaje(cliente,"RECIBIDO.");
                            Sleep(1000);
                        }
                        else{
                            enviarMensaje(cliente,"OK.");
                            Sleep(1000);
                        }
                }
                else{
                    enviarMensaje(cliente,"OK.");
                    Sleep(1000);
                }
}

void validarDestinoFechaTurno(char destino[23], char fecha[23], char turno[23],Cliente &cliente){
    bool destinoCorrecto=false;
    bool fechaCorrecta=false;
    bool turnoCorrecto=false;
    Sleep(1000);
    //Destino
    recibirMensaje(cliente);
        while(destinoCorrecto==false){
                cin >> destino;
                        if (strcmp(destino,"MDQ")==0||strcmp(destino,"BSAS")==0){
                            destinoCorrecto=true;
                        }else{cout << "Destino Incorrecto. Por favor, vuelva a ingresarlo:" << endl;
                        }
        }

        enviarMensaje(cliente,destino);
        Sleep(1000);
        recibirMensaje(cliente);
        //Fecha
            while(fechaCorrecta==false){
                    cin >> fecha;
                        if(strlen(fecha)<=10){
                            fechaCorrecta=true;
                        }else{
                        cout << "Fecha Incorrecta. Por favor, vuelva a ingresarla:" << endl;}
            }

            enviarMensaje(cliente,fecha);
            Sleep(1000);
            recibirMensaje(cliente);
            //turno
                while(turnoCorrecto==false){
                        cin >> turno;
                            if (strcmp(turno,"manana")==0||strcmp(turno,"tarde")==0||strcmp(turno,"noche")==0){
                                    turnoCorrecto=true;
                            }else{
                            cout << "Turno Incorrecto. Por favor, vuelva a ingresarlo:" << endl;}
                }

                enviarMensaje(cliente,turno);
                Sleep(1000);


}


void validarFilaColumna(char fila[5], char columna[5], Cliente &cliente){
    bool filaCorrecta=false;
    bool columnaCorrecta=false;
    Sleep(1000);
    //Fila
    recibirMensaje(cliente);
        while(filaCorrecta==false){
            cin >> fila;
            if (strcmp(fila,"A")==0||strcmp(fila,"B")==0||strcmp(fila,"C")==0
                ||strcmp(fila,"a")==0||strcmp(fila,"b")==0||strcmp(fila,"c")==0){
                filaCorrecta=true;
            }else{cout << "Fila Incorrecta. Por favor, vuelva a ingresarla:" << endl;
            }
        }
        enviarMensaje(cliente,fila);
        Sleep(1000);
        recibirMensaje(cliente);
        //columna
            while(columnaCorrecta==false){
                cin >> columna;
                    if(atoi(columna)>0&&atoi(columna)<21){
                        columnaCorrecta=true;
                    }else{
                        cout << "Columna Incorrecta. Por favor, vuelva a ingresarla:" << endl;}
                    }
                    enviarMensaje(cliente,columna);
                    Sleep(1000);
}

void lecturaRegistroActividades(string usuario){
    ifstream archivo;
    string texto;
    string extension=".txt";
    //abrimos el archivo en modo lectura para ir recorriendo y mostrando por pantalla
    archivo.open(usuario+extension,ios::in);

        if(archivo.fail()){
            cout<<"No se pudo abrir el archivo"<<endl;
            exit(1);
        }

        while(!archivo.eof()){
            getline(archivo,texto);
            cout<<texto<<endl;
        }
        archivo.close();
}



void registroDeActividades(Cliente &cliente,string usuario){

    Sleep(1000);
    recibirMensaje(cliente);
    recibirArchivo(cliente,usuario);
    system("cls");
    lecturaRegistroActividades(usuario);
    Sleep(2000);
    system("pause");
    enviarMensaje(cliente,"RECIBIDO.");
    Sleep(1000);
}

bool verConectividad(Cliente &cliente){ /** Sirve para comprobar si el servidor esta apto para recibir y enviar mensajes**/
        bool conectado =true;
        u_long iMode= 1;
        ioctlsocket(cliente.server,FIONBIO,&iMode); //Funcion que convierte la conexion en blocking-sockets a non-blocking sockets.
        memset(cliente.buffer, 0, sizeof(cliente.buffer));
          if(recibirMensaje(cliente)==2){
            conectado = false;
            }
        iMode = 0;
        ioctlsocket(cliente.server,FIONBIO,&iMode); //Funcion que convierte la conexion en non-blocking sockets a blocking-sockets.
        return conectado;
    }

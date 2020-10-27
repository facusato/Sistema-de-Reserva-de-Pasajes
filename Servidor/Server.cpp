#include "Server.h"
#include "Viaje.h"
using namespace std;

void crearServidor(Servidor &servidor,int puerto){
    WSAStartup(MAKEWORD(2,0), &servidor.WSAData); //iniciar winsock
    servidor.server= socket(AF_INET, SOCK_STREAM, 0);
    servidor.serverAddr.sin_addr.s_addr = INADDR_ANY;
    servidor.serverAddr.sin_family = AF_INET;
    servidor.serverAddr.sin_port = htons(puerto);
    /**Suministra un número a una dirección local a asociar con el socket, ya que
    cuando un socket es creado no cuenta con dirección alguna*/
    bind(servidor.server, (SOCKADDR *)&servidor.serverAddr, sizeof(servidor.serverAddr));
    /**Esta rutina prepara un socket para aceptar conexiones*/
    listen(servidor.server, 0);
    cout << "Esperando a que se conecte el cliente." << endl;
    int clientAddrSize = sizeof(servidor.clientAddr);
    /**crea un socket nuevo para la conexión y regresa su
    descriptor al que lo invoca, este nuevo socket es usado por el servidor para
    comunicarse con el cliente y al terminar se cierra */
        if((servidor.client = accept(servidor.server, (SOCKADDR *)&servidor.clientAddr, &clientAddrSize)) != INVALID_SOCKET){
            system("cls");
            cout << "SE CONECTO EL CLIENTE." << endl;
        }
}


void volver(Servidor &servidor){
    listen(servidor.server, 0);
    cout << "Esperando a que se conecte el cliente." << endl;
    int clientAddrSize = sizeof(servidor.clientAddr);
    /**crea un socket nuevo para la conexión y regresa su
    descriptor al que lo invoca, este nuevo socket es usado por el servidor para
    comunicarse con el cliente y al terminar se cierra */
        if((servidor.client = accept(servidor.server, (SOCKADDR *)&servidor.clientAddr, &clientAddrSize)) != INVALID_SOCKET)
        {
            system("cls");
            cout << "SE CONECTO EL CLIENTE." << endl;
        }
}


bool validarCredencial(Servidor &servidor){
    servidor.buffer[0] = '\0';
    string usuario;
    string password;
    bool valido=false;
    enviarMensaje(servidor,"INGRESE USUARIO");
    Sleep(1000);
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    usuario=servidor.buffer;
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
    enviarMensaje(servidor,"INGRESE PASSWORD");
    Sleep(1000);
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    password=servidor.buffer;
    memset(servidor.buffer, 0, sizeof(servidor.buffer));

    ifstream archivo("credenciales.txt");
        if(archivo && archivo.is_open()){
            string linea;
            string linea2;
            while(archivo.good() && !valido){
                    //Nombre del usuario
                    getline(archivo,linea, ';');
                    //Password del usuario
                    getline(archivo,linea2);
                    if( (linea==usuario) && (linea2==password)){
                        cout<<"correcto"<<endl;
                        valido=true;

                    }
        }
        archivo.close();
    }
    return valido;
}


int recibirMensaje(Servidor &servidor){
      servidor.buffer[0] = '\0';
      int retorno;
      /**Esta rutina lee datos desde un socket conectado es decir recibe el msj*/
      recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
            if(!strcmp(servidor.buffer, "Enviando archivo.")){
                memset(servidor.buffer, 0, sizeof(servidor.buffer));  //reinicia el buffer
                retorno= 1;
            }
            else if(!strcmp(servidor.buffer, "Se cerro el socket."))
            {
                cout << "\n El cliente termino la conexion" << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno= 2;
            }
            else if(!strcmp(servidor.buffer, "ALTA DE SERVICIO."))
            {
                cout << "\n El cliente intenta dar de alta un servicio" << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno= 3;

            }
            else if(!strcmp(servidor.buffer, "GESTIONAR PASAJES."))
            {
                cout << "\n El cliente esta gestionando un pasaje" << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno= 4;
            }
            else if(!strcmp(servidor.buffer, "RESERVAR UN ASIENTO."))
            {
                cout << "\n El cliente esta reservando un asiento" << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno= 5;
            }
            else
            {
                cout << "\nEl cliente dice: " << servidor.buffer << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno= 0;
            }
        return retorno;
}



void enviarMensaje(Servidor &servidor,string mensaje){
    //Copia la cadena del buffer en el mensaje
    strcpy(servidor.buffer, &mensaje[0]);
    //Envia datos sobre un canal de comunicación
    send(servidor.client, servidor.buffer, sizeof(servidor.buffer), 0);
    //Borra el buffer
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
        if(strcmp(servidor.buffer, "Enviando archivo.") && strcmp(servidor.buffer, "Se cerro el socket.")){
                cout << "Mensaje enviado!" << endl << endl;
        }
}

void enviarArchivo(Servidor &servidor,string ruta){
        FILE *File;
        char *Buffer;
        unsigned long Size;
        char nombre[512]= "\0";
        char rutaChar[1024] = "\0";
        string mensaje = "Enviando archivo.";
        cout<<mensaje<<endl;
        enviarMensaje(servidor,mensaje); // manda aviso para que limpie buffer
        strcpy(nombre, &ruta[0]); //Mando ruta y nombre de archivo
        SafeSend(servidor.client, nombre, sizeof(nombre));
        strcpy(rutaChar, &ruta[0]);
        /**"rb" archivo binario*/
        File = fopen(rutaChar, "rb");
            if(!File)
            {
                cout<<"Error al leer archivo"<<endl;
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
                SafeSend(servidor.client, cSize, MAX_PATH); // File size
                Sleep(1000);
                SafeSend(servidor.client,Buffer,Size);
            }
        free(Buffer);
}

void recibirArchivo(Servidor &servidor){
    cout<<"Recibiendo archivo..."<<endl;
    int Size;
    char Filesize[MAX_PATH] = "\0";
    char nombre[512] = "\0";
    recv(servidor.client, nombre, sizeof(nombre), 0);
        if(recv(servidor.client, Filesize, sizeof(Filesize), 0)){
            Size = atoi((const char*)Filesize);
            cout<< "Tamanio del archivo: "<< Size<<endl;
        }
        char *Buffer = new char[Size];
        recv(servidor.client, Buffer, Size, 0);
        cout<< "Se trajo el archivo: "<< nombre <<endl;
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

	while(sendlen != buflen)
	{
		sendlen = send(s, &buf[totalsend], remaining, 0);
            if(sendlen == SOCKET_ERROR)
            {
			return SOCKET_ERROR;
            }
		totalsend = totalsend + sendlen;
		remaining = sendlen - totalsend;
	}
    return 0;
}

void cerrarSocket(Servidor &servidor){
    closesocket(servidor.client);
    cout << "Se cerro el socket, se desconecto el cliente." << endl;
}


string msj(char* grupo){
    string cadena = "";
        for(int i=2;grupo[i]!='\0';i++){
            cadena = cadena + grupo[i];
        }
    return cadena;
}


void barraCargando(){
    int segundos=2;
    cout << "\n";
    cout << "\t\t\t CARGANDO SERVIDOR...\n";
        for(int i=0; i<=0; i++)
            cout << "_";
        for(int i=0; i<=70; i++){
            cout<<char(219);
            Sleep(segundos*1000/175);
        }
}


string fechaHora(){
    ostringstream oss;
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    oss<<put_time(&tm, "%d-%m-%Y %H:%M:%S");
    auto str = oss.str();
    return str;
}
void recibirDestino(Servidor &servidor,Viaje &viaje){
    servidor.buffer[0] = '\0';
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    strcpy(viaje.destino,servidor.buffer);
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
}


void recibirFecha(Servidor &servidor,Viaje &viaje){
    servidor.buffer[0] = '\0';
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    strcpy(viaje.fecha,servidor.buffer);
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
}

void recibirTurno(Servidor &servidor,Viaje &viaje){
    servidor.buffer[0] = '\0';
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    strcpy(viaje.turno,servidor.buffer);
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
}


void recibirFila(Servidor &servidor,Viaje &viaje){
    servidor.buffer[0] = '\0';
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    strcpy(viaje.esquema.fila4,servidor.buffer);
    /*if(servidor.buffer=='A' || servidor.buffer=='b'){
        strcpy(viaje.esquema.fila4,servidor.buffer);
    }
    else if(servidor.buffer=='B' || servidor.buffer=='b'){
        strcpy(viaje.esquema.fila5,servidor.buffer);
    }
    else if(servidor.buffer=='B' || servidor.buffer=='B'){
        strcpy(viaje.esquema.fila7,servidor.buffer);
    }*/
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
}

int recibirColumna(Servidor &servidor){
    servidor.buffer[0] = '\0';
    int columna;
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    columna=atoi(servidor.buffer);
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
    return columna;
}

int menuCrearViaje(Servidor &servidor,Viaje &viaje){

	enviarMensaje(servidor,"Ingrese origen (MDQ | BSAS) :");
    Sleep(1000);
    recibirDestino(servidor,viaje);
    enviarMensaje(servidor,"Ingrese fecha: (dd/mm/aaaa) : ");
    Sleep(1000);
    recibirFecha(servidor,viaje);
    enviarMensaje(servidor,"ingrese turno: (manana | tarde | noche) : ");
    Sleep(1000);
    recibirTurno(servidor,viaje);
	viaje = crearViaje(viaje.destino,viaje.fecha,viaje.turno);
	mostrarEsquema(viaje);
   return 40;
}



int menuAsignarAsiento(Servidor &servidor,Viaje &viaje){
    enviarMensaje(servidor,"Ingrese origen (MDQ | BSAS) :");
    Sleep(1000);
    recibirDestino(servidor,viaje);
    enviarMensaje(servidor,"Ingrese fecha: (dd/mm/aaaa) : ");
    Sleep(1000);
    recibirFecha(servidor,viaje);
    enviarMensaje(servidor,"Ingrese turno: (manana | tarde | noche) : ");
    Sleep(1000);
    recibirTurno(servidor,viaje);
    enviarMensaje(servidor,"Ingrese fila (A | B | C) : ");
    recibirFila(servidor,viaje);
    enviarMensaje(servidor,"Ingrese columna (1 al 20) : ");
    int columna=recibirColumna(servidor);
	//modificacionFicheroAsignar(a,a,a,a,recibirColumna(servidor));
	return 41;
}


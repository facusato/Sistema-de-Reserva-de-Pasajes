#include "Server.h"

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
        if((servidor.client = accept(servidor.server, (SOCKADDR *)&servidor.clientAddr, &clientAddrSize)) != INVALID_SOCKET)
        {
            system("cls");
            cout << "Se conecto el cliente." << endl;
        }
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
                cout << "\nEl cliente termino la conexion" << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno= 2;
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
    strcpy(servidor.buffer, &mensaje[0]);
    /**Envia datos sobre un canal de comunicación */
    send(servidor.client, servidor.buffer, sizeof(servidor.buffer), 0);
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

void menu(){
    cout<< "\n\n";
    cout<<"---Server---"<<endl;
    cout<< "Elija una opcion: " <<endl;
    cout<< " M (Mensaje)                    --->    Ejemplo: M hola\n";
    cout<< " T (Transferencia de archivo)   --->    Ejemplo: T C:/Users/Facu/Desktop/eee/a.jpg \n";
    cout<< " F (Salir)" <<endl<<endl;
}

void barraCarga(){
    int segundos=2;
    cout << "\n";
    cout << "\t\t\t CARGANDO SERVIDOR...\n";
        for(int i=0; i<=0; i++)
            cout << "_";
        for(int i=0; i<=70; i++)
        {
            cout<<char(219);
            Sleep(segundos*1000/175);
        }
}

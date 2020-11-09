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


void escuchando(Servidor &servidor){
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


bool validarCredencial(Servidor &servidor, string usuario){
    servidor.buffer[0] = '\0';
    string password;
    string txt= ".txt";
    bool valido=false;
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
            else if(!strcmp(servidor.buffer, "LIBERAR UN ASIENTO."))
            {

                cout<< "\n El cliente esta liberando un asiento" << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno=6;

            }
            else if(!strcmp(servidor.buffer, "VER SERVICIOS DISPONIBLES."))
            {
                cout<< "\n El cliente esta pidiendo el archivo" << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno=7;

            }
            else if(!strcmp(servidor.buffer, "VER POR DESTINO."))
            {
                cout<< "\n El cliente esta pidiendo el archivo" << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno=8;

            }
            else if(!strcmp(servidor.buffer, "VER POR FECHA."))
            {
                cout<< "\n El cliente esta pidiendo el archivo" << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno=9;

            }
            else if(!strcmp(servidor.buffer, "VER POR TURNO."))
            {
                cout<< "\n El cliente esta pidiendo el archivo" << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno=10;
            }
            else if(!strcmp(servidor.buffer, "VER REGISTRO DE ACTIVIDADES."))
            {
                cout<< "\n El cliente esta pidiendo su archivo de actividad" << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno=11;
            }
            else
            {
                cout << "\nEl cliente dice: " << servidor.buffer << endl;
                memset(servidor.buffer, 0, sizeof(servidor.buffer));
                retorno= 50;
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

void enviarArchivo(Servidor &servidor,string ruta)
    {
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

        File = fopen(rutaChar, "rb");

        if(!File)
        {
            cout<<"Error al leer archivo"<<endl;
            cin.ignore();
        }
        else
        {
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
void recibirDestino(Servidor &servidor,Viaje &viaje, string usuario){
    servidor.buffer[0] = '\0';
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    strcpy(viaje.destino,servidor.buffer);
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
    ingresarActividadCliente(usuario,""+fechaHora()+" Destino:");
    ingresarActividadCliente(usuario,""+fechaHora()+" "+ viaje.destino);
}


void recibirFecha(Servidor &servidor,Viaje &viaje, string usuario){
    servidor.buffer[0] = '\0';
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    strcpy(viaje.fecha,servidor.buffer);
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
    ingresarActividadCliente(usuario,""+fechaHora()+" Fecha:");
    ingresarActividadCliente(usuario,""+fechaHora()+" "+ viaje.fecha);
}

void recibirTurno(Servidor &servidor,Viaje &viaje, string usuario){
    servidor.buffer[0] = '\0';
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    strcpy(viaje.turno,servidor.buffer);
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
    ingresarActividadCliente(usuario,""+fechaHora()+ " Turno:");
    ingresarActividadCliente(usuario,""+fechaHora()+" "+ viaje.turno);
}


char recibirFila(Servidor &servidor, string usuario){
    servidor.buffer[0] = '\0';
    char unCaracter;
    char *puntero = NULL;
    puntero = &unCaracter;
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    strcpy(puntero,servidor.buffer);
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
    std::string fila;
    fila.push_back(unCaracter);
    ingresarActividadCliente(usuario,""+fechaHora()+" Fila: "+ fila);
    return unCaracter;
}

int recibirColumna(Servidor &servidor, string usuario){
    servidor.buffer[0] = '\0';
    int columna;
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    columna=atoi(servidor.buffer);
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
    ingresarActividadCliente(usuario,""+fechaHora()+" Columna: "+ std::to_string(columna));
    return columna;
}

int menuCrearViaje(Servidor &servidor,Viaje &viaje, string usuario){
	enviarMensaje(servidor,"Ingrese destino: (MDQ | BSAS) :");
    Sleep(1000);
    recibirDestino(servidor,viaje, usuario);
    enviarMensaje(servidor,"Ingrese fecha: (dd/mm/aaaa) : ");
    Sleep(1000);
    recibirFecha(servidor,viaje,usuario);
    enviarMensaje(servidor,"ingrese turno: (manana | tarde | noche) : ");
    Sleep(1000);
    recibirTurno(servidor,viaje,usuario);
    viaje = crearViaje(viaje.destino,viaje.fecha,viaje.turno);
    mostrarEsquema(viaje);
    enviarMensaje(servidor,"Alta correctamente");
    return 40;
}



int menuAsignarAsiento(Servidor &servidor,Viaje &viaje, string usuario){
    char fila;
    int flag=0;
    enviarMensaje(servidor,"Ingrese destino: (MDQ | BSAS) :");
    Sleep(1000);
    recibirDestino(servidor,viaje, usuario);
    enviarMensaje(servidor,"Ingrese fecha: (dd/mm/aaaa) : ");
    Sleep(1000);
    recibirFecha(servidor,viaje, usuario);
    enviarMensaje(servidor,"Ingrese turno: (manana | tarde | noche) : ");
    Sleep(1000);
    recibirTurno(servidor,viaje, usuario);
    enviarMensaje(servidor,"Ingrese fila (A | B | C) : ");
    fila=recibirFila(servidor, usuario);
    enviarMensaje(servidor,"Ingrese columna (1 al 20) : ");
	modificacionFicheroAsignar1(servidor,viaje.destino,viaje.fecha,viaje.turno,fila,recibirColumna(servidor,usuario));
	return flag;
}

int menuLiberarAsiento(Servidor &servidor, Viaje &viaje, string usuario){
    char fila;
    enviarMensaje(servidor,"Ingrese destino: (MDQ | BSAS) :");
    Sleep(1000);
    recibirDestino(servidor,viaje,usuario);
    enviarMensaje(servidor,"Ingrese fecha: (dd/mm/aaaa) : ");
    Sleep(1000);
    recibirFecha(servidor,viaje,usuario);
    enviarMensaje(servidor,"ingrese turno: (manana | tarde | noche) : ");
    Sleep(1000);
    recibirTurno(servidor,viaje,usuario);
    enviarMensaje(servidor,"Ingrese fila: (A | B | C):");
    fila=recibirFila(servidor, usuario);
    enviarMensaje(servidor,"Ingrese columna (1 al 20)");
    modificacionFicheroLiberar1(servidor,viaje.destino,viaje.fecha,viaje.turno,fila, recibirColumna(servidor,usuario));
    return 42;
}


int filtrarPorDestino(Servidor &servidor,Viaje &viaje, string usuario){

    enviarMensaje(servidor,"Ingrese destino: (MDQ | BSAS) :");
    Sleep(1000);
    recibirDestino(servidor,viaje,usuario);
    return consultaPorDestino1(servidor,viaje.destino);
}

int filtrarPorFecha(Servidor &servidor,Viaje &viaje, string usuario){

    enviarMensaje(servidor,"Ingrese fecha: (dd/mm/aaaa) : ");
    Sleep(1000);
    recibirFecha(servidor,viaje,usuario);
    return consultaPorFecha2(servidor,viaje.fecha);
}

int filtrarPorTurno(Servidor &servidor,Viaje &viaje, string usuario){

    enviarMensaje(servidor,"ingrese turno: (manana | tarde | noche) : ");
    Sleep(1000);
    recibirTurno(servidor,viaje, usuario);
    return consultaPorTurno2(servidor,viaje.turno);

}

void ingresarActividadCliente(string usuario, string actividad){

    ofstream archivoCliente;

    archivoCliente.open(""+usuario+".txt",ios::app);
    if(archivoCliente.fail()){
    cout<<"error al abrir o crear el archivo del cliente"<<endl;}

    archivoCliente <<actividad<<endl;

    archivoCliente.close();
}

string recibirUsuario (Servidor &servidor, string usuario){
    enviarMensaje(servidor,"INGRESE USUARIO");
    Sleep(1000);
    recv(servidor.client,servidor.buffer, sizeof(servidor.buffer), 0);
    usuario=servidor.buffer;
    memset(servidor.buffer, 0, sizeof(servidor.buffer));
    return usuario;
}


bool is_file(string file){
 bool existe=false;
 FILE * archivo;
    if (archivo = fopen(file.c_str(), "rb"))
    {
    fclose(archivo);
    existe=true;
    }
 return existe;
}

int consultaPorDestino1(Servidor &servidor,char destino[20]){

    FILE *fichero;
    fichero=fopen("Servicios.bin","rb");

    Viaje viaje;
    int existe=0;
    fread(&viaje, sizeof(Viaje), 1, fichero);
    while(!feof(fichero))
    {
        if (strcmp(getDestino(viaje),destino)==0)
        {
        	cout<<"------------------------"<<endl;
			cout<< getDestino(viaje)<<endl;
			cout<< getFecha(viaje)<<endl;
			cout<< getTurno(viaje)<<endl;
			cout<<endl;
			mostrarEsquema(viaje);
			escribirFicheroDestino(viaje);
			cout<<endl;
			cout<<"------------------------"<<endl;
        	existe=1;
        }
        fread(&viaje, sizeof(Viaje), 1, fichero);
    }
    if (existe==0)
        cout<<"No existe servicio con dichos parametros"<<endl;

    fclose(fichero);
    return existe;
}

int consultaPorFecha2(Servidor &servidor,char fecha[20]){

    FILE *fichero;
    fichero=fopen("Servicios.bin","rb");

    Viaje viaje;
    int existe=0;
    fread(&viaje, sizeof(Viaje), 1, fichero);
    while(!feof(fichero))
    {
        if (strcmp(getFecha(viaje),fecha) == 0){
        	cout<<"------------------------"<<endl;
			cout<< getDestino(viaje)<<endl;
			cout<< getFecha(viaje)<<endl;
			cout<< getTurno(viaje)<<endl;
			cout<<endl;
			mostrarEsquema(viaje);
			escribirFicheroFecha(viaje);
			cout<<endl;
			cout<<"------------------------"<<endl;
        	existe=1;
        }
        fread(&viaje, sizeof(Viaje), 1, fichero);
    }
    if (existe==0)
        cout<<"No existe servicio con dichos parametros"<<endl;
    fclose(fichero);
    return existe;
}


int consultaPorTurno2(Servidor &servidor,char turno[20]){

    FILE *fichero;
    fichero=fopen("Servicios.bin","rb");

    Viaje viaje;
    int existe=0;
    fread(&viaje, sizeof(Viaje), 1, fichero);
    while(!feof(fichero))
    {
        if (strcmp(getTurno(viaje),turno)==0)
        {
        	cout<<"------------------------"<<endl;
			cout<< getDestino(viaje)<<endl;
			cout<< getFecha(viaje)<<endl;
			cout<< getTurno(viaje)<<endl;
			cout<<endl;
			mostrarEsquema(viaje);
			escribirFicheroTurno(viaje);
			cout<<endl;
			cout<<"------------------------"<<endl;
        	existe=1;
        }
        fread(&viaje, sizeof(Viaje), 1, fichero);

    }
    if (existe==0)
        cout<<"No existe servicio con dichos parametros"<<endl;

    fclose(fichero);
    return existe;
}


void modificacionFicheroAsignar1(Servidor &servidor,char destino[20], char fecha[20], char turno[20], char fila, int columna ){

    FILE *fichero;
    fichero=fopen("Servicios.bin","r+b");
        if (fichero==NULL)
            exit(1);

    Viaje viaje;
    int existe=0;			//flag para comprobar si existe el registro buscado.

    fread(&viaje, sizeof(Viaje), 1,fichero);
        while(!feof(fichero))
        {
            if (strcmp(getDestino(viaje),destino) == 0 && strcmp(getFecha(viaje),fecha) == 0 && strcmp(getTurno(viaje),turno) == 0)			//compara si coinciden registro leido con parametro
            {
                asignarAsiento2(servidor,viaje,fila,columna);				//asigna el asiento al registro leido
                int pos=ftell(fichero)-sizeof(Viaje);			//lee la posicion del cursor en el fichero
                fseek(fichero,pos,SEEK_SET);						//reacomoda cursor en fichero
                fwrite(&viaje, sizeof(Viaje), 1, fichero);		//reescribe fichero modificado, pisando el anterior.
                existe=1;
                break;
            }
         fread(&viaje, sizeof(Viaje), 1, fichero);
        }
    if (existe==0){
        cout<<"No existe un viaje con dichos parametros"<<endl;
        enviarMensaje(servidor,"No existe un viaje con dichos parametros");
    }
    fclose(fichero);
}



void asignarAsiento2(Servidor &servidor,Viaje &viaje, char fila, int columna){

	int columna_aux = columna + 1;
	char* fila_temporal;
	char* fila_temporal1 = getFila2(viaje);		// pasa pisar la linea 2 del esquema (no encontre porque se setea mal dado que en ninguna parte del codigo se toca)

	if(true){			// validar si viaje existe (por ahora entra siempre)


		if(fila == 'A' ||fila == 'a'){
			fila_temporal = getFilaA(viaje);				//TRAE LA FILA A DEL ESQUEMA COMPLETA

				if(fila_temporal[columna_aux] == 'O'){					//verifica si esta libre el asiento, si esta libre entra
					fila_temporal[columna_aux] = 'X';

					strcpy(fila_temporal1," |12345678901234567890");
					setFila2(viaje, fila_temporal1);

					setFilaA(viaje, fila_temporal);					//SETEA EN EL VIAJE DEL PARAMETRO LA FILA COMPLETA YA MODIFICADA
					cout<<"Se asigno el asiento para dicho viaje."<<endl;
					enviarMensaje(servidor,"Se asigno el asiento correctamente");
					system("cls");
					mostrarEsquema(viaje);
				}else{
					cout<<"asiento ocupado"<<endl;
					enviarMensaje(servidor,"El asiento esta ocupado");
				}
		}

		if(fila == 'B' ||fila == 'b'){
			fila_temporal = getFilaB(viaje);

				if(fila_temporal[columna_aux] == 'O'){				//verifica si esta libre el asiento, si esta libre entra
					fila_temporal[columna_aux] = 'X';

					strcpy(fila_temporal1," |12345678901234567890");
					setFila2(viaje, fila_temporal1);

					setFilaB(viaje, fila_temporal);					//SETEA EN EL VIAJE DEL PARAMETRO LA FILA COMPLETA YA MODIFICADA
					cout<<"Se asigno el asiento para dicho viaje."<<endl;
					enviarMensaje(servidor,"Se asigno el asiento correctamente");
					mostrarEsquema(viaje);
				}else{
					cout<<"asiento ocupado"<<endl;
					enviarMensaje(servidor,"El asiento esta ocupado");
				}
		}
		if(fila == 'C' ||fila == 'c'){
			fila_temporal = getFilaC(viaje);

				if(fila_temporal[columna_aux] == 'O'){				//verifica si esta libre el asiento, si esta libre entra
					fila_temporal[columna_aux] = 'X';

					strcpy(fila_temporal1," |12345678901234567890");
					setFila2(viaje, fila_temporal1);

					setFilaC(viaje, fila_temporal);					//SETEA EN EL VIAJE DEL PARAMETRO LA FILA COMPLETA YA MODIFICADA
					cout<<"Se asigno el asiento para dicho viaje."<<endl;
					enviarMensaje(servidor,"Se asigno el asiento correctamente");
					mostrarEsquema(viaje);
				}else{
					cout<<"asiento ocupado"<<endl;
					enviarMensaje(servidor,"El asiento esta ocupado");
				}
		}
	}else{
		cout<<"No existe el viaje, proceda a dar de alta el servicio"<<endl;
	}

}


void modificacionFicheroLiberar1(Servidor &servidor,char destino[20], char fecha[20], char turno[20], char fila, int columna ){

    FILE *fichero;
    fichero=fopen("Servicios.bin","r+b");
    if (fichero==NULL)
        exit(1);

    Viaje viaje;
    int existe=0;			//flag para comprobar si existe el registro buscado.

    fread(&viaje, sizeof(Viaje), 1,fichero);
        while(!feof(fichero))
        {
            if (strcmp(getDestino(viaje),destino) == 0 && strcmp(getFecha(viaje),fecha) == 0 && strcmp(getTurno(viaje),turno) == 0)			//compara si coinciden registro leido con parametro
            {
                liberarAsiento2(servidor,viaje,fila,columna);				//asigna el asiento al registro leido
                int pos=ftell(fichero)-sizeof(Viaje);			//lee la posicion del cursor en el fichero
                fseek(fichero,pos,SEEK_SET);						//reacomoda cursor en fichero
                fwrite(&viaje, sizeof(Viaje), 1, fichero);		//reescribe fichero modificado, pisando el anterior.
                existe=1;
                break;
            }
         fread(&viaje, sizeof(Viaje), 1, fichero);
        }
    if (existe==0){
        cout<<"No existe un viaje con dichos parametros"<<endl;
        enviarMensaje(servidor,"No existe un viaje con dichos parametros");
    }
    fclose(fichero);
}

void liberarAsiento2(Servidor &servidor,Viaje &viaje, char fila, int columna){

	int columna_aux = columna + 1;
	char* fila_temporal;
	char* fila_temporal1 = getFila2(viaje);		// pasa pisar la linea 2 del esquema (no encontre porque se setea mal dado que en ninguna parte del codigo se toca)

	if(true){			// validar si viaje existe (por ahora entra siempre)


		if(fila == 'A' ||fila == 'a'){
			fila_temporal = getFilaA(viaje);				//TRAE LA FILA A DEL ESQUEMA COMPLETA

				if(fila_temporal[columna_aux] == 'X'){				//verifica si esta ocupado el asiento, si esta ocupado entra
					fila_temporal[columna_aux] = 'O';

					strcpy(fila_temporal1," |12345678901234567890");
					setFila2(viaje, fila_temporal1);

					setFilaA(viaje, fila_temporal);					//SETEA EN EL VIAJE DEL PARAMETRO LA FILA COMPLETA YA MODIFICADA
					cout<<"Se libero el asiento para dicho viaje."<<endl;
					enviarMensaje(servidor,"Se libero el asiento para dicho viaje.");
					mostrarEsquema(viaje);
				}else{
					cout<<"asiento vacio"<<endl;
					enviarMensaje(servidor,"El asiento que quiere liberar esta vacio");
				}

		}

		if(fila == 'B' ||fila == 'b'){
			fila_temporal = getFilaB(viaje);

				if(fila_temporal[columna_aux] == 'X'){				//verifica si esta ocupado el asiento, si esta ocupado entra
					fila_temporal[columna_aux] = 'O';

					strcpy(fila_temporal1," |12345678901234567890");
					setFila2(viaje, fila_temporal1);

					setFilaB(viaje, fila_temporal);					//SETEA EN EL VIAJE DEL PARAMETRO LA FILA COMPLETA YA MODIFICADA
					cout<<"Se libero el asiento para dicho viaje."<<endl;
					enviarMensaje(servidor,"Se libero el asiento para dicho viaje.");
					mostrarEsquema(viaje);
				}else{
					cout<<"asiento vacio"<<endl;
					enviarMensaje(servidor,"El asiento que quiere liberar esta vacio");
				}

		}
		if(fila == 'C' ||fila == 'c'){
			fila_temporal = getFilaC(viaje);

				if(fila_temporal[columna_aux] == 'X'){						//verifica si esta ocupado el asiento, si esta ocupado entra
					fila_temporal[columna_aux] = 'O';

					strcpy(fila_temporal1," |12345678901234567890");
					setFila2(viaje, fila_temporal1);

					setFilaC(viaje, fila_temporal);					//SETEA EN EL VIAJE DEL PARAMETRO LA FILA COMPLETA YA MODIFICADA
					cout<<"Se libero el asiento para dicho viaje."<<endl;
					enviarMensaje(servidor,"Se libero el asiento para dicho viaje.");
					mostrarEsquema(viaje);
				}
				else{
					cout<<"asiento vacio"<<endl;
					enviarMensaje(servidor,"El asiento que quiere liberar esta vacio");
				}
		}
	}else{
		cout<<"no existe viaje, favor de crearlo primero"<<endl;
	}

}



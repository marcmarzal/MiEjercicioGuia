#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
int contador;
contador = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *AtenderCliente(void *socket){
	int socket_conn;
	int *s;
	s= (int*) socket;
	sock_conn= *s;


	char peticion[512];
	char respuesta[512];


	int terminar = 0;
	int terminar = 0;
		while (terminar ==0);
		{
			
			
			
			// Ahora recibimos su nombre, que dejamos en buff
			ret=read(sock_conn,peticion, sizeof(peticion));
			printf ("Recibido\n");
			
			// Tenemos que a?adirle la marca de fin de string 
			// para que no escriba lo que hay despues en el buffer
			peticion[ret]='\0';
			
			//Escribimos el nombre en la consola
			
			printf ("Se ha conectado: %s\n",peticion);
			
			
			char *p = strtok( peticion, "/");
			int codigo =  atoi (p);
			char nombre[20];
			
			if ((codigo != 0)&&(codigo != 4))
			{
				p = strtok( NULL, "/");
				strcpy (nombre, p);
				printf ("Codigo: %d, Nombre: %s\n", codigo, nombre);
			}
			if ( codigo == 0)
				terminar = 1;
			
			if (codigo ==1) //piden la longitd del nombre
				sprintf (respuesta,"%d,",strlen (nombre));
			else if (codigo ==2)
			
					// quieren saber si el nombre es bonito
					if((nombre[0]=='M') || (nombre[0]=='S'))
						strcpy (respuesta,"SI,");
					else
						strcpy (respuesta,"NO,");
			else if(codigo ==3)
				{
					p = strtok(NULL,"/");
					float altura = atof(p);
					if(altura > 1.70)
						sprintf(respuesta , "%s: eres alto",nombre);
					else
						sprintf (respuesta, "%s: eres bajo",nombre);

				}
			else if(codigo ==4){
				pthread_mutex_lock(&mutex);
				sprintf (respuesta,"%d",contador);
				pthread_mutex_unlock(&mutex)
			}

			
			if (codigo != 0)
			{
				printf ("%s\n", respuesta);
				// Y lo enviamos
				write (sock_conn,respuesta, strlen(respuesta));		
			}
			if ((codigo==1)||(codigo == 2)||(codigo==3))
				contador =contador+1;
		}
		// Se acabo el servicio para este cliente
		close(sock_conn); 
}




int main(int argc, char *argv[])
{
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;

	// INICIALITZACIONS
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");
	// Fem el bind al port
	
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// escucharemos en el port 9050
	serv_adr.sin_port = htons(9080);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	//La cola de peticiones pendientes no podr? ser superior a 4
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");
	
	int i;
	int sockets[100];
	pthread_t thread;
	// Atenderemos solo 5 peticione
	i=0;
	for(;;){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexi?n\n");
		sockets[i] = sock_conn;
		//sock_conn es el socket que usaremos para este cliente
		
		pthread_create(&thread,NULL,AtenderCliente, &sockets[i]);
		i=i+1;
		
	}

	//for(i=0, i<5,i++)
		//pthread_join(thread[i],NULL);
}

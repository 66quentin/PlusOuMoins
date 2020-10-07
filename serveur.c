#include "conn.c"
#include <time.h>
#include <pthread.h>


void * devine_nombre(void *socket){
	int sol=1,x;
	srand(time(NULL));
	int d = rand()%1000;
	char msg[32],msg2[32];
	int socket2=(int)socket;
	
	while(sol>0){
		memset(msg2, 0,sizeof(msg2));
		memset(msg, 0,sizeof(msg));
		int r=recv(socket2, msg, sizeof(msg), 0);
		if(r==-1)
			perror("Recv");
		int r2=read(socket2, msg, sizeof(msg));
		if(r2==-1)
			perror("Read");
		x=atoi(msg);
		printf("Valeur reçue: %d, valeur attendue: %d\n",x,d);

		if(x<d)
			strcpy(msg2,"C'est plus");
		else if(x>d)
			strcpy(msg2,"C'est moins");
		else{
			strcpy(msg2,"Gagné !");
			sol=0;
		}
					
		int w=write(socket2, msg2, sizeof(msg2));
		if(w==-1)
			perror("Write");
		int s=send(socket2, msg2, sizeof(msg2), 0);
		if(s==-1)
			perror("Send");
		}
	pthread_exit(0);
}
	



int main (void){

	pthread_t my_thread;

	struct sockaddr_in sock;
	sock.sin_port=htons(3001);
	sock.sin_family=AF_INET;
	memset(sock.sin_zero,0,8);
	struct hostent *nv_host=gethostbyname("localhost");
	sock.sin_addr.s_addr=((struct in_addr *)(nv_host->h_addr_list[0]))->s_addr;

	int socket1 = socket(AF_INET, SOCK_STREAM, 0),socket2;

	if(socket1 != -1){
		int bind1= bind(socket1, (struct sockaddr*)&sock, sizeof(sock));
		if(bind1==-1)
			perror("Bind");
		while(1){
			int ecoute=listen(socket1, 1);
			if(ecoute==-1)
				perror("Listen");
			int taille=sizeof(struct sockaddr_in*);
			socket2=accept(socket1, (struct sockaddr*)&sock, (socklen_t*)&taille);
			if(socket2==-1)
				perror("Accept");
			pthread_create(&my_thread,NULL,devine_nombre,  (void *)socket2);

			pthread_join(my_thread, NULL);
		}
	}else
		printf("Erreur création socket\n");
	close(socket1);
	close(socket2);
		
	return 0;
}

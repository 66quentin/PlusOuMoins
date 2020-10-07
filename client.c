#include "conn.c"

int main (void){
	struct sockaddr_in sock;
	sock.sin_port=htons(3001);
	sock.sin_family=AF_INET;
	memset(sock.sin_zero,0,8);
	struct hostent *nv_host=gethostbyname("localhost");
	sock.sin_addr.s_addr=((struct in_addr *)(nv_host->h_addr_list[0]))->s_addr;

	int boucle=1;
	int socket1 = socket(AF_INET, SOCK_STREAM, 0);
	char msg[32],x[3];
	if(socket1 != -1){
		int c=connect(socket1, (struct sockaddr*)&sock, sizeof(sock));
		if(c==-1)
			perror("Connect");
		while(boucle){
			memset(msg, 0,sizeof(msg));
			memset(x, 0,sizeof(x));
			printf("Entrer une valeur:");
			scanf(" %s",x);
		
			int w=write(socket1, x, sizeof(x));
			if(w==-1)
				perror("Write");
			int s=send(socket1, x, sizeof(x), 0);
			if(s==-1)
				perror("Send");
			int r=recv(socket1, msg, 32, 0);
			if(r==-1)
				perror("Recv");
			int r2=read(socket1, msg, sizeof(msg));
			if(r2==-1)
				perror("Read");
			printf("Message: %s\n",msg);
			if(strlen(msg)<=8)
				boucle=0;
		}
	}else
		printf("Erreur en créant le socket\n");
	close(socket1);
		
	return 0;
}

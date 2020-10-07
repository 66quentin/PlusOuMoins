#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

struct sockaddr_in* adresse(char* host, int port){
	int p=1;
	struct sockaddr_in *nv_sock=malloc(sizeof(struct sockaddr_in*));
	nv_sock->sin_port=htons(port);
	nv_sock->sin_family=AF_INET;
	memset(nv_sock->sin_zero,0,8);

	struct hostent *nv_host=gethostbyname(host);
	

	//nv_sock->sin_addr.s_addr=(u_long)nv_host->h_addr_list[0];
	nv_sock->sin_addr.s_addr=inet_addr(host);

	return nv_sock;
}

void afficher(struct sockaddr_in* sock){
	printf("%s:%d\n",inet_ntoa(sock->sin_addr),sock->sin_port);
}


/*int main (void) {
	struct sockaddr_in* sock=adresse("localhost",80);
	afficher(sock);
	free(sock);
	return 0;
}*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define h_addr h_addr_list[0]
//#include <cstdlib>
//#include <cstdio>
//using namespace std;

void error(char* msg){
	perror(msg);
	exit(1);
}

int main(int argc, char*argv[]){
	int sockfd, portno, n;
	char buffer[256];
	struct sockaddr_in serv_addr;
	struct hostent *server;

	if(argc <3){
		fprintf(stderr, "ERROR, usage %s hostname port\n", argv[0]);
		exit(0);
	}
	portno = atoi(argv[2]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0) error("ERROR opening socket\n");

	server = gethostbyname(argv[1]);
	if(!server){
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}

	bzero((char*)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
//	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if(connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0) error("ERROR on connecting\n");
	printf("please enter message\n");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	n = write(sockfd, buffer, strlen(buffer));
	if(n < 0)error("ERROR writing to socket\n");

//	listen(sockfd, 5);
//	clilen = sizeof(cli_addr);
//	newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
//	if(newsockfd < 0)error("ERROR on accept\n");

	bzero(buffer, 256);
	n = read(sockfd, buffer, 255);
	if(n < 0)error("ERROR reading from socket\n");
	printf("%s\n", buffer);
//	n = write(newsockfd, "I got your message\n", 19);
//	if(n<0)error("ERROR writing to socket\n");
	return 0;
}

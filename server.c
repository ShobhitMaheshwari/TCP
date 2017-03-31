#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void dostuff(int); /* function prototype */
void error(char* msg){
	perror(msg);
	exit(1);
}

int main(int argc, char*argv[]){
	int sockfd, newsockfd, portno, clilen, pid;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	if(argc <2){
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0) error("ERROR opening socket\n");

	bzero((char*)&serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	int yes=1;
	//char yes='1'; // use this under Solaris
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
    	perror("setsockopt");
	    exit(1);
	}

	if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding\n");
	listen(sockfd, 2);

	clilen = sizeof(cli_addr);

	while(1){
		newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
		if(newsockfd < 0)error("ERROR on accept\n");
		pid = fork();
		if (pid < 0)
			error("ERROR on fork");
		if (pid == 0)  {
			close(sockfd);
			dostuff(newsockfd);
			exit(0);
		}
		else close(newsockfd);
//	bzero(buffer, 256);
//	n = read(newsockfd, buffer, 255);
//	if(n < 0)error("ERROR reading from socket\n");
//	printf("Here is message: %s\n", buffer);
//	n = write(newsockfd, "I got your message\n", 19);
//	if(n<0)error("ERROR writing to socket\n");
	//close(newsockfd);
	}
	return 0;
}

/******** DOSTUFF() *********************
 There is a separate instance of this function
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
void dostuff (int sock)
{
   int n;
   char buffer[256];

   bzero(buffer,256);
   n = read(sock,buffer,255);
   if (n < 0) error("ERROR reading from socket");
   printf("Here is the message: %s\n",buffer);
   n = write(sock,"I got your message",18);
   if (n < 0) error("ERROR writing to socket");
}

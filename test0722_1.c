#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<strings.h>


#define PORT    1234
#define MAXSOCKFD 10


	int main(){
	int sockfd,newsockfd,is_connected[MAXSOCKFD],fd;
	struct sockaddr_in addr;
	int addr_len =sizeof(struct sockaddr_in);
	fd_set readfds;
	char buffer[256];
	char msg[]="Welcome to server!";
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0){
	perror("socket");
	exit(1);

}
	bzero(&addr,sizeof(addr));
	addr.sin_family= AF_INET;
	addr.sin_port=htons(PORT);
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(sockfd, (struct sockaddr*)&addr,sizeof(addr))<0){
	perror("connect");
	exit(1);
}
	if(listen(sockfd,3)<0){
	perror("listen");
	exit(1);
}
	for(fd = 0;fd<MAXSOCKFD;fd++)
	is_connected[fd]=0;
	while(1){
	FD_ZERO(&readfds);
	FD_SET(sockfd,&readfds);
	for(fd=0; fd<MAXSOCKFD;fd++)
	if(is_connected[fd]) FD_SET(fd,&readfds);
	if(!select(MAXSOCKFD,&readfds,NULL,NULL,NULL))continue;
	for(fd=0;fd<MAXSOCKFD;fd++)
	if(FD_ISSET(fd,&readfds)){
	if(sockfd ==fd){
	if((newsockfd =accept(sockfd,(struct sockaddr*)&addr,&addr_len))<0)
	perror("accept");
	write(newsockfd,msg,sizeof(msg));
	is_connected[newsockfd]=1;
	printf("Connect from %s\n",inet_ntoa(addr.sin_addr));
}
	else{
	bzero(buffer,sizeof(buffer));
	if(read(fd,buffer,sizeof(buffer))<=0){
	printf("Connection closed.\n");
	is_connected[fd]=0;
	close(fd);
}	
	else
	printf("%s",buffer);

}
}
}
}

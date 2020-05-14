#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>

void main()
{
int con,sockid;
int socket_desc;
struct sockaddr_in servidor;
struct sockaddr_in  client;
sockid = socket(AF_INET , SOCK_STREAM , 0);
char buf[1000];
bzero(&buf, 1000);
int numbytes;

if (sockid == -1)
{
    printf("Não foi possível criar o socket");
    exit(1);
}
servidor.sin_family = AF_INET;
servidor.sin_addr.s_addr = htonl(INADDR_ANY);
servidor.sin_port = htons( 8789 );
if( bind(sockid,(struct sockaddr *)&servidor , sizeof(servidor)) < 0)
{
             printf("Falhou ao associar a porta\n");
                exit(1);
}
else{printf("Você conseguiu associar a porta !\n");}
listen(sockid , 3);
int c = sizeof(struct sockaddr_in);

while(1)
{
int new_socket = accept(sockid, (struct sockaddr *)&client, (socklen_t*)&c);
   if (new_socket<=0)
   {
       printf("Falhou ao aceitar a conexão\n");
exit(0);
   }
 printf("Conexão aceita\n");

 send(new_socket,"Bem vindo ao Servidor ! Envie valores de glicemia para obter uma resposta\n",74,0);


do{
if ((numbytes=recv(new_socket, buf, 1000, 0))==-1)
{
  printf("Erro ao receber mensagem\n");
            close(new_socket);
            exit(1);
}
//numbytes = recv(new_socket, buf, 1000, 0);
// printf("numbytes: %s\n", buf);
//do{
	//char buf2[100];
	//buf2=buf;
	int conv=0;
	conv=atoi(buf);
	printf("convertido %d\n", conv);
	if(conv<=100)
	{
		send(new_socket,"Normal\n", 7 ,0);
//		printf("Valor de glicemia normal");
	}
	if(conv>100 && conv<=125)
	{
	send(new_socket, "pre diabetes\n",13, 0);
	}
	if(conv>125)
	{
	send(new_socket, "Diabetes\n",9, 0);
	}

}while(buf!="quit");
close(new_socket); 
}

  
}


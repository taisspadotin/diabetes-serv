#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>

void main()
{
struct sockaddr_in sock;

        int con, sockid, porta;
        char ip[INET_ADDRSTRLEN];
	int resp;
        printf("Digite o ip:");
        scanf("%s", ip);
        printf("Digite a porta do ip: ");
 scanf("%d", &porta);
bzero( &(sock), sizeof(sock));

        sockid = socket(AF_INET, SOCK_STREAM, 0);
        sock.sin_family = AF_INET;
        sock.sin_port = htons(porta);
        inet_pton(AF_INET, ip, &sock.sin_addr);

        con = connect(sockid, (struct sockaddr *)&sock, sizeof(sock));
        char buf[1000];
bzero(buf, 1000);
if (con < 0)
           {
                    printf("\nNão foi possível conectar\n");
                    close(sockid);
           }

int numbytes;
if ((numbytes=recv(sockid, buf, 1000, 0))==-1)
{
  printf("Erro ao receber mensagem\n");
            close(sockid);
            exit(1);
      }
char glic[10];
//int glic=0;
printf("\n\n%s\n\n",buf);
printf("para sair digite quit\n");
do{
printf("Valor:\n");
scanf("%s", &glic);
send(sockid, glic, 10 ,0);


bzero(buf, 1000);


if ((resp=recv(sockid, buf, 1000, 0))==-1)
{
  printf("Erro ao receber mensagem\n");
            close(sockid);
            exit(1);
      }
//int glic=0;
if(buf=="quit"){close(sockid);exit(1);}
printf("\n\n%s\n\n",buf);
}while( strncmp(glic, "quit",4) != 0 /*glic!='quit'*/);

}

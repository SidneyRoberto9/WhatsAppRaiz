#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>

#include "menu.h"
#include "conta.h"
#include "contatos.h" // para evitar bugs //
#include "grupo.h"
#include "ult.h"
#include "socket.h"


#define SIZE 20
#define buffer 1024

void enviar()
{
	int op;
    do{
  		cls(3);
   		op = menu_envio(op);

   		if (op == 1){
   	 		cls(3);
    		client();

    	} else if (op == 2){
    		cls(3);
    		enviar_grupo();

    	} else if (op == 3)break;
	}while(op != 3);
}


int servidor()
{
	SOCKET socketS; // criando o socket 

 	WSADATA wsaData; // estrutura que contem informações sobre sockets no windows.
    WSAStartup(MAKEWORD(2, 2), &wsaData); // iniciando o winsock
   
    struct sockaddr_in local; // estrutura que contém os dados do host local.
    struct sockaddr_in from; // estrutura que contém os dados do cliente.
 
    int fromlen = sizeof(from);
    local.sin_family = AF_INET;
    local.sin_port = htons(5000); // porta que está sendo utilizada
    local.sin_addr.s_addr = INADDR_ANY; //ip local '127.0.0.1'

// iniciando o socket.

    socketS = socket(AF_INET,SOCK_DGRAM,0);

    bind(socketS,(SOCKADDR* )&local,sizeof(local));
    char msg[buffer];
    int t = 0;

//Loop para a comunicação, servidor a espera do cliente.
    cls(3);
    printf("Esperando mensagem\n");
	while (t != 1){
        ZeroMemory(msg, sizeof(msg));
        
        if (recvfrom(socketS,msg,sizeof(msg),0,(SOCKADDR*)&from,&fromlen)!=SOCKET_ERROR){
            printf("Mensagem recebida: %s\n", msg);
            printf("Resposta: ");
            
            setbuf(stdin, NULL);
			fgets(msg, buffer, stdin);
            setbuf(stdin, NULL);
			
			if (strcmp(msg,"sair\n") == 0){
            	t = 1;
			}
            sendto(socketS, msg, sizeof(msg), 0, (SOCKADDR*)&from, fromlen);
            ZeroMemory(msg, sizeof(msg));
        }
        if(t == 1)break;
    }
    closesocket(socketS); //fecha o sockets
}

grupos add[20];

void client()
{
	int i = 0, k = 0, linhas = 0;
	char name[SIZE], ip_conversa[10], palavra[SIZE], msg[buffer];
	
	cls(3); // limpa a tela e o buffer.
	FILE *arq;
	arq = fopen(nome_arquivo_online, "r"); // le o arquivo que pega os contatos 

	if(arq == NULL) { // verificação
		printf("\nERROR 404 - NAO ENCONTRADO\n");
		cls(1);
		getchar();
		client();

	} else {
		while(fgets(palavra, SIZE, arq) != NULL){  //pegando os grupos
			linhas++;
			if (i == 0){
				strcpy(add[k].nome, palavra); //colocando dentro do struct o nome do grupo
				i++;

			} else if (i == 1){
				strcpy(add[k].ip, palavra); //colocando dentro do struct o nome do integrante
				i = 0; 
				k++;
			}
		}
		fclose(arq);
		linhas = linhas/2;
		printf("+Lista_Contatos\n");
		for(i = 0; i < linhas; i++) {
			printf("Nome: %s IP: %s\n", add[i].nome, add[i].ip);
		}
		cls(1);
		printf("Digite Com quem conversar: ");
		fgets(name, SIZE,stdin);
		cls(3);
		for(i = 0; i < linhas; i++) {
			
			if(strcmp(name, add[i].nome) == 0) {
				strcpy(ip_conversa, add[i].ip);

				SOCKET socketC; // criando o socket 

	    		WSADATA wsaData; // estrutura que contem informações sobre sockets no windows.
	     
	            WSAStartup(MAKEWORD(2, 2), &wsaData); // iniciando o winsock
				
				int x = 0; // variavel utilizada para manter o loop

	    		struct sockaddr_in serverInfo; // estrutura que contém os dados do servidor.
	    		
	    		int len = sizeof(serverInfo); // amarzena o tamanho de serveInfo
	    		serverInfo.sin_family = AF_INET; // recebendo formato IPv4
	    		serverInfo.sin_port = htons(5000); // porta utilizada
	    		serverInfo.sin_addr.s_addr = inet_addr(ip_conversa); // onde fica o ip utilizado

	    		socketC = socket(AF_INET,SOCK_DGRAM,0); // iniciando o socket.
	   		
	    		//loop para a conversa acontecer.

				while (x != 1) {
	        		ZeroMemory(msg, sizeof(msg)); //zerar o buffer.
	        		printf("Envie: ");
	        
	        		setbuf(stdin, NULL); // limpa o que foi digitado no teclado.
	        		fgets(msg, buffer, stdin); // enviando a mensagem.
	        
	        		if (strcmp(msg,"sair\n") == 0){
	            		x = 1;
	            	}
	        		if (sendto(socketC, msg, sizeof(msg), 0, (SOCKADDR*)&serverInfo, len) != SOCKET_ERROR) {
	            		if (recvfrom(socketC, msg, sizeof(msg), 0, (SOCKADDR*)&serverInfo, &len) != SOCKET_ERROR) {
	                		printf("Mensagem recebida: %s", msg);
	            		}
	        		}
	        		if(x == 1)break; // caso para no if de sair, essa condição aqui quebra o loop.
	    		}
	    		closesocket(socketC); // fecha o socket cliente.
			}
			else {
				printf("\nEsse nome nao esta na sua lista de contatos\n");
				cls(1);
				getchar();
			}
		}
	}
}

void enviar_grupo()
{
	char palavra[SIZE], name[30], ip_conversa[SIZE], msg[buffer];	
	int i = 0, linhas = 0, k = 0, x = 0;

	FILE *arq;
	arq = fopen(grupo_online, "r"); // le o arquivo onde está o grupo. 

	if(arq == NULL){ // verifica se o grupo está no arquivo.
		printf("\nGrupo(s) nao encontrado(s)\n");
		cls(1);
		getchar();
		cls(3);
		enviar_grupo();

	}else {
		
		while(fgets(palavra, SIZE, arq) != NULL){  //pegando os grupos
			linhas++;
			if (i == 0){
				strcpy(gp[k].grupo, palavra); //colocando dentro do struct o nome do grupo
				i++;

			} else if (i == 1){
				strcpy(gp[k].nome, palavra); //colocando dentro do struct o nome do integrante
				i++;

			} else if (i == 2){
				strcpy(gp[k].ip, palavra); //colocando dentro do struct o ip do integrante
				i = 0;
				k++;
			}
		}
		fclose(arq);
		linhas = (linhas/3);
		printf("                        Zap Raiz");
	    printf("\n");
		printf("+Contatos dos Grupos+\n\n");
		for(i = 0; i < linhas ; i++) {
			printf("Grupo: %s Nome: %s IP: %s\n", gp[i].grupo, gp[i].nome, gp[i].ip);
		}
		cls(1);
		printf("Informe o nome do Grupo para qual devo mandar mensagem: ");
		fgets(name, SIZE,stdin);

		for(i = 0; i < linhas; i++) {
			
			if(strcmp(name, gp[i].grupo)==0) {
				strcpy(ip_conversa, gp[i].ip);
				SOCKET socketC;

				//inicia o socket como cliente.

	    		WSADATA wsaData;
	   			WSAStartup(MAKEWORD(2, 2), &wsaData);

	    		struct sockaddr_in serverInfo;
	    		int len = sizeof(serverInfo);
	    		serverInfo.sin_family = AF_INET;
	    		serverInfo.sin_port = htons(5000);
	    		serverInfo.sin_addr.s_addr = inet_addr(ip_conversa);

	    		socketC = socket(AF_INET,SOCK_DGRAM,0);

				while (x != 1) {
	        		ZeroMemory(msg, sizeof(msg));
	        		printf("Envie: ");
	        
	        		cls(1);
	        		fgets(msg, 1024, stdin);
	        
	            	printf("\nMensagem enviada para o Server: ");
	            	
	        		if (strcmp(msg,"sair\n") == 0)x = 1;
	        		sendto(socketC, msg, sizeof(msg), 0, (SOCKADDR*)&serverInfo, len) != SOCKET_ERROR;	
	    		}
	    		closesocket(socketC);	
			} else {
				printf("\n Grupo nao encontrado \n");
				cls(1);
				getchar();
				break;
			}
		}
	}
}


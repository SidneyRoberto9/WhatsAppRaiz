#define SIZE 20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "menu.h"
#include "conta.h"
#include "contatos.h"
#include "grupo.h"
#include "ult.h"
#include "socket.h"

char Contas_tudo[60][SIZE] = {'\0'}, usuario_online[SIZE]; // registrar o nome do usuário online

void registro()
{
	char nome[SIZE], usuario[SIZE], senha[SIZE], palavra[SIZE], *pos;
	int i = 0, valor = 0;

	FILE *arquivo; // criando o file do arquivo

	cls(3);  //modo 3 = limpa o buffer e a tela
	printf("                        Zap Raiz");
    printf("\n");

    printf("Nome: ");
    scanf("%s", nome);

    cls(1); //modo 1 = limpa o buffer
    printf("Usuario: ");
    scanf("%s", usuario);

    cls(1);
    printf("Senha: ");
    scanf("%s", senha);

    if ((arquivo = fopen("Contas.txt","r")) == NULL ){ // lendo se o usário está registrado
        printf("Error");
    }else{
        while(fgets(palavra, SIZE, arquivo)){
            if ((pos = strchr(palavra, '\n')) != NULL)*pos = '\0';
            if((strcmp(nome, palavra)) == 0){
                printf("\n");
                printf("Nome ja registrada, Pressione qualquer teclar para tentar novamente...\n");
                cls(1);
                getchar();
                valor = 1;
                registro();
                break;

            } else {
            	if(i > 30)break;
            	valor = 0;		
            }
            i++;
        }
    }
    fclose(arquivo); // fecha o arquivo.
    if (valor == 1){ 
    	cls(1);

    }else if (valor == 0) {
    	if ((arquivo = fopen("Contas.txt","a")) == NULL ){
        	printf("Error");

    	}else{
        	fprintf(arquivo, "%s\n", nome);
			fprintf(arquivo, "%s\n", usuario);
        	fprintf(arquivo, "%s\n", senha);   
    }
    fclose(arquivo);  
    }    
}

int login()
{
	char usuario[SIZE], senha[SIZE], *pos, carlos[SIZE];
	int i = 0, valor = 0, ln = 0, k = 0, linha = 0, l = 0;

	FILE *arquivo;
    if ((arquivo = fopen("Contas.txt","r")) == NULL ){
        printf("Error");

    }else{
        while(fgets(carlos, SIZE, arquivo) != NULL){
            ln++; // pega a quantidade de linhas no arquivo
        }
    }
    fclose(arquivo);
    memset(carlos, 0, sizeof(carlos));
    if (ln <  1){ // verifica se não é uma estrutura vazia.
        printf("\nNenhuma conta registrada... \n");
        cls(1);
        getchar();

    } else {
        cls(3);

        printf("                        Zap Raiz");
        printf("\n");

        cls(1);
        printf("Usuario: ");
        scanf("%s", usuario);

        cls(1);
        printf("Senha: ");
        scanf("%s", senha);
     
        if ((arquivo = fopen("Contas.txt","r")) == NULL ){
            printf("Error");

        }else{
        	i = 0;
            while(fgets(Contas_tudo[i], SIZE, arquivo)){ // registrando tudo que está nas contas.txt e colocando dentro de um array bidimensional 
                if ((pos = strchr(Contas_tudo[i], '\n')) != NULL)*pos = '\0'; 
                i++;
            }
            for(k = 0; k < i; k =  k + 3){
                if(((strcmp(Contas_tudo[k+1], usuario)) == 0) && (strcmp(Contas_tudo[k+2], senha) == 0)){ // verificando se o usuário e a senha estão registrados.
                	strcpy(usuario_online, Contas_tudo[k]);
                    valor = 1;
                    break;
                } else {
                    valor = 0;           
                }
            }
            if (valor == 1){ 
                printf("\nLogado com Sucesso...\nPressione qualquer tecla para contiunuar..\n");
                cls(1);
                contato_arq(usuario_online);
                fclose(arquivo);  
                return 1;

            } else if (valor == 0){
                printf("\nUsuario ou Senha incorreta, tente novamente...\n");
                cls(1);
                getchar();
                fclose(arquivo);
                login();
            }   
        }
    }
}

void listar_contas()
{
	int i = 0, k = 0;
	FILE *arquivo;

	cls(3);
	printf("                        Zap Raiz");
    printf("\n");
    printf("Contas+");
    printf("\n");

	if ((arquivo = fopen("Contas.txt","r")) == NULL ){
        printf("Error");
    } else {
    	while(fgets(Contas_tudo[i], SIZE, arquivo) != NULL){
    		i++; // preenchendo o contas_tudo com todas as linhas de contas.
    	}
    	for(k = 0; k < i; k = k + 3){
			printf("Account Name: %s", Contas_tudo[k]); // apenas printa os nomes das contas.
		}
    }
    fclose(arquivo);
    printf("\nPressione Qualquer Tecla para Sair...");
	cls(1);
	getchar();
}

void exluir_conta()
{
	char nome[SIZE], palavra[SIZE], *pos;
	int i = 0, linha = 0, l = 1;
	FILE *arquivo; // arquivo para armazenar as contas
	FILE *arquivo2; // arquivo que server para criar um auxiliar na hora de exclusão de alguma conta.

	cls(3);
	printf("                        Zap Raiz");
    printf("\n");

    printf("Informe o Nome da Conta que deseja Excluir\n");
    printf("Nome: ");
    scanf("%s", nome);

	if ((arquivo = fopen("Contas.txt","r")) == NULL ){ // abrindo contas.
        printf("Error");

    } else {
    	while(fgets(Contas_tudo[i], SIZE, arquivo)){ // preenchendo um array bidimensional com tudo o que tem no contas.txt
            if ((pos = strchr(Contas_tudo[i], '\n')) != NULL)*pos = '\0';
            if((strcmp(Contas_tudo[i], nome)) == 0){
            	linha = i;
            }
            i++;
        }
    }
    
    if ((arquivo2 = fopen("Contasaida.txt","w")) == NULL ){ // abri o arquivo auxiliar.
        printf("Error");

    } else {
    	rewind(arquivo); // reposiciona (voltando para o inicio do arquivo).
    	for(i = 0; !feof(arquivo); i++){//tira tudo o que está no arquivo principal e coloca no auxiliar, menos o que o usuário decidiu excluir.
    		memset(palavra, '\0', SIZE);
    		fgets(palavra, SIZE, arquivo);

    		if (l == linha - 1){
    			fputc('\r', arquivo2);
    			l++;
    			continue;
    		}
    		if (l == linha){
    			fputc('\r', arquivo2);
    			l++;
    			continue;
    		}
    		if (l == linha + 1){
    			fputc('\r', arquivo2);
    			l++;
    			continue;
    		}
    		l++;
    		fputs(palavra, arquivo2);
    	}
    }
    fclose(arquivo);
    fclose(arquivo2);
    remove("Contas.txt"); // apaga o arquivo principal
    rename("Contasaida.txt", "Contas.txt");  // renomeia o arquivo auxiliar para o mesmo nome do principal.
}

void editar_conta()
{
	char nome1[SIZE], nome[SIZE], usuario[SIZE], senha[SIZE],*pos;
	int i = 0, valor = 0, k = 0, ln = 0;
	FILE *arquivo;
    FILE *arquivo2;

    cls(3);
	printf("                        Zap Raiz");
    printf("\n");
    printf("Editor de Contas\n");
    printf("Nome da Conta: ");
    scanf("%s", nome1);

	if ((arquivo = fopen("Contas.txt","r")) == NULL ){
        printf("Error");

    } else {
    	while(fgets(Contas_tudo[i], SIZE, arquivo) != NULL){
    		if ((pos = strchr(Contas_tudo[i], '\n')) != NULL)*pos = '\0';
    		if(strcmp(Contas_tudo[i],nome1) == 0){
    			k = i;
    			valor = 1;
    		}
    		i++;
    	}
    }
    
    if (valor == 1){
    	printf("\n Conta Selecionada \n");

    } else if(valor == 0){
    	printf("\nConta novamente Encontrada, Pressione qualquer tecla para tentar novamente...\n");
    	cls(1);
    	getchar();
    	cls(3);
    	editar_conta();
    }
    
    printf("\nInforme os Seguinte Dados\n"); //modificando os pontos dentro do array bidimensional que o usuário deseja editar
    cls(1);
    printf("Nome: ");
   	scanf("%s", nome);
   	strcpy(Contas_tudo[k], nome);
    cls(1);
    printf("Usuario: ");
    scanf("%s", usuario);
    strcpy(Contas_tudo[k + 1], usuario);
    cls(1);
    printf("Senha: ");
    scanf("%s", senha);
    strcpy(Contas_tudo[k + 2], senha);

    if ((arquivo2 = fopen("Contasaida.txt","w")) == NULL ){
        printf("Error");

    } else {
    	rewind(arquivo);
    	while(fgets(nome1, SIZE,arquivo) != NULL){
    		fprintf(arquivo2,"%s\n" , Contas_tudo[ln]);
    		ln++;
    	}
    }	
    fclose(arquivo);
    fclose(arquivo2);
    remove("Contas.txt"); // apaga o arquivo principal
    rename("Contasaida.txt", "Contas.txt"); // renomeia o arquivo auxiliar para o mesmo nome do principal. 
}
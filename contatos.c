#define SIZE 20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "conta.h"
#include "contatos.h"
#include "grupo.h"
#include "ult.h"
#include "socket.h"

typedef struct {
	char nome[SIZE];
	char ip[32];
}contact;

contact agenda[SIZE];

char nome_arquivo_online[50] = {'\0'};

void contato_arq(char* variavel)
{
	char nome_arq[50] = {'\0'}, *pos;
	FILE *arq;

	if ((pos = strchr(variavel, '\n')) != NULL)*pos = '\0';

    sprintf(nome_arq, "Contatos_%s.txt", variavel);
	strcpy(nome_arquivo_online, nome_arq);
    getchar();
	if ((arq = fopen(nome_arq,"a")) == NULL ){
        printf("Error");
    }else{	
        printf("lul");
    }    
}

void estrutura_contato()
{
	char palavra[SIZE] = {'\0'};
	int k = 0, c = 0;
	FILE *arquivo;

	arquivo = fopen(nome_arquivo_online, "r");

	if (arquivo == NULL){
		printf("error");
		cls(5);

	} else {
		while(fgets(palavra, SIZE, arquivo) != NULL){
			if(c == 0){
				strcpy(agenda[k].nome, palavra);
				c++;
				continue;
			} else if (c == 1){
				strcpy(agenda[k].ip, palavra);
				c = 0;
				k++;
				continue;
			}
		}
		fclose(arquivo);
	}
}

void contato_adicionar()
{
	char nome[SIZE], ip[SIZE];
	int i = 0, valor;
	FILE *arquivo;

	cls(3);
	printf("                        Zap Raiz");
    printf("\n");
    printf("Adicionando Contato+ \n");

   	printf("Nome: ");
   	fgets(nome, SIZE, stdin);
   	cls(1);
   	printf("Ip: ");
   	fgets(ip, SIZE, stdin);

   	while(i < SIZE){
   		if (strcmp(ip, agenda[i].ip) == 0){
   			valor = 1;
   			break;
   		} else {
   			valor = 0;
   		}
   		i++;
   	}
   	
   	if (valor == 1){
   		printf("\nIp Ja cadastrado, Pressione Qualquer tecla para tentar novamente...\n");
   		cls(1);
   		getchar();
   		contato_adicionar();

   	} else if (valor == 0){
		if ((arquivo = fopen(nome_arquivo_online,"a")) == NULL){
			printf("Error");
			contato_adicionar();

		} else {
			fprintf(arquivo, "%s", nome);
			fprintf(arquivo, "%s", ip);	

	   	}    
		fclose(arquivo);
	}
}

void contato_excluir()
{
	char ip[SIZE], palavra[SIZE], linhas[SIZE], *pos, saida[20] = {"Contasaida.txt"};
	int i = 0, linha = 0, l = 1, valor = 0;
	FILE *arquivo;
	FILE *arquivo2;

	cls(3);
	printf("                        Zap Raiz");
    printf("\n");
    printf("Informe o ip do Contato que deseja Excluir\n");
    printf("Ip: ");
    scanf("%s", ip);

	if ((arquivo = fopen(nome_arquivo_online,"r")) == NULL ){
        printf("Error");

    } else {
    	while(fgets(linhas, SIZE, arquivo)){
            if ((pos = strchr(linhas, '\n')) != NULL)*pos = '\0';
            if((strcmp(linhas,ip)) == 0){
            	linha = i;
                valor = 1;
                break;
            } else {
                valor = 0;
            }
            i++;
        }
    }
    if(valor == 0){
        printf("\nContato nao encontrado, tente novamente..\n");
        cls(1);
        getchar();
        cls(3);
        contato_excluir();

    } else {
        if ((arquivo2 = fopen(saida,"w")) == NULL ){
        printf("Error");

        } else {
            rewind(arquivo);
            for(i = 0; !feof(arquivo); i++){
                memset(palavra, '\0', SIZE);
                fgets(palavra, SIZE, arquivo);

                if (l == linha){
                    l++;
                    continue;
                }
                if (l == linha + 1){
                    l++;
                    continue;
                }
                l++;
                fputs(palavra, arquivo2);
            }
        }        
    }
    fclose(arquivo);
    fclose(arquivo2);

    if((arquivo = fopen(saida, "r")) == NULL){
        printf("error");

    } else {
        if ((arquivo2 = fopen(nome_arquivo_online,"w")) == NULL ){
        printf("Error");

        } else {
            rewind(arquivo);
            while(fgets(palavra, SIZE, arquivo)){  
                fputs(palavra, arquivo2);
            }
        }        
    }
    fclose(arquivo);
    fclose(arquivo2);
    remove(saida);
}

void contato_editar()
{
    char nome[SIZE], ip[SIZE], palavra[SIZE], linhas[SIZE], *pos, saida[20] = {"Contasaida.txt"};
    int i = 0, linha = 0, l = 1, valor = 0;
    FILE *arquivo;
    FILE *arquivo2;

    cls(3);
    printf("                        Zap Raiz");
    printf("\n");
    printf("Informe o ip do Contato que deseja Editar\n");
    printf("Ip: ");
    scanf("%s", ip);

    if ((arquivo = fopen(nome_arquivo_online,"r")) == NULL ){
        printf("Error");

    } else {
        while(fgets(linhas, SIZE, arquivo)){
            if ((pos = strchr(linhas, '\n')) != NULL)*pos = '\0';
            if((strcmp(linhas,ip)) == 0){
                linha = i;
                valor = 1;
                break;
            } else {
                valor = 0;
            }
            i++;
        }
    }
    if(valor == 0){
        printf("\nContato nao encontrado, tente novamente..\n");
        cls(1);
        getchar();
        cls(3);
        contato_editar();

    } else {
        printf("\nInforme os seguintes datos+\n");
        cls(1);
        printf("Nome: ");
        scanf("%s",nome);

        cls(1);
        printf("Ip: ");
        scanf("%s", ip);

        if ((arquivo2 = fopen(saida,"w")) == NULL ){
        printf("Error");

        } else {
            rewind(arquivo);
            for(i = 0; !feof(arquivo); i++){
                memset(palavra, '\0', SIZE);
                fgets(palavra, SIZE, arquivo);

                if (l == linha){
                    fprintf(arquivo2,"%s\n", nome);
                    l++;
                    continue;
                }
                if (l == linha + 1){
                    fprintf(arquivo2,"%s\n", ip);
                    l++;
                    continue;
                }
                l++;
                fputs(palavra, arquivo2);
            }
        }        
    }
    fclose(arquivo);
    fclose(arquivo2);

    if((arquivo = fopen(saida, "r")) == NULL){
        printf("error");

    } else {
        if ((arquivo2 = fopen(nome_arquivo_online,"w")) == NULL ){
        printf("Error");

        } else {
            rewind(arquivo);
            while(fgets(palavra, SIZE, arquivo)){  
                fputs(palavra, arquivo2);
            }
        }        
    }
    fclose(arquivo);
    fclose(arquivo2);
    remove(saida);
}

void listar_contatos()
{
	char palavra[SIZE];
	int k = 0, linhas = 0;
	FILE *arquivo;

	cls(3);
	printf("                        Zap Raiz");
    printf("\n");
    printf("%s+\n", nome_arquivo_online);

	arquivo = fopen(nome_arquivo_online, "r");

	if (arquivo == NULL){
		printf("error");
		cls(5);

	} else {
		while(fgets(palavra, SIZE, arquivo) != NULL){
			linhas++;
		}
		fclose(arquivo);
		for(k = 0; k < (linhas/2); k++){
			printf("Nome do Contato %d: %sIp do Contato %d: %s\n", k+1, agenda[k].nome, k+1, agenda[k].ip);
		}
	}
	printf("\nPressione Qualquer Tecla para Sair...");
	cls(1);
	getchar();
}

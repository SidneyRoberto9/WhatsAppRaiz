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

grupos gp[10];

char grupo_online[100] = {"\0"};

void verificar_grupo()
{
	char nome_arq[SIZE];

	sprintf(nome_arq,"grupos_%s.txt", usuario_online);
    strcpy(grupo_online, nome_arq);
}

void criar_grupo()
{
    char nome_integrante[SIZE], ip_par[32], nome_grupo[SIZE];
	int i = 0, quantidade = 0;
	FILE *arquivo;

    arquivo = fopen(grupo_online, "a");

    if(arquivo == NULL){
        printf("\nGrupo nao existe, Pressione Qualquer tecla para tentar novamente..\n");
        cls(1);
        getchar();
        criar_grupo();

    } else {
    	cls(3);
    	printf("                        Zap Raiz");
    	printf("\n");

		printf("Nome do grupo: ");
    	scanf("%s", nome_grupo);

    	printf("Quantos contatos deseja adicionar no grupo: ");
    	scanf("%d", &quantidade);

    	if (quantidade < 5){
    		printf("\nInforme os Dados dos Contatos que deseja adicionar no Grupo+\n");
    		for(i = 0; i < quantidade; i++) {
				printf("Nome: ");
	    		scanf("%s", nome_integrante);

	    		printf("Ip: ");
	    		scanf("%s", ip_par);

				fprintf(arquivo, "%s\n", nome_grupo);
				fprintf(arquivo, "%s\n", nome_integrante);
				fprintf(arquivo, "%s\n", ip_par);
				printf("\n");
			}
			printf("\nGrupo criado.\n");
	    	cls(5);
	    	cls(2);

    	} else {
    		printf("\nQuantidade de Contatos Acima do limite, tente novamente...\n");
    		cls(1);
    		getchar();
    		criar_grupo();
    	}
	}
    fclose(arquivo);
}

void editar_grupo() 
{
	cls(3);
	char nome[SIZE], palavra[SIZE];
	int i = 0, k = 0, linhas = 0, j, n, cont = 0;
	FILE *arquivo;

	arquivo = fopen(grupo_online, "r"); 
	
	if(arquivo == NULL) {
		printf("\nGrupos nao encontrado\n");
		cls(1);
		getchar();
		editar_grupo();

	} else {
		while(fgets(palavra, SIZE, arquivo) != NULL){  //pegando os grupos
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
	}
	fclose(arquivo);
	linhas = linhas/3;

	printf("                        Zap Raiz");
    printf("\n");

	if (linhas > 0){ //evita listar arquivo vazio.
		printf("+Contatos dos Grupos+\n\n");
		for(i = 0; i < linhas; i++) {
			printf("Grupo: %sNome: %sIP: %s\n", gp[i].grupo, gp[i].nome, gp[i].ip);
		}
	
		printf("Informe o nome do Grupo para editar:  ");
		fgets(nome, SIZE, stdin);
		printf("\n");
		for(i = 0; i < linhas; i++) {
			if(strcmp(gp[i].grupo, nome) == 0) {
				if (cont == 0){
					cont = 1;
					printf("Novo Nome Grupo: ");
					scanf("%s", gp[i].grupo);
						
					printf("Quantidade de Contatos no grupo(Max 5): ");
					scanf("%d", &n);
						
					if (n > 5){
						printf("Numero de Contatos Execiddo, reinicalizando sistema de edicao...\n");
						printf("DIgite qualquer tecla para continuar...\n");
						cls(1);
						getchar();
						editar_grupo();
					}else{
						arquivo = fopen(grupo_online, "w"); // permite escrever no arquivo.
							
						if(arquivo == NULL){
							printf("DIgite qualquer tecla para continuar...\n");
							cls(1);
							getchar();
							editar_grupo();

						} else {
							for(j = 0; j < n; j++) {	
								printf("Nome %d: ", j+1);
								cls(1);
								scanf("%s", gp[j].nome);
									
								printf("Ip %d: ", j+1);
								cls(1);
								scanf("%s", gp[j].ip);
									
								fprintf(arquivo, "%s\n", gp[i].grupo);
								fprintf(arquivo, "%s\n", gp[j].nome);
								fprintf(arquivo, "%s\n", gp[j].ip);
							}
						}
					}
				} 
			}
		}
		if (cont == 0) {
			printf("\nGrupo não encontrado ou não está na sua lista");
			cls(5);
		} else if (cont == 1){
			printf("\nGrupo alterado!"); 
			cls(5);
		}
		fclose(arquivo);
	} else {
		printf("\nA lista está vazia, adicione alguém\n");
		cls(5);
	}
}


void remover_grupo()
{
	cls(3);
	char grupo[SIZE], aux[SIZE], caractere[150][SIZE], *ptr = NULL;
	int i = 0, j = 0, valor = 0;
	
	FILE *dados;
    dados = fopen(grupo_online,"r");

	if(dados == NULL){
		printf("Erro ao abrir o arquivo!\n");
		printf("Pressione qualquer tecla para tentar novamente...\n");
		cls(1);
		getchar();
		remover_grupo();

	} else {
		printf("                        Zap Raiz");
    	printf("\n");
		printf("Informe o grupo que deseja remover: ");
		scanf("%s", grupo);

					
		while(fgets(aux, SIZE, dados) != NULL){ // Lendo o arquivo até o final
			strcpy(caractere[i],aux); // copiando os dados da string caractere para uma string auxiliar.
			i++; // contador para verificar o tamanho do arquivo.		 	
		}
		fclose(dados); 
		dados = fopen(grupo_online, "w");  

		if(dados == NULL){
			printf("Erro ao abrir o arquivo!\n");
			printf("Pressione qualquer tecla para tentar novamente...\n");
			cls(1);
			getchar();
			remover_grupo();

		} else {
			for(j = 0; j < i; j++){  // percorrendo a string.
				ptr = strstr(caractere[j],grupo); // Verificando se existem caracteres identicos no arquivo.		
				if(ptr != NULL){  // Se for ptr != NULL significa que encontrou a palavra.			 
					caractere[j][0] = '\0'; 
					caractere[j+1][0] = '\0'; 
					caractere[j+2][0] = '\0';  // Substituindo a palavra por '\0', a linha que continha a palavra irá ficar em branco.
					valor = 1; // Usando para saber se achou a palavra ou não.
				}
			}
			if(valor == 0){  // A negação de acho significa que ele não encontrou a palavra no arquivo.
				printf("\nnao encontrei o nome do contato no arquivo... \n");			
				printf("Pressione qualquer tecla para tentar novamente...\n");
				cls(1);
				getchar();
				remover_grupo();
			}
			for(j = 0; j < i; j++){  // Printando a palavra removida por '\0'.
				fprintf(dados,"%s",caractere[j]);
			}
			fclose(dados);
		}
	}	
}
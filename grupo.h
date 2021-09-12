#ifndef __GRUPO_H__
#define __GRUPO_H__

void criar_grupo();

void editar_grupo();

void remover_grupo();

void verificar_grupo();

extern char grupo_online[100];

typedef struct { // criando uma struct global para representar o grupo 
	char grupo[20];
	char nome[20];
	char ip[20];
}grupos;

extern grupos gp[10]; // variavel global do grupo.

#endif
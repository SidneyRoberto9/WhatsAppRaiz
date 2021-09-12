#ifndef __MENU_H__
#define __MENU_H__

int menu1(int esc);

int menu2(int esc);

int menu3_server(int esc);

int menu3_client(int esc);

int definir_modo(int esc);

int menu_conta(int esc);

int menu_contato(int esc);

int menu_grupo(int esc);

int menu_envio(int esc);

void start();

typedef struct
{
    char nome[20];
    char usuario[20];
    char senha[20];

} Conta;

extern Conta reg[20];

#endif
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "conta.h"
#include "contatos.h"
#include "grupo.h"
#include "ult.h"
#include "socket.h"

Conta reg[20];

int menu1(int esc)
{
    printf("**********************************************\n");
    printf("Seja Bem-vida ao ZapRaiz, o melhor programa\nde troca de mensagens do planeta!\n");
    printf("**********************************************\n");
    printf("\n");
    printf("1 - Iniciar\n");
    printf("2 - Sair\n");
    printf("\n");
    printf("Por Favor Informe uma alternativa \n");
    printf("--> ");

    scanf("%d", &esc);
    return esc;
}

int menu2(int esc)
{
    printf("                        Zap Raiz");
    printf("\n");
    printf("1 - Registrar\n");
    printf("2 - Login\n");
    printf("3 - Sair\n");
    printf("\n");
    printf("Por Favor Informe uma alternativa \n");
    printf("--> ");

    scanf("%d", &esc);
    return esc;
}

int definir_modo(int esc)
{
    printf("                        Zap Raiz");
    printf("\n");
    printf("Selecione o Modo Que o Programa ira executar\n");
    printf("1 - Cliente\n");
    printf("2 - Servidor\n");
    printf("3 - Sair\n");
    printf("\n");
    printf("Por Favor Informe uma alternativa \n");
    printf("--> ");

    scanf("%d", &esc);
    return esc;
}

int menu3_client(int esc)
{
    printf("                        Zap Raiz");
    printf("\n");
    printf("      Menu Cliente\n");
    printf("1 - Gerenciar Contas\n");
    printf("2 - Gerenciar contatos\n");
    printf("3 - Gerenciar grupos\n");
    printf("4 - Iniciar conversa\n");
    printf("5 - Sair\n");
    printf("\n");
    printf("Por Favor Informe uma alternativa \n");
    printf("--> ");

    scanf("%d", &esc);
    return esc;
}

int menu3_server(int esc)
{
    printf("                        Zap Raiz");
    printf("\n");
    printf("      Menu Servidor\n");
    printf("1 - Gerenciar Contas\n");
    printf("2 - Gerenciar contatos\n");
    printf("3 - Gerenciar grupos\n");
    printf("4 - Participar de uma conversa\n");
    printf("5 - Sair\n");
    printf("\n");
    printf("Por Favor Informe uma alternativa \n");
    printf("--> ");

    scanf("%d", &esc);
    return esc;
}

int menu_conta(int esc)
{
    printf("                        Zap Raiz");
    printf("\n");
    printf("1 - Criar Conta\n");
    printf("2 - Editar Conta\n");
    printf("3 - Excluir Conta\n");
    printf("4 - listar Contas\n");
    printf("5 - Voltar\n");
    printf("\n");
    printf("Por Favor Informe uma alternativa \n");
    printf("--> ");

    scanf("%d", &esc);
    return esc;
}

int menu_contato(int esc)
{
    printf("                        Zap Raiz");
    printf("\n");
    printf("1 - Adicionar contato\n");
    printf("2 - Editar contato\n");
    printf("3 - Excluir contato\n");
    printf("4 - Listar Contatos\n");
    printf("5 - Voltar\n");
    printf("\n");
    printf("Por Favor Informe uma alternativa \n");
    printf("--> ");

    scanf("%d", &esc);
    return esc;
}

int menu_grupo(int esc)
{
    printf("                        Zap Raiz");
    printf("\n");
    printf("1 - Criar Grupo\n");
    printf("2 - Editar Grupo\n");
    printf("3 - Excluir Grupo\n");
    printf("4 - Voltar\n");
    printf("\n");
    printf("Por Favor Informe uma alternativa \n");
    printf("--> ");

    scanf("%d", &esc);
    return esc;
}

int menu_envio(int esc)
{
	printf("                        Zap Raiz");
    printf("\n");
    printf("1 - Enviar Mensagem Privada\n");
    printf("2 - Enviar Mensagem em Grupo\n");
    printf("3 - voltar\n");
    printf("\n");
    printf("Por Favor Informe uma alternativa \n");
    printf("--> ");

    scanf("%d", &esc);
    return esc;
}

void start()
{   
    int op, result = 0;
    system("color 70");
    /* Abrindo o Primeiro menu
        1 - Iniciar
        2 - Sair
    */
    op = menu1(op);

    if (op == 1){                             
        printf("\n");
    }else if (op == 2)cls(4);
    /*Fim menu1*/

    /*Abrindo o Segundo menu
        1 - Register
        2 - Login
        3 - Sair
    */
    do{
        cls(3);
        op = menu2(op);
    
        if (op == 1){
            registro();

        } else if (op == 2){
            result = login();
            break;

        } else if (op == 3)cls(4);
    }while(op != 3);
    /*Fim menu2*/

    /*Abrindo o Terceiro menu
        1 - Gerenciar Contas
        2 - Gerenciars Contatos
        3 - Gerenciar grupos
        4 - Iniciar Conversa/participar da conversa
        5 - Sair
    */
    do{
        cls(3);

        op = definir_modo(op);
            /*Abrindo a moneu difinindo se é cliente  ou servidor
              1 - cliente
              2 - servidor
              3 - voltar
                */
        if (op == 1){
            do{
                cls(3);
                op = menu3_client(op);

                if (op == 1){

                /*Abrindo o Menu das Contas
                    1 - Criar Conta
                    2 - Editar Conta
                    3 - Excluir Conta
                    4 - Listar Contas
                    5 - Voltar
                */
                do{
                    cls(3);
                    op = menu_conta(op);

                    if ( op == 1){
                        registro();

                    } else if (op == 2){
                            editar_conta();

                    } else if (op == 3){
                        exluir_conta();

                    } else if (op == 4){
                        listar_contas();

                    } else if (op == 5)break;
                }while(op != 5);
                /*Fim do Menu das Contas*/
                op = 0;
                } else if (op == 2){

                    /*Abrindo o Menu dos Contatos
                        1 - Adicionar Contato
                        2 - Editar Contato
                        3 - Exclir Contato
                        4 - Listar Contato
                        5 - voltar
                    */
                    do{
                        estrutura_contato();
                        cls(3);
                        op = menu_contato(op);

                        if ( op == 1){
                            contato_adicionar();

                        } else if (op == 2){
                            contato_editar();

                        } else if (op == 3){
                            contato_excluir();

                        } else if (op == 4){
                            listar_contatos();

                        }else if (op == 5)break;
                    }while(op != 5);
                    /*Fim Menu dos Contatos*/
                    op = 0;

                } else if (op == 3){
                    /*Abrindo o Menu dos grupos
                        1 - Criar Grupo
                        2 - Editar Grupo
                        3 - Exclir Grupo
                        4 - Voltar
                    */

                    do{
                        verificar_grupo();
                        cls(3);
                        op = menu_grupo(op);

                        if (op == 1){
                            criar_grupo();

                        } else if (op == 2){
                            editar_grupo();

                        } else if (op == 3){
                            remover_grupo();

                        } else if (op == 4)break;
                    }while(op != 4);
                    /*Fim Menu dos Contatos*/
                    op = 0;
                } else if (op == 4){
                    enviar();

                } else if (op == 5)cls(4);
            }while(op != 5);
            op = 0;

        } else if (op == 2){
            do{
                cls(3);
                op = menu3_server(op);

                if (op == 1){
                /*Abrindo o Menu das Contas
                    1 - Criar Conta
                    2 - Editar Conta
                    3 - Excluir Conta
                    4 - Listar Contas
                    5 - Voltar
                */
                do{
                    cls(3);
                    op = menu_conta(op);

                    if ( op == 1){
                        registro();

                    } else if (op == 2){
                            editar_conta();

                    } else if (op == 3){
                        exluir_conta();

                    } else if (op == 4){
                        listar_contas();

                    } else if (op == 5)break;
                }while(op != 5);
                /*Fim do Menu das Contas*/
                op = 0;
                } else if (op == 2){
                    /*Abrindo o Menu dos Contatos
                        1 - Adicionar Contato
                        2 - Editar Contato
                        3 - Exclir Contato
                        4 - Listar Contato
                        5 - voltar
                    */
                    do{
                        estrutura_contato();
                        cls(3);
                        op = menu_contato(op);

                        if ( op == 1){
                            contato_adicionar();

                        } else if (op == 2){
                            contato_editar();

                        } else if (op == 3){
                            contato_excluir();

                        } else if (op == 4){
                            listar_contatos();

                        }else if (op == 5)break;
                    }while(op != 5);
                    /*Fim Menu dos Contatos*/
                    op = 0;

                } else if (op == 3){
                    /*Abrindo o Menu dos grupos
                        1 - Criar Grupo
                        2 - Editar Grupo
                        3 - Exclir Grupo
                        4 - Voltar
                    */
                    do{
                        cls(3);
                        verificar_grupo();
                        op = menu_grupo(op);

                        if (op == 1){
                            criar_grupo();

                        } else if (op == 2){
                            editar_grupo();

                        } else if (op == 3){
                            remover_grupo();

                        } else if (op == 4)break;
                    }while(op != 4);
                    /*Fim Menu dos Contatos*/
                    op = 0;
                } else if (op == 4){
                    servidor();

                } else if (op == 5)cls(4);
            }while(op != 5);
            op = 0;

        } else if (op == 3)break;
    }while(op != 3);

}

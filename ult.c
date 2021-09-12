#include <stdio.h>
#include <stdlib.h>
#include "ult.h"

void cls(int number)
{
	 /*
	 cls: modo 1 = limpa o buffer
          modo 2 = limpa a tela
          modo 3 = limpa o buffer e a tela
          modo 4 = fechar o tudo
          modo 5 = pausa o systema
    */
	if(number == 1){
        setbuf(stdin, NULL);

    } else if (number == 2) {
        system("cls");

    } else if (number == 3){
        setbuf(stdin, NULL);
        system("cls");

    } else if (number == 4){
        exit(1);
        system("exit");

    } else if (number == 5){
        system("pause");

    }
}
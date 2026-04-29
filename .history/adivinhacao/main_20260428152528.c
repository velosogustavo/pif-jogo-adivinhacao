#include <stdio.h>
#include "game.h"

int main(void)
{
    rng_init();
    int op;
    do
    {
        printf("Bem-vindo ao jogo de adivinhacao!\n");
        printf("1. Jogar\n");
        printf("2. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &op) != 1)
        {
            printf("Entrada invalida. Por favor, digite um numero.\n");
            while (getchar() != '\n')
                ; // Limpa o buffer de entrada
            continue;
        }

        switch (op)
        {
        case 1:
            Session s = game_new_session();
            printf("DEBUG — número secreto: %d\n", s.secret);
            break;
        case 2:
            printf("Obrigado por jogar! Ate a proxima.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op != 2);
    return 0;
}
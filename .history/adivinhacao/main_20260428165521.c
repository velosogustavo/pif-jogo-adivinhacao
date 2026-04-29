#include <stdio.h>
#include "game.h"

int main(void) {
    rng_init();
    int op = 0;

    do {
        printf("\n--- MENU PIF 2026.1 ---\n");
        printf("1. Jogar nova partida\n");
        printf("2. Analisar historico\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        fflush(stdout);

        if (scanf("%d", &op) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (op) {
            case 1: {
                Session s = game_new_session();
                hi(s);
                break;
            }
            case 2:
                io_display_history();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (op != 0);

    return 0;
}
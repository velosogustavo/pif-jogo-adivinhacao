#include <stdio.h>
#include "game.h"

int main(void) {
    rng_init(); // RF01
    int op = 0;

    do {
        printf("\n--- MENU PIF 2026.1 ---\n");
        printf("1. Jogar nova partida\n");
        printf("2. Analisar historico\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        if (scanf("%d", &op) != 1) {
            while (getchar() != '\n'); // Limpa buffer (Tratamento de erro)
            continue;
        }

        switch (op) {
            case 1: {
                Session s = game_new_session(); // Deve conter o loop de 1 a 100 (RF02)
                io_save_session(s);      // Salva em arquivo texto (RF03)
                break;
            }
            case 2:
                io_display_history();    // Parsing CSV e exibicao (RF04)
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
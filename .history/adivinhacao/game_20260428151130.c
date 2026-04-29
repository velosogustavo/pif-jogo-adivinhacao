#include <stdlib.h>
#include <time.h>
#include "game.h"

void rng_init(void) {
    srand((unsigned int)time(NULL));
}

int rng_generate(int min, int max) {
    return rand() % (max - min + 1) + min;
}

Session game_new_session(void) {
    Session s = { 0 };
    s.secret = rng_generate(1, 100);

    int guess = 0;
    printf("\nNovo Jogo! Tente adivinhar o numero entre 1 e 100.\n");

    while(guess != s.secret && s.total_guesses < MAX_GUESSES) {
        printf("Digite seu palpite: ");
        if(scanf("%d", &guess) != 1) {
            printf("Entrada invalida. Por favor, digite um numero.\n");
            while(getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }
        
        if(guess < 1 || guess > 100) {
            printf("Palpite fora do intervalo. Tente novamente.\n");
            continue;
        }

        s.guesses_list[s.total_guesses++] = guess;

        if (guess < s.secret) {
            printf("Muito baixo! Tente novamente.\n");
            s.bias_low = guess + 1;
        } else if (guess > s.secret) {
            printf("Muito alto! Tente novamente.\n");
            s.bias_high = guess - 1;
        } else {
            printf("Parabéns! Você adivinhou o número!\n");
        }

        s.guesses_list[s.total_guesses++] = guess;
    }
    return s;
}
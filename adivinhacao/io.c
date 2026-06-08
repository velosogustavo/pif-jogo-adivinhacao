#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"
#include "stats.h"

#define MAX_SESSIONS 500

void history_save(Session s) {
    FILE *f = fopen("historico.txt", "a");
    if (!f) return;

    fprintf(f, "%s;%d;%d;%d;%d;",
            s.timestamp, s.secret, s.total_attempts, s.bias_low, s.bias_high);

    for (int i = 0; i < s.total_attempts; i++)
        fprintf(f, "%d%s", s.guesses_list[i], (i == s.total_attempts - 1) ? "" : ",");

    fprintf(f, "\n");
    fclose(f);
}

void history_load_and_print(void) {
    FILE *f = fopen("historico.txt", "r");
    if (!f) {
        printf("Nenhum historico encontrado.\n");
        return;
    }

    int tentativas[MAX_SESSIONS];
    int total_partidas = 0;
    char line[1024];

    printf("\n--- RELATORIO ANALITICO ---\n");
    while (fgets(line, sizeof(line), f) && total_partidas < MAX_SESSIONS) {
        strtok(line, ";");
        strtok(NULL, ";");
        char *token = strtok(NULL, ";");

        if (token) {
            int t = atoi(token);
            tentativas[total_partidas++] = t;
            printf("Partida %3d: %2d tentativas | %s\n",
                   total_partidas, t, obter_heuristica(t));
        }
    }
    fclose(f);

    if (total_partidas == 0) {
        printf("Historico vazio.\n");
        return;
    }

    int   soma   = soma_recursiva(tentativas, total_partidas);
    float media  = (float)soma / total_partidas;
    int   melhor = min_recursivo(tentativas, total_partidas);
    int   pior   = max_recursivo(tentativas, total_partidas);
    float dp     = desvio_padrao(tentativas, total_partidas);

    printf("\n--- ESTATISTICAS AGREGADAS (%d partidas) ---\n", total_partidas);
    printf("Media de palpites : %.2f\n", media);
    printf("Desvio padrao     : %.2f\n", dp);
    printf("Melhor partida    : %d tentativas\n", melhor);
    printf("Pior partida      : %d tentativas\n", pior);
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"

void history_save(Session s) {
    FILE *f = fopen("historico.txt", "a");
    if (!f) return;

    // Salva seguindo o formato da Fonte 67 e 136
    fprintf(f, "%s;%d;%d;%d;%d;", s.timestamp, s.secret, s.total_attempts, s.bias_low, s.bias_high);
    
    for (int i = 0; i < s.total_attempts; i++) {
        fprintf(f, "%d%s", s.guesses_list[i], (i == s.total_attempts - 1) ? "" : ",");
    }
    fprintf(f, "\n");
    fclose(f);
}

void history_load_and_print(void) {
    FILE *f = fopen("historico.txt", "r");
    if (!f) return;

    int tentativas[100]; // Array para guardar os dados
    int total_partidas = 0;
    char line[1024];

    printf("\n--- RELATORIO ANALITICO ---\n");
    while (fgets(line, sizeof(line), f) && total_partidas < 100) {
        char *token = strtok(line, ";"); // Data
        strtok(NULL, ";"); // Pula segredo
        token = strtok(NULL, ";"); // Pega tentativas
        
        if (token) {
            int t = atoi(token);
            tentativas[total_partidas++] = t;
            printf("Partida %d: %d tentativas | %s\n", total_partidas, t, obter_heuristica(t));
        }
    }
    fclose(f);

    if (total_partidas > 0) {
        int soma = soma_recursiva(tentativas, total_partidas);
        float media = (float)soma / total_partidas;
        int melhor = min_recursivo(tentativas, total_partidas);
        int pior = max_recursivo(tentativas, total_partidas);

        printf("\n--- ESTATISTICAS AGREGADAS ---\n");
        printf("Media de palpites: %.2f\n", media);
        printf("Melhor partida: %d\n", melhor);
        printf("Pior partida: %d\n", pior);
    }
}
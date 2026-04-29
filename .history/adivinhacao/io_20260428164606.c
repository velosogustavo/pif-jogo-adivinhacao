#include <stdio.h>
#include <string.h>
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
    if (!f) {
        printf("Nenhum historico encontrado.\n"); // Tratamento de erro (Fonte 104)
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), f)) { // Uso de fgets (Fonte 25)
        // Exemplo simples de parsing com strtok
        char *token = strtok(line, ";");
        if (token) printf("Data: %s | ", token); // Timestamp
        
        token = strtok(NULL, ";"); // Pula Alvo
        token = strtok(NULL, ";"); // Tentativas
        if (token) printf("Tentativas: %s\n", token);
    }
    fclose(f);
}
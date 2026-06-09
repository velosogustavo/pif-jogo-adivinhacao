#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

/*
 * Gera NUM_SESSIONS sessoes simuladas em historico.txt.
 * Estrategia: busca binaria pura com 20% de chance de palpite aleatorio,
 * produzindo uma distribuicao realista de tentativas (3 a 15).
 * Semente fixa (42) para reproducibilidade.
 */
#define NUM_SESSIONS 105

int main(void) {
    srand(42);

    FILE *f = fopen("historico.txt", "w");
    if (!f) {
        fprintf(stderr, "Erro: nao foi possivel criar historico.txt\n");
        return 1;
    }

    /* Base: 2026-01-10 08:00:00 — sessoes de 5 em 5 minutos */
    struct tm base_tm = {0};
    base_tm.tm_year = 126;
    base_tm.tm_mon  = 0;
    base_tm.tm_mday = 10;
    base_tm.tm_hour = 8;
    time_t base = mktime(&base_tm);

    for (int i = 0; i < NUM_SESSIONS; i++) {
        Session s = {0};
        s.secret = (rand() % 100) + 1;

        time_t t = base + (time_t)i * 300;
        struct tm *ti = localtime(&t);
        sprintf(s.timestamp, "%04d-%02d-%02d %02d:%02d:%02d",
                ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday,
                ti->tm_hour, ti->tm_min, ti->tm_sec);

        int lo = 1, hi = 100, guess = 0;
        while (guess != s.secret && s.total_attempts < MAX_GUESSES) {
            if (rand() % 5 == 0)
                guess = lo + rand() % (hi - lo + 1);
            else
                guess = (lo + hi) / 2;

            s.guesses_list[s.total_attempts++] = guess;
            if      (guess < s.secret) { s.bias_low++;  lo = guess + 1; }
            else if (guess > s.secret) { s.bias_high++; hi = guess - 1; }
        }

        fprintf(f, "%s;%d;%d;%d;%d;",
                s.timestamp, s.secret, s.total_attempts, s.bias_low, s.bias_high);
        for (int j = 0; j < s.total_attempts; j++)
            fprintf(f, "%d%s", s.guesses_list[j], (j == s.total_attempts - 1) ? "" : ",");
        fprintf(f, "\n");
    }

    fclose(f);
    printf("%d sessoes de teste geradas em historico.txt\n", NUM_SESSIONS);
    return 0;
}

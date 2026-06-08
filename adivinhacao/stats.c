#include <math.h>
#include "stats.h"

int soma_recursiva(int v[], int n) {
    if (n <= 0) return 0;
    return v[n - 1] + soma_recursiva(v, n - 1);
}

int min_recursivo(int v[], int n) {
    if (n == 1) return v[0];
    int m = min_recursivo(v, n - 1);
    return (v[n - 1] < m) ? v[n - 1] : m;
}

int max_recursivo(int v[], int n) {
    if (n == 1) return v[0];
    int m = max_recursivo(v, n - 1);
    return (v[n - 1] > m) ? v[n - 1] : m;
}

long soma_quadrados_recursiva(int v[], int n) {
    if (n <= 0) return 0;
    return (long)v[n - 1] * v[n - 1] + soma_quadrados_recursiva(v, n - 1);
}

/* Desvio padrao usando a identidade Var = E[X^2] - (E[X])^2 */
float desvio_padrao(int v[], int n) {
    if (n <= 1) return 0.0f;
    float media    = (float)soma_recursiva(v, n) / n;
    long  sq       = soma_quadrados_recursiva(v, n);
    float variancia = (float)sq / n - media * media;
    return sqrtf(variancia < 0.0f ? 0.0f : variancia);
}

const char* obter_heuristica(int tentativas) {
    if (tentativas <= 4) return "Excelente! Voce usou uma otima estrategia de busca.";
    if (tentativas <= 7) return "Bom trabalho! Tente reduzir o intervalo mais rapidamente.";
    return "Dica: Use a busca binaria (sempre chute no meio do intervalo).";
}

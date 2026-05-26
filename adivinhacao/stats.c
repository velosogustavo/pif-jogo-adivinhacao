#include "game.h"

// Soma recursiva das tentativas
int soma_recursiva(int v[], int n) {
    if (n <= 0) {
        return 0;
    }
    return v[n - 1] + soma_recursiva(v, n - 1);
}

// Mínimo recursivo (Melhor partida)
int min_recursivo(int v[], int n) {
    if (n == 1) {
        return v[0];
    }
    int m = min_recursivo(v, n - 1);
    return (v[n - 1] < m) ? v[n - 1] : m;
}

// Máximo recursivo (Pior partida)
int max_recursivo(int v[], int n) {
    if (n == 1) {
        return v[0];
    }
    int m = max_recursivo(v, n - 1);
    return (v[n - 1] > m) ? v[n - 1] : m;
}

// Soma dos quadrados (Desvio Padrão)
long soma_quadrados_recursiva(int v[], int n) {
    if (n <= 0) return 0;
    return (v[n - 1] * v[n - 1]) + soma_quadrados_recursiva(v, n - 1);
}

const char* obter_heuristica(int tentativas) {
    if (tentativas <= 4) {
        return "Excelente! Voce usou uma otima estrategia de busca.";
    } else if (tentativas <= 7) {
        return "Bom trabalho! Tente reduzir o intervalo mais rapidamente na proxima.";
    } else {
        return "Dica: Use a busca binaria (sempre chute no meio do intervalo).";
    }
}
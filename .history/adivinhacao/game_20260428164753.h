#ifndef GAME_H
#define GAME_H

#define MAX_GUESSES 100

typedef struct {
    char timestamp[20];
    int secret;
    int total_attempts;
    int bias_low;
    int bias_high;
    int guesses_list[MAX_GUESSES];
} Session;

void    rng_init(void);
int     rng_generate(int min, int max);
Session (void); // Realiza o loop de palpites
void    history_save(Session s);
void    history_load_and_print(void); // Exemplo de parsing/carregamento

#endif
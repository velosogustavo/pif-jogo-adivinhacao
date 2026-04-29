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
    s.secret = rng_generate(min, max);
    return s;
}
#include <stdio.h>
#include "game.h"

int main(void) {
    rng_init();
    int op;
    do {}
    Session s = game_new_session(1, 100);
    printf("DEBUG — número secreto: %d\n", s.secret);
    return 0;
}
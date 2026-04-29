#define MAX_GUESSES 100

typedef struct {
    int secret;       
    int guesses_list[MAX_GUESSES];      
    int bias_low;     
    int bias_high;
    int total    
} Session;

void    rng_init(void);
int     rng_generate(int min, int max);
Session game_new_session(int min, int max);
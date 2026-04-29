#define MAX_GUESSES 100

typedef struct {
    int secret;       
    int guesses_list;      
    int bias_low;     
    int bias_high;    
} Session;

void    rng_init(void);
int     rng_generate(int min, int max);
Session game_new_session(int min, int max);
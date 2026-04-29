#

typedef struct {
    int secret;       
    int guesses;      
    int bias_low;     
    int bias_high;    
} Session;

void    rng_init(void);
int     rng_generate(int min, int max);
Session game_new_session(int min, int max);
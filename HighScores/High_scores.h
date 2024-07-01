#ifndef HIGH_SCORES_H
#define HIGH_SCORES_H
    
    typedef struct{
    char * name [10];
    char * points [10];
    }BestPlayers_t;

    BestPlayers_t reading_top (void);

#endif

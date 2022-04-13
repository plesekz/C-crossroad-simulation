#ifndef __CONFIG
#define __CONFIG

#define CONFIG struct configuration

struct configuration {
    /* the probability with which the car arrives on the left side */
    int trARateL;
    /* the probability with which the car arrives on the right side */
    int trARateR;
    /* the number of durrations for which the light is green on the left side */
    int trLPerL;
    /* the number of durrations for which the light is green on the right side */
    int trLPerR;
};

#endif
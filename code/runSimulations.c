#include "runSimulations.h"

/* main */

int main(int argc, char* argv[]){
    /* declaring variables */
    CONFIG c;
    RESULTS r[SIMULATIONS];
    RESULTS rFinal;
    int i;

    /* code */

    /* Get Config from arguments */

    if(argc != 5){
        fprintf(stderr, "Incorrect number of arguments specified.\nProgram accepts 4 arguments in the following form: (int:trafic arrival rate on the left) (int:traffic arrival rate on the right) (int:traffic light period on the left) (int:traffic light period on the right)\n");
        exit(1);
    }

    errno=0;

    c.trARateL = strtol(argv[1], NULL, 10);
    if (errno!=0){
        fprintf(stderr,"An error n %i has occured during parsing of the traffic arrival rate on the left. Consult strtol documentation.", errno);
        exit(1);
    }

    c.trARateR = strtol(argv[2], NULL, 10);
    if (errno!=0){
        fprintf(stderr, "An error n %i has occured during parsing of the traffic arrival rate on the right. Consult strtol documentation.", errno);
        exit(1);
    }

    c.trLPerL = strtol(argv[3], NULL, 10);
    if (errno!=0){
        fprintf(stderr, "An error n %i has occured during parsing of the traffic light period on the left. Consult strtol documentation.", errno);
        exit(1);
    }

    c.trLPerR = strtol(argv[4], NULL, 10);
    if (errno!=0){
        fprintf(stderr, "An error n %i has occured during parsing of the traffic light period on the right. Consult strtol documentation.", errno);
        exit(1);
    }

    /* setting up RNG */
    const gsl_rng_type *gsl_T;
    gsl_rng *gsl_r;
    gsl_rng_env_setup();
    gsl_T = gsl_rng_default;
    gsl_r = gsl_rng_alloc(gsl_T);
    gsl_rng_set(gsl_r,time(0));

    /* Running simulations */
    fprintf(stdout, "Entering simulation block.\n");
    fprintf(stdout, "Parameter values:\n    from left:\n        traffic arrival rate: % 4i\n        traffic light period: % 4i\n    from right:\n        traffic arrival rate: % 4i\n        traffic light period: % 4i\n", c.trARateL, c.trLPerL, c.trARateR, c.trLPerR);

    for(i = 0; i<SIMULATIONS; i++){
        r[i] = runOneSimulation(c, gsl_r);
        fprintf(stdout, "Simulation n%03i finished.\n",i+1);
    }

    /* Calculating average value to display to the user */
    rFinal.avgWTimeL = 0;
    rFinal.avgWTimeR = 0;
    rFinal.clTimeL = 0;
    rFinal.clTimeR = 0;
    rFinal.maxWTimeL = 0;
    rFinal.maxWTimeR = 0;
    rFinal.nVehL = 0;
    rFinal.nVehR = 0;

    for(i = 0; i<SIMULATIONS; i++){
        rFinal.avgWTimeL+= r[i].avgWTimeL;
        rFinal.avgWTimeR+= r[i].avgWTimeR;
        rFinal.clTimeL+= r[i].clTimeL;
        rFinal.clTimeR+= r[i].clTimeR;
        rFinal.maxWTimeL+= r[i].maxWTimeL;
        rFinal.maxWTimeR+= r[i].maxWTimeR;
        rFinal.nVehL+= r[i].nVehL;
        rFinal.nVehR+= r[i].nVehR;
    }

    rFinal.avgWTimeL = rFinal.avgWTimeL / (double) SIMULATIONS;
    rFinal.avgWTimeR = rFinal.avgWTimeR / (double) SIMULATIONS;
    rFinal.clTimeL = rFinal.clTimeL / (double) SIMULATIONS;
    rFinal.clTimeR = rFinal.clTimeR / (double) SIMULATIONS;
    rFinal.maxWTimeL = rFinal.maxWTimeL / (double) SIMULATIONS;
    rFinal.maxWTimeR = rFinal.maxWTimeR / (double) SIMULATIONS;
    rFinal.nVehL = rFinal.nVehL / (double) SIMULATIONS;
    rFinal.nVehR = rFinal.nVehR / (double) SIMULATIONS;

    /* reporting */

    fprintf(stdout, "Parameter values:\n    from left:\n        traffic arrival rate: % 4i\n        traffic light period: % 4i\n    from right:\n        traffic arrival rate: % 4i\n        traffic light period: % 4i\n", c.trARateL, c.trLPerL, c.trARateR, c.trLPerR);
    fprintf(stdout, "Results (average over %i runs):\n", SIMULATIONS);
    fprintf(stdout, "    from left:\n        number of vehicles: % 6i\n        average waiting time: % 4i\n        maximum waiting time: % 4i\n        clearance time: % 10i\n", rFinal.nVehL, rFinal.avgWTimeL, rFinal.maxWTimeL, rFinal.clTimeL);
    fprintf(stdout, "    from right:\n        number of vehicles: % 6i\n        average waiting time: % 4i\n        maximum waiting time: % 4i\n        clearance time: % 10i\n", rFinal.nVehR, rFinal.avgWTimeR, rFinal.maxWTimeR, rFinal.clTimeR);
}

/*
    Error codes:

    1 - Improperly formatted arguments
    2 - Program ran out of memeory in while running simulations.
    3 - Attempted to pop an empty stack.

*/
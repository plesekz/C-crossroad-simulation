#include "runOneSimulation.h"

/* code */

RESULTS runOneSimulation(CONFIG c, gsl_rng* gsl_r){
    /* variable declarations */
    /* variables necessary for generating the simulation report */
    RESULTS r;
    int carsPassedFromLeft = 0;
    int carsPassedFromRight = 0;
    int totalWaitingTimeOnLeft = 0;
    int totalWaitingTimeOnRight = 0;
    int maxWTimeL = 0;
    int maxWTimeR = 0;
    int clTimeL = 0;
    int clTimeR = 0;

    /* variables necessary for internal simulation control */
    CARQUEUE* rq = newQueue();
    CARQUEUE* lq = newQueue();
    LR greenLight = LEFT;
    int iteration = 0;
    int greenFor = 0;

    /* main body of the simulation */
    for(iteration = 0; iteration < 500; iteration++) {
        /* checks whether lights need to change */
        /* Check whether the left or right side is open */
        if(greenLight == LEFT){
            /* Check whether the side reached duration */
            if(c.trLPerL==greenFor){
                /* Duration reached, switch sides and reset the counter */
                greenLight = RIGHT;
                greenFor = 0;
                continue;
            }
        } else {
            if(c.trLPerR==greenFor){
                greenLight = LEFT;
                greenFor = 0;
                continue;
            }
        }
        /* cars arrive */
        
        /* Check whether new car arrives within this period on the left */
        if(checkFor(c.trARateL, gsl_r)){
            /* new car arrived */
            CAR* c = malloc(sizeof(CAR));
            if(c == NULL){
                fprintf(stderr, "Failed to allocate memory for a new car.");
                exit(2);
            }
            c->cycleArrived=iteration;
            push(lq,c);
        }
        /* Check whether new car arrives within this period on the right */
        if(checkFor(c.trARateR, gsl_r)){
            /* new car arrived */
            CAR* c = malloc(sizeof(CAR));
            if(c == NULL){
                fprintf(stderr, "Failed to allocate memory for a new car.");
                exit(2);
            }
            c->cycleArrived=iteration;
            push(rq,c);
        }

        /* A car passes */
        if(greenLight==LEFT){
            if(!isEmpty(lq)){
                CAR* c = (CAR*) pop(lq);
                
                if(iteration-(c->cycleArrived)>maxWTimeL){
                    maxWTimeL=iteration-(c->cycleArrived);
                }
                totalWaitingTimeOnLeft+=iteration-(c->cycleArrived);
                carsPassedFromLeft++;

                free(c);
            }
        } else {
            if(!isEmpty(rq)){
                CAR* c = (CAR*) pop(rq);
                
                if(iteration-(c->cycleArrived)>maxWTimeR){
                    maxWTimeR=iteration-(c->cycleArrived);
                }
                totalWaitingTimeOnRight+=iteration-(c->cycleArrived);
                carsPassedFromRight++;
                
                free(c);
            }
        }
        greenFor++;
    }
    
    /*
    fprintf(stdout, "Finished first 500 cycles.\n    Cars on left: %02i\n    Cars on right: %02i\n", lq->elements, rq->elements);
    */

    /* Cars stop arriving and the system continues until empty. */
    while((!(isEmpty(rq)))||(!(isEmpty(lq)))){
        /* checks whether lights need to change */
        /* Check whether the left or right side is open */
        if(greenLight == LEFT){
            /* Check whether the side reached duration */
            if(c.trLPerL==greenFor){
                /* Duration reached, switch sides and reset the counter */
                greenLight = RIGHT;
                greenFor = 0;
                continue;
            }
        } else {
            if(c.trLPerR==greenFor){
                greenLight = LEFT;
                greenFor = 0;
                continue;
            }
        }

        /* A car passes */
        if(greenLight==LEFT){
            if(!isEmpty(lq)){
                CAR* c = (CAR*) pop(lq);
                
                if(iteration-(c->cycleArrived)>maxWTimeL){
                    maxWTimeL=iteration-(c->cycleArrived);
                }
                totalWaitingTimeOnLeft+=iteration-(c->cycleArrived);
                carsPassedFromLeft++;

                free(c);
            } else {
                if(clTimeL==-1)
                clTimeL = iteration-500;
            }
        } else {
            if(!isEmpty(rq)){
                CAR* c = (CAR*) pop(rq);
                
                if(iteration-(c->cycleArrived)>maxWTimeR){
                    maxWTimeR=iteration-(c->cycleArrived);
                }
                totalWaitingTimeOnRight+=iteration-(c->cycleArrived);
                carsPassedFromRight++;
                
                free(c);
            }else {
                if(clTimeR==-1)
                clTimeR = iteration-500;
            }
        }
        greenFor++;
        iteration++;
        /*
        if(iteration%10==0)
        fprintf(stdout, "Finished 200 cycles.\n    Cars on left: %02i\n    Cars on right: %02i\n", lq->elements, rq->elements);
        */
    }
    emptyQueue(lq);
    emptyQueue(rq);

    /* return */
    r.nVehL = carsPassedFromLeft;
    r.nVehR = carsPassedFromRight;
    r.avgWTimeL = totalWaitingTimeOnLeft/carsPassedFromLeft;
    r.avgWTimeR = totalWaitingTimeOnRight/carsPassedFromRight;
    r.maxWTimeL = maxWTimeL;
    r.maxWTimeR = maxWTimeR;
    r.clTimeL = clTimeL;
    r.clTimeR = clTimeR;

    return r;
}

bool checkFor(double probability, gsl_rng* gsl_r){
    if(gsl_ran_flat(gsl_r, 1,100)<=probability){
        return true;
    } else {
        return false;
    }
}
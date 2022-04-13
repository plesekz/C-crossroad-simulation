/* includes */
#ifndef __runOneSimulation
#define __runOneSimulation

#include <gsl/gsl_rng.h>

#include "configuration/configuration.h"
#include "results/results.h"
#include "queue/queue.h"
#include "leftright/leftright.h"
#include "car/car.h"


/* defines */

#define CARQUEUE ROOT

/* function prototypes */

RESULTS runOneSimulation(CONFIG c, gsl_rng* gsl_r);
bool checkFor(double probability, gsl_rng* gsl_r);

#endif
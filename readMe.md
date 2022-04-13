Thank you for downloading the traffic light simulation.

# REQUIREMENTS

## COMPILING

For compilation of all components gcc is required.

## runOneSimulation.c

### car

Defines a struct storing properties of a single car.
Needs to be in a folder of the same name found in the compile directory.

### configuration

Defines a struct that holds initial properties of the simulation.
Needs to be in a folder of the same name found in the compile directory.

### leftright

Defines an enum needed to keep track of which side currently has green light.
Needs to be in a folder of the same name found in the compile directory.

### queue

Defines a stack used to keep track of the cars currently in the queue.
Needs to be in a folder of the same name found in the compile directory.

### results

Defines a struct used to hold the results of the simulation.
Needs to be ina  folder of the same name found in the compile directory.

### gsl standard library

The random number generation functionality of the gsl library is utilised to generate strong ranomness for car's arrival.
The library needs to be installed in its default location.

## runSimulations.c

### configuration

Defines a struct that holds initial properties of the simulation.
Needs to be in a folder of the same name found in the compile directory.

### results

Defines a struct used to hold the results of the simulation.
Needs to be in a folder of the same name found in the compile directory.

### runOneSimulation

Contains the main body of a single simulation.
Needs to be found in the compile directory.

# COMPILING THE FILES

In order to compile the program, assume that you fulfill all requirements, and then run the `compileSim` shell script with `./compileSim` in the compile directory.

# RUNNING THE PROGRAM

After teh `compileSim` shell script has been run, you can run the program with `./runSimulation`.
The program requires four non optional position sensitive arguments in the following form:
	(int:trafic arrival rate on the left) (int:traffic arrival rate on the right) (int:traffic light period on the left) (int:traffic light period on the right)
Example
	./runSimulation 50 50 2 2
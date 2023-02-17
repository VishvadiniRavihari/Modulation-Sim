// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
float analog_signal_generator(asignal signal, int t)
{
	//TODO
}
void sampler(float *samples, int interval, asignal signal)
{
	//TODO
}
void quantizer(float *samples, int *pcmpulses, int levels)
{
	//TODO
}
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
	//TODO
}
// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "mypcm.h"


// function prototypes
void run(asignal * inputsignal);


int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    free(inputsignal);
	return 0;
}

void run(asignal * inputsignal) 
{
	float A;
    float omega;
    float sigma;
    int duration;
    int interval;
    int encoderbits;

    scanf( "%f %f %f %d %d %d", &A, &omega, &sigma, &duration, &interval, &encoderbits);

    inputsignal->A = A;
    inputsignal->omega = omega;
    inputsignal->sigma = sigma;
    inputsignal->duration = duration;

    //declare an array for sampling points storing and call the sampler function
    float samples[1000];
    sampler( samples, interval, *inputsignal );
    //declare an array for pcmpulses storing and call the quantizer function
    int pcmpulses[1000];
    quantizer( samples, pcmpulses, pow(2,encoderbits));
    //declare an array for modulated stream's component vice storing and call the encoder function
    int dsignal[1000];
    encoder(pcmpulses, dsignal, encoderbits);

    //print the modulated stream
    int iterations = ((duration / interval) +1) * encoderbits;
    for( int i=0; i<iterations; i++){
        printf("%d", dsignal[i]);
    }

}

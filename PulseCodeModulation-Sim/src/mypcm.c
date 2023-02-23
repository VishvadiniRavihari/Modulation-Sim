// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <math.h>


// user-defined header files
#include "mypcm.h" // do not modify this file

float analog_signal_generator(asignal signal, int t)
{	float signal_val = (signal.A) * sin( (signal.omega * t) + signal.sigma );
	return signal_val; }

void sampler(float *samples, int interval, asignal signal)
{	/*set the first elemnt in samples array to be the count of sampling points
	  and second to be the amplitude*/
	samples[0] = (signal.duration / interval) +1;
	samples[1] = signal.A;

	// iterate and add the sampling points to the samples array 
	for( int i = 0; i * interval <= signal.duration; i++){
		int time = i * interval;
		float sampler_value = analog_signal_generator( signal, time );
		samples[i+2] = sampler_value; 
	}
}
void quantizer(float *samples, int *pcmpulses, int levels)
{	int sampling_points = samples[0];
	float A = samples[1];
	pcmpulses[0] = sampling_points;
	
	/*iterate and add the quantization value to the pcmpulses array*/
	for ( int i=0; i<sampling_points; i++ ){
		int pcm_value = floor( ((samples[i+2] - (-A)) / (A - (-A)) ) * levels);
		pcmpulses[i+1] = pcm_value; }
}

void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{	int iterations = pcmpulses[0];
	for( int j=0; j<iterations; j++){
		int array[encoderbits];
		// iterate and get the quantiazation number into binary format
		for (int i = encoderbits-1; i >= 0; i--) {
			int mask = (1 << i);
        
        	if (pcmpulses[j+1] & mask){
				array[(encoderbits-1)-i] = 1;} 
        	else{
				array[(encoderbits-1)-i] = 0;}
    	}
		//append the bit stream to the dsignal array
		for( int i=0; i<encoderbits; i++){
			dsignal[(encoderbits*j)+i] = array[i];
		}

	}
}
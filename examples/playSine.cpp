#include <stdio.h>
#include <math.h>
#include "AudioDevice.h"
 


 
 /*******************************************************************/
 int main(void)
 {
     AudioDevice d;
     d.Start();
     printf("Play for %d seconds.\n", NUM_SECONDS);
     Pa_Sleep(2 * 1000);
     d.SetWaveParameters(442.0,0.9);
     Pa_Sleep(3 * 1000);
     d.Stop();

 }
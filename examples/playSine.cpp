#include <stdio.h>
#include <math.h>
#include "AudioDevice.h"
#include <chrono>
#include <thread>

 int main(void)
 {
     AudioDevice d;
     d.Start(100);
     std::this_thread::sleep_for(std::chrono::milliseconds(2000));
     d.SetWaveParameters(442.0,0.9);
     std::this_thread::sleep_for(std::chrono::milliseconds(3000));
     d.Stop();

 }
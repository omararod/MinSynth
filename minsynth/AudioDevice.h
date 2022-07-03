#pragma once
#include "IAudioDevice.h"
#include <stdio.h>
#include <math.h>
#include "portaudio.h"


#define NUM_SECONDS   (5)
#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (64)

#ifndef M_PI
#define M_PI  (3.14159265)
#endif

#define TABLE_SIZE   (SAMPLE_RATE)

class AudioDevice : public IAudioDevice
{
public:
    virtual void Start() override;
    virtual void SetWaveParameters(float frequency, float amplitude) override;
    virtual void Stop()override;

private:
    static int patestCallback(const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData);
    /*
    * This routine is called by portaudio when playback is done.
    */
    static void StreamFinished(void* userData);

    void PrintError();

    struct paTestData
    {
        float sine[TABLE_SIZE];
        int currentOffset;
        int frequency;
        float amplitude;
        char message[20];
    };

    PaError err;
    PaStream *stream;
    paTestData data;
    
};
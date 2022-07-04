#include "AudioDevice.h"
#include <string>
#include <exception>
#include <cmath>
#include "portaudio.h"

const float pi = 3.14159265358979323846;
const int FRAMES_PER_BUFFER = 64;
const int SAMPLE_RATE = 44100;
const int TABLE_SIZE = SAMPLE_RATE;

PaError err;
PaStream *stream;

void PrintError()
{
    Pa_Terminate();
    fprintf(stderr, "An error occurred while using the portaudio stream\n");
    fprintf(stderr, "Error number: %d\n", err);
    fprintf(stderr, "Error message: %s\n", std::string(Pa_GetErrorText(err)));
}

int patestCallback(const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData)
{
    AudioDevice::AudioData *data = (AudioDevice::AudioData*)userData;

    float *out = (float*)outputBuffer;
    unsigned long i;

    for (i = 0; i<framesPerBuffer; i++)
    {
        float sampleValue = data->sineLUT[data->currentOffset] * data->amplitude;
        *out++ = sampleValue;  /* left */
        *out++ = sampleValue;  /* right */
        data->currentOffset = (data->currentOffset + data->frequency) % TABLE_SIZE;
    }
    return paContinue;
}
void StreamFinished(void* userData)
{
    AudioDevice::AudioData *data = static_cast<AudioDevice::AudioData *>(userData);
}

AudioDevice::AudioDevice()
{
    int i;
    //initialize sine look-up table
    float stepSize = (2.0*pi) / static_cast<float>(TABLE_SIZE);
    data.sineLUT.resize(TABLE_SIZE);
    for (i = 0; i<TABLE_SIZE; i++)
    {
        data.sineLUT[i] = (float)sin(i *stepSize);
    }
    data.currentOffset = data.currentOffset = 0;
    data.frequency = 442;
    data.amplitude = 1.0;
}
void AudioDevice::Start(unsigned int frequency,float amplitude)
{
    data.frequency = frequency;
    data.amplitude = amplitude;
    PaStreamParameters outputParameters;
    try {

        err = Pa_Initialize();
        if (err != paNoError) throw std::runtime_error("Error initializing audio device");

        outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
        if (outputParameters.device == paNoDevice) {
           throw std::runtime_error("Error initializing audio device");
        }
        outputParameters.channelCount = 2;       /* stereo output */
        outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
        outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = NULL;

        err = Pa_OpenStream(
            &stream,
            NULL, /* no input */
            &outputParameters,
            SAMPLE_RATE,
            FRAMES_PER_BUFFER,
            paClipOff,      /* we won't output out of range samples so don't bother clipping them */
            patestCallback,
            &data);
        if (err != paNoError) throw std::runtime_error("Error opening audio device");

        err = Pa_SetStreamFinishedCallback(stream, &StreamFinished);
        if (err != paNoError) throw std::runtime_error("Error registering callback on audio device");

        err = Pa_StartStream(stream);
        if (err != paNoError) throw std::runtime_error("Error starting audio stream");
    }
    catch (std::runtime_error)
    {
        PrintError();
        throw;
    }
    
}
void AudioDevice::SetWaveParameters(unsigned int frequency, float amplitude)
{
    //current implementation supports only integer frequencies
    data.frequency = static_cast<int>(frequency);
    data.amplitude = amplitude;
}
void AudioDevice::Stop()
{
    err = Pa_StopStream(stream);
    if (err != paNoError) PrintError();

    err = Pa_CloseStream(stream);
    if (err != paNoError) PrintError();

    Pa_Terminate();
    printf("Test finished.\n");
}
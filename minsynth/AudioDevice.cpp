#include "AudioDevice.h"


void AudioDevice::Start()
{
    PaStreamParameters outputParameters;

    paTestData data;
    int i;

    printf("PortAudio Test: output sine wave. SR = %d, BufSize = %d\n", SAMPLE_RATE, FRAMES_PER_BUFFER);

    /* initialise sinusoidal wavetable */
    for (i = 0; i<TABLE_SIZE; i++)
    {
        data.sine[i] = (float)sin(((double)i / (double)TABLE_SIZE) * M_PI * 2.);
    }
    data.left_phase = data.right_phase = 0;
    data.count = 40;

    err = Pa_Initialize();
    if (err != paNoError) PrintError();

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
        fprintf(stderr, "Error: No default output device.\n");
        PrintError();
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
    if (err != paNoError) PrintError();

    sprintf(data.message, "No Message");
    err = Pa_SetStreamFinishedCallback(stream, &StreamFinished);
    if (err != paNoError) PrintError();

    err = Pa_StartStream(stream);
    if (err != paNoError) PrintError();

    printf("Play for %d seconds.\n", NUM_SECONDS);
    //Pa_Sleep( NUM_SECONDS * 1000 );
    for (int i = 0; i< NUM_SECONDS * 100; i++)
    {

        Pa_Sleep(10);
        data.count++;
    }
}
void AudioDevice::SetWaveParameters(float frequency, float amplitude)
{
    
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


int AudioDevice::patestCallback(const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData)
{
    paTestData *data = (paTestData*)userData;

    float *out = (float*)outputBuffer;
    unsigned long i;

    (void)timeInfo; /* Prevent unused variable warnings. */
    (void)statusFlags;
    (void)inputBuffer;

    for (i = 0; i<framesPerBuffer; i++)
    {
        *out++ = data->sine[data->left_phase];  /* left */
        *out++ = data->sine[data->right_phase];  /* right */
        data->left_phase += data->count;
        if (data->left_phase >= TABLE_SIZE) data->left_phase -= TABLE_SIZE;
        data->right_phase += data->count;
        if (data->right_phase >= TABLE_SIZE) data->right_phase -= TABLE_SIZE;
    }
    return paContinue;
}

void AudioDevice::StreamFinished(void* userData)
{
    paTestData *data = (paTestData *)userData;
    printf("Stream Completed: %s\n", data->message);
}

void AudioDevice::PrintError()
{
    Pa_Terminate();
    fprintf(stderr, "An error occurred while using the portaudio stream\n");
    fprintf(stderr, "Error number: %d\n", err);
    fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
}
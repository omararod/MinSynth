#pragma once
#include "IAudioDevice.h"
#include <vector>

class AudioDevice : public IAudioDevice
{
public:
    struct AudioData
    {
        std::vector<float> sineLUT;
        int currentOffset;
        unsigned int frequency;
        float amplitude;
    };
    virtual void Start(unsigned int frequency = 440, float amplitude = 1.0) override;
    virtual void SetWaveParameters(unsigned int frequency, float amplitude) override;
    virtual void Stop()override;

    AudioDevice();

private: 
    AudioData data;   
};
#pragma once

class IAudioDevice
{
    public:
    virtual ~IAudioDevice() = default;
    virtual void Start(unsigned int frequency, float amplitude) = 0;
    virtual void SetWaveParameters(unsigned int frequency, float amplitude) = 0;
    virtual void Stop() = 0;
};
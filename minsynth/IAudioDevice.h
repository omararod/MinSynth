#pragma once

class IAudioDevice
{
    public:
    virtual ~IAudioDevice() = default;
    virtual void Start() = 0;
    virtual void SetWaveParameters(float frequency, float amplitude) = 0;
    virtual void Stop() = 0;
};
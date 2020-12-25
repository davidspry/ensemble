//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef SAMPLECLOCK_H
#define SAMPLECLOCK_H

#include "ClockEngine.h"

/// @brief An internal clock engine that uses the sample rate of the sound output device to measure time.

class SampleClock: public ClockEngine, public ofBaseSoundOutput
{
public:
    SampleClock()
    {
        setSampleRate(44100);
    }
    
    ~SampleClock()
    {
        soundstream.stop();
    }
    
public:
    inline void toggleClock() noexcept override
    {
        ClockEngine::toggleClock();
        
        if (ticking)
             soundstream.start();
        else soundstream.stop();
    }
    
    /// @brief Set the clock's sample rate in samples per second.
    /// @param samplesPerSecond The desired sample rate.

    inline void setSampleRate(unsigned int samplesPerSecond) noexcept
    {
        if (sampleRate == samplesPerSecond)
            return;
        
        initialiseSoundStream(samplesPerSecond);
        sampleRate = samplesPerSecond;
        updateParameters();
    }
    
    inline void setTempo(unsigned int beatsPerMinute) noexcept override
    {
        ClockEngine::setTempo(beatsPerMinute);
        
        updateParameters();
    }

    inline void setSubdivision(unsigned int ticksPerBeat) noexcept override
    {
        ClockEngine::setSubdivision(ticksPerBeat);
        
        updateParameters();
    }

    /// @brief The audio callback where sound buffers are processed at the sample rate.
    /// @param buffer The buffer of samples to be output.

    inline void audioOut(ofSoundBuffer& buffer) override
    {
        for (size_t k = 0; k < buffer.getNumFrames(); ++k)
        {
            advance();
        }
    }
    
private:
    /// @brief Adance the clock forwards and broadcast ticks to listeners when appropriate.
    
    inline void advance()
    {
        time = time + 1;
        time = time * static_cast<int>(time < tickLength);

        if (time == 0)
            tick();
    }

private:
    /// @brief Update the tick length based on the clock's tempo, sample rate, and time subdivision.

    inline void updateParameters() noexcept
    {
        const float sixty = static_cast<float>(sampleRate * 60);
        const float ticks = static_cast<float>(tempo)
                          * static_cast<float>(subdivision);

        tickLength = static_cast<int>(sixty / ticks);
    }
    
    /// @brief Initialise the sound output settings and begin processing buffers at the sample rate.
    /// @param sampleRate The sample rate to use.
    /// @note  This is called whenever the sample rate is updated using `setSampleRate`.

    void initialiseSoundStream(unsigned int sampleRate)
    {
        ofSoundDevice * const device = getDefaultOutputDevice();

        if (device == nullptr)
            return;
        
        ofSoundStreamSettings settings;
            settings.setOutDevice(*device);
            settings.numInputChannels  = 0;
            settings.numOutputChannels = 1;
            settings.setOutListener(this);
            settings.sampleRate = sampleRate;
            settings.bufferSize = 64;

        soundstream.setup(settings);
        soundstream.stop();
    }
    
    /// @brief Get the default sound output device.
    /// @throw An exception will be thrown if no output device is found.

    inline ofSoundDevice* getDefaultOutputDevice() noexcept
    {
        for (ofSoundDevice& output : soundstream.getDeviceList())
        {
            if (output.isDefaultOutput)
                return &output;
        }
        
        ofLogError("SampleClock", "No output device was located.");

        return nullptr;
    }
    
private:
    ofSoundStream soundstream;
    
private:
    unsigned int time;
    unsigned int tickLength;
    unsigned int sampleRate;
};

#endif

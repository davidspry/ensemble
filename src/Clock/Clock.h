//  Ensemble
//  Created by David Spry on 25/12/20.

#ifndef CLOCK_H
#define CLOCK_H

#include "ClockListener.h"
#include "SampleClock.h"
#include "MIDIClock.h"

/// @brief A clock that contains both an internal audio rate clock engine and an external MIDI clock engine.
///
/// This clock can be used by subclassing ClockListener, overriding the virtual `tick` method, and connecting to the clock.
/// The `tick` method will be called whenever the chosen clock engine ticks.

class Clock: public ClockListener
{
public:
    Clock();
    
public:
    inline void tick() override
    {
        for (ClockListener* listener : listeners)
        {
            listener->tick();
        }
    }
    
public:
    /// @brief Connect a new listener, who will subsequently receive notifications when the clock ticks.
    /// @param listener The listener who should be connected.
    
    void connect(ClockListener* listener);
    
    /// @brief Disconnect an existing listener from the clock.
    /// @param listener The listener who should be disconnected.

    void disconnect(ClockListener* listener);
    
public:
    /// @brief Use the underlying audio sample rate clock as the clock source.

    void useSampleClock();
    
    /// @brief Use the underlying MIDI clock listener as the clock source.

    void useMidiClock();
    
// MARK: - Global Clock Interface
public:
    /// @brief Toggle the `ticking` state of the selected clock source.

    inline void toggleClock() noexcept
    {
        (*getClockEngine()).toggleClock();
    }
    
    /// @brief Set the `ticking` state of the selected clock source explicitly.
    /// @param shouldTick Whether or not the clock should tick.

    inline void setClockShouldTick(bool shouldTick) noexcept
    {
        (*getClockEngine()).setClockShouldTick(shouldTick);
    }
    
    /// @brief Get the tempo of the clock.
    /// @note  The tempo of the MIDI clock is inferred and may not be accurate.
    
    inline int getTempo() noexcept
    {
        return (*getClockEngine()).getTempo();
    }
    
    /// @brief Get the subdivison value of the clock.

    inline int getSubdivision() noexcept
    {
        return (*getClockEngine()).getSubdivision();
    }
    
    /// @brief Set the tempo of the internal clock engine.
    /// @param beatsPerMinute The desired tempo in beats per minute.
    /// @note  The tempo of the external MIDI clock should be set at the source.

    inline void setTempo(unsigned int beatsPerMinute) noexcept
    {
        sampleClock.setTempo(beatsPerMinute);
    }
    
    /// @brief Set the time subdivision of all underlying clock engines.
    /// @param ticksPerBeat The number of ticks per beat.

    inline void setSubdivision(unsigned int ticksPerBeat) noexcept
    {
        (*getClockEngine()).setSubdivision(ticksPerBeat);
    }

// MARK: - Sample Clock Interface
    
public:
    /// @brief Set the sample rate of the underlying audio sample clock.
    /// @param samplesPerSecond The desired sample rate in samples per second.

    inline void setSampleRate(unsigned int samplesPerSecond) noexcept
    {
        sampleClock.setSampleRate(samplesPerSecond);
    }
    
    
// MARK: - MIDI Clock Interface
    
public:
    /// @brief Specify the frame rate of the underlying MIDI clock.
    /// @param framesPerSecond The frame rate in frames per second.

    inline void setFrameRate(unsigned int framesPerSecond) noexcept
    {
        midiClock.setFrameRate(framesPerSecond);
    }
    
    /// @brief Select the next of the available MIDI ports for the underlying MIDI clock.
    
    inline void selectNextMIDIPort() noexcept
    {
        midiClock.selectNextMIDIPort();
    }
    
    /// @brief Select the previous of the available MIDI ports for the underlying MIDI clock.
    
    inline void selectPreviousMIDIPort() noexcept
    {
        midiClock.selectPreviousMIDIPort();
    }
    
    /// @brief Return the clock's MIDI input port.
    
    inline unsigned int getMIDIPort() noexcept
    {
        return midiClock.getMIDIPort();
    }
    
    /// @brief Return a textual description of the clock's MIDI input port.

    inline std::string getMIDIPortDescription() noexcept
    {
        return midiClock.getMIDIPortDescription();
    }

private:
    /// @brief Return a pointer to the clock engine that's currently in use.

    inline ClockEngine * getClockEngine() noexcept
    {
        if (usingSampleClock)
             return &sampleClock;
        else return &midiClock;
    }
    
    inline void connectToClockEngines() noexcept
    {
        midiClock.connect(this);
        sampleClock.connect(this);
    }

private:
    bool usingSampleClock;
    
private:
    MIDIClock   midiClock;
    SampleClock sampleClock;

private:
    std::vector<ClockListener*> listeners;
};

#endif

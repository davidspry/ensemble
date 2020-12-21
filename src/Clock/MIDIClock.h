//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef MIDICLOCK_H
#define MIDICLOCK_H

#include "ClockEngine.h"
#include "ofxMidiClock.h"
#include "ofxMidi.h"

/// @brief A clock engine that receives ticks from an external MIDI clock source.

class MIDIClock: public ClockEngine, public ofxMidiListener
{
public:
    MIDIClock()
    {
        setFrameRate(24);
        initialiseMIDIInput();
    }
    
    ~MIDIClock()
    {
        midiIn.closePort();
        midiIn.removeListener(this);
    }
    
private:
    inline void initialiseMIDIInput()
    {
        midiIn.openPort(0);
        midiIn.ignoreTypes(true, false, true);
        midiIn.addListener(this);
    }
    
public:
    /// @brief Set the frame rate of the MIDI clock in frames per second.
    /// @param framesPerSecond The frame rate of the MIDI clock.

    inline void setFrameRate(unsigned int framesPerSecond) noexcept
    {
        if (frameRate == framesPerSecond)
            return;
        
        frameRate = std::max(static_cast<int>(framesPerSecond), 1);
        updateParameters();
    }
    
    /// @brief Close the current MIDI port and open the given MIDI port.
    /// @param port The number of the port to be opened.

    inline void selectMIDIPort(unsigned int port) noexcept
    {
        if (port == midiIn.getPort())
            return;
        
        if (port >= midiIn.getNumInPorts())
            return;
        
        midiIn.closePort();
        midiIn.openPort(port);
    }
    
    /// @brief Open the next available MIDI port.
    
    inline void selectNextMIDIPort() noexcept
    {
        const int ports = midiIn.getNumInPorts();
        const int port  = midiIn.getPort();
        
        selectMIDIPort((port + 1) % ports);
    }
    
    /// @brief Open the previous available MIDI port.

    inline void selectPreviousMIDIPort() noexcept
    {
        const int ports = midiIn.getNumInPorts();
        const int port  = midiIn.getPort();
        
        selectMIDIPort((port - 1 + ports) % ports);
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
    
    /// @brief Reset the time keeping value to zero.

    inline void reset()
    {
        time = 0;
    }
    
    /// @brief Update the inferred tempo value from the MIDI clock.

    inline void updateInferredTempo()
    {
        inferredTempo = inferredTempo + (midiClock.getBpm() - inferredTempo) / 5.0;
        
        tempo = static_cast<unsigned int>(inferredTempo);
    }
    
    /// @brief The callback executed when new MIDI messages are received.
    /// @param message The MIDI message that was received.

    inline void newMidiMessage(ofxMidiMessage& message)
    {
        auto & bytes = message.bytes;
        auto & state = message.status;

        midiClock.update(bytes);
        updateInferredTempo();

        switch (state)
        {
            case MIDI_TIME_CLOCK:
            {
                advance();
                return;
            }
            
            case MIDI_STOP:
            {
                reset();
                return;
            }

            default: return;
        }
    }

    /// @brief Update the tick length based on the frame rate and the subdivision.

    inline void updateParameters()
    {
        tickLength = frameRate / subdivision;
    }

private:
    ofxMidiIn    midiIn;
    ofxMidiClock midiClock;
    
private:
    unsigned int time;
    unsigned int tickLength;
    unsigned int frameRate;
    
private:
    double inferredTempo = 100.0;
};

#endif

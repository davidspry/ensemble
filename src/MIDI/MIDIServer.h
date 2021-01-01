//  Ensemble
//  Created by David Spry on 30/12/20.

#ifndef MIDISERVER_H
#define MIDISERVER_H

#include "CircularQueue.h"
#include "MIDITypes.h"
#include "ofxMidi.h"

class MIDIServer
{
public:
    MIDIServer()
    {
        midiOut.openPort(0);
    }

    ~MIDIServer()
    {
        midiOut.closePort();
    }
    
public:
    /// @brief Broadcast the given note.
    /// @param note The MIDI note to broadcast.

    inline void broadcast(const MIDINote& note) noexcept
    {
        notes.enqueue(note);
        midiOut.sendNoteOn(note.midi.channel, note.note, note.midi.velocity);
    }
    
    /// @brief Release all notes pending release.

    inline void release() noexcept
    {
        while (notes.isNotEmpty())
        {
            MIDINote release = notes.dequeue();
            midiOut.sendNoteOff(release.midi.channel, release.note, 0);
        }
    }
    
public:
    /// @brief Close the current MIDI port and open the given MIDI port.
    /// @param port The number of the port to be opened.

    inline void selectMIDIPort(unsigned int port) noexcept
    {
        if (port == midiOut.getPort())
            return;
        
        if (port >= midiOut.getNumOutPorts())
            return;
        
        midiOut.closePort();
        midiOut.openPort(port);
    }
    
    /// @brief Open the next available MIDI port.
    
    inline void selectNextMIDIPort() noexcept
    {
        const int port  = midiOut.getPort();
        const int ports = midiOut.getNumOutPorts();
        selectMIDIPort((port + 1) % ports);
    }
    
    /// @brief Open the previous available MIDI port.

    inline void selectPreviousMIDIPort() noexcept
    {
        const int port  = midiOut.getPort();
        const int ports = midiOut.getNumOutPorts();
        selectMIDIPort((port - 1 + ports) % ports);
    }
    
private:
    ofxMidiOut midiOut;
    
private:
    CircularQueue<MIDINote, 16> notes;
};

#endif

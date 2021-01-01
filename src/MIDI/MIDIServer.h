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
        if (notes.full())
        {
            release(notes.dequeue());
        }
        
        if (notes.enqueue(note))
        {
            midiOut.sendNoteOn(note.midi.channel, note.note, note.midi.velocity);
        }
    }
    
    /// @brief Release all notes pending release.

    inline void releaseAllNotes() noexcept
    {
        while (notes.isNotEmpty())
        {
            release(notes.dequeue());
        }
    }
    
public:
    /// @brief Close the current MIDI port and open the given MIDI port.
    /// @param port The number of the port to be opened.
    /// @return A Boolean value indicating whether the given port was successfully opened or not.

    inline bool selectMIDIPort(unsigned int port) noexcept
    {
        if (port == midiOut.getPort())
            return true;
        
        if (port >= midiOut.getNumOutPorts())
            return false;
        
        midiOut.closePort();
        return midiOut.openPort(port);
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
    /// @brief Send a note off message for the given MIDI note.
    /// @param note The note to be released.

    inline void release(const MIDINote & note) noexcept
    {
        midiOut.sendNoteOff(note.midi.channel, note.note, 0);
    }
    
private:
    ofxMidiOut midiOut;
    
private:
    CircularQueue<MIDINote, 16> notes;
};

#endif

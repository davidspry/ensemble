//  Ensemble
//  Created by David Spry on 30/12/20.

#ifndef MIDISERVER_H
#define MIDISERVER_H

#include "MIDINoteQueue.h"
#include "MIDITypes.h"
#include "ofxMidi.h"

class MIDIServer
{
public:
     MIDIServer();
    ~MIDIServer();

public:
    /// @brief Broadcast the given note.
    /// @param note The MIDI note to broadcast.

    void broadcast(const MIDINote& note) noexcept;
    
    /// @brief Release any expired notes.

    void releaseExpiredNotes() noexcept;
    
    /// @brief Release all notes pending release.

    void releaseAllNotes() noexcept;
    
public:
    /// @brief Close the current MIDI port and open the given MIDI port.
    /// @param port The number of the port to be opened.
    /// @return A Boolean value indicating whether the given port was successfully opened or not.

    bool selectMIDIPort(unsigned int port) noexcept;
    
    /// @brief Open the next available MIDI port.
    
    void selectNextMIDIPort() noexcept;
    
    /// @brief Open the previous available MIDI port.

    void selectPreviousMIDIPort() noexcept;
    
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
    MIDINoteQueue<16> notes;
};

#endif

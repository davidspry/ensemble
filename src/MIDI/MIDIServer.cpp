//  Ensemble
//  Created by David Spry on 9/1/21.

#include "MIDIServer.h"

MIDIServer::MIDIServer()
{
    midiOut.openPort(0);
}

MIDIServer::~MIDIServer()
{
    midiOut.closePort();
}

void MIDIServer::broadcast(const MIDINote &note) noexcept
{
    if (notes.full())
    {
        release(notes.pop());
    }

    if (notes.push(note))
    {
        midiOut.sendNoteOn(note.midi.channel, note.note, note.midi.velocity);
    }
}

void MIDIServer::releaseExpiredNotes() noexcept
{
    notes.sustain();
    
    while (notes.containsExpiredNotes())
    {
        release(notes.pop());
    }
}

void MIDIServer::releaseAllNotes() noexcept
{
    while (notes.isNotEmpty())
    {
        release(notes.pop());
    }
}

bool MIDIServer::selectMIDIPort(unsigned int port) noexcept
{
    if (port == midiOut.getPort())
        return true;
    
    if (port >= midiOut.getNumOutPorts())
        return false;
    
    midiOut.closePort();
    return midiOut.openPort(port);
}

void MIDIServer::selectNextMIDIPort() noexcept
{
    const int port  = midiOut.getPort();
    const int ports = midiOut.getNumOutPorts();
    selectMIDIPort((port + 1) % ports);
}

void MIDIServer::selectPreviousMIDIPort() noexcept
{
    const int port  = midiOut.getPort();
    const int ports = midiOut.getNumOutPorts();
    selectMIDIPort((port - 1 + ports) % ports);
}

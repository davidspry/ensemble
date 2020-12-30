//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef MIDINOTE_H
#define MIDINOTE_H

#include "MIDISettings.h"

/// @brief A MIDI note, which can be broadcast from the Ensemble sequencer.

struct MIDINote
{
    uint8_t note;
    MIDISettings midi;
    
    MIDINote()
    {
        note = 60;
        midi = {};
    }
    
    MIDINote(uint8_t noteNumber, const MIDISettings& settings)
    {
        note = 12 * (settings.octave + 1) + (noteNumber % 12);
        midi = settings;
    }
};

#endif

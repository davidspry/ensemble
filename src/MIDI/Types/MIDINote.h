//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef MIDINOTE_H
#define MIDINOTE_H

#include "MIDISettings.h"

/// @brief A MIDI note, which can be broadcast from the Ensemble sequencer.

struct MIDINote
{
    uint8_t note = 60;
    MIDISettings midi;
};

#endif

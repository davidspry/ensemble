//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef MIDISETTINGS_H
#define MIDISETTINGS_H

#include <cstdint>
#include "MIDISettingsValues.h"

/// @brief The properties of a MIDI note that can be specified on the Ensemble sequencer.

struct MIDISettings
{
    uint8_t octave   = 0x3;
    uint8_t channel  = 0x1;
    uint8_t duration = 0x1;
    uint8_t velocity = 100;

    MIDISettings()
    {
        set(3, 1, 1, 100);
    }

    MIDISettings(uint8_t octave, uint8_t channel, uint8_t duration, uint8_t velocity)
    {
        set(octave, channel, duration, velocity);
    }

    void set(uint8_t octave, uint8_t channel, uint8_t duration, uint8_t velocity)
    {
        this->octave   = octave;
        this->channel  = channel;
        this->duration = duration;
        this->velocity = velocity;
    }
};

#endif

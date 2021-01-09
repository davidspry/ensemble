//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef MIDINOTE_H
#define MIDINOTE_H

#include <array>
#include <string>
#include "MIDISettings.h"

/// @brief A MIDI note, which can be broadcast from the Ensemble sequencer.

struct MIDINote
{
    uint8_t      note;
    MIDISettings midi;

    MIDINote()
    {
        note = 60;
        midi = {};
    }
    
    /// @brief Construct a MIDI note.
    /// @param noteIndex A number in the range [0, 11] representing a note from the chromatic scale, beginning with C.
    /// @param settings The note's MIDI settings, including duration, channel, velocity, and octave.

    MIDINote(uint8_t noteIndex, const MIDISettings& settings)
    {
        note = 12 * (settings.octave + 1) + (noteIndex % 12);
        midi = settings;
    }
    
    /// @brief Return the MIDI note's note name.

    inline std::string notename() noexcept
    {
        const std::array<std::string, 12> notes =
        {
            "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
        };

        return notes[note % 12] + std::to_string(midi.octave - 1);
    }
    
    /// @brief Compute a textual description of the note and its MIDI settings.

    inline std::string description() noexcept
    {
        const auto channel  = std::to_string(midi.channel);
        const auto velocity = std::to_string(midi.velocity);

        return "NOTE "      + notename()
             + " CHANNEL "  + channel
             + " VELOCITY " + velocity;
    }
};

#endif

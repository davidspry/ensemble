//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef CURSOR_H
#define CURSOR_H

#include "Ensemble.h"
#include "GridCell.h"

/// @brief The user's sequencer position and MIDI settings.

class Cursor: public GridCell
{
public:
    Cursor(unsigned int cursorSize):
    GridCell(cursorSize)
    {
        initialisePath();
    }

    Cursor(unsigned int cursorSize, UIPoint<int> position, MIDISettings settings):
    GridCell(cursorSize, position), midi(settings)
    {
        initialisePath();
    }
    
// MARK: - MIDI Settings

public:
    
    /// @brief Return the current MIDI settings.

    [[nodiscard]] inline const MIDISettings& getMIDISettings() const noexcept
    {
        return midi;
    }
    
    /// @brief Set the octave of the cursor's MIDI settings.
    /// @param octave The desired octave number in the range [0, 6].
    /// @note The given octave value will be bound by the range [0, 6]

    void setOctave(const int octave) noexcept
    {
        midi.octave = Utilities::boundBy(0, 6, octave);
    }
    
    void setChannel(const int channel) noexcept
    {
        midi.channel = Utilities::boundBy(1, 16, channel);
    }
    
    void setDuration(const int duration) noexcept
    {
        midi.duration = Utilities::boundBy(1, 8, duration);
    }

private:
    MIDISettings midi;
};

#endif

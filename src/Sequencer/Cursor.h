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

public:
    void draw() override
    {
        const int x = origin.x + margins.l + screenPosition.x;
        const int y = origin.y + margins.t + screenPosition.y;

        if (shouldRedraw)
        {
            path.clear();
            path.rectangle(0, 0, size.w, size.h);
            path.setColor(colours->foregroundColour);
        }

        path.draw(x, y);
    }
    
    /// @brief Move the cursor on the sequencer in the given direction.
    /// @param direction The direction in which the cursor should be moved.
    /// @param gridSize The dimensions of the sequencer grid in rows and columns.

    inline void move(Direction& direction, const UISize<int>& gridSize)
    {
        const int dy = -static_cast<int>(direction == Direction::N)
                     +  static_cast<int>(direction == Direction::S);
        const int dx = -static_cast<int>(direction == Direction::W)
                     +  static_cast<int>(direction == Direction::E);

        xy.x = (xy.x + dx + gridSize.w) % gridSize.w;
        xy.y = (xy.y + dy + gridSize.h) % gridSize.h;

        moveToGridPosition(xy);
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

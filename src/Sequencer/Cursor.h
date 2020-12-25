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
    
    /// @brief Return the current MIDI settings.

    [[nodiscard]] inline const MIDISettings& getMIDISettings() const noexcept
    {
        return midi;
    }
    
public:
    void draw() override
    {
        if (shouldRedraw)
        {
            path.clear();
            path.circle(0.5f * size.w, 0.5f * size.h, 0.4f * size.w);
            path.setColor(colours.foregroundColour);
        }

        path.draw(origin.x + margins.l + gridPosition.x,
                  origin.y + margins.t + gridPosition.y);
    }

private:
    MIDISettings midi;
};

#endif

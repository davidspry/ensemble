//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef CURSOR_H
#define CURSOR_H

#include "Ensemble.h"

/// @brief The user's sequencer position and MIDI settings.

class Cursor: public UIComponent
{
public:
    Cursor(unsigned int cursorSize):
    UIComponent()
    {
        setSize(cursorSize, cursorSize);
        moveToGridPosition(0, 0);

        initialisePath();
    }

    Cursor(unsigned int cursorSize, UIPoint<int> position, MIDISettings settings):
    UIComponent()
    {
        setSize(cursorSize, cursorSize);
        moveToGridPosition(position);

        midi = settings;
        initialisePath();
    }

private:
    inline void initialisePath()
    {
        cursor.setFilled(true);
        cursor.setStrokeWidth(0.0f);
        cursor.clear();
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

        setPositionWithOrigin(xy.x * size.w, xy.y * size.h);
    }
    
    /// @brief Return the current MIDI settings.

    [[nodiscard]] inline const MIDISettings& getMIDISettings() const noexcept
    {
        return midi;
    }
    
private:
    /// @brief Move the cursor to the given position on the sequencer.
    /// @param position The desired position as row and column indices.

    inline void moveToGridPosition(UIPoint<int>& position)
    {
        moveToGridPosition(position.y, position.x);
    }
    
    /// @brief Move the cursor to the given position on the sequencer.
    /// @param row The desired row index
    /// @param col The desired column index

    inline void moveToGridPosition(int row, int col)
    {
        xy.x = row;
        xy.y = col;
        setPositionWithOrigin(xy.x * size.w, xy.y * size.h);
    }
    
public:
    void draw() override
    {
        if (shouldRedraw)
        {
            cursor.clear();
            cursor.rectangle(0, 0, size.w, size.h);
            cursor.setColor(colours.foregroundColour);
        }
        
        cursor.draw(origin.x + margins.l, origin.y + margins.t);
    }
    
private:
    ofPath cursor;

private:
    UIPoint<int> xy;
    MIDISettings midi;
};

#endif

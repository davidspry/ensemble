//  Ensemble
//  Created by David Spry on 9/1/21.

#ifndef SQSUBSEQUENCE_H
#define SQSUBSEQUENCE_H

#include "SQNote.h"
#include "MIDITypes.h"
#include "Constants.h"
#include "SequenceGrid.h"

/// @brief A node representing an sequence of MIDI notes.

class SQSubsequence: public SQNode
{
public:
    SQSubsequence(unsigned int cellSize):
    SQNode(cellSize, Subsequence)
    {
        initialise();
    }

    SQSubsequence(unsigned int cellSize, const UIPoint<int>& position):
    SQNode(cellSize, position, Subsequence)
    {
        initialise();
    }

    SQSubsequence(unsigned int cellSize, const UIPoint<int>& position, MIDINote midiNote):
    SQNode(cellSize, position, Subsequence)
    {
        initialise();
        
        sequence.emplace_back(grid.getGridCellSize(), midiNote);
        
        grid.increaseNumberOfVisibleCells();
    }

public:
    /// @brief Draw the note at the current position in the subsequence to the sequencer.

    void draw() override;

    /// @brief Draw the full subsequence at the given position.
    /// @param centre The desired centre point at which to draw the sequence.

    void drawSequence(UIPoint<int> & centre);

    /// @brief Combine each note's description into one description string.

    std::string describe() noexcept override;

    /// @brief Move to the next position within the subsequence and broadcast from the current position.
    /// @param node The node that's interacting with the SQSubsequence.
    /// @param server The sequencer's MIDI server.
    /// @param gridSize The dimensions of the sequencer's grid in rows and columns.

    void interact(SQNode& node, MIDIServer& server, const UISize<int>& gridSize) noexcept override;

public:
    /// @brief Move the subsequence's cursor in the given direction.
    /// @param direction The direction in which the subsequence's cursor should be moved.

    void moveCursor(Direction direction) noexcept;
    
    /// @brief Place a note at the subsequence's cursor's current position.
    /// @param noteIndex A number in the range [0, 11] representing a note from the chromatic scale, beginning with C.
    /// @param midiSettings The MIDI settings that the note should use.

    bool placeNote(uint8_t noteIndex, MIDISettings midiSettings) noexcept;

    /// @brief Erase from the subsequence at the subsequence's cursor's current position.

    void eraseFromCurrentPosition() noexcept;
    
private:
    /// @brief Initialise the subsequence and its members.

    inline void initialise() noexcept
    {
        sequence.reserve(16);
        grid.setCurrentSequenceIndex(0);
    }
    
private:
    uint8_t index = 0;

private:
    std::vector<SQNote> sequence;

private:
    SequenceGrid grid = {8, 8};
};

#endif

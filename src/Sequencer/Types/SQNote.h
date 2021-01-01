//  Ensemble
//  Created by David Spry on 31/12/20.

#ifndef SQNOTE_H
#define SQNOTE_H

#include "SQNode.h"
#include "MIDITypes.h"

class SQNote: public SQNode
{
public:
    SQNote(unsigned int cellSize):
    SQNode(cellSize, Note)
    {
        
    }
    
    SQNote(unsigned int cellSize, const UIPoint<int>& position):
    SQNode(cellSize, position, Note)
    {
        
    }
    
    SQNote(unsigned int cellSize, const UIPoint<int>& position, MIDINote midiNote):
    SQNode(cellSize, position, Note), note(midiNote)
    {
        
    }

public:
    void draw() override
    {
        if (shouldRedraw)
        {
            auto colour = getNoteColour();
            path.setColor(colour);
        }

        GridCell::draw();
    }
    
    /// @brief Broadcast the SQNode's underlying MIDI note using the sequencer's MIDI server.
    /// @param node The node that's interacting with the SQNote.
    /// @param server The sequencer's MIDI server.
    /// @param gridSize The dimensions of the sequencer's grid in rows and columns.

    void interact(SQNode& node, MIDIServer& server, const UISize<int>& gridSize) noexcept override
    {
        server.broadcast(note);
    }
    
protected:
    /// @brief Get the ofColor corresponding to the SQNote's underlying MIDI note.

    inline ofColor getNoteColour() noexcept
    {
        // TODO: Differentiate note channels by colour (or something similar)

        return colours->secondaryForegroundColour;
    }

private:
    MIDINote note;
};

#endif

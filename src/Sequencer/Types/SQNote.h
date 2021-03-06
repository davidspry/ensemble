//  Ensemble
//  Created by David Spry on 31/12/20.

#ifndef SQNOTE_H
#define SQNOTE_H

#include "SQNode.h"
#include "MIDITypes.h"

/// @brief A node representing a MIDI note on the sequencer.

class SQNote: public SQNode
{
public:
    SQNote(unsigned int cellSize):
    SQNode(cellSize, Note)
    {
        
    }
    
    SQNote(unsigned int cellSize, MIDINote midiNote):
    SQNode(cellSize, Note), note(midiNote)
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

        SQNode::draw();
    }
    
    /// @brief Broadcast the SQNode's underlying MIDI note using the sequencer's MIDI server.
    /// @param node The node that's interacting with the SQNote.
    /// @param server The sequencer's MIDI server.
    /// @param gridSize The dimensions of the sequencer's grid in rows and columns.

    void interact(SQNode& node, MIDIServer& server, const UISize<int>& gridSize) noexcept override
    {
        if (node.getIsEnabled())
        {
            server.broadcast(note);
        }
    }
    
    inline std::string describe() noexcept override
    {
        return note.description();
    }
    
    /// @brief Modify the underlying MIDI note.
    /// @param noteIndex A number in the range [0, 11] representing a note from the chromatic scale, beginning with C.
    /// @param midiSettings The MIDI settings that the note should use.

    void modify(uint8_t noteIndex, MIDISettings settings) noexcept
    {
        note.set(noteIndex, settings);
    }
    
    /// @brief Pass the given note's notename into the given stream.
    /// @param ostream The stream that should be written to.
    /// @param note The note whose notename should be written.

    friend std::ostream & operator << (std::ostream& stream, const SQNote& note)
    {
        stream << note.note.notename();

        return stream;
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

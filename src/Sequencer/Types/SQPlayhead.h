//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef SQPLAYHEAD_H
#define SQPLAYHEAD_H

#include "SQNode.h"

/// @brief A playhead node that moves on the sequencer and broadcasts information.

class SQPlayhead: public SQNode
{
public:
    SQPlayhead(unsigned int cellSize):
    SQNode(cellSize, Playhead)
    {
        delta.set(0, 1);
    }
    
    SQPlayhead(unsigned int cellSize, const UIPoint<int>& position):
    SQNode(cellSize, position, Playhead)
    {
        delta.set(0, 1);
    }
    
    SQPlayhead(unsigned int cellSize, const UIPoint<int>& position, int deltaX, int deltaY):
    SQNode(cellSize, position, Playhead)
    {
        delta.set(deltaX, deltaY);
    }

public:
    void draw() override
    {
        const auto enabled = isEnabled  ? colours->foregroundColour : colours->secondaryForegroundColour;
        const auto colour  = isSelected ? colours->accentColour     : enabled;

        path.setColor(colour);

        SQNode::draw();
    }
    
    void interact(SQNode& node, MIDIServer& server, const UISize<int>& gridSize) noexcept override
    {
        
    }
    
    inline std::string describe() noexcept override
    {
        return "";
    }
};

#endif

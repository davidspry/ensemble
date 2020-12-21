//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef SQPLAYHEAD_H
#define SQPLAYHEAD_H

#include "SQNode.h"

/// @brief A playhead node that moves on the sequencer and broadcasts information.

class SQPlayhead: public SQNode
{
public:
    SQPlayhead():
    SQNode()
    {
        delta.set(0, 1);
    }
    
    SQPlayhead(int x, int y):
    SQNode(x, y)
    {
        delta.set(0, 1);
    }
    
    SQPlayhead(int x, int y, int deltaX, int deltaY):
    SQNode(x, y)
    {
        delta.set(deltaX, deltaY);
    }
    
public:
    /// @brief Update the node's position on the sequencer.
    /// @param gridSize The dimensions of the sequencer grid in rows and columns.

    inline void update(UISize<int>& gridSize)
    {
        xy.x = (xy.x + delta.x + gridSize.w) % gridSize.w;
        xy.y = (xy.y + delta.y + gridSize.h) % gridSize.h;
    }
};

#endif

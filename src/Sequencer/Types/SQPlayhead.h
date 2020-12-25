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
    SQNode(cellSize)
    {
        initialisePath();
        delta.set(0, 1);
    }
    
    SQPlayhead(unsigned int cellSize, UIPoint<int>& position):
    SQNode(cellSize, position)
    {
        initialisePath();
        delta.set(0, 1);
    }
    
    SQPlayhead(unsigned int cellSize, UIPoint<int>& position, int deltaX, int deltaY):
    SQNode(cellSize, position)
    {
        initialisePath();
        delta.set(deltaX, deltaY);
    }

public:
    void draw() override
    {
        GridCell::draw();
    }
};

#endif

//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef SQNODE_H
#define SQNODE_H

#include "UITypes.h"

/// @brief A node that can be placed on the Ensemble sequencer.

class SQNode
{
public:
    SQNode()
    {
        xy.set(0, 0);
    }
    
    SQNode(int x, int y)
    {
        xy.set(x, y);
    }
    
public:
    
    
public:
    /// @brief The node's position on the sequencer.

    UIPoint<int> xy;
    
    /// @brief The node's direction.
    
    UIVector<int> delta;
};

#endif

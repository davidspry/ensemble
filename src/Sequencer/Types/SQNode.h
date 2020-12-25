//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef SQNODE_H
#define SQNODE_H

#include "GridCell.h"

/// @brief A node that can be placed on the Ensemble sequencer.

class SQNode: public GridCell
{
public:
    SQNode(unsigned int cellSize):
    GridCell(cellSize)
    {
        
    }
    
    SQNode(unsigned int cellSize, UIPoint<int>& position):
    GridCell(cellSize, position)
    {
        
    }
    
public:
    /// @brief Interact with the given node.
    /// @param node The node that should be interacted with.
    /// @param gridSize The dimensions of the grid in rows and columns.

    virtual void interact(SQNode& node, const UISize<int>& gridSize) noexcept
    {
        
    }

    /// @brief Update the node's position on the sequencer.
    /// @param gridSize The dimensions of the sequencer grid in rows and columns.

    inline void update(const UISize<int>& gridSize)
    {
        xy.x = (xy.x + delta.x + gridSize.w) % gridSize.w;
        xy.y = (xy.y + delta.y + gridSize.h) % gridSize.h;
        
        moveToGridPosition(xy);
    }
    
    /// @brief Get the node's grid position as row and column indices.

    inline const UIPoint<int>& getPosition() const noexcept
    {
        return xy;
    }
    
    /// @brief Get the node's direction of movement.
    
    inline const UIVector<int>& getDirection() const noexcept
    {
        return delta;
    }
    
public:
    /// @brief The node's direction.
    
    UIVector<int> delta;
};

#endif

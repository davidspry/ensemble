//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef SQNODE_H
#define SQNODE_H

#include "Label.h"
#include "GridCell.h"
#include "MIDIServer.h"
#include "ofxRisographColours.hpp"

/// @brief Constants defining nodes that can be placed on the Ensemble sequencer.

enum  SQNodeType { Redirect, Playhead, Portal, Note, Subsequence };

/// @brief A node that can be placed on the Ensemble sequencer.

class SQNode: public GridCell
{
public:
    SQNode(unsigned int cellSize, SQNodeType type):
    GridCell(cellSize), nodeType(type)
    {
        text.setSize(cellSize, cellSize);
    }
    
    SQNode(unsigned int cellSize, const UIPoint<int>& position, SQNodeType type):
    GridCell(cellSize, position), nodeType(type)
    {
        text.setSize(cellSize, cellSize);
    }
    
public:
    /// @brief Draw the node at its position on the sequencer.

    void draw() override
    {
        const int x = origin.x + margins.l + screenPosition.x;
        const int y = origin.y + margins.t + screenPosition.y;

        if (shouldRedraw)
        {
            path.clear();
            path.circle(centre.x, centre.y, static_cast<int>(0.40f * size.w));
            shouldRedraw = false;
        }

        path.draw(x, y);
    }
    
    /// @brief Interact with the given node.
    /// @param node The node that should be interacted with.
    /// @param server The sequencer's MIDI server.
    /// @param gridSize The dimensions of the grid in rows and columns.

    virtual void interact(SQNode& node, MIDIServer& server, const UISize<int>& gridSize) noexcept = 0;

    /// @brief Provide a textual description of the node.
    
    virtual std::string describe() noexcept = 0;

    /// @brief Update the node's position on the sequencer.
    /// @param gridSize The dimensions of the sequencer grid in rows and columns.

    inline void update(const UISize<int>& gridSize)
    {
        xy.x = (xy.x + delta.x + gridSize.w) % gridSize.w;
        xy.y = (xy.y + delta.y + gridSize.h) % gridSize.h;
        
        moveToGridPosition(xy);
    }
    
    /// @brief Get the node's direction of movement.
    
    inline const UIVector<int>& getDirection() const noexcept
    {
        return delta;
    }
    
public:
    /// @brief The node's direction.
    
    UIVector<int> delta;
    
    /// @brief The node's type.

    SQNodeType nodeType;
    
protected:
    Label text;
};

#endif

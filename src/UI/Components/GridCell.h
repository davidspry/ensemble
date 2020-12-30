//  Ensemble
//  Created by David Spry on 24/12/20.

#ifndef GRIDCELL_H
#define GRIDCELL_H

#include "UIPoint.h"
#include "Label.h"

/// @brief A component whose position is defined in grid cell indices.

class GridCell: public UIComponent
{
public:
    GridCell(unsigned int cellSize):
    UIComponent()
    {
        setSize(cellSize, cellSize);
        moveToGridPosition(0, 0);
        initialisePath();
        
        text.setSize(cellSize, cellSize);
    }
    
    GridCell(unsigned int cellSize, UIPoint<int> position):
    UIComponent()
    {
        setSize(cellSize, cellSize);
        moveToGridPosition(position);
        initialisePath();
        
        text.setSize(cellSize, cellSize);
    }
    
protected:
    /// @brief Initialise the grid cell's path for drawing.

    virtual inline void initialisePath()
    {
        path.setFilled(true);
        path.setStrokeWidth(0.0f);
        path.setCircleResolution(256);
        path.setColor(colours->foregroundColour);
        path.clear();
    }

public:
    /// @brief Move the cell to the given position on the grid.
    /// @param position The desired position as row and column indices.

    inline void moveToGridPosition(UIPoint<int> position)
    {
        moveToGridPosition(position.y, position.x);
    }
    
    /// @brief Move the cell to the given position on the grid.
    /// @param row The desired row index
    /// @param col The desired column index

    inline void moveToGridPosition(int row, int col)
    {
        xy.x = col;
        xy.y = row;
        screenPosition.x = xy.x * size.w;
        screenPosition.y = xy.y * size.h;
    }
    
    /// @brief Get the cell's position as row and column indices.

    inline const UIPoint<int>& getGridPosition() const noexcept
    {
        return xy;
    }

    void draw() override
    {
        if (shouldRedraw)
        {
            path.clear();
            path.circle(0.5f * size.w, 0.5f * size.h, 0.4f * size.w);
            shouldRedraw = false;
        }
        
        path.draw(origin.x + margins.l + screenPosition.x,
                  origin.y + margins.t + screenPosition.y);
    }

protected:
    Label  text;
    UIPath path;

public:
    UIPoint<int> xy;
    UIPoint<int> screenPosition;
};

#endif

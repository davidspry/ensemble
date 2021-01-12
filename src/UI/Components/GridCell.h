//  Ensemble
//  Created by David Spry on 24/12/20.

#ifndef GRIDCELL_H
#define GRIDCELL_H

#include "UITypes.h"

/// @brief A component whose position is defined in grid indices.

class GridCell: public UIComponent
{
public:
    GridCell(unsigned int cellSize):
    UIComponent()
    {
        setSize(cellSize, cellSize);
        moveToGridPosition(0, 0);
        initialisePath();
    }
    
    GridCell(unsigned int cellSize, UIPoint<int> position):
    UIComponent()
    {
        setSize(cellSize, cellSize);
        moveToGridPosition(position);
        initialisePath();
    }
    
protected:
    /// @brief Initialise the grid cell's path for drawing.

    virtual inline void initialisePath()
    {
        path.setFilled(true);
        path.setCircleResolution(128);
        path.setColor(colours->foregroundColour);
        path.clear();
    }

public:
    /// @brief Move the cell in the given direction on the grid.
    /// @param direction The direction in which the cell should be moved.
    /// @param gridSize The dimensions of the grid in rows and columns.

    inline void move(Direction& direction, const UISize<int>& gridSize)
    {
        const int dy = -static_cast<int>(direction == Direction::N)
                     +  static_cast<int>(direction == Direction::S);
        const int dx = -static_cast<int>(direction == Direction::W)
                     +  static_cast<int>(direction == Direction::E);

        xy.x = (xy.x + dx + gridSize.w) % gridSize.w;
        xy.y = (xy.y + dy + gridSize.h) % gridSize.h;

        moveToGridPosition(xy);
    }
    
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
    
    /// @brief Get the cell's screen position relative to the origin point and margins.
    
    inline const UIPoint<int>& getScreenPosition() const noexcept
    {
        return screenPosition;
    }
    
    /// @brief Set the cell's fill colour.
    /// @param colour The desired fill colour.

    inline void setCellColour(const ofColor & colour) noexcept
    {
        path.setColor(colour);
    }

    void draw() override
    {
        const int x = origin.x + margins.l + screenPosition.x;
        const int y = origin.y + margins.t + screenPosition.y;

        if (shouldRedraw)
        {
            path.clear();
            path.rectangle(0, 0, size.w, size.h);
        }

        path.draw(x, y);
    }

protected:
    UIPath path;

public:
    UIPoint<int> xy;
    UIPoint<int> screenPosition;
};

#endif

//  Ensemble
//  Created by David Spry on 10/1/21.

#ifndef SEQUENCEGRID_H
#define SEQUENCEGRID_H

#include "Grid.h"
#include "Constants.h"

/// @brief A sequence of squares that conforms to a grid shape.

class SequenceGrid: public Grid
{
public:
    /// @brief Construct a sequence grid with the given dimensions.
    /// @param rows The maximum number of rows.
    /// @param cols The maximum number of columns.

    SequenceGrid(int rows, int cols):
    Grid(), cursor(SPACE)
    {
        initialise(rows, cols);
        setNumberOfVisibleCells(1);
    }

private:
    /// @brief Initialise the grid with the given dimensions.
    /// @param rows The maximum number of rows.
    /// @param cols The maximum number of columns.

    inline void initialise(int rows, int cols) noexcept
    {
        shape.set(cols, rows);
        setSize(shape.w * SPACE, shape.h * SPACE);
    }

public:
    void draw() override
    {
        const int x = origin.x + margins.l;
        const int y = origin.y + margins.t;
        
        ofPushMatrix();
        ofTranslate(x, y);
        
        if (shouldRedraw)
        {
            grid.clear();
            shouldRedraw = false;
            
            const uint & H = visibleShape.h;
            drawRows(0, H, shape.w);
            drawRows(H, 1, visibleShape.w);

            grid.setColor(colours->secondaryForegroundColour);
        }

        cursor.draw();
        grid.draw();
        ofPopMatrix();
    }
    
    /// @brief Draw the given number of rows with the given number of cells.
    /// @param row The index of the first row to be drawn.
    /// @param rows The number of rows to draw.
    /// @param cols The number of columns in each row.

    void drawRows(unsigned int row, unsigned int rows, unsigned int cols) noexcept
    {
        if (rows == 0 || cols == 0) return;

        const int l = margins.l;
        const int t = margins.t + row  * SPACE;
        const int r = margins.l + cols * SPACE;
        const int b = margins.t + rows * SPACE + row * SPACE;

        for (size_t y = row; y < rows + 1; ++y)
        {
            grid.moveTo(l - 1, t + y * SPACE);
            grid.lineTo(r + 1, t + y * SPACE);
        }
        
        for (size_t x = 0; x < cols + 1; ++x)
        {
            grid.moveTo(l + x * SPACE, t - 1);
            grid.lineTo(l + x * SPACE, b + 1);
        }
    }

    /// @brief Set the number of cells that should be drawn.
    /// @param cells The number of cells that should be drawn.

    void setNumberOfVisibleCells(int cells) noexcept
    {
        const unsigned int visibleCells = std::max(1, cells);
        const unsigned int rows = visibleCells / shape.w;
        const unsigned int cols = visibleCells % shape.w;

        if (rows == visibleShape.h &&
            cols == visibleShape.w)
        {
            return;
        }

        visibleShape.h = rows;
        visibleShape.w = cols;
        setShouldRedraw();
    }

    /// @brief Increase the number of visible cells by one.

    void increaseNumberOfVisibleCells() noexcept
    {
        const int visibleCells = visibleShape.h * shape.w + visibleShape.w;

        setNumberOfVisibleCells(visibleCells + 1);
    }
    
    /// @brief Decrease the number of visible cells by one.

    void decreaseNumberOfVisibleCells() noexcept
    {
        const int visibleCells = visibleShape.h * shape.w + visibleShape.w;

        setNumberOfVisibleCells(visibleCells - 1);
    }
    
    /// @brief Move the cursor on the grid.

    void moveCursor(Direction direction) noexcept
    {
        const int col = cursor.xy.x;
        const int row = cursor.xy.y;

        if (col  < visibleShape.w)
        if (row == visibleShape.h)
             return cursor.move(direction, {visibleShape.w, visibleShape.h + 1});
        else return cursor.move(direction, {shape.w, visibleShape.h + 1});
        else return cursor.move(direction, {shape.w, visibleShape.h + 0});
    }

private:
    /// @brief The number of visible complete rows and partial rows.

    UISize<int> visibleShape;
    
    /// @brief A cursor for navigating the grid.

    GridCell cursor;
};

#endif

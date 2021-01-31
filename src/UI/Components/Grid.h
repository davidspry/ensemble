//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef GRID_H
#define GRID_H

#include "Ensemble.h"

/// @brief A grid of squares.

class Grid: public UIComponent
{
public:
    Grid():
    UIComponent(), SPACE(20)
    {
        grid.setFilled(false);
        grid.setStrokeWidth(2.0f);
        updateGridDimensions();
    }

    void draw() override
    {
        if (shouldRedraw)
        {
            grid.clear();
            shouldRedraw = false;

            const int t = margins.t;
            const int l = margins.l;
            const int r = margins.l + shape.w * SPACE;
            const int b = margins.t + shape.h * SPACE;

            for (size_t y = 0; y < shape.h + 1; ++y)
            {
                grid.moveTo(l - 1, t + y * SPACE);
                grid.lineTo(r + 1, t + y * SPACE);
            }

            for (size_t x = 0; x < shape.w + 1; ++x)
            {
                grid.moveTo(l + x * SPACE, t - 1);
                grid.lineTo(l + x * SPACE, b + 1);
            }

            grid.setColor(colours->gridColour);
        }

        grid.draw(origin.x, origin.y);
    }
    
    void setSize(const float width, const float height) override
    {
        UIComponent::setSize(width, height);
        
        updateGridDimensions();
    }
    
    void setSizeFromCentre(const float width, const float height) override
    {
        UIComponent::setSizeFromCentre(width, height);

        updateGridDimensions();
    }

    void setMargins(const int top, const int left, const int right, const int bottom) override
    {
        UIComponent::setMargins(top, left, right, bottom);

        updateGridDimensions();
    }
    
    /// @brief Compute the position of a grid cell in pixels.
    /// @note  The position of the centre of the grid cell is returned.
    /// @param row The cell's row index, beginning from 0.
    /// @param col The cell's column index, beginning from 0.
    /// @throw An exception will be thrown in the case where the given indices are out of range.

    const UIPoint<int> positionOfCell(uint row, uint col) const noexcept(false)
    {
        if (!(row < shape.h && col < shape.w))
        {
            constexpr auto error = "The given cell position is out of range";
            throw std::out_of_range(error);
        }

        const int x = (float) SPACE * ((float) row + 0.5f);
        const int y = (float) SPACE * ((float) col + 0.5f);

        return {x, y};
    }

    /// @brief Return the size of the grid's cells in pixels.

    inline const int getGridCellSize() const noexcept
    {
        return static_cast<int>(SPACE);
    }
    
    /// @brief Return the grid's dimensions in rows and columns.

    inline const UISize<int>& getGridDimensions() const noexcept
    {
        return shape;
    }
    
protected:
    /// @brief Update the grid's dimensions using its component size, margins, and cell spacing.

    inline void updateGridDimensions()
    {
        const int W = (size.w - margins.l - margins.r) / SPACE;
        const int H = (size.h - margins.t - margins.b) / SPACE;
        shape.set(W, H);
    }

protected:
    ofPath grid;
    unsigned int SPACE;
    UISize <int> shape;
};

#endif

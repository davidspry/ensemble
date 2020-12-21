//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef GRID_H
#define GRID_H

#include "Ensemble.h"

class Grid: public UIComponent
{
public:
    Grid():
    UIComponent(), SPACE(25)
    {
        grid.setFilled(false);
        grid.setStrokeWidth(1.5f);
        grid.setColor(15);

        updateGridDimensions();
    }

    void draw() override
    {
        if (shouldRedraw)
        {
            grid.clear();
            shouldRedraw = false;

            const int R = W * SPACE;
            const int B = H * SPACE;

            for (size_t y = 0; y < H + 1; ++y)
            {
                grid.moveTo(0 - 1, y * SPACE);
                grid.lineTo(R + 1, y * SPACE);
            }

            for (size_t x = 0; x < W + 1; ++x)
            {
                grid.moveTo(x * SPACE, 0 - 1);
                grid.lineTo(x * SPACE, B + 1);
            }
            
            grid.setColor(colours.foregroundColour);
        }

        grid.draw(origin.x + margins.l, origin.y + margins.t);
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

    void setMargins(UIMargins<int>& margins) override
    {
        this->setMargins(margins.t, margins.l, margins.r, margins.b);
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
        if (!(row < H && col < W))
        {
            constexpr auto error = "The given cell position is out of range";
            throw std::out_of_range(error);
        }

        const int x = (float) SPACE * ((float) row + 0.5f);
        const int y = (float) SPACE * ((float) col + 0.5f);

        return {x, y};
    }

    /// @brief Return the size of the grid's cells in pixels.

    const int getGridCellSize() const noexcept
    {
        return static_cast<int>(SPACE);
    }
    
    /// @brief Return the grid's dimensions in rows and columns.

    const UISize<int>& getGridDimensions() const noexcept
    {
        return shape;
    }
    
protected:
    /// @brief Update the grid's dimensions using its component size, margins, and cell spacing.

    inline void updateGridDimensions()
    {
        W = (size.w - margins.l - margins.r) / SPACE;
        H = (size.h - margins.t - margins.b) / SPACE;
        shape.set(W, H);
    }

private:
    ofPath grid;
    
private:
    unsigned int W;
    unsigned int H;
    unsigned int SPACE;
    UISize <int> shape;
};

#endif

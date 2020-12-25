//  Ensemble
//  Created by David Spry on 24/12/20.

#ifndef DOTGRID_H
#define DOTGRID_H

#include "Ensemble.h"

class DotGrid: public UIComponent
{
public:
    DotGrid():
    UIComponent(), SPACE(15)
    {
        grid.setFilled(true);
        grid.setStrokeWidth(0.0f);
        updateGridDimensions();
    }

    void draw() override
    {
        if (shouldRedraw)
        {
            grid.clear();
            shouldRedraw = false;

            for (size_t y = 0; y < H; ++y)
            {
                grid.moveTo(0, margins.t + y * SPACE);
                for (size_t x = 0; x < W; ++x)
                    grid.circle(margins.l + SPACE * (x + 0.5f),
                                margins.t + SPACE * (y + 0.5f), 1.0f);
            }

            grid.setColor(colours.secondaryForegroundColour);
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

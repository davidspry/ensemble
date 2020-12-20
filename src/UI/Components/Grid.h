//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef GRID_H
#define GRID_H

#include "Ensemble.h"

class Grid: public UIComponent
{
public:
    Grid(): UIComponent()
    {
        grid.setFilled(false);
        grid.setStrokeWidth(2.0f);
        grid.setColor(15);

        SPACE = 20;
        W = size.w / SPACE;
        H = size.h / SPACE;
    }

    void draw() override
    {
        if (shouldRedraw)
        {
            grid.clear();
            shouldRedraw = false;
            grid.setColor(foregroundColour);

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
        }

        grid.draw(origin.x + margins.l, origin.y + margins.t);
    }
    
    void setSize(const float width, const float height) override
    {
        UIComponent::setSize(width, height);

        W = static_cast<int>(1.0f / (float) SPACE * width);
        H = static_cast<int>(1.0f / (float) SPACE * height);
        
        setMargins(margins);
    }
    
    void setSizeFromCentre(const float width, const float height) override
    {
        UIComponent::setSizeFromCentre(width, height);

        W = static_cast<int>(1.0f / (float) SPACE * width);
        H = static_cast<int>(1.0f / (float) SPACE * height);
        
        setMargins(margins);
    }

    void setMargins(UIMargins<int>& margins) override
    {
        this->setMargins(margins.t, margins.l, margins.r, margins.b);
    }
    
    void setMargins(const int top, const int left, const int right, const int bottom) override
    {
        UIComponent::setMargins(top, left, right, bottom);

        W = (size.w - margins.l - margins.r) / SPACE;
        H = (size.h - margins.t - margins.b) / SPACE;
    }

    const UIPoint<int> locationOfCell(uint row, uint col) const noexcept(false)
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

private:
    ofPath grid;
    
private:
    unsigned int W;
    unsigned int H;
    unsigned int SPACE;
};

#endif

//  Ensemble
//  Created by David Spry on 24/12/20.

#ifndef DOTGRID_H
#define DOTGRID_H

#include "Ensemble.h"
#include "Grid.h"

/// @brief A grid of dots.

class DotGrid: public Grid
{
public:
    DotGrid():
    Grid()
    {
        SPACE = 15;
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

            for (size_t y = 0; y < shape.h; ++y)
            {
                grid.moveTo(0, margins.t + y * SPACE);
                for (size_t x = 0; x < shape.w; ++x)
                    grid.circle(margins.l + SPACE * (x + 0.5f),
                                margins.t + SPACE * (y + 0.5f), 1.0f);
            }

            grid.setColor(colours->secondaryForegroundColour);
        }

        grid.draw(origin.x, origin.y);
    }
};

#endif

//  Ensemble
//  Created by David Spry on 6/1/21.

#ifndef SEQUENCERWINDOW_HPP
#define SEQUENCERWINDOW_HPP

#include "Ensemble.h"

/// @brief A window containing the Ensemble sequencer grid.

class SequencerWindow: public UIWindow, public Commandable
{
public:
    SequencerWindow();
    SequencerWindow(int x, int y, int width, int height);

public:
    /// @brief Indicate whether the window contains the given screen position.
    /// @param x The x-coordinate of the screen position to check.
    /// @param y The y-coordinate of the screen position to check.

    inline bool containsPoint(int x, int y) noexcept override
    {
        return x >= (origin.x + margins.l)
            && x <= (origin.x + margins.l + size.w)
            && y >= (origin.y + margins.t)
            && y <= (origin.y + margins.t + size.h);
    }
    
public:
    
};

#endif

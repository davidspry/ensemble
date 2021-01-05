//  Ensemble
//  Created by David Spry on 6/1/21.

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Ensemble.h"

/// @brief A window containing an arrangement of labels describing the state of the Ensemble sequencer.

class InformationWindow: public UIWindow, public Commandable
{
public:
    InformationWindow();

    InformationWindow(int x, int y, int width, int height);

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

private:
    
    
private:
    Label position;
    Label polyphony;
    Label midiInPort;
    Label midiOutPort;
    Label description;
    Label cursorMidiSettings;
};

#endif

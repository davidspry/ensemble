//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef CLOCKLISTENER_H
#define CLOCKLISTENER_H

/// @brief A class to be subclassed by classes that should be notified when a clock ticks.

class ClockListener
{
public:

    /// @brief The callback that's executed when a clock ticks.

    virtual void tick() = 0;
};

#endif

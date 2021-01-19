//  Ensemble
//  Created by David Spry on 19/1/21.

#include "Clock.h"

Clock::Clock()
{
    connectToClockEngines();
    useSampleClock();
}

void Clock::connect(ClockListener* listener)
{
    const auto target = std::find(listeners.begin(), listeners.end(), listener);
    const auto exists = target != listeners.end();
    
    if (!exists)
        listeners.push_back(listener);
}

void Clock::disconnect(ClockListener* listener)
{
    auto & list = listeners;

    list.erase(std::remove(list.begin(), list.end(), listener), list.end());
}

void Clock::useSampleClock()
{
    if (usingSampleClock)
        return;
    
    const bool isTicking = midiClock.clockIsTicking();
    
    midiClock.setClockShouldTick(false);
    sampleClock.setClockShouldTick(isTicking);
    
    usingSampleClock = true;
}

void Clock::useMidiClock()
{
    if (!usingSampleClock)
        return;
    
    const bool isTicking = midiClock.clockIsTicking();

    sampleClock.setClockShouldTick(false);
    midiClock.setClockShouldTick(isTicking);
    
    usingSampleClock = false;
}

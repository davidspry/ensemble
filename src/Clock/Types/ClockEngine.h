//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef CLOCKENGINE_H
#define CLOCKENGINE_H

#include "ofMain.h"
#include "ClockListener.h"

class ClockEngine
{
public:
    ClockEngine()
    {
        setTempo(120);
        setSubdivision(4);
    }
    
    virtual ~ClockEngine()
    {
        
    }

public:

    /// @brief Connect a new listener, who will subsequently receive notifications when the clock ticks.
    /// @param listener The listener who should be connected.
    
    void connect(ClockListener* listener)
    {
        const auto target = std::find(listeners.begin(), listeners.end(), listener);
        const auto exists = target != listeners.end();
        
        if (!exists)
            listeners.push_back(listener);
    }
    
    /// @brief Disconnect an existing listener from the clock.
    /// @param listener The listener who should be disconnected.

    void disconnect(ClockListener* listener)
    {
        auto & list = listeners;

        list.erase(std::remove(list.begin(), list.end(), listener), list.end());
    }
    
    /// @brief Get the `ticking` state of the clock.

    inline bool clockIsTicking() const noexcept
    {
        return ticking;
    }
    
    /// @brief Toggle the clock's ticking state.

    virtual inline void toggleClock() noexcept
    {
        ticking = !ticking;
    }
    
    /// @brief Set the clock's ticking state explicitly.
    /// @param shouldTick Whether the clock should tick or not.

    virtual inline void setClockShouldTick(bool shouldTick) noexcept
    {
        ticking = shouldTick;
    }
    
    /// @brief Get the clock's tempo in beats per minute.

    virtual inline int getTempo() const noexcept
    {
        return tempo;
    }
    
    /// @brief Get the clock's time subdivision.

    virtual inline int getSubdivision() const noexcept
    {
        return subdivision;
    }
    
    /// @brief Set the clock's tempo in beats per minute.
    /// @note  This function does not apply to external clocks.
    /// @param beatsPerMinute The desired tempo of the clock.

    virtual inline void setTempo(unsigned int beatsPerMinute) noexcept
    {
        if (tempo == beatsPerMinute)
            return;
        
        tempo = std::max(beatsPerMinute, (unsigned int) ClockEngine::MINIMUM_TEMPO);
        tempo = std::min(tempo,          (unsigned int) ClockEngine::MAXIMUM_TEMPO);
    }

    /// @brief Set the clock's time subdivision.
    /// @note  This function applies to both internal and external clocks.
    /// @param ticksPerBeat The desired time subdivision.

    virtual inline void setSubdivision(unsigned int ticksPerBeat) noexcept
    {
        if (subdivision == ticksPerBeat)
            return;

        subdivision = std::max(ticksPerBeat, (unsigned int) ClockEngine::MINIMUM_SUBDIVISION);
        subdivision = std::min(subdivision,  (unsigned int) ClockEngine::MAXIMUM_SUBDIVISION);
    }
    
protected:

    /// @brief Broadcast a notification to all connected listeners.

    inline void tick()
    {
        for (ClockListener* listener : listeners)
        {
            listener->tick();
        }
    }

protected:
    bool ticking;
    
protected:
    unsigned int tempo;
    unsigned int subdivision;
    
/// Consider moving subdivisions into SQPlayhead:
///   - i.e., Playhead moves once every `n` ticks
///   - This allows for more complex rhythms
/// Alternatively duplicate subdivisions in SQPlayhead and retain a global subdivision.

protected:
    constexpr static unsigned int MINIMUM_TEMPO = 5;
    constexpr static unsigned int MAXIMUM_TEMPO = 300;
    constexpr static unsigned int MINIMUM_SUBDIVISION = 1;
    constexpr static unsigned int MAXIMUM_SUBDIVISION = 7;

private:
    std::vector<ClockListener*> listeners;
};

#endif

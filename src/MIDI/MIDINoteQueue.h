//  Ensemble
//  Created by David Spry on 9/1/21.

#ifndef MIDINOTEQUEUE_H
#define MIDINOTEQUEUE_H

#include "MIDINote.h"
#include <algorithm>
#include <vector>

/// @brief A priority queue of MIDI notes that orders each note by its duration.

template <unsigned int Capacity>
class MIDINoteQueue
{
public:
    MIDINoteQueue()
    {
        
    }

public:
    /// @brief Add the given MIDI note to the queue, provided the queue is not full.
    /// @param note The MIDI note to be added to tbe underlying queue.

    bool push(const MIDINote & note) noexcept
    {
        if (full())
        {
            return false;
        }
        
        queue.push_back(note);

        std::push_heap(queue.begin(), queue.end(), compare);
        
        return true;
    }

    /// @brief  Remove the note with the least duration from the queue.
    /// @return The MIDI note with the least duration in the queue.
    
    const MIDINote pop() noexcept
    {
        std::pop_heap(queue.begin(), queue.end(), compare);

        const MIDINote note = queue.back();

        queue.pop_back();

        return note;
    }

    /// @brief Sustain all notes by one time unit, reducing the duration value of each note by one.

    inline void sustain() noexcept
    {
        for (auto & note : queue)
        {
            note.midi.duration = note.midi.duration - 1;
        }
    }

public:
    /// @brief Indicate whether the underlying queue contains expired notes or not.
    
    inline bool containsExpiredNotes() noexcept
    {
        return isNotEmpty() && queue.front().midi.duration < 1;
    }
    
    /// @brief Indicate whether the underlying queue is full or not.

    inline bool full() noexcept
    {
        return queue.size() >= Capacity;
    }

    /// @brief Indicate whether the underlying queue is empty or not.
    
    inline bool empty() noexcept
    {
        return queue.empty();
    }
    
    /// @brief Indicate whether the underlying queue contains elements or not.
    
    inline bool isNotEmpty() noexcept
    {
        return !(queue.empty());
    }

private:
    using M = const MIDINote &;

    /// @brief A custom comparator for MIDI note durations.

    std::function<bool(M, M)> compare = [](M x, M y)
    {
        return x.midi.duration > y.midi.duration;
    };

private:
    std::vector<MIDINote> queue;
};

#endif

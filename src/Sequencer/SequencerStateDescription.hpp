//  Ensemble
//  Created by David Spry on 19/1/21.

#ifndef SEQUENCERSTATEDESCRIPTION_HPP
#define SEQUENCERSTATEDESCRIPTION_HPP

#include <string>
#include <cstdint>
#include "UIPoint.h"

/// @brief Data that can be used to derive a textual description of the Ensemble sequencer's state.

typedef struct SequencerStateDescription
{
    /// @brief The number of notes being output currently.

    uint8_t midiPolyphony;

    /// @brief The port number of the MIDI server's input port (where clock ticks are received).
    
    uint8_t midiPortNumberIn;
    
    /// @brief The port number of the MIDI server's output port (where notes are broadcast).
    
    uint8_t midiPortNumberOut;
    
    /// @brief A textual description of the MIDI server's input port.
    
    std::string midiPortDescriptionIn;
    
    /// @brief A textual description of the MIDI server's output port.
    
    std::string midiPortDescriptionOut;
    
    /// @brief The sequencer cursor's MIDI octave.
    
    uint8_t cursorOctave;
    
    /// @brief The sequencer cursor's MIDI channel.
    
    uint8_t cursorChannel;
    
    /// @brief The sequencer cursor's MIDI velocity.
    
    uint8_t cursorVelocity;
    
    /// @brief The sequencer's cursor's grid position.

    UIPoint<uint8_t> cursorGridPosition;
    
    /// @brief A textual description of the sequencer's contents at the sequencer's cursor's current position.
    
    std::string cursorHoverDescription;
    
    /// @brief A flag indicating whether the state contains updated data (that has yet to be read) or not.

    bool containsUpdatedData;
    
    /// @brief Set a flag to indicate that the state description contains new data.

    inline void setContainsNewData()
    {
        containsUpdatedData = true;
    }
    
    /// @brief Set a flag to indicate that the state description's most recently updated data has been consumed.

    inline void setDataWasConsumed()
    {
        containsUpdatedData = false;
    }

} SequencerStateDescription;

#endif

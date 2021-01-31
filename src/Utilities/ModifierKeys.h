//  Ensemble
//  Created by David Spry on 31/1/21.

#ifndef MODIFIERKEYS_H
#define MODIFIERKEYS_H

#include <array>
#include "KeyCodes.h"

/// @brief Constants defining the available modifier keys.

enum ModifierKey { MK_Shift = 0, MK_Control = 1, MK_Option = 2, MK_Command = 3 };

/// @brief A class for managing the state of modifier keyboard keys.

class ModifierKeys
{
public:
    ModifierKeys()
    {
        
    }
    
public:
    /// @brief Press a modifier key.
    /// @param keyCode The code of the modifier key.
    
    void keyPressed(int keyCode) noexcept
    {
        switch (keyCode)
        {
            case K_Shift:   { keyIsPressed[MK_Shift]   = true; return; }
            case K_Control: { keyIsPressed[MK_Control] = true; return; }
            case K_Option:  { keyIsPressed[MK_Option]  = true; return; }
            case K_Command: { keyIsPressed[MK_Command] = true; return; }
            default: return;
        }
    }
    
    /// @brief Release a modifier key.
    /// @param keyCode The code of the modifier key.
    
    void keyReleased(int keyCode) noexcept
    {
        switch (keyCode)
        {
            case K_Shift:   { keyIsPressed[MK_Shift]   = false; return; }
            case K_Control: { keyIsPressed[MK_Control] = false; return; }
            case K_Option:  { keyIsPressed[MK_Option]  = false; return; }
            case K_Command: { keyIsPressed[MK_Command] = false; return; }
            default: return;
        }
    }
    
    /// @brief Determine whether the given modifier key is pressed.
    /// @param keyCode The code of the modifier key.

    bool isKeyPressed(int keyCode) const noexcept
    {
        switch (keyCode)
        {
            case K_Shift:   { return keyIsPressed[MK_Shift];   }
            case K_Control: { return keyIsPressed[MK_Control]; }
            case K_Option:  { return keyIsPressed[MK_Option];  }
            case K_Command: { return keyIsPressed[MK_Command]; }
            default: return false;
        }
    }
    
private:
    /// @brief The state of the modifier keys: Shift, Control, Option, Command.
    
    std::array<bool, 4> keyIsPressed;
};

#endif

//  Ensemble
//  Created by David Spry on 6/1/21.

#ifndef COMMANDABLE_H
#define COMMANDABLE_H

/// @brief A class that can receive commands from input devices.
/// @note  A Commandable class must define the function `containsPoint`.

class Commandable
{
public:
// MARK: - Keyboard

    /// @brief The callback that's executed when a keyboard key is pressed.
    /// @param key The ASCII key code.

    virtual void keyPressed (int key)
    {
        
    }
    
    /// @brief The callback that's executed when a pressed key is released.
    /// @param key The ASCII key code.

    virtual void keyReleased(int key)
    {
        
    }

public:
// MARK: - Mouse
    
    /// @brief Indicate whether the given screen position is contained within the Commandable region.
    /// @param x The x-coordinate of the screen position to check.
    /// @param y The y-coordinate of the screen position to check.

    virtual bool containsPoint(int x, int y) noexcept = 0;
    
    /// @brief The callback that's executed when the mouse enters the Commandable region.
    /// @param x The x-coordinate of the mouse cursor's screen position.
    /// @param y The y-coordinate of the mouse cursor's screen position.
    
    virtual void mouseEntered(int x, int y)
    {
        
    }
    
    /// @brief The callback that's executed when the mouse exits the Commandable window.
    /// @param x The x-coordinate of the mouse cursor's screen position.
    /// @param y The y-coordinate of the mouse cursor's screen position.
    
    virtual void mouseExited(int x, int y)
    {
        
    }
    
    /// @brief The callback that's executed when the mouse is moved within the Commandable window.
    /// @param x The x-coordinate of the mouse cursor's screen position.
    /// @param y The y-coordinate of the mouse cursor's screen position.

    virtual void mouseMoved(int x, int y)
    {
        
    }
    
    /// @brief The callback that's executed when the mouse is pressed within the Commandable window.
    /// @param x The x-coordinate of the mouse cursor's screen position.
    /// @param y The y-coordinate of the mouse cursor's screen position.
    /// @param buttonIndex A number representing the index of the pressed mouse button.
    
    virtual void mousePressed (int x, int y, int buttonIndex)
    {
        
    }
    
    /// @brief The callback that's executed when the mouse is released within the Commandable window.
    /// @param x The x-coordinate of the mouse cursor's screen position.
    /// @param y The y-coordinate of the mouse cursor's screen position.
    /// @param buttonIndex A number representing the index of the released mouse button.
    
    virtual void mouseReleased(int x, int y, int buttonIndex)
    {
        
    }
    
    /// @brief The callback that's executed when the mouse is dragged within the Commandable window.
    /// @param x The x-coordinate of the mouse cursor's screen position.
    /// @param y The y-coordinate of the mouse cursor's screen position.
    /// @param buttonIndex A number representing the index of the pressed mouse button.

    virtual void mouseDragged (int x, int y, int buttonIndex)
    {
        
    }
};

#endif

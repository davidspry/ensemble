//  Ensemble
//  Created by David Spry on 6/1/21.

#ifndef SEQUENCERWINDOW_HPP
#define SEQUENCERWINDOW_HPP

#include "Ensemble.h"
#include "Sequencer.hpp"

/// @brief A window containing the Ensemble sequencer grid.

class SequencerWindow: public UIWindow, public Commandable
{
public:
    SequencerWindow();
    
    SequencerWindow(int x, int y, int width, int height);
    
public:
    /// @brief Set the size of the sequencer window and layout its child components.
    /// @param width The desired width of the sequencer window.
    /// @param height The desired height of the sequencer window.
    
    void setSize(const float width, const float height) override;

    /// @brief Set the size of the sequencer window while retaining its centre point, then layout its child components.
    /// @param width The desired width of the sequencer window.
    /// @param height The desired height of the sequencer window.

    void setSizeFromCentre(const float width, const float height) override;
    
    /// @brief Set the component's position to the given origin point.
    /// @param x The x-coordinate of the desired origin point.
    /// @param y The y-coordinate of the desired origin point.
    
    void setPositionWithOrigin(const int x, const int y) override;
    
    /// @brief Set the component's position using the given centre point.
    /// @param x The x-coordinate of the desired centre point.
    /// @param y The y-coordinate of the desired centre point.

    void setPositionWithCentre(const int x, const int y) override;
    
    /// @brief Get the component's margins.

    [[nodiscard]] const UIMargins<int>& getMargins() const noexcept override;
    
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
    void keyPressed(int key) noexcept override;
    void mousePressed(int x, int y, int buttonIndex) noexcept override;
    void mouseDragged(int x, int y, int buttonIndex) noexcept override;

private:
    Sequencer sequencer;
};

#endif

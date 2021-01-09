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
    void draw() override;
    
    /// @brief Set the size of the sequencer window and layout its child components.
    /// @param width The desired width of the sequencer window.
    /// @param height The desired height of the sequencer window.
    
    void setSize(const float width, const float height) override;

    /// @brief Set the size of the sequencer window while retaining its centre point, then layout its child components.
    /// @param width The desired width of the sequencer window.
    /// @param height The desired height of the sequencer window.

    void setSizeFromCentre(const float width, const float height) override;
    
    /// \brief Set the component's position to the given origin point.
    /// \param x The x-coordinate of the desired origin point.
    /// \param y The y-coordinate of the desired origin point.
    
    void setPositionWithOrigin(const int x, const int y) override;
    
    /// \brief Set the component's position using the given centre point.
    /// \param x The x-coordinate of the desired centre point.
    /// \param y The y-coordinate of the desired centre point.

    void setPositionWithCentre(const int x, const int y) override;
    
    /// @brief Indicate whether the window contains the given screen position.
    /// @param x The x-coordinate of the screen position to check.
    /// @param y The y-coordinate of the screen position to check.
    
    inline bool containsPoint(int x, int y) noexcept override
    {
        return x >= (origin.x + margins.l)
            && x <= (origin.x - margins.r + size.w)
            && y >= (origin.y + margins.t)
            && y <= (origin.y - margins.b + size.h);
    }

private:
    /// @brief Add all labels as child components of the window.

    inline void initialiseLabels() noexcept
    {
        addChildComponent(&position);
        addChildComponent(&polyphony);
        addChildComponent(&midiInPort);
        addChildComponent(&midiOutPort);
        addChildComponent(&description);
        addChildComponent(&cursorMidiSettings);
    }
    
    /// @brief Layout the position of each child component.

    void layoutChildComponents() noexcept;
    
private:
    Label position;
    Label polyphony;
    Label midiInPort;
    Label midiOutPort;
    Label description;
    Label cursorMidiSettings;
};

#endif

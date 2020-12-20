//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include "UITypes.h"
#include "ofxRisographColours.hpp"

// ** TODO: Abstract colours into ColourScheme class. ** //

/// @brief A component with a rectangular shape that can be drawn to the screen.

class UIComponent
{
public:
    UIComponent()
    {
        setSize(200, 200);
        setPositionWithOrigin(0, 0);
    }
    
    UIComponent(int x, int y, int width, int height)
    {
        setSize(width, height);
        setPositionWithOrigin(x, y);
    }
    
    virtual ~UIComponent()
    {
        
    }

public:
    /// \brief Draw the component in the current render context.

    virtual void draw() = 0;
    
    /// \brief Get the component's bounds rectangle.

    [[nodiscard]] UIRect getBounds() const noexcept
    {
        return {origin, size};
    }
    
    /// \brief Get the component's origin point.
    
    [[nodiscard]] UIPoint<int> getOriginPoint() const noexcept
    {
        return origin;
    }
    
    /// \brief Get the component's centre point.

    [[nodiscard]] UIPoint<int> getCentrePoint() const noexcept
    {
        return centre;
    }
    
    /// \brief Get the component's background colour.
    
    [[nodiscard]] ofColor getBackgroundColour() const noexcept
    {
        return backgroundColour;
    }
    
    /// \brief Get the component's foreground colour.
    
    [[nodiscard]] ofColor getForegroundColour() const noexcept
    {
        return foregroundColour;
    }
    
    /// \brief Get the component's accent colour.
    
    [[nodiscard]] ofColor getAccentColour() const noexcept
    {
        return accentColour;
    }
    
    /// \brief Set the component's background colour and flag the component for redrawing.
    /// \param colour The desired background colour.

    virtual void setBackgroundColour(ofColor colour)
    {
        backgroundColour = colour;
        
        setShouldRedraw();
    }
    
    /// \brief Set the component's foreground colour and flag the component for redrawing.
    /// \param colour The desired foreground colour.

    virtual void setForegroundColour(ofColor colour)
    {
        foregroundColour = colour;
        
        setShouldRedraw();
    }
    
    /// \brief Set the component's accent colour and flag the component for redrawing.
    /// \param colour The desired accent colour.

    virtual void setAccentColour(ofColor colour)
    {
        accentColour = colour;
        
        setShouldRedraw();
    }

    /// \brief Set the component's position to the given origin point.
    /// \param x The x-coordinate of the desired origin point.
    /// \param y The y-coordinate of the desired origin point.

    virtual void setPositionWithOrigin(const float x, const float y)
    {
        origin.x = static_cast<int>(x);
        origin.y = static_cast<int>(y);
        centre.x = static_cast<int>(x + (float) size.w * 0.5f);
        centre.y = static_cast<int>(y + (float) size.h * 0.5f);
    }

    /// \brief Set the component's position using the given centre point.
    /// \param x The x-coordinate of the desired centre point.
    /// \param y The y-coordinate of the desired centre point.

    virtual void setPositionWithCentre(const float x, const float y)
    {
        centre.x = static_cast<int>(x);
        centre.y = static_cast<int>(y);
        origin.x = static_cast<int>(x - (float) size.w * 0.5f);
        origin.y = static_cast<int>(y - (float) size.h * 0.5f);
    }

    /// \brief Set the component's size and flag the component for redrawing.
    /// \param width The desired width of the component in pixels
    /// \param height The desired height of the component in pixels

    virtual void setSize(const float width, const float height)
    {
        size.w = static_cast<int>(width);
        size.h = static_cast<int>(height);

        setShouldRedraw();
    }

    /// \brief Set the component's size while maintaining its centre point.
    /// \param width The deisred width of the component in pixels
    /// \param height The desired height of the component in pixel

    virtual void setSizeFromCentre(const float width, const float height)
    {
        const int mx = static_cast<int>((float) centre.x - width  * 0.5f);
        const int my = static_cast<int>((float) centre.y - height * 0.5f);

        setSize(width, height);
        setPositionWithCentre(mx, my);
    }
    
    /// \brief Set the component's margins and flag the component for redrawing.
    /// \param margins The desired margins.

    virtual void setMargins(UIMargins<int>& margins)
    {
        this->margins.t = margins.t;
        this->margins.l = margins.l;
        this->margins.r = margins.r;
        this->margins.b = margins.b;
        
        setShouldRedraw();
    }
    
    /// \brief Set the component's margins and flag the component for redrawing.
    /// \param top The desired top margin in pixels.
    /// \param left The desired left margin in pixels.
    /// \param right The desired right margin in pixels.
    /// \param bottom The desired bottom margin in pixels.

    virtual void setMargins(const int top, const int left, const int right, const int bottom)
    {
        margins.t = top;
        margins.l = left;
        margins.r = right;
        margins.b = bottom;
        
        setShouldRedraw();
    }

    /// \brief Indicate that the component should be redrawn.

    inline void setShouldRedraw()
    {
        shouldRedraw = true;
    }

protected:
    /// \brief The component's origin point.

    UIPoint<int> origin = {0, 0};
    
    /// \brief The component's centre point.

    UIPoint<int> centre = {0, 0};
    
    /// \brief The dimensions of the component

    UISize<int> size = {0, 0};

    /// \brief The margins around the component
    
    UIMargins<int> margins = {0, 0, 0, 0};
    
protected:
    
    /// \brief The component's background colour.
    
    ofColor backgroundColour = {215};
    
    /// \brief The component's foreground colour.
    
    ofColor foregroundColour = {15};
    
    /// \brief The component's accent colour.
    
    ofColor accentColour = ofxRisographColours::ivy;
    
protected:

    /// \brief Indicate whether or not the component should be redrawn.

    bool shouldRedraw = true;
};

#endif

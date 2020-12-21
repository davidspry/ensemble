//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include "ofMain.h"
#include "UITypes.h"

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

    [[nodiscard]] const UIRect getBounds() const noexcept
    {
        return {origin, size};
    }
    
    /// \brief Get the component's origin point.
    
    [[nodiscard]] const UIPoint<int>& getOriginPoint() const noexcept
    {
        return origin;
    }
    
    /// \brief Get the component's centre point.

    [[nodiscard]] const UIPoint<int>& getCentrePoint() const noexcept
    {
        return centre;
    }
    
    /// \brief Get the component's background colour.
    
    [[nodiscard]] const UIColourScheme& getColourScheme() const noexcept
    {
        return colours;
    }
    
    /// \brief Set the component's colour scheme and flag the component for redrawing.
    /// \param scheme The desired colour scheme.

    virtual void setColourScheme(UIColourScheme scheme)
    {
        colours = scheme;

        setShouldRedraw();
    }
    
    /// \brief Set the component's position and size using the given bounds rectangle.
    /// \param bounds The desired bounds rectangle.

    virtual void setBounds(UIRect bounds) noexcept
    {
        const auto origin = bounds.getTopLeft();
        
        setSize(bounds.width, bounds.height);
        setPositionWithOrigin(origin.x, origin.y);
    }

    /// \brief Set the component's position to the given origin point.
    /// \param position The desired origin point.

    virtual inline void setPositionWithOrigin(UIPoint<int>& position)
    {
        origin.x = position.x;
        origin.y = position.y;
        centre.x = static_cast<int>((float) position.x + (float) size.w * 0.5f);
        centre.y = static_cast<int>((float) position.y + (float) size.h * 0.5f);
    }
    
    /// \brief Set the component's position to the given origin point.
    /// \param x The x-coordinate of the desired origin point.
    /// \param y The y-coordinate of the desired origin point.

    virtual inline void setPositionWithOrigin(const float x, const float y)
    {
        origin.x = static_cast<int>(x);
        origin.y = static_cast<int>(y);
        centre.x = static_cast<int>(x + (float) size.w * 0.5f);
        centre.y = static_cast<int>(y + (float) size.h * 0.5f);
    }

    /// \brief Set the component's position using the given centre point.
    /// \param centrePoint The desired centre point.

    virtual inline void setPositionWithCentre(UIPoint<int>& centrePoint)
    {
        centre.x = centrePoint.x;
        centre.y = centrePoint.y;
        origin.x = static_cast<int>((float) centrePoint.x - (float) size.w * 0.5f);
        origin.y = static_cast<int>((float) centrePoint.y - (float) size.h * 0.5f);
    }
    
    /// \brief Set the component's position using the given centre point.
    /// \param x The x-coordinate of the desired centre point.
    /// \param y The y-coordinate of the desired centre point.

    virtual inline void setPositionWithCentre(const float x, const float y)
    {
        centre.x = static_cast<int>(x);
        centre.y = static_cast<int>(y);
        origin.x = static_cast<int>(x - (float) size.w * 0.5f);
        origin.y = static_cast<int>(y - (float) size.h * 0.5f);
    }

    /// \brief Set the component's size and flag the component for redrawing.
    /// \param width The desired width of the component in pixels
    /// \param height The desired height of the component in pixels

    virtual inline void setSize(const float width, const float height)
    {
        size.w = static_cast<int>(width);
        size.h = static_cast<int>(height);

        setShouldRedraw();
    }

    /// \brief Set the component's size while maintaining its centre point and flag the component for redrawing.
    /// \param width The deisred width of the component in pixels
    /// \param height The desired height of the component in pixels

    virtual inline void setSizeFromCentre(const float width, const float height)
    {
        setSize(width, height);
        setPositionWithCentre(centre.x, centre.y);
    }
    
    /// \brief Set the component's margins and flag the component for redrawing.
    /// \param margins The desired margins.

    virtual inline void setMargins(UIMargins<int>& margins)
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

    virtual inline void setMargins(const int top, const int left, const int right, const int bottom)
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
    
    /// \brief The component's colour scheme.
    
    UIColourScheme colours;
    
protected:

    /// \brief Indicate whether or not the component should be redrawn.

    bool shouldRedraw = true;
};

#endif

//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include "ofMain.h"

#include "Themes.h"
#include "UISize.h"
#include "UIRect.h"
#include "UIPoint.h"
#include "UIMargins.h"
#include "UIColourScheme.h"

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
    
    /// \brief Indicate that the component should be redrawn.

    inline void setShouldRedraw()
    {
        shouldRedraw = true;
    }
    
    // MARK: - Geometry
    
    /// \brief Get the component's bounds rectangle.

    [[nodiscard]] inline UIRect getBounds() const noexcept
    {
        return {origin, size};
    }
    
    /// \brief Get the component's inner bounds rectangle (i.e., the bounds less the margins).

    [[nodiscard]] inline UIRect getInnerBounds() const noexcept
    {
        return UIRect(origin, size).subtractMargins(margins);
    }

    /// \brief Get the component's size.

    [[nodiscard]] inline const UISize<int>& getSize() const noexcept
    {
        return size;
    }

    /// \brief Get the component's origin point.
    
    [[nodiscard]] inline const UIPoint<int>& getOriginPoint() const noexcept
    {
        return origin;
    }
    
    /// \brief Get the component's centre point.

    [[nodiscard]] inline const UIPoint<int>& getCentrePoint() const noexcept
    {
        return centre;
    }
    
    /// \brief Get the component's margins.

    [[nodiscard]] virtual inline const UIMargins<int>& getMargins() const noexcept
    {
        return margins;
    }
    
    /// \brief Set the component's position and size using the given bounds rectangle.
    /// \param bounds The desired bounds rectangle.

    virtual inline void setBounds(UIRect bounds) noexcept
    {
        const auto origin = bounds.getTopLeft();
        
        setSize(bounds.width, bounds.height);
        setPositionWithOrigin(origin.x, origin.y);
    }

    /// \brief Set the component's position to the given origin point.
    /// \param position The desired origin point.

    virtual inline void setPositionWithOrigin(UIPoint<int>& position)
    {
        this->setPositionWithOrigin(position.x, position.y);
    }
    
    /// \brief Set the component's position to the given origin point.
    /// \param x The x-coordinate of the desired origin point.
    /// \param y The y-coordinate of the desired origin point.

    virtual inline void setPositionWithOrigin(const int x, const int y)
    {
        origin.x = x;
        origin.y = y;
        centre.x = x + static_cast<int>((float) size.w * 0.5f);
        centre.y = y + static_cast<int>((float) size.h * 0.5f);
    }

    /// \brief Set the component's position using the given centre point.
    /// \param centrePoint The desired centre point.

    virtual inline void setPositionWithCentre(UIPoint<int>& centrePoint)
    {
        this->setPositionWithCentre(centrePoint.x, centrePoint.y);
    }
    
    /// \brief Set the component's position using the given centre point.
    /// \param x The x-coordinate of the desired centre point.
    /// \param y The y-coordinate of the desired centre point.

    virtual inline void setPositionWithCentre(const int x, const int y)
    {
        centre.x = x;
        centre.y = y;
        origin.x = x - static_cast<int>((float) size.w * 0.5f);
        origin.y = y - static_cast<int>((float) size.h * 0.5f);
    }

    /// \brief Set the component's size and flag the component for redrawing.
    /// \param width The desired width of the component in pixels
    /// \param height The desired height of the component in pixels

    virtual inline void setSize(const float width, const float height)
    {
        size.w = static_cast<int>(width);
        size.h = static_cast<int>(height);
        setPositionWithOrigin(origin);

        setShouldRedraw();
    }

    /// \brief Set the component's size while maintaining its centre point and flag the component for redrawing.
    /// \param width The deisred width of the component in pixels
    /// \param height The desired height of the component in pixels

    virtual inline void setSizeFromCentre(const float width, const float height)
    {
        size.w = static_cast<int>(width);
        size.h = static_cast<int>(height);
        setPositionWithCentre(centre);

        setShouldRedraw();
    }
    
    /// \brief Set each of the component's margins to the given value and flag the component for redrawing.
    /// \param marginSize The desired size for each of the component's margins in pixels.

    virtual inline void setMargins(const int marginSize)
    {
        this->setMargins(marginSize, marginSize, marginSize, marginSize);
    }
    
    /// \brief Set the component's margins and flag the component for redrawing.
    /// \param margins The desired margins.

    virtual inline void setMargins(const UIMargins<int>& margins)
    {
        this->setMargins(margins.t, margins.l, margins.r, margins.b);
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
    
    UIColourScheme* colours = &(Themes::theme);
    
protected:

    /// \brief Indicate whether or not the component should be redrawn.

    bool shouldRedraw = true;
};

#endif

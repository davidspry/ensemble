//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef UIRECT_H
#define UIRECT_H

#include "ofMain.h"
#include "UISize.h"
#include "UIPoint.h"
#include "UIMargins.h"
#include "Constants.h"

/// @brief A rectangular component that can be successively subdivided into smaller rectangles.

class UIRect: public ofRectangle
{
public:
    UIRect():
    ofRectangle()
    {
        
    }
    
    template <typename T>
    UIRect(UIPoint<T> origin, UISize<T> size):
    ofRectangle(origin.x, origin.y, size.w, size.h)
    {
        
    }

    UIRect(float x, float y, float width, float height):
    ofRectangle(x, y, width, height)
    {
        
    }

public:
    /// @brief Remove a rectangle from the top of the UIRect and return it.
    /// @param amountToRemove The desired number of pixels to remove from the top.

    [[nodiscard]] UIRect removeFromTop(int amountToRemove) noexcept(false);
    
    /// @brief Remove a rectangle from the bottom of the UIRect and return it.
    /// @param amountToRemove The desired number of pixels to remove from the bottom.

    [[nodiscard]] UIRect removeFromBottom(int amountToRemove) noexcept(false);
    
    /// @brief Remove a rectangle from the left of the UIRect and return it.
    /// @param amountToRemove The desired number of pixels to remove from the left.

    [[nodiscard]] UIRect removeFromLeft(int amountToRemove) noexcept(false);
    
    /// @brief Remove a rectangle from the right of the UIRect and return it.
    /// @param amountToRemove The desired number of pixels to remove from the right.

    [[nodiscard]] UIRect removeFromRight(int amountToRemove) noexcept(false);
    
    /// @brief Subdivide the UIRect into some number of smaller rectangles along the given axis.
    /// @param axis The axis along which to subdivide the UIRect
    /// @param subdivisions The number of subdivisions to compute

    [[nodiscard]] std::vector<UIRect> subdivide(Axis axis, int subdivisions) const noexcept(false);
    
public:
    /// @brief Subtract the given margins from the UIRect and return the result.
    /// @param margins The margins to be subtracted from the UIRect.

    template <typename T>
    [[nodiscard]] inline UIRect subtractMargins(UIMargins<T> margins) noexcept
    {
        UIRect r = *(this);
        
        r.translateY(margins.t);
        r.translateX(margins.l);
        r.setWidth(width - margins.l - margins.r);
        r.setHeight(height - margins.t - margins.b);

        return r;
    }
};

#endif

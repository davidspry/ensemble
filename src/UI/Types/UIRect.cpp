//  Ensemble
//  Created by David Spry on 20/12/20.

#include "UIRect.h"

UIRect UIRect::removeFromTop(int amountToRemove) noexcept(false)
{
    if (!(amountToRemove > 0)) {
        throw std::out_of_range("The amount to remove must be positive.");
    }

    const auto origin  = getTopLeft();
    const auto removed = std::fmin((float) amountToRemove, height);

    setHeight(height - removed);
    translateY(removed);
    
    return {origin.x, origin.y, width, removed};
}

UIRect UIRect::removeFromBottom(int amountToRemove) noexcept(false)
{
    if (!(amountToRemove > 0)) {
        throw std::out_of_range("The amount to remove must be positive.");
    }

    const auto origin  = getBottomLeft();
    const auto removed = std::fmin((float) amountToRemove, height);

    setHeight(height - removed);
    
    return {origin.x, origin.y - removed, width, removed};
}

UIRect UIRect::removeFromLeft(int amountToRemove) noexcept(false)
{
    if (!(amountToRemove > 0)) {
        throw std::out_of_range("The amount to remove must be positive.");
    }

    const auto origin  = getTopLeft();
    const auto removed = std::fmin((float) amountToRemove, width);

    setWidth(width - removed);
    translateX(removed);
    
    return {origin.x, origin.y, removed, height};
}

UIRect UIRect::removeFromRight(int amountToRemove) noexcept(false)
{
    if (!(amountToRemove > 0)) {
        throw std::out_of_range("The amount to remove must be positive.");
    }

    const auto origin  = getTopRight();
    const auto removed = std::fmin((float) amountToRemove, width);

    setWidth(width - removed);
    
    return {origin.x - removed, origin.y, width, height};
}

std::vector<UIRect> UIRect::subdivide(Axis axis, int subdivisions) const noexcept(false)
{
    if (subdivisions < 1) {
        throw std::out_of_range("The number of subdivisions must be positive.");
    }
    
    ofRectMode mode = ofGetRectMode();
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    std::vector<UIRect> vector;

    vector.reserve(subdivisions);
    
    const float scale = 1.0f / subdivisions;
    
    for (int k = subdivisions - 1; k >= 0; --k)
    {
        UIRect r = *(this);

        if (axis == Axis::X) {
            r.scaleHeight(scale);
            r.translateY(k * height * scale);
        }

        else if (axis == Axis::Y) {
            r.scaleWidth(scale);
            r.translateX(k * width * scale);
        }

        vector.push_back(r);
    }
    
    ofSetRectMode(mode);
    return vector;
}

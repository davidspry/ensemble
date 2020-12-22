//  Ensemble
//  Created by David Spry on 20/12/20.

#include "UIRect.h"

UIRect::UIRect():
ofRectangle()
{
    
}

UIRect::UIRect(float x, float y, float width, float height):
ofRectangle(x, y, width, height)
{
    
}

const UISize<int> UIRect::getSize() const noexcept
{
    return {static_cast<int>(width), static_cast<int>(height)};
}

UIRect UIRect::translatedTo(int x, int y) noexcept
{
    UIRect r = *(this);
    
    r.setX(x);
    r.setY(y);

    return r;
}

void UIRect::trimFromTop(int amountToRemove) noexcept(false)
{
    if (!(amountToRemove > 0)) {
        throw std::out_of_range("The amount to remove must be positive.");
    }
    
    const auto removed = std::fmin((float) amountToRemove, height);
    setHeight(height - removed);
    translateY(removed);
    
    return;
}

void UIRect::trimFromBottom(int amountToRemove) noexcept(false)
{
    if (!(amountToRemove > 0)) {
        throw std::out_of_range("The amount to remove must be positive.");
    }
    
    const auto removed = std::fmin((float) amountToRemove, height);
    setHeight(height - removed);
    
    return;
}

void UIRect::trimFromLeft(int amountToRemove) noexcept(false)
{
    if (!(amountToRemove > 0)) {
        throw std::out_of_range("The amount to remove must be positive.");
    }
    
    const auto removed = std::fmin((float) amountToRemove, width);
    setWidth(width - removed);
    translateX(removed);
    
    return;
}

void UIRect::trimFromRight(int amountToRemove) noexcept(false)
{
    if (!(amountToRemove > 0)) {
        throw std::out_of_range("The amount to remove must be positive.");
    }
    
    const auto removed = std::fmin((float) amountToRemove, width);
    setWidth(width - removed);
    
    return;
}

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
    
    return {origin.x - removed, origin.y, removed, height};
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

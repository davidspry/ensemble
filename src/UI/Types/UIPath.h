//  UIPath.h
//  Ensemble
//  Created by David Spry on 24/12/20.

#ifndef UIPATH_H
#define UIPATH_H

#include "ofMain.h"
#include "UIPoint.h"

/// @brief An extension of `ofPath`.

class UIPath: public ofPath
{
public:
    /// @brief Add a hexagon to the path.
    /// @param x The x-coordinate of the origin point
    /// @param y The y-coordinate of the origin point
    /// @param size The width and height of the hexagon

    void hexagon(int x, int y, int size)
    {
        const float theta  = static_cast<float>(PI) / 3.0f;
        const float radius = size * 0.5f;

        UIPoint<int> centre;
        centre.x = x + static_cast<int>(radius);
        centre.y = y + static_cast<int>(radius);

        const auto computeHexagonPoint = [&](int pointIndex) -> glm::vec2
        {
            return
            {
                centre.x + radius * std::cosf(static_cast<float>(pointIndex) * theta),
                centre.y + radius * std::sinf(static_cast<float>(pointIndex) * theta)
            };
        };
        
        moveTo(centre.x + radius, centre.y);
        lineTo(computeHexagonPoint(1));
        lineTo(computeHexagonPoint(2));
        lineTo(computeHexagonPoint(3));
        lineTo(computeHexagonPoint(4));
        lineTo(computeHexagonPoint(5));
        close();
    }
};

#endif

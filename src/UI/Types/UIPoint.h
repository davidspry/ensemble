//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef UIPOINT_H
#define UIPOINT_H

#include <type_traits>

/// @brief A two-component struct representing a point on a 2D plane.

template <typename T>
struct UIPoint
{
    UIPoint()
    {
        static_assert(std::is_arithmetic<T>::value, "The given type must be numeric.");
        
        this->x = static_cast<T>(0);
        this->y = static_cast<T>(0);
    }
    
    UIPoint(T x, T y)
    {
        static_assert(std::is_arithmetic<T>::value, "The given type must be numeric.");

        this->x = x;
        this->y = y;
    }

    T x;
    T y;
};

#endif

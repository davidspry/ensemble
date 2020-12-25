//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef UIPOINT_H
#define UIPOINT_H

#include <type_traits>

/// @brief A two-component struct representing a point on a 2D plane.

template <typename T>
struct UIPoint
{
    T x;
    T y;
    
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
    
    void set(T x, T y)
    {
        this->x = x;
        this->y = y;
    }
    
    inline bool operator == (const UIPoint<T>& q)
    {
        return x == q.x && y == q.y;
    }
    
    friend UIPoint<T> operator + (const UIPoint<T>& p, const UIPoint<T>& q)
    {
        return {p.x + q.x, p.y + q.y};
    }
    
    friend UIPoint<T> operator - (const UIPoint<T>& p, const UIPoint<T>& q)
    {
        return {p.x - q.x, p.y - q.y};
    }
};

#endif

//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef UISIZE_H
#define UISIZE_H

#include <type_traits>

/// @brief A two-component struct representing the dimensions of a 2D rectangular object.

template <typename T>
struct UISize
{
    T w;
    T h;

    UISize()
    {
        static_assert(std::is_arithmetic<T>::value, "The given type must be numeric.");
        
        this->w = static_cast<T>(0);
        this->h = static_cast<T>(0);
    }
    
    UISize(T width, T height)
    {
        static_assert(std::is_arithmetic<T>::value, "The given type must be numeric.");

        this->w = width;
        this->h = height;
    }
    
    void set(T width, T height)
    {
        this->w = width;
        this->h = height;
    }
};

#endif

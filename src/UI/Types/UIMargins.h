//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef UIMARGINS_H
#define UIMARGINS_H

#include <type_traits>

/// @brief A four-component struct representing a margin around a rectangle.

template <typename T>
struct UIMargins
{
    T t;
    T l;
    T r;
    T b;
    
    UIMargins()
    {
        static_assert(std::is_arithmetic<T>::value, "The given type must be numeric.");

        this->l = static_cast<T>(0);
        this->r = static_cast<T>(0);
        this->t = static_cast<T>(0);
        this->b = static_cast<T>(0);
    }
    
    UIMargins(T horizontal, T vertical)
    {
        static_assert(std::is_arithmetic<T>::value, "The given type must be numeric.");

        this->l = horizontal;
        this->r = horizontal;
        this->t = vertical;
        this->b = vertical;
    }
    
    UIMargins(T top, T left, T right, T bottom)
    {
        static_assert(std::is_arithmetic<T>::value, "The given type must be numeric.");

        this->l = left;
        this->r = right;
        this->t = top;
        this->b = bottom;
    }
    
    void set(T top, T left, T right, T bottom)
    {
        this->l = left;
        this->r = right;
        this->t = top;
        this->b = bottom;
    }
};


#endif

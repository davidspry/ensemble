//  Ensemble
//  Created by David Spry on 31/12/20.

#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

/// @brief A collection of objects.

template <typename T>
class Array
{
public:
    Array()
    {
        collection.reserve(55);
    }
    
public:
    T & at(unsigned int index) const noexcept(false)
    {
        return collection.at(index);
    }
    
    T & last() noexcept
    {
        return collection.at(collection.size() - 1);
    }
    
    int size() const noexcept
    {
        return collection.size();
    }
    
    typename std::vector<T>::iterator begin()
    {
        return collection.begin();
    }
    
    typename std::vector<T>::iterator end()
    {
        return collection.end();
    }
    
public:
    /// @brief Swap the elements at the given indices.
    /// @param x The index of the first element.
    /// @param y The index of the second element.
    /// @throw An exception will be thrown if either index if out of range.

    void swap(size_t x, size_t y) noexcept(false)
    {
        T t = collection.at(y);
        collection.at(y) = collection.at(x);
        collection.at(x) = t;
    }
    
    /// @brief Construct a new object in the collection using the given arguments.
    /// @param arguments The new object's constructor parameters.
    /// @return A reference to the new object.

    template <typename ...A>
    T& include(A... arguments) noexcept(false)
    {
        collection.emplace_back(arguments...);
        return collection.back();
    }
    
    /// @brief Swap the given element to the end of the underlying array and erase it.
    /// @param element A pointer to the element that should be erased.
    /// @return A pointer to the element that was swapped into the target element's original position.
 
    T* swapAndErase(T* element)
    {
        const size_t index = std::distance(collection.data(), element);
        const size_t endIndex = collection.size() - 1;

        if (index == endIndex)
        {
            collection.pop_back();
            return nullptr;
        }

        else
        {
            swap(index, endIndex);
            collection.pop_back();
            return &collection.at(index);
        }
    }
    
private:
    std::vector<T> collection;
};

#endif

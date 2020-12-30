//  Ensemble
//  Created by David Spry on 30/12/20.

#ifndef TABLE_H
#define TABLE_H

#include "ofMain.h"

/// @brief A 2D array of pointers.

template <typename T>
class Table
{
public:
    /// @brief Construct a table with four rows and four columns.

    Table()
    {
        static_assert(std::is_pointer<T>::value, "The given type must be a pointer type");
        
        rows = 4;
        cols = 4;
        table.assign(rows * cols, nullptr);
    }
    
    /// @brief Construct a table with the given number of rows and columns.
    /// @param rows The desired number of rows.
    /// @param cols The desired number of columns.

    Table(unsigned int rows, unsigned int cols)
    {
        static_assert(std::is_pointer<T>::value, "The given type must be a pointer type");
        
        this->rows = rows;
        this->cols = cols;
        table.assign(rows * cols, nullptr);
    }

public:
    /// @brief Set the size of the table.
    /// @param rows The desired number of rows.
    /// @param cols The desired number of columns.

    // TODO: Add appropriate shrinking behaviour.
    inline void setSize(unsigned int rows, unsigned int cols) noexcept(false)
    {
        if (!(rows > 0 && cols > 0))
        {
            constexpr auto error = "The table must have a positive number of rows and columns";
            throw std::invalid_argument(error);
        }

        this->rows = rows;
        this->cols = cols;
        table.resize(rows * cols, nullptr);
    }
    
public:
    /// @brief Set the contents of the table at the given position.
    /// @param element The pointer to be stored at the given position.
    /// @param x The x-coordinate of the position.
    /// @param y The y-coordinate of the position.
    /// @throw An exception will be thrown if the given position is out of range.

    inline void set(T element, unsigned int x, unsigned int y) noexcept(false)
    {
        const int i = index(x, y);

        table.at(i) = element;
    }
    
    /// @brief Erase the contents of the table at the given position.
    /// @param x The x-coordinate of the desired position.
    /// @param y The y-coordinate of the desired position.
    /// @throw An exception will be thrown if the given position is out of range.
    
    inline void erase(unsigned int x, unsigned int y) noexcept(false)
    {
        const int i = index(x, y);
        
        table.at(i) = nullptr;
    }

    /// @brief Return the contents of the table at the given position.
    /// @param x The x-coordinate of the desired position.
    /// @param y The y-coordinate of the desired position.
    /// @throw An exception will be thrown if the given position is out of range.
    
    inline T get(unsigned int x, unsigned int y) const noexcept(false)
    {
        const int i = index(x, y);
        
        return table.at(i);
    }

    /// @brief Indicate whether the table contains an entry at the given position.
    /// @param x The x-coordinate of the desired position.
    /// @param y The y-coordinate of the desired position.
    /// @throw An exception will be thrown if the given position is out of range.

    inline bool contains(unsigned int x, unsigned int y) const noexcept(false)
    {
        const int i = index(x, y);
        
        return table.at(i) != nullptr;
    }
    
protected:
    /// @brief Compute an array index from a table position.
    /// @param x The x-coordinate of the desired table position.
    /// @param y The y-coordinate of the desired table position.
    /// @throw An exception will be thrown if the given position is out of range.

    const int index(unsigned int x, unsigned int y) const noexcept(false)
    {
        const int index = y * cols + x;
        
        if (index < 0 || !(index < table.size()))
        {
            constexpr auto error = "The given position is out of range.";
            throw std::out_of_range(error);
        }

        return index;
    }
    
private:
    unsigned int rows;
    unsigned int cols;
    std::vector<T> table;
};

#endif

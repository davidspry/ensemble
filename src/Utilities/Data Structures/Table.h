//  Ensemble
//  Created by David Spry on 30/12/20.

#ifndef TABLE_H
#define TABLE_H

#include "ofMain.h"

/// @brief A 2D array of pointers with a range-based iteration linear in the number of elements (not the size of the table).

template <typename T>
class Table
{
public:
    /// @brief Construct a table with four rows and four columns.

    Table()
    {
        rows = 4;
        cols = 4;
        indices.assign(rows * cols, Table::None);
    }
    
    /// @brief Construct a table with the given number of rows and columns.
    /// @param rows The desired number of rows.
    /// @param cols The desired number of columns.

    Table(unsigned int rows, unsigned int cols)
    {
        this->rows = rows;
        this->cols = cols;
        indices.assign(rows * cols, Table::None);
    }
    
    using Index     = int16_t;
    using TableCell = std::pair<T, Index>;

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
        indices.resize(rows * cols, Table::None);
    }
    
public:
    /// @brief Set the contents of the table at the given position.
    /// @param element The element to be stored in the table.
    /// @param x The x-coordinate of the position.
    /// @param y The y-coordinate of the position.
    /// @throw An exception will be thrown if the given position is out of range.

    inline void set(T element, unsigned int x, unsigned int y) noexcept(false)
    {
        const int i = index(x, y);
        const int n = static_cast<int>(table.size());
        
        table.emplace_back(element, i);
        indices.at(i) = n;
    }
    
    /// @brief Return the contents of the table at the given position (or nullptr if the position is empty).
    /// @param x The x-coordinate of the desired position.
    /// @param y The y-coordinate of the desired position.
    /// @throw An exception will be thrown if the given position is out of range.
    
    inline const T* get(unsigned int x, unsigned int y) const noexcept(false)
    {
        const Index i = index(x, y);
        const Index t = indices.at(i);
        
        if (t == Table::None)
            return nullptr;
        
        else
            return &(table.at(t).first);
    }
    
    /// @brief Erase the contents of the table at the given position.
    /// @param x The x-coordinate of the desired position.
    /// @param y The y-coordinate of the desired position.
    /// @throw An exception will be thrown if the given position is out of range.
    
    inline void erase(unsigned int x, unsigned int y) noexcept(false)
    {
        const Index i = index(x, y);
        const Index n = swapAndErase(i);

        indices.at(n) = indices.at(i);
        indices.at(i) = Table::None;
    }

    /// @brief Indicate whether the table contains an entry at the given position.
    /// @param x The x-coordinate of the desired position.
    /// @param y The y-coordinate of the desired position.
    /// @throw An exception will be thrown if the given position is out of range.

    inline bool contains(unsigned int x, unsigned int y) const noexcept(false)
    {
        const int i = index(x, y);
        
        return indices.at(i) != Table::None;
    }
    
protected:
    /// @brief Compute an array index from a table position.
    /// @param x The x-coordinate of the desired table position.
    /// @param y The y-coordinate of the desired table position.
    /// @throw An exception will be thrown if the given position is out of range.

    const Index index(unsigned int x, unsigned int y) const noexcept(false)
    {
        const Index index = y * cols + x;
        
        if (index < 0 || !(index < indices.size()))
        {
            constexpr auto error = "The given position is out of range.";
            throw std::out_of_range(error);
        }

        return index;
    }
    
private:
    /// @brief Swap the element at the given table index to the end of the underlying vector,
    /// erase it, then return the table index of the element that was swapped into its original position.
    /// @param  index The table index of the element to be erased.
    /// @return The table index of the element that was swapped into the given table index after deletion.

    const Index & swapAndErase(Index index)
    {
        const auto a = table.begin() + indices.at(index);
        const auto b = table.end() - 1;

        std::iter_swap(a, b);
        
        table.pop_back();

        return (*a).second;
    }
    
private:
    unsigned int rows;
    unsigned int cols;
    std::vector<Index> indices;
    std::vector<TableCell> table;
    
private:
    constexpr static Index None = -1;
    
// MARK: - Iterator

public:
    /// @brief An iterator that extracts objects from the table.

    class Iterator
    {
    public:
        Iterator(const TableCell * x): pointer(x) {};
        
        Iterator operator ++ ()
        {
            ++pointer;
            return *(this);
        }
    
        bool operator != (const Iterator & other) const
        {
            return pointer != other.pointer;
        }
        
        const T & operator * () const
        {
            return (*pointer).first;
        }
        
    private:
        const TableCell * pointer;
    };
    
    Iterator begin() const
    {
        return Iterator(table.data());
    }
    
    Iterator end() const
    {
        return Iterator(&(*table.end()));
    }
};

template <typename T> constexpr typename Table<T>::Index Table<T>::None;

#endif

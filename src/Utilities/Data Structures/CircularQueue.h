//  Ensemble
//  Created by David Spry on 30/12/20.

#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <vector>

template <typename T, unsigned int N>
class CircularQueue
{
public:
    CircularQueue()
    {
        queue.resize(N);
    }
    
public:
    /// @brief Indicate whether the queue is empty or not.
    
    inline bool empty()
    {
        return count == 0;
    }
    
    /// @brief Indicate whether the queue contains elements or not.

    inline bool isNotEmpty()
    {
        return count > 0;
    }
    
    /// @brief Indicate whether the queue is full or not.

    inline bool full()
    {
        return tail == head && count > 0;
    }
    
public:
    /// @brief Enqueue a new element.
    /// @param element The element to be enqueued.
    /// @return A Boolean value to indicate whether the element was added to the queue or not.

    bool enqueue(T element) noexcept
    {
        if (full())
            return false;
        
        queue.at(tail) = element;
        
        tail = tail + 1;
        tail = tail % N;
        count = count + 1;
        
        return true;
    }
    
    /// @brief Dequeue an element from the queue.
    /// @return The dequeued element.
    /// @throw An exception will be thrown if the queue is empty.

    [[nodiscard]] T dequeue() noexcept(false)
    {
        if (empty())
        {
            constexpr auto error = "[CircularQueue] Dequeue was called on an empty queue.";
            throw std::out_of_range(error);
        }
        
        const T element = queue.at(head);
        
        head = head + 1;
        head = head % N;
        count = count - 1;
        
        return element;
    }
    
private:
    unsigned int head = 0;
    unsigned int tail = 0;
    unsigned int count = 0;
    std::vector<T> queue;
};

#endif

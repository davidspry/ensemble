//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef SQREDIRECT_H
#define SQREDIRECT_H

#include "SQNode.h"

/// @brief A node that redirects moving nodes.

class SQRedirect: public SQNode
{
public:
    SQRedirect():
    SQNode()
    {
        
    }
    
    SQRedirect(int x, int y):
    SQNode(x, y)
    {
        
    }
    
public:
    void redirect(SQNode& node) noexcept
    {
        if (node.delta.x == 0 &&
            node.delta.y == 0)
            return;
        
        // [TODO]
        // * option for clockwise / anticlockwise redirection
        //
        // * x-redirection:
        //      if (dy == 0) return reverse(node);
        //      if (dx == 0) return turn(node);
        //      return setInHorizontalDirection(node);
        //
        // * y-redirection:
        //      if (dy == 0) return turn(node);
        //      if (dx == 0) return reverse(node);
        //      return setInVerticalDirection(node);
        //
        // * diagonal-redirection:
        //      if (dx * dy == 0) return diagonalise(node);
        //      return turn(node);
    }
    
private:
    /// @brief Turn a node in the clockwise direction.
    /// @param node The node whose direction should be modified.

    inline static void turn(SQNode& node) noexcept
    {
        const int x = -node.delta.y;
        const int y = +node.delta.x;
        
        node.delta.set(x, y);
    }
    
    /// @brief Reverse a node's direction by negating its directional components.
    /// @param node The node whose direction should be modified.

    inline static void reverse(SQNode& node) noexcept
    {
        const int x = -node.delta.x;
        const int y = -node.delta.y;
        
        node.delta.set(x, y);
    }
    
    /// @brief Set the direction of the given node to be the vertical direction.
    /// @note  The node's `y` directional component should not be zero.
    /// @param node The node whose direction should be modified.

    inline static void setInVerticalDirection(SQNode& node) noexcept
    {
        const int x = 0;
        const int y = -node.delta.y;
        
        node.delta.set(x, y);
    }
    
    /// @brief Set the direction of the given node to be the horizontal direction.
    /// @note  The node's `x` directional component should not be zero.
    /// @param node The node whose direction should be modified.
    
    inline static void setInHorizontalDirection(SQNode& node) noexcept
    {
        const int x = -node.delta.x;
        const int y = 0;
        
        node.delta.set(x, y);
    }
    
    /// @brief Set the direction of the given node to be diagonal.
    /// @param node The node whose direction should be modified.

    inline static void diagonalise(SQNode& node) noexcept
    {
        const int x = node.delta.x == +1 ? -1 : +1;
        const int y = node.delta.y == -1 ? +1 : -1;
        
        node.delta.set(x, y);
    }
};

#endif

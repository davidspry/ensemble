//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef SQREDIRECT_H
#define SQREDIRECT_H

#include "SQNode.h"
#include "Constants.h"

/// @brief A node that redirects moving nodes.

class SQRedirect: public SQNode
{
public:
    SQRedirect(unsigned int cellSize):
    SQNode(cellSize)
    {
        initialisePath();
    }
    
    SQRedirect(unsigned int cellSize, UIPoint<int>& position):
    SQNode(cellSize, position)
    {
        initialisePath();
    }
    
    SQRedirect(unsigned int cellSize, UIPoint<int>& position, Redirection type):
    SQNode(cellSize, position)
    {
        initialisePath();
        setRedirectionType(type);
    }

protected:
    inline void initialisePath() override
    {
        GridCell::initialisePath();
    }

public:
    void draw() override
    {
        path.setColor(getRedirectionTypeColour());

        GridCell::draw();
    }

public:
    /// @brief Set the node's redirection type.
    /// @param type The desired redirection type.

    inline void setRedirectionType(Redirection type) noexcept
    {
        redirection = type;
    }
    
    /// @brief Get the node's redirection type.

    inline Redirection getRedirectionType() const noexcept
    {
        return redirection;
    }
    
    /// @brief Get the colour corresponding to the redirect's type.
    
    inline ofColor getRedirectionTypeColour() noexcept
    {
//        const Redirection r = determineBasicRedirection();
        switch (redirection)
        {
            case Redirection::X: return ofxRisographColours::lake;
            case Redirection::Y: return ofxRisographColours::cranberry;
            case Redirection::Diagonal: return ofxRisographColours::indigo;
            case Redirection::Alternating: return ofxRisographColours::hunter_green;
            case Redirection::Random: return ofxRisographColours::metallic_gold;
            default: return colours.foregroundColour;
        }
    }

public:
    /// @brief Redirect the given node based on its direction.
    /// @param node The node that should be redirected.
    /// @param gridSize The dimensions of the grid in rows and columns.

    void interact(SQNode& node, const UISize<int>& gridSize) noexcept override
    {
        if (node.delta.x == 0 && node.delta.y == 0)
            return;

        switch (determineBasicRedirection())
        {
            case Redirection::X:
            {
                     if (node.delta.x == 0) turn(node);
                else if (node.delta.y == 0) reverse(node);
                else setInHorizontalDirection(node);
                break;
            }
            
            case Redirection::Y:
            {
                     if (node.delta.x == 0) reverse(node);
                else if (node.delta.y == 0) turn(node);
                else setInVerticalDirection(node);
                break;
            }
            
            case Redirection::Diagonal:
            {
                if (node.delta.x == 0 || node.delta.y == 0)
                     diagonalise(node);
                else turn(node);
                break;
            }
                
            default: return;
        }
        
        const int row = (xy.y + node.delta.y + gridSize.h) % gridSize.h;
        const int col = (xy.x + node.delta.x + gridSize.w) % gridSize.w;
        node.moveToGridPosition(row, col);
    }

private:
    /// @brief Determine whether the redirection type is currently X, Y, or Diagonal.
    /// @note  This should only be called when an interaction occurs.

    inline Redirection determineBasicRedirection() noexcept
    {
        switch (redirection)
        {
            case Redirection::X:
            case Redirection::Y:
            case Redirection::Diagonal:
            {
                return redirection;
            }
                
            case Redirection::Alternating:
            {
                state = !state;
                return static_cast<Redirection>(static_cast<int>(state));
            }
                
            case Redirection::Random:
            {
                const int choice = ofRandom(3);
                return static_cast<Redirection>(choice);
            }
        }
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
    
private:
    Redirection redirection;
    
private:
    bool state;
};

#endif

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
    SQNode(cellSize, Redirect)
    {
        updateLabelText(redirection);
    }
    
    SQRedirect(unsigned int cellSize, const UIPoint<int>& position):
    SQNode(cellSize, position, Redirect)
    {
        updateLabelText(redirection);
    }
    
    SQRedirect(unsigned int cellSize, const UIPoint<int>& position, Redirection type):
    SQNode(cellSize, position, Redirect),
    redirection(type)
    {
        const auto r = determineBasicRedirectionType();

        updateLabelText(r);
    }

public:
    inline void draw() override
    {
        const int x = origin.x + margins.l + screenPosition.x;
        const int y = origin.y + margins.t + screenPosition.y;

        if (shouldRedraw)
        {
            path.clear();
            path.rectangle(0, 0, size.w, size.h);
            path.setColor(getRedirectionTypeColour());
            text.setPositionWithOrigin(x, y);
            shouldRedraw = false;
        }
        
        path.draw(x, y);
        text.draw();
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
        switch (redirection)
        {
            case Redirection::X:           return ofxRisographColours::sky_blue;
            case Redirection::Y:           return ofxRisographColours::crimson;
            case Redirection::Diagonal:    return ofxRisographColours::light_mauve;
            case Redirection::Alternating: return ofxRisographColours::grass;
            case Redirection::Random:      return ofxRisographColours::apricot;
            default: return colours->foregroundColour;
        }
    }

public:
    /// @brief Redirect the given node based on its direction.
    /// @param node The node that should be redirected.
    /// @param server The sequencer's MIDI server.
    /// @param gridSize The dimensions of the grid in rows and columns.

    void interact(SQNode& node, MIDIServer& server, const UISize<int>& gridSize) noexcept override
    {
        if (node.delta.x == 0 && node.delta.y == 0)
            return;

        switch (determineBasicRedirectionType())
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
        updateRedirectionIfNeeded();
    }
    
    inline std::string describe() noexcept override
    {
        switch (determineBasicRedirectionType())
        {
            case Redirection::X: return "REDIRECT X";
            case Redirection::Y: return "REDIRECT Y";
            case Redirection::Diagonal: return "REDIRECT DIAGONAL";
            default: return "REDIRECT";
        }
    }

private:
    /// @brief Determine whether the redirection type is currently X, Y, or Diagonal.
    /// @note  This should only be called when an interaction occurs.

    inline Redirection determineBasicRedirectionType() noexcept
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
                return static_cast<Redirection>(static_cast<int>(state));
            }
                
            case Redirection::Random:
            {
                return static_cast<Redirection>(static_cast<int>(choice));
            }
        }
    }
    
    /// @brief Update the redirection if it has a dynamic type.
    /// @note  This should be called when an interaction occurs.

    inline void updateRedirectionIfNeeded() noexcept
    {
        switch (redirection)
        {
            case Redirection::Alternating:
            {
                state = !state;
                const Redirection r = static_cast<Redirection>(static_cast<int>(state));
                return updateLabelText(r);
            }
                
            case Redirection::Random:
            {
                choice = ofRandom(3);
                const Redirection r = static_cast<Redirection>(choice);
                return updateLabelText(r);
            }

            default: return;
        }
    }
    
private:
    /// @brief Update the node's text label to match its redirection type.
    /// @param type The node's basic redirection type (i.e., X, Y, or Diagonal).

    inline void updateLabelText(Redirection type) noexcept
    {
        switch (type)
        {
            case Redirection::X: { return text.setText("X"); }
            case Redirection::Y: { return text.setText("Y"); }
            case Redirection::Diagonal: { return text.setText("Z"); }
            default: { return text.setText("?"); }
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
    /// @brief The alternating state of an Alternating redirect node.

    bool state;
    
    /// @brief The current redirection type of a Random redirect node.

    uint8_t choice = 0;
};

#endif

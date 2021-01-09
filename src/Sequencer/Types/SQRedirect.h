//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef SQREDIRECT_H
#define SQREDIRECT_H

#include "SQNode.h"
#include "Constants.h"

/// @brief Constants defining the different types of redirection nodes.

enum  Redirection { X, Y, Diagonal, Alternating, Random };

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
    void draw() override;
    
    std::string describe() noexcept override;
    
    /// @brief Redirect the given node based on its direction.
    /// @param node The node that should be redirected.
    /// @param server The sequencer's MIDI server.
    /// @param gridSize The dimensions of the grid in rows and columns.

    void interact(SQNode& node, MIDIServer& server, const UISize<int>& gridSize) noexcept override;

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

    ofColor getRedirectionTypeColour() noexcept;

private:
    /// @brief Determine whether the redirection type is currently X, Y, or Diagonal.
    /// @note  This should only be called when an interaction occurs.

    Redirection determineBasicRedirectionType() noexcept;
    
    /// @brief Update the redirection if it has a dynamic type.
    /// @note  This should be called when an interaction occurs.

    void updateRedirectionIfNeeded() noexcept;

    /// @brief Update the node's text label to match its redirection type.
    /// @param type The node's basic redirection type (i.e., X, Y, or Diagonal).

    void updateLabelText(Redirection type) noexcept;

private:
    /// @brief Turn a node in the clockwise direction.
    /// @param node The node whose direction should be modified.

    static void turn(SQNode& node) noexcept;
    
    /// @brief Reverse a node's direction by negating its directional components.
    /// @param node The node whose direction should be modified.

    static void reverse(SQNode& node) noexcept;
    
    /// @brief Set the direction of the given node to be the vertical direction.
    /// @note  The node's `y` directional component should not be zero.
    /// @param node The node whose direction should be modified.

    static void setInVerticalDirection(SQNode& node) noexcept;
    
    /// @brief Set the direction of the given node to be the horizontal direction.
    /// @note  The node's `x` directional component should not be zero.
    /// @param node The node whose direction should be modified.
    
    static void setInHorizontalDirection(SQNode& node) noexcept;
    
    /// @brief Set the direction of the given node to be diagonal.
    /// @param node The node whose direction should be modified.

    static void diagonalise(SQNode& node) noexcept;
    
private:
    Redirection redirection;
    
private:
    /// @brief The alternating state of an Alternating redirect node.

    bool state;
    
    /// @brief The current redirection type of a Random redirect node.

    uint8_t choice = 0;
};

#endif

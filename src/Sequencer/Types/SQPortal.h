//  Ensemble
//  Created by David Spry on 23/12/20.

#ifndef SQPORTAL_H
#define SQPORTAL_H

#include "SQNode.h"

/// @brief Constants defining the two different types of portals.

enum  PortalType { A, B };

/// @brief A node that teleports other nodes to different locations on the sequencer.

class SQPortal: public SQNode
{
public:
    SQPortal(unsigned int cellSize, PortalType portalType):
    SQNode(cellSize, Portal),
    type(portalType),
    pair(nullptr)
    {
        text.setText("P");
    }
    
    SQPortal(unsigned int cellSize, const UIPoint<int>& position, PortalType portalType):
    SQNode(cellSize, position, Portal),
    type(portalType),
    pair(nullptr)
    {
        text.setText("P");
    }
    
    ~SQPortal()
    {
        breakPair();
    }
    
public:
    void draw() override;
    
    inline std::string describe() noexcept override
    {
        if (isPaired())
             return "PORTAL PAIRED";
        else return "PORTAL UNPAIRED";
    }
    
    /// @brief Teleport the given node on the sequencer grid.
    /// @param node The node that's passing through the portal.
    /// @param server The sequencer's MIDI server.
    /// @param gridSize The dimensions of the sequencer grid in rows and columns.
    
    void interact(SQNode& node, MIDIServer& server, const UISize<int>& gridSize) noexcept override;

public:
    /// @brief Pair the portal with another portal node.
    /// @param portal The portal to be paired.
    /// @throw An exception will be thrown in the case where the SQPortal is already paired or
    ///        the proposed pair has the same type.

    void pairWith(SQPortal* portal) noexcept(false);

    /// @brief Pair the portal with another portal node.
    /// @param portal The portal to be paired.
    /// @throw An exception will be thrown in the case where the SQPortal is already paired or
    ///        the proposed pair has the same type.

    inline void pairWith(SQPortal& portal) noexcept(false)
    {
        this->pairWith(&portal);
    }

    /// @brief A function that should be called when the portal nodes pair disconnects.

    inline void pairDidBreak() noexcept
    {
        pair = nullptr;

        setShouldRedraw();
    }
    
    /// @brief Indicate whether the SQPortal can be paired with the given portal.
    /// @param portal The proposed pair.

    inline bool canPairWith(SQPortal & portal) const noexcept
    {
        return pair == nullptr && !portal.isPaired() && type != portal.type;
    }
    
    /// @brief Get the portal's pair (or nullptr if the portal is unpaired).

    [[nodiscard]] inline SQPortal* getPair() const noexcept
    {
        return pair;
    }
    
    /// @brief Get the portal node's portal type.
    
    [[nodiscard]] inline PortalType getPortalType() const noexcept
    {
        return type;
    }

    /// @brief Get the portal node's opposite portal type.

    [[nodiscard]] inline PortalType getPairPortalType() const noexcept
    {
        switch (type)
        {
            case PortalType::A: return PortalType::B;
            case PortalType::B: return PortalType::A;
        }
    }

    /// @brief Indicate if the portal is currently paired.

    [[nodiscard]] inline bool isPaired() const noexcept
    {
        return !(pair == nullptr);
    }
    
private:
    /// @brief Disconnect from the paired node if the node is paired
    ///        and notify the paired node of the disconnection.
    /// @note  This should be called when the node is deleted.

    inline void breakPair() const noexcept
    {
        if (pair == nullptr)
            return;

        pair->pairDidBreak();
    }
    
    /// @brief Get the ofColor that matches the portal's type.

    inline const ofColor& getPortalColour() const noexcept
    {
        if (!isPaired())
        {
            return ofxRisographColours::crimson;
        }

        switch (type)
        {
            case PortalType::A: return ofxRisographColours::lake;
            case PortalType::B: return ofxRisographColours::lake;
        }
    }

private:
    /// @brief Teleport a node travelling along the x-axis to the opposite end of the row.
    /// @param node The node to be teleported.
    /// @param gridSize The dimensions of the grid in rows and columns.
    
    void teleportNodeAlongXAxis(SQNode& node, const UISize<int>& gridSize) const noexcept;
    
    /// @brief Teleport a node travelling along the y-axis to the opposite end of the row.
    /// @param node The node to be teleported.
    /// @param gridSize The dimensions of the grid in rows and columns.

    void teleportNodeAlongYAxis(SQNode& node, const UISize<int>& gridSize) const noexcept;
    
    /// @brief Teleport a node travelling in the north-west direction to the opposite corner of the grid.
    /// @param node The node to be teleported.
    /// @param gridSize The dimensions of the grid in rows and columns.

    void teleportNodeTravellingNW(SQNode& node, const UISize<int>& gridSize) const noexcept;
    
    /// @brief Teleport a node travelling in the north-east direction to the opposite corner of the grid.
    /// @param node The node to be teleported.
    /// @param gridSize The dimensions of the grid in rows and columns.

    void teleportNodeTravellingNE(SQNode& node, const UISize<int>& gridSize) const noexcept;
    
    /// @brief Teleport a node travelling in the south-east direction to the opposite corner of the grid.
    /// @param node The node to be teleported.
    /// @param gridSize The dimensions of the grid in rows and columns.
    
    void teleportNodeTravellingSE(SQNode& node, const UISize<int>& gridSize) const noexcept;
    
    /// @brief Teleport a node travelling in the south-west direction to the opposite corner of the grid.
    /// @param node The node to be teleported.
    /// @param gridSize The dimensions of the grid in rows and columns.

    void teleportNodeTravellingSW(SQNode& node, const UISize<int>& gridSize) const noexcept;

private:
    PortalType type;
    SQPortal * pair;
};

#endif

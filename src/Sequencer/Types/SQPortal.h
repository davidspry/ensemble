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
    /**
     [OVERVIEW]
     - Portal placement alternates between two subtypes.
     - Portals are paired together. The first portal pairs with the second, the third pairs with the four, etc.
     - If a portal is deleted, it becomes paired with the next portal that's placed on the sequencer.
     - Unpaired portals send incoming nodes back to the beginning of their row or column, depending on their direction.
     - Nodes maintain their direction when travelling through a portal.
     */

public:
    SQPortal(unsigned int cellSize, PortalType portalType):
    SQNode(cellSize, Portal),
    type(portalType),
    pair(nullptr)
    {
        text.setText(portalType == PortalType::A ? "PX" : "PY");
    }
    
    SQPortal(unsigned int cellSize, const UIPoint<int>& position, PortalType portalType):
    SQNode(cellSize, position, Portal),
    type(portalType),
    pair(nullptr)
    {
        text.setText(portalType == PortalType::A ? "PX" : "PY");
    }
    
    ~SQPortal()
    {
        breakPair();
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
            path.setColor(getPortalColour());
            text.setPositionWithOrigin(x, y);
            shouldRedraw = false;
        }
        
        path.draw(x, y);
        text.draw();
    }

public:
    /// @brief Pair the portal with another portal node.
    /// @param portal The portal to be paired.
    /// @throw An exception will be thrown in the case where the SQPortal is already paired or
    ///        the proposed pair has the same type.

    inline void pairWith(SQPortal* portal) noexcept(false)
    {
        if (pair != nullptr)
            throw std::invalid_argument("A paired SQPortal cannot be paired with a new SQPortal.");
        
        else if (type == portal->type)
            throw std::invalid_argument("Paired SQPortals must have different types.");
            
        else pair = portal;
        
        setShouldRedraw();
    }

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
        return pair == nullptr &&
              !portal.isPaired() &&
               type != portal.type;
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
        if (type == PortalType::A) return PortalType::B;
        if (type == PortalType::B) return PortalType::A;
        else                       return PortalType::A;
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
    
public:
    
    /// @brief Teleport the given node on the sequencer grid.
    /// @param node The node that's passing through the portal.
    /// @param server The sequencer's MIDI server.
    /// @param gridSize The dimensions of the sequencer grid in rows and columns.
    
    void interact(SQNode& node, MIDIServer& server, const UISize<int>& gridSize) noexcept override
    {
        if (pair != nullptr)
        {
            const int col = (pair->xy.x + node.delta.x + gridSize.w) % gridSize.w;
            const int row = (pair->xy.y + node.delta.y + gridSize.h) % gridSize.h;
            node.moveToGridPosition(row, col);
            return;
        }

        else
        {
            if (node.delta.x == 0) return teleportNodeAlongYAxis(node, gridSize);
            if (node.delta.y == 0) return teleportNodeAlongXAxis(node, gridSize);
            if (node.delta.x < 0 && node.delta.y < 0) return teleportNodeTravellingNW(node, gridSize);
            if (node.delta.x < 0 && node.delta.y > 0) return teleportNodeTravellingSW(node, gridSize);
            if (node.delta.x > 0 && node.delta.y < 0) return teleportNodeTravellingNE(node, gridSize);
            if (node.delta.x > 0 && node.delta.y > 0) return teleportNodeTravellingSE(node, gridSize);
        }
    }

private:
    /// @brief Teleport a node travelling along the x-axis to the opposite end of the row.
    /// @param node The node to be teleported.
    /// @param gridSize The dimensions of the grid in rows and columns.
    
    inline void teleportNodeAlongXAxis(SQNode& node, const UISize<int>& gridSize) const noexcept
    {
        const int col = node.delta.x > 0 ? 0 : gridSize.w - 1;
        const int row = node.xy.y;
        node.moveToGridPosition(row, col);
    }
    
    /// @brief Teleport a node travelling along the y-axis to the opposite end of the row.
    /// @param node The node to be teleported.
    /// @param gridSize The dimensions of the grid in rows and columns.

    inline void teleportNodeAlongYAxis(SQNode& node, const UISize<int>& gridSize) const noexcept
    {
        const int col = node.xy.x;
        const int row = node.delta.y > 0 ? 0 : gridSize.h - 1;
        node.moveToGridPosition(row, col);
    }
    
    /// @brief Teleport a node travelling in the north-west direction to the opposite corner of the grid.
    /// @param node The node to be teleported.
    /// @param gridSize The dimensions of the grid in rows and columns.

    inline void teleportNodeTravellingNW(SQNode& node, const UISize<int>& gridSize) const noexcept
    {
        const int k = std::min(gridSize.w - node.xy.x - 1, gridSize.h - node.xy.y - 1);
        const int col = (node.xy.x + k) % gridSize.w;
        const int row = (node.xy.y + k) % gridSize.h;
        node.moveToGridPosition(row, col);
    }
    
    /// @brief Teleport a node travelling in the north-east direction to the opposite corner of the grid.
    /// @param node The node to be teleported.
    /// @param gridSize The dimensions of the grid in rows and columns.

    inline void teleportNodeTravellingNE(SQNode& node, const UISize<int>& gridSize) const noexcept
    {
        const int k = std::min(node.xy.x, gridSize.h - node.xy.y - 1);
        const int col = (node.xy.x - k) % gridSize.w;
        const int row = (node.xy.y + k) % gridSize.h;
        node.moveToGridPosition(row, col);
    }
    
    /// @brief Teleport a node travelling in the south-east direction to the opposite corner of the grid.
    /// @param node The node to be teleported.
    /// @param gridSize The dimensions of the grid in rows and columns.
    
    inline void teleportNodeTravellingSE(SQNode& node, const UISize<int>& gridSize) const noexcept
    {
        const int k = std::min(node.xy.x, node.xy.y);
        const int col = (node.xy.x - k) % gridSize.w;
        const int row = (node.xy.y - k) % gridSize.h;
        node.moveToGridPosition(row, col);
    }
    
    /// @brief Teleport a node travelling in the south-west direction to the opposite corner of the grid.
    /// @param node The node to be teleported.
    /// @param gridSize The dimensions of the grid in rows and columns.

    inline void teleportNodeTravellingSW(SQNode& node, const UISize<int>& gridSize) const noexcept
    {
        const int k = std::min(gridSize.w - node.xy.x - 1, node.xy.y);
        const int col = (node.xy.x + k) % gridSize.w;
        const int row = (node.xy.y - k) % gridSize.h;
        node.moveToGridPosition(row, col);
    }

private:
    PortalType type;
    SQPortal * pair;
};

#endif

//  Ensemble
//  Created by David Spry on 9/1/21.

#include "SQPortal.h"

void SQPortal::draw()
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

void SQPortal::pairWith(SQPortal* portal) noexcept(false)
{
    if (pair != nullptr)
        throw std::invalid_argument("`pairWith` was called on a paired SQPortal.");
    
    else if (type == portal->type)
        throw std::invalid_argument("Paired SQPortals must have different types.");
        
    else pair = portal;
    
    setShouldRedraw();
}

void SQPortal::interact(SQNode& node, MIDIServer& server, const UISize<int>& gridSize) noexcept
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

/// @brief Teleport a node travelling along the x-axis to the opposite end of the row.
/// @param node The node to be teleported.
/// @param gridSize The dimensions of the grid in rows and columns.

void SQPortal::teleportNodeAlongXAxis(SQNode& node, const UISize<int>& gridSize) const noexcept
{
    const int col = node.delta.x > 0 ? 0 : gridSize.w - 1;
    const int row = node.xy.y;
    node.moveToGridPosition(row, col);
}

/// @brief Teleport a node travelling along the y-axis to the opposite end of the row.
/// @param node The node to be teleported.
/// @param gridSize The dimensions of the grid in rows and columns.

void SQPortal::teleportNodeAlongYAxis(SQNode& node, const UISize<int>& gridSize) const noexcept
{
    const int col = node.xy.x;
    const int row = node.delta.y > 0 ? 0 : gridSize.h - 1;
    node.moveToGridPosition(row, col);
}

void SQPortal::teleportNodeTravellingNW(SQNode& node, const UISize<int>& gridSize) const noexcept
{
    const int k = std::min(gridSize.w - node.xy.x - 1, gridSize.h - node.xy.y - 1);
    const int col = (node.xy.x + k) % gridSize.w;
    const int row = (node.xy.y + k) % gridSize.h;
    node.moveToGridPosition(row, col);
}

void SQPortal::teleportNodeTravellingNE(SQNode& node, const UISize<int>& gridSize) const noexcept
{
    const int k = std::min(node.xy.x, gridSize.h - node.xy.y - 1);
    const int col = (node.xy.x - k) % gridSize.w;
    const int row = (node.xy.y + k) % gridSize.h;
    node.moveToGridPosition(row, col);
}

void SQPortal::teleportNodeTravellingSE(SQNode& node, const UISize<int>& gridSize) const noexcept
{
    const int k = std::min(node.xy.x, node.xy.y);
    const int col = (node.xy.x - k) % gridSize.w;
    const int row = (node.xy.y - k) % gridSize.h;
    node.moveToGridPosition(row, col);
}

void SQPortal::teleportNodeTravellingSW(SQNode& node, const UISize<int>& gridSize) const noexcept
{
    const int k = std::min(gridSize.w - node.xy.x - 1, node.xy.y);
    const int col = (node.xy.x + k) % gridSize.w;
    const int row = (node.xy.y - k) % gridSize.h;
    node.moveToGridPosition(row, col);
}

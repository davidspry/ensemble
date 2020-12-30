//  Ensemble
//  Created by David Spry on 25/12/20.

#include "Sequence.hpp"

Sequence::Sequence(Grid & grid, MIDIServer & server):
table(grid.getGridDimensions().height,
      grid.getGridDimensions().width)
{
    this->grid   = &grid;
    this->server = &server;
}

void Sequence::tick()
{
    server->release();
    
    const auto dimensions = grid->getGridDimensions();

    for (auto& playhead : playheads)
    {
        const UIPoint<int> originalPosition = playhead.xy;

        playhead.update(dimensions);

        if (table.contains(playhead.xy.x, playhead.xy.y))
        {
            SQNode * node = table.get(playhead.xy.x, playhead.xy.y);

            node->interact(playhead, *server, dimensions);   
        }

        if (playhead.xy == originalPosition)
            playhead.update(dimensions);

        if (table.contains(playhead.xy.x, playhead.xy.y))
        {
            SQNode * node = table.get(playhead.xy.x, playhead.xy.y);

            node->interact(playhead, *server, dimensions);
        }
        
        if (table.contains(playhead.xy.x, playhead.xy.y))
        {
            SQNode * node = table.get(playhead.xy.x, playhead.xy.y);

            node->interact(playhead, *server, dimensions);
        }
    }
}

void Sequence::gridDimensionsDidUpdate() noexcept(false)
{
    const UISize<int>& dimensions = grid->getGridDimensions();

    table.setSize(dimensions.h, dimensions.w);
}

bool Sequence::placeNote(MIDINote note, const UIPoint<int>& xy) noexcept(false)
{
    if (table.contains(xy.x, xy.y))
        return false;
    
    SQNote & node = notes.include(grid->getGridCellSize(), xy, note);
    table.set(&node, xy.x, xy.y);
    
    return true;
}

bool Sequence::placePortal(const UIPoint<int>& xy) noexcept
{
    if (table.contains(xy.x, xy.y))
        return false;
    
    SQPortal & node = portals.include(grid->getGridCellSize(), xy, nextPortalType);
    
    table.set(&node, xy.x, xy.y);
    
    nextPortalType = static_cast<PortalType>((static_cast<int>(nextPortalType) + 1) % 2);

    for (SQPortal & portal : portals)
    {
        if (&portal != &node && portal.canPairWith(node))
        {
            portal.pairWith(node);
            node.pairWith(portal);
        }
    }
    
    return true;
}

bool Sequence::placePlayhead(const UIPoint<int>& xy) noexcept(false)
{
    if (table.contains(xy.x, xy.y))
        return false;
    
    SQPlayhead & node = playheads.include(grid->getGridCellSize(), xy, 0, 1);
    
    return true;
}

bool Sequence::placeRedirect(Redirection type, const UIPoint<int>& xy) noexcept
{
    if (table.contains(xy.x, xy.y))
        return false;
    
    SQRedirect & node = redirects.include(grid->getGridCellSize(), xy, type);
    table.set(&node, xy.x, xy.y);
    
    return true;
}

void Sequence::eraseFromPosition(const UIPoint<int>& xy) noexcept(false)
{
    if (!table.contains(xy.x, xy.y))
        return;

    SQNode* node = table.get(xy.x, xy.y);
    table.erase(xy.x, xy.y);

    switch (node->nodeType)
    {
        case SQNodeType::Note:
        {
            SQNote* cast = static_cast<SQNote*>(node);
            SQNote* node = notes.swapAndErase(cast);
            
            if (node != nullptr)
                table.set(node, node->xy.x, node->xy.y);
            
            return;
        }

        case SQNodeType::Portal:
        {
            SQPortal* cast = static_cast<SQPortal*>(node);
            nextPortalType = cast->getPortalType();
            SQPortal* node = portals.swapAndErase(cast);
            
            if (node != nullptr)
            {
                table.set(node, node->xy.x, node->xy.y);
                
                if (node->getPair() != nullptr)
                    node->getPair()->pairWith(*node);
            }
            
            return;
        }
            
        case SQNodeType::Redirect:
        {
            SQRedirect* cast = static_cast<SQRedirect*>(node);
            SQRedirect* node = redirects.swapAndErase(cast);
            
            if (node != nullptr)
                table.set(node, node->xy.x, node->xy.y);
            
            return;
        }
            
        case SQNodeType::Playhead:
        {
            SQPlayhead* cast = static_cast<SQPlayhead*>(node);
            SQPlayhead* node = playheads.swapAndErase(cast);
            
            if (node != nullptr)
                table.set(node, node->xy.x, node->xy.y);
            
            return;
        }
    }
}



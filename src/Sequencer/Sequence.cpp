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

    for (auto & playhead : playheads)
    {
        const UIPoint<int> originalPosition = playhead.xy;

        playhead.update(dimensions);

        if (table.contains(playhead.xy.x, playhead.xy.y))
        {
            auto node = table.get(playhead.xy.x, playhead.xy.y);
            node->get()->interact(playhead, *server, dimensions);
        }

        if (playhead.xy == originalPosition)
            playhead.update(dimensions);

        if (table.contains(playhead.xy.x, playhead.xy.y))
        {
            auto node = table.get(playhead.xy.x, playhead.xy.y);
            node->get()->interact(playhead, *server, dimensions);
        }
        
        if (table.contains(playhead.xy.x, playhead.xy.y))
        {
            auto node = table.get(playhead.xy.x, playhead.xy.y);
            node->get()->interact(playhead, *server, dimensions);
        }
    }
}

void Sequence::gridDimensionsDidUpdate() noexcept(false)
{
    const UISize<int>& dimensions = grid->getGridDimensions();

    table.setSize(dimensions.h, dimensions.w);
}

bool Sequence::placeNote(MIDINote midiNote, const UIPoint<int>& xy) noexcept(false)
{
    if (table.contains(xy.x, xy.y))
        return false;

    SQNote* node = new SQNote(grid->getGridCellSize(), xy, midiNote);

    table.set(std::shared_ptr<SQNode>(node), xy.x, xy.y);
    
    return true;
}

bool Sequence::placePortal(const UIPoint<int>& xy) noexcept
{
    if (table.contains(xy.x, xy.y))
        return false;
    
    if (!unpairedPortals.empty())
    {
        SQPortal* pair = unpairedPortals.back();
        SQPortal* node = new SQPortal(grid->getGridCellSize(), xy, pair->getPairPortalType());
        
        node->pairWith(pair);
        pair->pairWith(node);
        unpairedPortals.pop_back();

        table.set(std::shared_ptr<SQPortal>(node), xy.x, xy.y);
    }

    else
    {
        SQPortal* node = new SQPortal(grid->getGridCellSize(), xy, PortalType::A);
        
        unpairedPortals.push_back(node);
        
        table.set(std::shared_ptr<SQPortal>(node), xy.x, xy.y);
    }

    return true;
}

bool Sequence::placeRedirect(Redirection type, const UIPoint<int>& xy) noexcept
{
    if (table.contains(xy.x, xy.y))
        return false;
    
    SQRedirect* node = new SQRedirect(grid->getGridCellSize(), xy, type);

    table.set(std::shared_ptr<SQNode>(node), xy.x, xy.y);

    return true;
}

void Sequence::eraseFromPosition(const UIPoint<int>& xy) noexcept(false)
{
    if (!table.contains(xy.x, xy.y)) return;

    auto node = table.get(xy.x, xy.y);

    if (node->get()->nodeType == SQNodeType::Portal)
    {
        SQPortal* portal = static_cast<SQPortal*>(node->get());

        if (portal->isPaired())
        {
            unpairedPortals.push_back(portal->getPair());
        }
        
        else
        {
            auto & nodes = unpairedPortals;
            nodes.erase(std::remove(nodes.begin(), nodes.end(), node->get()), nodes.end());
        }
    }

    table.erase(xy.x, xy.y);
}

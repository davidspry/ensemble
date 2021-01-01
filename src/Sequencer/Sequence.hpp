//  Ensemble
//  Created by David Spry on 25/12/20.

#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include "Ensemble.h"
#include "Grid.h"

/// @brief A grid of SQNode objects.

class Sequence: public UIComponent, public ClockListener
{
public:
    Sequence(Grid & grid, MIDIServer & server);

public:
    void tick() override;

    inline void draw() override
    {
        ofPushMatrix();
        ofTranslate(origin.x + margins.l, origin.y + margins.t);
        
        for (auto & node : table)
            node->draw();
        
        for (auto & node : playheads)
            node.draw();

        ofPopMatrix();
    }

public:
    bool placeNote(MIDINote midiNote, const UIPoint<int>& xy) noexcept(false);
    
    bool placePortal(const UIPoint<int>& xy) noexcept;
    
    bool placeRedirect(Redirection type, const UIPoint<int>& xy) noexcept;
    
    void eraseFromPosition(const UIPoint<int>& xy) noexcept(false);
    
    inline void placePlayhead(const UIPoint<int>& xy) noexcept(false)
    {
        playheads.emplace_back(grid->getGridCellSize(), xy, 0, 1);
    }

public:
    /// @brief Update the underlying data structures to reflect a change in the size of the sequencer grid.

    void gridDimensionsDidUpdate() noexcept(false);

private:
    Grid*       grid   = nullptr;
    MIDIServer* server = nullptr;

private:
    std::vector<SQPlayhead> playheads;
    std::vector<SQPortal *> unpairedPortals;
    Table<std::shared_ptr<SQNode>> table;
};

#endif

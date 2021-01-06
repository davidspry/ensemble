//  Ensemble
//  Created by David Spry on 20/12/20.

#include "Sequencer.hpp"

Sequencer::Sequencer():
UIComponent(),
cursor(grid.getGridCellSize())
{
    const int cellSize = grid.getGridCellSize() * 2;
    setMargins(cellSize, cellSize, cellSize, 0);
    
    clock.connect(this);
}

Sequencer::Sequencer(int x, int y, int width, int height):
UIComponent(x, y, width, height),
cursor(grid.getGridCellSize())
{
    const int cellSize = grid.getGridCellSize() * 2;
    setMargins(cellSize, cellSize, cellSize, 0);
    
    clock.connect(this);
}

Sequencer::~Sequencer()
{
    midiServer.releaseAllNotes();
}

// MARK: - UIComponent drawing

void Sequencer::draw()
{
    grid.draw();

    ofPushMatrix();
    ofTranslate(origin.x + margins.l, origin.y + margins.t);
    
    for (auto & node : table)
        node->draw();
    
    for (auto & node : playheads)
        node.draw();

    ofPopMatrix();
    
    cursor.draw();
}

// MARK: - UIComponent callbacks

const UIMargins<int>& Sequencer::getMargins() const noexcept
{
    return grid.getMargins();
}

void Sequencer::setPositionWithOrigin(const int x, const int y)
{
    UIComponent::setPositionWithOrigin(x, y);
    
    grid.setPositionWithOrigin(x, y);
    cursor.setPositionWithOrigin(x, y);
}

void Sequencer::setPositionWithCentre(const int x, const int y)
{
    UIComponent::setPositionWithCentre(x, y);
    
    grid.setPositionWithCentre(x, y);
    cursor.setPositionWithOrigin(origin.x, origin.y);
}

void Sequencer::setSizeFromCentre(const float width, const float height)
{
    UIComponent::setSizeFromCentre(width, height);
    
    grid.setSizeFromCentre(width, height);
    const int cellSize = grid.getGridCellSize();
    cursor.setSizeFromCentre(cellSize, cellSize);
    
    gridDimensionsDidUpdate();
}

void Sequencer::setSize(const float width, const float height)
{
    UIComponent::setSize(width, height);
    
    grid.setSize(width, height);
    const int cellSize = grid.getGridCellSize();
    cursor.setSize(cellSize, cellSize);
    
    gridDimensionsDidUpdate();
}

void Sequencer::setMargins(const int top, const int left, const int right, const int bottom)
{
    UIComponent::setMargins(top, left, right, bottom);
    
    grid.setMargins(top, left, right, bottom);
    cursor.setMargins(top, left, right, bottom);
}

// MARK: - Clock control

void Sequencer::toggleClock() noexcept
{
    clock.toggleClock();

    midiServer.releaseAllNotes();
}

void Sequencer::tick()
{
    midiServer.releaseAllNotes();
    
    const auto dimensions = grid.getGridDimensions();

    for (auto & playhead : playheads)
    {
        const UIPoint<int> originalPosition = playhead.xy;

        playhead.update(dimensions);

        if (table.contains(playhead.xy.x, playhead.xy.y))
        {
            auto node = table.get(playhead.xy.x, playhead.xy.y);
            node->get()->interact(playhead, midiServer, dimensions);
        }

        if (playhead.xy == originalPosition)
            playhead.update(dimensions);

        for (size_t k = 0; k < 4; ++k)
        {
            if (table.contains(playhead.xy.x, playhead.xy.y))
            {
                auto node = table.get(playhead.xy.x, playhead.xy.y);
                node->get()->interact(playhead, midiServer, dimensions);
            }
            
            else break;
        }
    }
}

// MARK: - Sequence contents

void Sequencer::moveCursor(Direction direction) noexcept
{
    cursor.move(direction, grid.getGridDimensions());
    updateHoverDescriptionString();
}

void Sequencer::moveCursorToScreenPosition(const int x, const int y) noexcept
{
    UIPoint<int> xy;
    xy.x = (x - origin.x - margins.l) / grid.getGridCellSize();
    xy.y = (y - origin.y - margins.t) / grid.getGridCellSize();
    xy.x = Utilities::boundBy(0, grid.getGridDimensions().w - 1, xy.x);
    xy.y = Utilities::boundBy(0, grid.getGridDimensions().h - 1, xy.y);

    cursor.moveToGridPosition(xy.y, xy.x);
    updateHoverDescriptionString();
}

void Sequencer::updateHoverDescriptionString() noexcept
{
    if (table.contains(cursor.xy.x, cursor.xy.y))
    {
        const auto node  = table.get(cursor.xy.x, cursor.xy.y)->get();
        hoverDescription = node->describe();
    }
    
    else
    {
        hoverDescription = "";
    }
}

void Sequencer::setCursorOctave(const int octave) noexcept
{
    cursor.setOctave(octave);
}

bool Sequencer::placeNote(uint8_t noteIndex) noexcept(false)
{
    const UIPoint<int>& xy = cursor.getGridPosition();
    
    if (table.contains(xy.x, xy.y))
        return false;
    
    const MIDINote note = {noteIndex, cursor.getMIDISettings()};

    SQNote* node = new SQNote(grid.getGridCellSize(), xy, note);

    table.set(std::shared_ptr<SQNode>(node), xy.x, xy.y);
    
    updateHoverDescriptionString();
    
    return true;
}

bool Sequencer::placePortal() noexcept(false)
{
    const UIPoint<int>& xy = cursor.getGridPosition();
    
    if (table.contains(xy.x, xy.y))
        return false;
    
    if (!unpairedPortals.empty())
    {
        SQPortal* pair = unpairedPortals.back();
        SQPortal* node = new SQPortal(grid.getGridCellSize(), xy, pair->getPairPortalType());
        
        node->pairWith(pair);
        pair->pairWith(node);
        unpairedPortals.pop_back();

        table.set(std::shared_ptr<SQPortal>(node), xy.x, xy.y);
    }

    else
    {
        SQPortal* node = new SQPortal(grid.getGridCellSize(), xy, PortalType::A);

        unpairedPortals.push_back(node);

        table.set(std::shared_ptr<SQPortal>(node), xy.x, xy.y);
    }
    
    updateHoverDescriptionString();

    return true;
}

void Sequencer::placePlayhead(Direction direction) noexcept
{
    const int dx = direction == Direction::E ? 1 : direction == Direction::W ? -1 : 0;
    const int dy = direction == Direction::S ? 1 : direction == Direction::N ? -1 : 0;
    const UIPoint<int>& xy = cursor.getGridPosition();

    playheads.emplace_back(grid.getGridCellSize(), xy, dx, dy);
}

bool Sequencer::placeRedirect(Redirection type) noexcept(false)
{
    const UIPoint<int>& xy = cursor.getGridPosition();

    if (table.contains(xy.x, xy.y)) return false;
    
    SQRedirect* node = new SQRedirect(grid.getGridCellSize(), xy, type);

    table.set(std::shared_ptr<SQNode>(node), xy.x, xy.y);
    
    updateHoverDescriptionString();

    return true;
}

void Sequencer::eraseFromCurrentPosition() noexcept(false)
{
    const UIPoint<int>& xy = cursor.getGridPosition();
    
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
            auto& nodes = unpairedPortals;
            auto remove = std::remove(nodes.begin(), nodes.end(), node->get());
            nodes.erase(remove, nodes.end());
        }
    }

    table.erase(xy.x, xy.y);
    
    updateHoverDescriptionString();
}

void Sequencer::gridDimensionsDidUpdate() noexcept(false)
{
    const UISize<int>& dimensions = grid.getGridDimensions();

    table.setSize(dimensions.h, dimensions.w);
}

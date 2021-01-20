//  Ensemble
//  Created by David Spry on 20/12/20.

#include "Sequencer.hpp"

Sequencer::Sequencer():
UIComponent(),
cursor(grid.getGridCellSize())
{
    initialise();
}

Sequencer::Sequencer(int x, int y, int width, int height):
UIComponent(x, y, width, height),
cursor(grid.getGridCellSize())
{
    initialise();
}

Sequencer::~Sequencer()
{
    midiServer.releaseAllNotes();
}

void Sequencer::initialise() noexcept
{
    const int cellSize = grid.getGridCellSize() * 2;
    setMargins(cellSize, cellSize, cellSize, 0);
    updateCursorStateDescription();
    updateMIDIStateDescription();
    clock.connect(this);
}

// MARK: - UIComponent drawing

void Sequencer::draw()
{
    ofClear(colours->backgroundColour);

    grid.draw();

    ofPushMatrix();
    ofTranslate(origin.x + margins.l, origin.y + margins.t);
    
    for (auto & node : table)
        node->draw();

    for (auto & node : playheads)
        node.draw();

    ofPopMatrix();
    
    cursor.draw();
    
    drawSubsequenceIfRequested();
}

void Sequencer::drawSubsequenceIfRequested() noexcept
{
    if (!isViewingSubsequence)
    {
        return;
    }

    if (!table.contains(cursor.xy.x, cursor.xy.y))
    {
        isViewingSubsequence = false;
        
        return;
    }

    ofSetColor(colours->backgroundColour, 175);
    ofDrawRectangle(origin.x, origin.y, size.w, size.h);

    const auto node = table.get(cursor.xy.x, cursor.xy.y)->get();
    const auto type = node->nodeType;

    if (type == Subsequence)
    {
        static_cast<SQSubsequence&>(*node).drawSequence(centre);
    }
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
    
    updateMIDIStateDescription();
}

void Sequencer::tick()
{
    midiServer.releaseExpiredNotes();

    const auto dimensions = grid.getGridDimensions();

    const auto interact = [&](SQPlayhead & playhead) -> bool
    {
        if (table.contains(playhead.xy.x, playhead.xy.y))
        {
            const auto & xy = playhead.xy;
            const auto node = table.get(xy.x, xy.y)->get();
            const auto type = node->nodeType;
            node->interact(playhead, midiServer, dimensions);
            return type == Subsequence;
        }

        return false;
    };

    for (auto & playhead : playheads)
    {
        const UIPoint<int> originalPosition = playhead.xy;

        playhead.update(dimensions);

        if (interact(playhead)) continue;

        if (playhead.xy == originalPosition)
            playhead.update(dimensions);

        for (size_t k = 0; k < 4; ++k)
        {
            if (interact(playhead)) break;
        }
    }
    
    updateMIDIStateDescription();
}

// MARK: - Sequencer cursor

void Sequencer::setCursorOctave(const int octave) noexcept
{
    cursor.setOctave(octave);
    updateCursorStateDescription();
}

void Sequencer::setCursorChannel(const int channel) noexcept
{
    cursor.setChannel(channel);
    updateCursorStateDescription();
}

void Sequencer::setCursorDuration(const int duration) noexcept
{
    cursor.setDuration(duration);
    updateCursorStateDescription();
}

void Sequencer::moveCursor(Direction direction) noexcept
{
    if (!isViewingSubsequence)
    {
        cursor.move(direction, grid.getGridDimensions());
        updateCursorStateDescription();
        return;
    }

    else if (table.contains(cursor.xy.x, cursor.xy.y))
    {
        const auto node = table.get(cursor.xy.x, cursor.xy.y)->get();
        const auto type = node->nodeType;
        if (type == Subsequence)
        {
            static_cast<SQSubsequence&>(*(node)).moveCursor(direction);
            updateCursorStateDescription();
        }
    }
}

void Sequencer::moveCursorToScreenPosition(const int x, const int y) noexcept
{
    UIPoint<int> xy;
    xy.x = (x - origin.x - margins.l) / grid.getGridCellSize();
    xy.y = (y - origin.y - margins.t) / grid.getGridCellSize();
    xy.x = Utilities::boundBy(0, grid.getGridDimensions().w - 1, xy.x);
    xy.y = Utilities::boundBy(0, grid.getGridDimensions().h - 1, xy.y);

    cursor.moveToGridPosition(xy.y, xy.x);
    updateCursorStateDescription();
}

// MARK: - Sequence contents

void Sequencer::updateCursorStateDescription() noexcept
{
    stateDescription.cursorGridPosition.x = cursor.xy.x;
    stateDescription.cursorGridPosition.y = cursor.xy.y;

    stateDescription.cursorOctave   = cursor.getMIDISettings().octave;
    stateDescription.cursorChannel  = cursor.getMIDISettings().channel;
    stateDescription.cursorVelocity = cursor.getMIDISettings().velocity;

    if (table.contains(cursor.xy.x, cursor.xy.y))
    {
        const auto node = table.get(cursor.xy.x, cursor.xy.y)->get();
        stateDescription.cursorHoverDescription = node->describe();
    }

    else
    {
        stateDescription.cursorHoverDescription.clear();
    }

    stateDescription.setContainsNewData();
}

void Sequencer::updateMIDIStateDescription() noexcept
{
    stateDescription.midiPolyphony          = midiServer.getPolyphony();
    stateDescription.midiPortNumberIn       = clock.getMIDIPort();
    stateDescription.midiPortNumberOut      = midiServer.getMIDIPort();
    stateDescription.midiPortDescriptionIn  = clock.getMIDIPortDescription();
    stateDescription.midiPortDescriptionOut = midiServer.getMIDIPortDescription();
    
    stateDescription.setContainsNewData();
}

void Sequencer::expandSubsequence() noexcept
{
    if (isViewingSubsequence)
    {
        isViewingSubsequence = false;
        return;
    }
    
    else if (table.contains(cursor.xy.x, cursor.xy.y))
    {
        const auto node = table.get(cursor.xy.x, cursor.xy.y)->get();
        const auto type = node->nodeType;
        isViewingSubsequence = type == Subsequence;
    }
}

bool Sequencer::placeNote(uint8_t noteIndex) noexcept(false)
{
    const UIPoint<int>& xy = cursor.getGridPosition();

    if (table.contains(xy.x, xy.y))
    {
        if (!isViewingSubsequence)
            return false;

        const auto node = table.get(xy.x, xy.y);
        const auto type = node->get()->nodeType;
        
        if (type == Subsequence)
        {
            auto& subsequence = static_cast<SQSubsequence&>(*(node->get()));
            const bool result = subsequence.placeNote(noteIndex, cursor.getMIDISettings());
            updateCursorStateDescription();
            return result;
        }
    }

    const MIDINote note = {noteIndex, cursor.getMIDISettings()};
    std::shared_ptr<SQNode> node = std::make_shared<SQSubsequence>(grid.getGridCellSize(), xy, note);
    table.set(std::move(node), xy.x, xy.y);
    updateCursorStateDescription();

    return true;
}

bool Sequencer::placePortal() noexcept(false)
{
    const UIPoint<int>& xy = cursor.getGridPosition();
    
    if (table.contains(xy.x, xy.y)) return false;
    
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

    updateCursorStateDescription();

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
    
    updateCursorStateDescription();

    return true;
}

void Sequencer::eraseFromCurrentPosition() noexcept(false)
{
    const UIPoint<int>& xy = cursor.getGridPosition();

    if (!table.contains(xy.x, xy.y)) return;

    const auto node = table.get(xy.x, xy.y)->get();
    const auto type = node->nodeType;
    
    if (isViewingSubsequence)
    {
        auto & sequence = static_cast<SQSubsequence&>(*node);
        sequence.eraseFromCurrentPosition();
        updateCursorStateDescription();
        return;
    }
    
    if (type == Portal)
    {
        const auto & portal = static_cast<SQPortal&>(*node);

        if (portal.isPaired())
        {
            unpairedPortals.push_back(portal.getPair());
        }

        else
        {
            auto &nodes = unpairedPortals;
            auto remove = std::remove(nodes.begin(), nodes.end(), node);
            nodes.erase(remove, nodes.end());
        }
    }

    table.erase(xy.x, xy.y);
    updateCursorStateDescription();
}

void Sequencer::gridDimensionsDidUpdate() noexcept(false)
{
    const UISize<int>& dimensions = grid.getGridDimensions();

    table.setSize(dimensions.h, dimensions.w);
}

//  Ensemble
//  Created by David Spry on 9/1/21.

#include "SQSubsequence.h"

void SQSubsequence::draw()
{
    if (shouldRedraw)
    {
        auto colour = colours->secondaryForegroundColour;
        path.setColor(colour);
    }

    SQNode::draw();
}

void SQSubsequence::drawSequence(UIPoint<int> & centre)
{
    const int x = centre.x - grid.getSize().w * 0.5f;
    const int y = centre.y - grid.getSize().h * 0.5f;

    ofPushMatrix();
    ofTranslate(x, y);

    grid.draw();
    for (auto & note : sequence)
        note.draw();

    ofPopMatrix();
}

std::string SQSubsequence::describe() noexcept
{
    std::stringstream stringstream;

    const auto & a = std::begin(sequence);
    const auto & b = std::end(sequence);
    const auto iterator = std::ostream_iterator<SQNote>(stringstream, "-");

    std::copy(a, b, iterator);
    std::string string = stringstream.str();

    string.pop_back();

    return string;
}

void SQSubsequence::interact(SQNode& node, MIDIServer& server, const UISize<int>& gridSize) noexcept
{
    if (sequence.empty())
    {
        return;
    }

    sequence.at(index).interact(node, server, gridSize);

    index = index + 1;
    index = index % sequence.size();
}

void SQSubsequence::moveCursor(Direction direction) noexcept
{
    grid.moveCursor(direction);
}

void SQSubsequence::placeNote(uint8_t noteIndex, MIDISettings midiSettings) noexcept
{
    const auto size = grid.getGridDimensions();
    const int index = static_cast<int>(sequence.size());

    if (!(index < size.w * size.h))
        return;

    const UIPoint<int> xy =
    {
        index % size.w,
        index / size.w
    };

    MIDINote note (noteIndex, midiSettings);
    sequence.emplace_back(grid.getGridCellSize(), xy, note);
    grid.increaseNumberOfVisibleCells();
}

void SQSubsequence::eraseFromCurrentPosition() noexcept
{
    // TODO: Implement erasing
    
    grid.decreaseNumberOfVisibleCells();
}

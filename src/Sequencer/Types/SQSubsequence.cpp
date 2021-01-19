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
    for (auto & node : sequence)
        node.draw();

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

    auto & note = sequence.at(index);
    grid.setCurrentSequenceIndex(index);
    note.interact(node, server, gridSize);

    index = index + 1;
    index = index % sequence.size();
}

void SQSubsequence::moveCursor(Direction direction) noexcept
{
    grid.moveCursor(direction);
}

bool SQSubsequence::placeNote(uint8_t noteIndex, MIDISettings midiSettings) noexcept
{
    const auto size = grid.getGridDimensions();
    const int index = grid.getCursorPosition().y * size.w
                    + grid.getCursorPosition().x;

    if (grid.getCursorPosition().x >= size.w ||
        grid.getCursorPosition().y >= size.h)
        return false;

    if (index < sequence.size())
    {
        sequence.at(index).modify(noteIndex, midiSettings);
        return true;
    }

    const UIPoint<int> xy =
    {
        index % size.w,
        index / size.w
    };

    MIDINote const note (noteIndex, midiSettings);
    sequence.emplace_back(grid.getGridCellSize(), xy, note);
    grid.increaseNumberOfVisibleCells();

    return true;
}

void SQSubsequence::eraseFromCurrentPosition() noexcept
{
    const int length = static_cast<int>(sequence.size());
    const int cursor = grid.getCursorPosition().y
                     * grid.getGridDimensions().w
                     + grid.getCursorPosition().x;

    if (length <= 1 || cursor == length) return;

    const auto decrementPosition = [&](SQNode & node)
    {
        const UIPoint<int> & xy = node.xy;
        const UISize <int> & dimensions = grid.getGridDimensions();
        const int n = xy.y * dimensions.w + xy.x;
        const int row = (n - 1) / dimensions.w;
        const int col = (n - 1) % dimensions.w;
        node.moveToGridPosition(row, col);
    };

    for (size_t k = cursor + 1; k < length; ++k)
    {
        auto & node = sequence.at(k);
        decrementPosition(node);
    }
    
    sequence.erase(sequence.begin() + cursor);
    
    index = index % sequence.size();

    grid.decreaseNumberOfVisibleCells();
}

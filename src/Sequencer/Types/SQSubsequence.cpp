//  Ensemble
//  Created by David Spry on 9/1/21.

#include "SQSubsequence.h"

SQSubsequence::SQSubsequence(unsigned int cellSize):
SQNode(cellSize, Subsequence), grid(8, 8), index(0)
{
    initialiseSequence();
}

SQSubsequence::SQSubsequence(unsigned int cellSize, const UIPoint<int>& position):
SQNode(cellSize, position, Subsequence), grid(8, 8), index(0)
{
    initialiseSequence();
}

SQSubsequence::SQSubsequence(unsigned int cellSize, const UIPoint<int>& position, MIDINote midiNote):
SQNode(cellSize, position, Subsequence), grid(8, 8), index(0)
{
    initialiseSequence();

    sequence.emplace_back(cellSize, position, midiNote);
}

void SQSubsequence::draw()
{
    sequence.at(index).draw();
}

void SQSubsequence::drawSequence(UIPoint<int> & centre)
{
    
    
    grid.setPositionWithCentre(centre);
    grid.draw();
    
    
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
    
}

void SQSubsequence::placeNote(uint8_t noteIndex, MIDISettings midiSettings) noexcept
{
    
}

void SQSubsequence::eraseFromCurrentPosition() noexcept
{
    
}

//  Ensemble
//  Created by David Spry on 20/12/20.

#include "Sequencer.hpp"

Sequencer::Sequencer():
UIComponent(),
cursor(grid.getGridCellSize()),
sequence(grid, midiServer)
{
    const int cellSize = grid.getGridCellSize() * 2;
    setMargins(cellSize, cellSize, cellSize, 0);
    clock.connect(&sequence);
}

Sequencer::Sequencer(int x, int y, int width, int height):
UIComponent(x, y, width, height),
cursor(grid.getGridCellSize()),
sequence(grid, midiServer)
{
    const int cellSize = grid.getGridCellSize() * 2;
    setMargins(cellSize, cellSize, cellSize, 0);
    clock.connect(&sequence);
}

Sequencer::~Sequencer()
{
    midiServer.release();
}

// MARK: - UIComponent Drawing

void Sequencer::draw()
{
    grid.draw();
    sequence.draw();
    cursor.draw();
}

void Sequencer::setPositionWithOrigin(const float x, const float y)
{
    UIComponent::setPositionWithOrigin(x, y);
    
    grid.setPositionWithOrigin(x, y);
    cursor.setPositionWithOrigin(x, y);
    sequence.setPositionWithOrigin(x, y);
}

void Sequencer::setPositionWithCentre(const float x, const float y)
{
    UIComponent::setPositionWithCentre(x, y);
    
    grid.setPositionWithCentre(x, y);
    sequence.setPositionWithCentre(x, y);
    cursor.setPositionWithOrigin(origin.x, origin.y);
}

void Sequencer::setSizeFromCentre(const float width, const float height)
{
    UIComponent::setSizeFromCentre(width, height);
    
    grid.setSizeFromCentre(width, height);
    sequence.setSizeFromCentre(width, height);
    sequence.gridDimensionsDidUpdate();
    const int cellSize = grid.getGridCellSize();
    cursor.setSizeFromCentre(cellSize, cellSize);
}

void Sequencer::setSize(const float width, const float height)
{
    UIComponent::setSize(width, height);
    
    grid.setSize(width, height);
    sequence.setSize(width, height);
    sequence.gridDimensionsDidUpdate();
    const int cellSize = grid.getGridCellSize();
    cursor.setSize(cellSize, cellSize);
}

void Sequencer::setMargins(const int top, const int left, const int right, const int bottom)
{
    UIComponent::setMargins(top, left, right, bottom);
    
    grid.setMargins(top, left, right, bottom);
    cursor.setMargins(top, left, right, bottom);
    sequence.setMargins(top, left, right, bottom);
}

// MARK: - Clock Controls

void Sequencer::toggleClock() noexcept
{
    clock.toggleClock();
    midiServer.release();
}

void Sequencer::moveCursor(Direction direction) noexcept
{
    cursor.move(direction, grid.getGridDimensions());
}

void Sequencer::placeNote(uint8_t noteNumber) noexcept
{
    const MIDINote note = { noteNumber, cursor.getMIDISettings() };

    sequence.placeNote(note, cursor.getGridPosition());
}

void Sequencer::placePortal() noexcept
{
    sequence.placePortal(cursor.getGridPosition());
}

void Sequencer::placePlayhead() noexcept
{
    sequence.placePlayhead(cursor.getGridPosition());
}

void Sequencer::placeRedirect(Redirection type) noexcept
{
    sequence.placeRedirect(type, cursor.getGridPosition());
}

void Sequencer::eraseFromCurrentPosition() noexcept
{
    sequence.eraseFromPosition(cursor.getGridPosition());
}

//  Ensemble
//  Created by David Spry on 20/12/20.

#include "Sequencer.hpp"

Sequencer::Sequencer():
UIComponent(), cursor(grid.getGridCellSize())
{
    const int cellSize = grid.getGridCellSize() * 2;
    setMargins(cellSize, cellSize, cellSize, 0);
    
    clock.connect(this);

    UIPoint<int> xy;
    
    xy.x = 14;
    xy.y = 11;
    playheads.emplace_back(grid.getGridCellSize(), xy, 1, 0);
    
    xy.x = 8;
    xy.y = 8;
    playheads.emplace_back(grid.getGridCellSize(), xy, 0, 1);
}

Sequencer::Sequencer(int x, int y, int width, int height):
UIComponent(x, y, width, height), cursor(grid.getGridCellSize())
{
    const int cellSize = grid.getGridCellSize() * 2;
    setMargins(cellSize, cellSize, cellSize, 0);
}

// MARK: - UIComponent Drawing

void Sequencer::draw()
{
    grid.draw();
    
    ofPushMatrix();
    ofTranslate(origin.x + margins.l, origin.y + margins.t);
    
    cursor.draw();

    for (auto& playhead : playheads)
        playhead.draw();
    
    for (auto& redirect : redirects)
        redirect.draw();
    
    ofPopMatrix();
}

void Sequencer::tick()
{
    const auto dimensions = grid.getGridDimensions();
    for (auto& playhead : playheads)
    {
        const UIPoint<int> originalPosition = playhead.xy;

        playhead.update(dimensions);

        for (auto& redirect : redirects)
        {
            if (playhead.xy.x == redirect.xy.x &&
                playhead.xy.y == redirect.xy.y)
            {
                redirect.interact(playhead, grid.getGridDimensions());
            }
        }

        if (playhead.xy == originalPosition)
            playhead.update(dimensions);

        for (auto& redirect : redirects)
        {
            if (playhead.xy.x == redirect.xy.x &&
                playhead.xy.y == redirect.xy.y)
            {
                redirect.interact(playhead, grid.getGridDimensions());
            }
        }
    }
}

void Sequencer::setPositionWithOrigin(const float x, const float y)
{
    UIComponent::setPositionWithOrigin(x, y);
    grid.setPositionWithOrigin(x, y);
}

void Sequencer::setPositionWithCentre(const float x, const float y)
{
    UIComponent::setPositionWithCentre(x, y);
    grid.setPositionWithCentre(x, y);
}

void Sequencer::setSizeFromCentre(const float width, const float height)
{
    grid.setSizeFromCentre(width, height);
    cursor.setSizeFromCentre(grid.getGridCellSize(), grid.getGridCellSize());
    UIComponent::setSizeFromCentre(width, height);
}

void Sequencer::setSize(const float width, const float height)
{
    grid.setSize(width, height);
    cursor.setSize(grid.getGridCellSize(), grid.getGridCellSize());
    UIComponent::setSize(width, height);
}

void Sequencer::setMargins(const int top, const int left, const int right, const int bottom)
{
    grid.setMargins(top, left, right, bottom);
    UIComponent::setMargins(top, left, right, bottom);
}

// MARK: - Clock Controls

void Sequencer::toggleClock() noexcept
{
    clock.toggleClock();
}

// MARK: - Sequencer API

void Sequencer::moveCursor(Direction direction) noexcept
{
    cursor.move(direction, grid.getGridDimensions());
}

void Sequencer::placeRedirect(Redirection type) noexcept
{
    redirects.emplace_back(grid.getGridCellSize(), cursor.xy, type);
}

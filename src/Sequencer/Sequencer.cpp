//  Ensemble
//  Created by David Spry on 20/12/20.

#include "Sequencer.hpp"

Sequencer::Sequencer():
UIComponent()
{
    
}

Sequencer::Sequencer(int x, int y, int width, int height):
UIComponent(x, y, width, height)
{
    
}

// MARK: - UIComponent Drawing

void Sequencer::draw()
{
    grid.draw();
}

void Sequencer::setPositionWithOrigin(const float x, const float y)
{
    grid.setPositionWithOrigin(x, y);
    UIComponent::setPositionWithOrigin(x, y);
}

void Sequencer::setPositionWithCentre(const float x, const float y)
{
    grid.setPositionWithCentre(x, y);
    UIComponent::setPositionWithCentre(x, y);
}

void Sequencer::setSizeFromCentre(const float width, const float height)
{
    grid.setSizeFromCentre(width, height);
    UIComponent::setSizeFromCentre(width, height);
}

void Sequencer::setSize(const float width, const float height)
{
    grid.setSize(width, height);
    UIComponent::setSize(width, height);
}

void Sequencer::setMargins(const int top, const int left, const int right, const int bottom)
{
    grid.setMargins(top, left, right, bottom);
    UIComponent::setMargins(top, left, right, bottom);
}

// MARK: - Sequencer API

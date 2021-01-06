//  Ensemble
//  Created by David Spry on 6/1/21.

#include "InformationWindow.hpp"

InformationWindow::InformationWindow():
UIWindow()
{
    initialiseLabels();
}

InformationWindow::InformationWindow(int x, int y, int width, int height):
UIWindow(x, y, width, height)
{
    setSize(width, height);
    setPositionWithOrigin(x, y);

    initialiseLabels();
}

// MARK: - Child Components

void InformationWindow::layoutChildComponents() noexcept
{
    description.setText("DESCRIPTION");
    description.shrinkToFitText();
    description.setShouldFillBackground(true);
    description.setPositionWithOrigin(margins.l, 15);
    
    position.setText("NxM");
    position.shrinkToFitText();
    position.setShouldFillBackground(true);
    position.setPositionWithOrigin(margins.l, size.h - 30 - position.getSize().h);
    
    polyphony.setText("........\n........");
    polyphony.shrinkToFitText();
    polyphony.setShouldFillBackground(true);
    polyphony.setPositionWithOrigin(size.w - polyphony.getSize().w - margins.r, 15);
}

// MARK: - Drawing

void InformationWindow::draw()
{
    if (shouldRedraw)
    {
        layoutChildComponents();
        shouldRedraw = false;
    }
    
    UIWindow::draw();
}

// MARK: - UIComponent callbacks

void InformationWindow::setSize(const float width, const float height)
{
    UIWindow::setSize(width, height);
    
    
}

void InformationWindow::setSizeFromCentre(const float width, const float height)
{
    UIWindow::setSizeFromCentre(width, height);
    
    
}

void InformationWindow::setPositionWithOrigin(const int x, const int y)
{
    UIWindow::setPositionWithOrigin(x, y);
    
    
}

void InformationWindow::setPositionWithCentre(const int x, const int y)
{
    UIWindow::setPositionWithCentre(x, y);
    
    
}

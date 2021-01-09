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

    cursorMidiSettings.setText("O3:C1:V100");
    cursorMidiSettings.shrinkToFitText();
    cursorMidiSettings.setShouldFillBackground(true);
    cursorMidiSettings.setPositionWithOrigin(margins.l, size.h - 30 - cursorMidiSettings.getSize().h);
    
    position.setText("NxM");
    position.shrinkToFitText();
    position.setShouldFillBackground(true);
    position.setPositionWithOrigin(margins.l, size.h - 30 - cursorMidiSettings.getSize().h - position.getSize().h);

    polyphony.setText("........\n........");
    polyphony.shrinkToFitText();
    polyphony.setShouldFillBackground(true);
    polyphony.setPositionWithOrigin(size.w - polyphony.getSize().w - margins.r, 15);
    
    midiOutPort.setText("O: IAC Driver");
    midiOutPort.shrinkToFitText();
    midiOutPort.setShouldFillBackground(true);
    midiOutPort.setPositionWithOrigin(size.w - midiOutPort.getSize().w - margins.r,
                                      size.h - 30 - midiOutPort.getSize().h);
    
    midiInPort.setText("I: 0");
    midiInPort.shrinkToFitText();
    midiInPort.setShouldFillBackground(true);
    midiInPort.setPositionWithOrigin(size.w - midiInPort.getSize().w - margins.r,
                                     size.h - 30 - midiOutPort.getSize().h - midiInPort.getSize().h);
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

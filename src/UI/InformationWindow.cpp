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

void InformationWindow::updateLabelsContents() noexcept
{
    if (stateDescription != nullptr && stateDescription->containsUpdatedData)
    {
        std::string state;

        description.setText(stateDescription->cursorHoverDescription);

        state.reserve(64);
        state.append("O" + std::to_string(stateDescription->cursorOctave)   + ":");
        state.append("C" + std::to_string(stateDescription->cursorChannel)  + ":");
        state.append("V" + std::to_string(stateDescription->cursorVelocity));
        cursorMidiSettings.setText(state);
        
        state.clear();
        state.append(std::to_string(stateDescription->cursorGridPosition.x));
        state.append("x");
        state.append(std::to_string(stateDescription->cursorGridPosition.y));
        position.setText(state);
        
        state.clear();
        state.append("I: ");
        state.append(Utilities::stringWithLength(stateDescription->midiPortDescriptionIn,  16));
        midiInPort.setText(state);
        
        state.clear();
        state.append("O: ");
        state.append(Utilities::stringWithLength(stateDescription->midiPortDescriptionOut, 16));
        midiOutPort.setText(state);

        polyphony.setText(computePolyphonyString(8, stateDescription->midiPolyphony));

        stateDescription->setDataWasConsumed();
        
        setShouldRedraw();
    }
}

const std::string InformationWindow::computePolyphonyString(uint8_t width, uint8_t polyphony) const noexcept
{
    std::string string;
    std::pair<int, int> rows;

    rows.first  = std::min(polyphony, width);
    rows.second = polyphony - rows.first;
    
    string.append(rows.first, '|');
    string.append(width - rows.first, '.');
    string.append("\n");

    string.append(rows.second, '|');
    string.append(width - rows.second, '.');

    return string;
}

void InformationWindow::layoutChildComponents() noexcept
{
    description.shrinkToFitText();
    description.setShouldFillBackground(true);
    description.setPositionWithOrigin(margins.l, 15);

    cursorMidiSettings.shrinkToFitText();
    cursorMidiSettings.setShouldFillBackground(true);
    cursorMidiSettings.setPositionWithOrigin(margins.l, size.h - 30 - cursorMidiSettings.getSize().h);

    position.shrinkToFitText();
    position.setShouldFillBackground(true);
    position.setPositionWithOrigin(margins.l, size.h - 30 - cursorMidiSettings.getSize().h - position.getSize().h);

    polyphony.shrinkToFitText();
    polyphony.setShouldFillBackground(true);
    polyphony.setPositionWithOrigin(size.w - polyphony.getSize().w - margins.r, 15);

    midiOutPort.shrinkToFitText();
    midiOutPort.setShouldFillBackground(true);
    midiOutPort.setPositionWithOrigin(size.w - midiOutPort.getSize().w - margins.r,
                                      size.h - 30 - midiOutPort.getSize().h);

    midiInPort.shrinkToFitText();
    midiInPort.setShouldFillBackground(true);
    midiInPort.setPositionWithOrigin(size.w - midiInPort.getSize().w - margins.r,
                                     size.h - 30 - midiOutPort.getSize().h - midiInPort.getSize().h);
}

// MARK: - Drawing

void InformationWindow::draw()
{
    updateLabelsContents();
    
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
    
    layoutChildComponents();
}

void InformationWindow::setSizeFromCentre(const float width, const float height)
{
    UIWindow::setSizeFromCentre(width, height);
    
    layoutChildComponents();
}

void InformationWindow::setPositionWithOrigin(const int x, const int y)
{
    UIWindow::setPositionWithOrigin(x, y);
    
    layoutChildComponents();
}

void InformationWindow::setPositionWithCentre(const int x, const int y)
{
    UIWindow::setPositionWithCentre(x, y);
    
    layoutChildComponents();
}

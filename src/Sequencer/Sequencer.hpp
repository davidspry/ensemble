//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include "Ensemble.h"
#include "Cursor.h"
#include "DotGrid.h"
#include "Sequence.hpp"

class Sequencer: public UIComponent
{
public:
    Sequencer();
    Sequencer(int x, int y, int width, int height);
    ~Sequencer();

public:
    void draw() override;
    void setPositionWithOrigin(const float x, const float y) override;
    void setPositionWithCentre(const float x, const float y) override;
    void setSizeFromCentre(const float width, const float height) override;
    void setSize(const float width, const float height) override;
    void setMargins(const int top, const int left, const int right, const int bottom) override;
    
public:
    void toggleClock() noexcept;
    
public:
    void moveCursor(Direction direction) noexcept;
    void placeNote(uint8_t noteNumber) noexcept;
    void placePortal() noexcept;
    void placePlayhead() noexcept;
    void placeRedirect(Redirection type) noexcept;
    void eraseFromCurrentPosition() noexcept;

private:
    Clock      clock;
    Cursor     cursor;
    DotGrid    grid;
    Sequence   sequence;
    MIDIServer midiServer;
};

#endif

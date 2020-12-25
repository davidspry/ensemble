//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include "Ensemble.h"
#include "Cursor.h"
#include "DotGrid.h"
#include "Grid.h"

#include "SampleClock.h"

class Sequencer: public UIComponent, public ClockListener
{
public:
    Sequencer();
    Sequencer(int x, int y, int width, int height);
    
public:
    void draw() override;
    void setPositionWithOrigin(const float x, const float y) override;
    void setPositionWithCentre(const float x, const float y) override;
    void setSizeFromCentre(const float width, const float height) override;
    void setSize(const float width, const float height) override;
    void setMargins(const int top, const int left, const int right, const int bottom) override;
    
public:
    void tick() override;
    void toggleClock() noexcept;
    
public:
    void placeNote(MIDINote note) noexcept;
    void placeRedirect(Redirection type) noexcept;
    void eraseFromCurrentPosition() noexcept;
    void moveCursor(Direction direction) noexcept;

private:
    DotGrid grid;
    Cursor cursor;
    
private:
    SampleClock clock;
    std::vector<SQPlayhead> playheads;
    std::vector<SQRedirect> redirects;
};

#endif

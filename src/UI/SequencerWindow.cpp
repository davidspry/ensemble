//  Ensemble
//  Created by David Spry on 6/1/21.

#include "SequencerWindow.hpp"

SequencerWindow::SequencerWindow():
UIWindow()
{
    addChildComponent(&sequencer);
}

SequencerWindow::SequencerWindow(int x, int y, int width, int height):
UIWindow(x, y, width, height)
{
    setSize(width, height);
    setPositionWithOrigin(x, y);

    addChildComponent(&sequencer);
}

// MARK: - UIComponent callbacks

void SequencerWindow::setSize(const float width, const float height)
{
    UIWindow::setSize(width, height);
    
    sequencer.setSize(width, height);
    sequencer.setPositionWithCentre(centre.x, centre.y);
}

void SequencerWindow::setSizeFromCentre(const float width, const float height)
{
    UIWindow::setSizeFromCentre(width, height);
    
    sequencer.setSize(width, height);
    sequencer.setPositionWithCentre(centre.x, centre.y);
}

void SequencerWindow::setPositionWithOrigin(const int x, const int y)
{
    UIWindow::setPositionWithOrigin(x, y);
    sequencer.setPositionWithCentre(centre.x, centre.y);
}

void SequencerWindow::setPositionWithCentre(const int x, const int y)
{
    UIWindow::setPositionWithCentre(x, y);
    sequencer.setPositionWithCentre(x, y);
}

const UIMargins<int>& SequencerWindow::getMargins() const noexcept
{
    return sequencer.getMargins();
}

// MARK: - Commandable callbacks

void SequencerWindow::keyPressed(int key) noexcept
{
//    printf("%d\n", key);
    modifiers.keyPressed(key);
    
    switch (key)
    {
        case K_UArrow: { return sequencer.moveCursor(Direction::N); }
        case K_DArrow: { return sequencer.moveCursor(Direction::S); }
        case K_LArrow: { return sequencer.moveCursor(Direction::W); }
        case K_RArrow: { return sequencer.moveCursor(Direction::E); }
            
        case K_Space:  { return sequencer.toggleClock(); }
        case K_Delete: { return sequencer.eraseFromCurrentPosition(); }
        case K_Tab:    { return sequencer.expandSubsequence(); }

        case K_Plus:   { return sequencer.placePlayhead(Direction::S); }
            
        case K_LowerA: { sequencer.placeNote(0x9); return; }
        case K_LowerB: { sequencer.placeNote(0xB); return; }
        case K_LowerC: { sequencer.placeNote(0x0); return; }
        case K_LowerD: { sequencer.placeNote(0x2); return; }
        case K_LowerE: { sequencer.placeNote(0x4); return; }
        case K_LowerF: { sequencer.placeNote(0x5); return; }
        case K_LowerG: { sequencer.placeNote(0x7); return; }
            
        case K_UpperA: { sequencer.placeNote(0xA); return; }
        case K_UpperB: { sequencer.placeNote(0xC); return; }
        case K_UpperC: { sequencer.placeNote(0x1); return; }
        case K_UpperD: { sequencer.placeNote(0x3); return; }
        case K_UpperE: { sequencer.placeNote(0x5); return; }
        case K_UpperF: { sequencer.placeNote(0x6); return; }
        case K_UpperG: { sequencer.placeNote(0x8); return; }

        case K_LowerX: { sequencer.placeRedirect(Redirection::X); return; }
        case K_LowerY: { sequencer.placeRedirect(Redirection::Y); return; }
        case K_LowerV: { sequencer.placeRedirect(Redirection::Alternating); return; }
        case K_LowerL: { sequencer.placeRedirect(Redirection::Diagonal); return; }
        case K_LowerR: { sequencer.placeRedirect(Redirection::Random); return; }
        
        case K_LowerP: { sequencer.placePortal(); return; }
        
        case K_Tilde:
        case K_NRow0:  { sequencer.setCursorOctave(0); return; }
        case K_NRow1:  { sequencer.setCursorOctave(1); return; }
        case K_NRow2:  { sequencer.setCursorOctave(2); return; }
        case K_NRow3:  { sequencer.setCursorOctave(3); return; }
        case K_NRow4:  { sequencer.setCursorOctave(4); return; }
        case K_NRow5:  { sequencer.setCursorOctave(5); return; }
        case K_NRow6:  { sequencer.setCursorOctave(6); return; }
            
        case K_RSqrBracket: { sequencer.selectNextCursorChannel();     return; }
        case K_LSqrBracket: { sequencer.selectPreviousCursorChannel(); return; }

        case K_Enter:       { sequencer.toggleSelectedPlayhead();    return; }
        case K_BSlash:      { sequencer.toggleSelectPlayheadsMode(); return; }
        case K_Pipe:        { sequencer.selectNextPlayhead();        return; }

        default: return;
    }
}

void SequencerWindow::keyReleased(int key) noexcept
{
    modifiers.keyReleased(key);
}

void SequencerWindow::mousePressed(int x, int y, int buttonIndex) noexcept
{
    switch (buttonIndex)
    {
        case M_ButtonL: return;
        case M_ButtonM: return;
        case M_ButtonR: return sequencer.moveCursorToScreenPosition(x, y);
        default:        return;
    }
}

void SequencerWindow::mouseDragged(int x, int y, int buttonIndex) noexcept
{
    switch (buttonIndex)
    {
        case M_ButtonL: return;
        case M_ButtonM: return;
        case M_ButtonR: return sequencer.moveCursorToScreenPosition(x, y);
        default:        return;
    }
}

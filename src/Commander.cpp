#include "Commander.hpp"

Commander::Commander()
{
    windowResized(ofGetWidth(), ofGetHeight());
}

void Commander::setup()
{
    ui.addChildComponent(&sequencer);
}

void Commander::update()
{

}

void Commander::draw()
{
    ui.draw();
}

void Commander::keyPressed(int key)
{
//    printf("%d\n", key);
    switch (key)
    {
        case K_UArrow: { return sequencer.moveCursor(Direction::N); }
        case K_DArrow: { return sequencer.moveCursor(Direction::S); }
        case K_LArrow: { return sequencer.moveCursor(Direction::W); }
        case K_RArrow: { return sequencer.moveCursor(Direction::E); }
            
        case K_Space:  { return sequencer.toggleClock(); }
        case K_Delete: { return sequencer.eraseFromCurrentPosition(); }
        
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
        case K_NRow0:  { return sequencer.setCursorOctave(0); }
        case K_NRow1:  { return sequencer.setCursorOctave(1); }
        case K_NRow2:  { return sequencer.setCursorOctave(2); }
        case K_NRow3:  { return sequencer.setCursorOctave(3); }
        case K_NRow4:  { return sequencer.setCursorOctave(4); }
        case K_NRow5:  { return sequencer.setCursorOctave(5); }
        case K_NRow6:  { return sequencer.setCursorOctave(6); }

        default: return;
    }
}

void Commander::keyReleased(int key)
{
    
}

void Commander::mouseEntered(int x, int y)
{
    
}

void Commander::mouseExited(int x, int y)
{
    
}

void Commander::mouseMoved(int x, int y)
{
    
}

void Commander::mousePressed(int x, int y, int button)
{
    sequencer.moveCursorToScreenPosition(x, y);
}

void Commander::mouseReleased(int x, int y, int button)
{
    
}

void Commander::mouseDragged(int x, int y, int button)
{
    sequencer.moveCursorToScreenPosition(x, y);
}

void Commander::windowResized(int w, int h)
{
    size.w = w;
    size.h = h;
    centre.x = static_cast<int>(static_cast<float>(w) * 0.5f);
    centre.y = static_cast<int>(static_cast<float>(h) * 0.5f);

    ui.setPositionWithCentre(centre.x, centre.y);
    
    UIRect grid = ui.getBounds();
    UIRect menu = grid.removeFromBottom(140);
    UIRect left = menu.removeFromLeft(125).trimFromLeft(25);
    
    sequencer.setSize(grid.width, grid.height);
    sequencer.setPositionWithCentre(grid.getCenter().x, grid.getCenter().y);
}

void Commander::gotMessage(ofMessage msg)
{
    
}

void Commander::dragEvent(ofDragInfo dragInfo)
{
    
}

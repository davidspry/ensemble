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
        
        case K_Plus:   { return sequencer.placePlayhead(); }
            
        case K_LowerA: { return sequencer.placeNote(9);  }
        case K_LowerB: { return sequencer.placeNote(11); }
        case K_LowerC: { return sequencer.placeNote(0);  }
        case K_LowerD: { return sequencer.placeNote(2);  }
        case K_LowerE: { return sequencer.placeNote(4);  }
        case K_LowerF: { return sequencer.placeNote(5);  }
        case K_LowerG: { return sequencer.placeNote(7);  }
            
        case K_UpperA: { return sequencer.placeNote(10); }
        case K_UpperB: { return sequencer.placeNote(12); }
        case K_UpperC: { return sequencer.placeNote(1);  }
        case K_UpperD: { return sequencer.placeNote(3);  }
        case K_UpperE: { return sequencer.placeNote(5);  }
        case K_UpperF: { return sequencer.placeNote(6);  }
        case K_UpperG: { return sequencer.placeNote(8);  }

        case K_LowerX: { return sequencer.placeRedirect(Redirection::X); }
        case K_LowerY: { return sequencer.placeRedirect(Redirection::Y); }
        case K_LowerV: { return sequencer.placeRedirect(Redirection::Alternating); }
        case K_LowerL: { return sequencer.placeRedirect(Redirection::Diagonal); }
        case K_LowerR: { return sequencer.placeRedirect(Redirection::Random); }
            
        case K_LowerP: { return sequencer.placePortal(); }

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
    
}

void Commander::mouseReleased(int x, int y, int button)
{
    
}

void Commander::mouseDragged(int x, int y, int button)
{
    
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

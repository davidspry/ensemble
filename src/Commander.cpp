#include "Commander.hpp"

Commander::Commander()
{
    windowResized(ofGetWidth(), ofGetHeight());
}

void Commander::setup()
{
    UIRect window  = ui.getBounds();
    UIRect options = window.removeFromBottom(150);
    
    sequencer.setMargins(20, 20, 20, 0);
    sequencer.setSize(window.width, window.height);
    sequencer.setPositionWithCentre(window.getCenter().x, window.getCenter().y);

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
    centre.x = static_cast<float>(w) * 0.5f;
    centre.y = static_cast<float>(h) * 0.5f;

    ui.setPositionWithCentre(centre.x, centre.y);
}

void Commander::gotMessage(ofMessage msg)
{
    
}

void Commander::dragEvent(ofDragInfo dragInfo)
{
    
}

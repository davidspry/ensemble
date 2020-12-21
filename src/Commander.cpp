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

    UIRect grid = ui.getBounds();
    UIRect menu = grid.removeFromBottom(150);

    sequencer.setMargins(50, 50, 50, 0);
    sequencer.setSize(grid.width, grid.height);
    sequencer.setPositionWithCentre(grid.getCenter().x, grid.getCenter().y);
}

void Commander::gotMessage(ofMessage msg)
{
    
}

void Commander::dragEvent(ofDragInfo dragInfo)
{
    
}

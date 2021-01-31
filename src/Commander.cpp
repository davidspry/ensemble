#include "Commander.hpp"

Commander::Commander()
{
    windowResized(ofGetWidth(), ofGetHeight());
}

void Commander::setup()
{
    auto & state = sequencerWindow.getSequencer().getSequencerStateDescription();

    informationWindow.setStateDescription(&state);
}

void Commander::update()
{
    
}

void Commander::draw()
{
    sequencerWindow.draw();
    informationWindow.draw();
}

void Commander::keyPressed(int key)
{
    sequencerWindow.keyPressed(key);
    informationWindow.keyPressed(key);
}

void Commander::keyReleased(int key)
{
    sequencerWindow.keyReleased(key);
    informationWindow.keyReleased(key);
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
    if (sequencerWindow.containsPoint(x, y))
    {
        sequencerWindow.mousePressed(x, y, button);
    }
    
    if (informationWindow.containsPoint(x, y))
    {
        informationWindow.mousePressed(x, y, button);
    }
}

void Commander::mouseReleased(int x, int y, int button)
{
    
}

void Commander::mouseDragged(int x, int y, int button)
{
    if (sequencerWindow.containsPoint(x, y))
    {
        sequencerWindow.mouseDragged(x, y, button);
    }
    
    if (informationWindow.containsPoint(x, y))
    {
        informationWindow.mouseDragged(x, y, button);
    }
}

void Commander::windowResized(int w, int h)
{
    size.w = w;
    size.h = h;
    centre.x = static_cast<int>(static_cast<float>(w) * 0.5f);
    centre.y = static_cast<int>(static_cast<float>(h) * 0.5f);

    UIRect grid (size);
    UIRect menu = grid.removeFromBottom(140);

    sequencerWindow  .setBounds(grid);
    informationWindow.setBounds(menu);
    informationWindow.setMargins(sequencerWindow.getMargins());
}

void Commander::gotMessage(ofMessage msg)
{
    
}

void Commander::dragEvent(ofDragInfo dragInfo)
{
    
}

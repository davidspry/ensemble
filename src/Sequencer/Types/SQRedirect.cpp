//  Ensemble
//  Created by David Spry on 9/1/21.

#include "SQRedirect.h"

void SQRedirect::draw()
{
    const int x = origin.x + margins.l + screenPosition.x;
    const int y = origin.y + margins.t + screenPosition.y;

    if (shouldRedraw)
    {
        path.clear();
        path.rectangle(0, 0, size.w, size.h);
        path.setColor(getRedirectionTypeColour());
        text.setPositionWithOrigin(x, y);
        shouldRedraw = false;
    }
    
    path.draw(x, y);
    text.draw();
}

ofColor SQRedirect::getRedirectionTypeColour() noexcept
{
    switch (redirection)
    {
        case Redirection::X:           return ofxRisographColours::sky_blue;
        case Redirection::Y:           return ofxRisographColours::crimson;
        case Redirection::Diagonal:    return ofxRisographColours::light_mauve;
        case Redirection::Alternating: return ofxRisographColours::grass;
        case Redirection::Random:      return ofxRisographColours::apricot;
        default: return colours->foregroundColour;
    }
}

void SQRedirect::interact(SQNode& node, MIDIServer& server, const UISize<int>& gridSize) noexcept
{
    if (node.delta.x == 0 && node.delta.y == 0)
        return;

    switch (readBasicRedirectionType())
    {
        case Redirection::X:
        {
                 if (node.delta.x == 0) turn(node);
            else if (node.delta.y == 0) reverse(node);
            else setInHorizontalDirection(node);
            break;
        }
        
        case Redirection::Y:
        {
                 if (node.delta.x == 0) reverse(node);
            else if (node.delta.y == 0) turn(node);
            else setInVerticalDirection(node);
            break;
        }
        
        case Redirection::Diagonal:
        {
            if (node.delta.x == 0 || node.delta.y == 0)
                 diagonalise(node);
            else turn(node);
            break;
        }
            
        default: return;
    }
    
    const int row = (xy.y + node.delta.y + gridSize.h) % gridSize.h;
    const int col = (xy.x + node.delta.x + gridSize.w) % gridSize.w;
    node.moveToGridPosition(row, col);
    updateRedirectionIfNeeded();
}

std::string SQRedirect::describe() noexcept
{
    switch (readBasicRedirectionType())
    {
        case Redirection::X: return "REDIRECT X";
        case Redirection::Y: return "REDIRECT Y";
        case Redirection::Diagonal: return "REDIRECT DIAGONAL";
        default: return "REDIRECT";
    }
}

Redirection SQRedirect::readBasicRedirectionType() noexcept
{
    switch (redirection)
    {
        case Redirection::X:
        case Redirection::Y:
        case Redirection::Diagonal:
        {
            return redirection;
        }
            
        case Redirection::Alternating:
        {
            return static_cast<Redirection>(static_cast<int>(state));
        }
            
        case Redirection::Random:
        {
            return static_cast<Redirection>(static_cast<int>(choice));
        }
    }
}

void SQRedirect::updateRedirectionIfNeeded() noexcept
{
    switch (redirection)
    {
        case Redirection::Alternating:
        {
            state = !state;
            const Redirection r = static_cast<Redirection>(static_cast<int>(state));
            return updateLabelText(r);
        }
            
        case Redirection::Random:
        {
            choice = ofRandom(3);
            const Redirection r = static_cast<Redirection>(choice);
            return updateLabelText(r);
        }

        default: return;
    }
}
    
void SQRedirect::updateLabelText(Redirection type) noexcept
{
    switch (type)
    {
        case Redirection::X: { return text.setText("X"); }
        case Redirection::Y: { return text.setText("Y"); }
        case Redirection::Diagonal: { return text.setText("Z"); }
        default: { return text.setText("?"); }
    }
}

void SQRedirect::turn(SQNode& node) noexcept
{
    const int x = -node.delta.y;
    const int y = +node.delta.x;
    
    node.delta.set(x, y);
}

void SQRedirect::reverse(SQNode& node) noexcept
{
    const int x = -node.delta.x;
    const int y = -node.delta.y;
    
    node.delta.set(x, y);
}

void SQRedirect::setInVerticalDirection(SQNode& node) noexcept
{
    const int x = 0;
    const int y = -node.delta.y;
    
    node.delta.set(x, y);
}

void SQRedirect::setInHorizontalDirection(SQNode& node) noexcept
{
    const int x = -node.delta.x;
    const int y = 0;
    
    node.delta.set(x, y);
}

void SQRedirect::diagonalise(SQNode& node) noexcept
{
    const int x = node.delta.x == +1 ? -1 : +1;
    const int y = node.delta.y == -1 ? +1 : -1;
    
    node.delta.set(x, y);
}

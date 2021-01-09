//  Ensemble
//  Created by David Spry on 9/1/21.

#include "Label.h"

void Label::shrinkToFitText() noexcept
{
    const auto bounds = font.getStringBoundingBox(text, 0, 0);
    const auto width  = bounds.width  + margins.l + margins.r;
    const auto height = bounds.height + margins.t + margins.b;

    setSize(width, height);
}

void Label::draw()
{
    ofPushStyle();
    ofPushMatrix();
    
    if (shouldRedraw)
    {
        setTextAlignment(horizontalTextAlignment, verticalTextAlignment);
        shouldRedraw = false;
    }
    
    if (shouldFillBackground)
    {
        const UIRect r = getBounds();
        ofSetColor(colours->accentColour);
        ofDrawRectangle(r);
    }

    ofSetColor(colours->textColour);
    ofTranslate(origin.x, origin.y);
    
    font.drawString(text, textOrigin.x, textOrigin.y);
    
    ofPopMatrix();
    ofPopStyle();
}

void Label::setTextAlignment(HorizontalAlignment horizontal, VerticalAlignment vertical) noexcept
{
    const auto lineHeight = font.getLineHeight();
    const auto bounds = font.getStringBoundingBox(text, 0, 0);

    using H = HorizontalAlignment;
    switch (horizontal)
    {
        case H::Left:   { textOrigin.x = margins.l; break; }
        case H::Right:  { textOrigin.x = size.w - margins.r - bounds.width; break; }
        case H::Centre: {
            const int frame = size.w - margins.l - margins.r;
            textOrigin.x = margins.l + (frame - bounds.width) * 0.5f;
            break;
        }
    }

    using V = VerticalAlignment;
    switch (vertical)
    {
        case V::Top:    { textOrigin.y = margins.t + lineHeight; break; }
        case V::Bottom: { textOrigin.y = size.h - margins.b - bounds.height + lineHeight; break; }
        case V::Centre: {
            const int frame = size.h - margins.t - margins.b;
            textOrigin.y = margins.t + (frame - bounds.height) * 0.5f + lineHeight;
            break;
        }
    }

    verticalTextAlignment   = vertical;
    horizontalTextAlignment = horizontal;
}

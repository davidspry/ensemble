//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef LABEL_H
#define LABEL_H

#include "ofMain.h"
#include "Constants.h"
#include "UIComponent.h"

class Label: public UIComponent
{
public:
    Label():
    UIComponent()
    {
        setSize(50, 25);
        setFont("JetBrainsMono-Medium.ttf", 10);
        setText("Label");
        setTextAlignment(HorizontalAlignment::Centre, VerticalAlignment::Centre);
    }

public:
    void draw() override
    {
        ofPushStyle();
        ofPushMatrix();
        ofSetColor(colours.textColour);
        
        if (shouldFillBackground)
        {
            const UIRect r = getInnerBounds();
            ofSetColor(colours.accentColour);
            ofDrawRectangle(r);
        }

        ofSetColor(colours.textColour);
        ofTranslate(origin.x, origin.y);
        font->drawString(text, textOrigin.x, textOrigin.y);
        
        ofPopMatrix();
        ofPopStyle();
    }
    
    /// @brief Match the size of the label to the size of the label's text

    void shrinkToFitText() noexcept
    {
        const auto bounds = font->getStringBoundingBox(text, 0, 0);

        setSize(bounds.width, bounds.height);
    }
    
    inline void setSize(const float width, const float height) override
    {
        UIComponent::setSize(width, height);

        setTextAlignment(horizontalTextAlignment, verticalTextAlignment);

        setShouldRedraw();
    }
    
    inline void setSizeFromCentre(const float width, const float height) override
    {
        UIComponent::setSizeFromCentre(width, height);
        
        setTextAlignment(horizontalTextAlignment, verticalTextAlignment);

        setShouldRedraw();
    }
    
    inline void setMargins(const int marginSize) override
    {
        this->setMargins(marginSize, marginSize, marginSize, marginSize);
    }
    
    inline void setMargins(UIMargins<int>& margins) override
    {
        this->setMargins(margins.t, margins.l, margins.r, margins.b);
    }
    
    inline void setMargins(const int top, const int left, const int right, const int bottom) override
    {
        UIComponent::setMargins(top, left, right, bottom);
        setTextAlignment(horizontalTextAlignment, verticalTextAlignment);
    }
    
    
public:
    /// @brief Set the label's text component.
    /// @param string The desired text.

    inline void setText(const char * string) noexcept
    {
        text = std::string(string);

        if (font != nullptr)
        {
            setTextAlignment(horizontalTextAlignment, verticalTextAlignment);
        }
    }

    /// @brief Get the label's text component.

    inline std::string_view getText() const noexcept
    {
        return {text};
    }
    
    /// @brief Indicate whether the label should fill its background with its background colour or not.
    /// @param fillBackground Whether the label should fill its background with its background colour or not.

    inline void setShouldFillBackground(bool fillBackground) noexcept
    {
        shouldFillBackground = fillBackground;
        setShouldRedraw();
    }
    
    /// @brief Set the label's font.
    /// @param filepath The filepath of the TrueTypeFont font file, relative to Ensemble's 'data' folder.
    /// @param pointSize The desired point size of the font.

    inline void setFont(const char * filepath, int pointSize) noexcept(false)
    {
        font = UIFontLibrary::get(filepath, pointSize);
    }
    
    /// @brief Set the label text's alignment in terms of its horizontal and veritcal positions.
    /// @param horizontal The desired horizontal position for the label's text.
    /// @param vertical The desired vertical position for the label's text.

    inline void setTextAlignment(HorizontalAlignment horizontal, VerticalAlignment vertical) noexcept
    {
        const ofRectangle bounds = font->getStringBoundingBox(text, 0, 0);

        using H = HorizontalAlignment;
        switch (horizontal)
        {
            case H::Left:   { textOrigin.x = margins.l; break; }
            case H::Centre: { textOrigin.x = (size.w - bounds.width) * 0.5f; break; }
            case H::Right:  { textOrigin.x = size.w - margins.r; break; }
        }

        using V = VerticalAlignment;
        switch (vertical)
        {
            case V::Top:    { textOrigin.y = margins.t + bounds.height; break; }
            case V::Centre: { textOrigin.y = (size.h + bounds.height) * 0.5f; break; }
            case V::Bottom: { textOrigin.y = size.h - margins.b; break; }
        }

        verticalTextAlignment = vertical;
        horizontalTextAlignment = horizontal;
    }

private:
    /// @brief Whether the label's background should be filled with the component's background colour or not.
    
    bool shouldFillBackground = false;

private:
    /// @brief The label's text component.

    std::string text;
    
    /// @brief The label's font.

    ofTrueTypeFont * font;
    
    /// @brief The origin point of the label's text.
    /// @note  ofTrueTypeFont uses the bottom-left corner as the origin point.

    UIPoint<int> textOrigin;
    
    /// @brief The horizontal alignment of the label's text.
    
    HorizontalAlignment horizontalTextAlignment;
    
    /// @brief The vertical alignment of the label's text.
    
    VerticalAlignment verticalTextAlignment;
};

#endif

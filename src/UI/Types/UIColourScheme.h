//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef UICOLOURSCHEME_H
#define UICOLOURSCHEME_H

#include "ofMain.h"
#include "ofxRisographColours.hpp"

/// @brief A colour scheme to be used by a `UIComponent`.

struct UIColourScheme
{
    ofColor backgroundColour;
    ofColor foregroundColour;
    ofColor secondaryForegroundColour;
    ofColor accentColour;
    ofColor textColour;
    
    /// @brief Construct a colour scheme by specifying each colour.
    /// @param background A background colour
    /// @param foreground A foreground colour
    /// @param secondary A secondary foreground colour
    /// @param accent An accent colour
    /// @param text A text colour

    UIColourScheme(ofColor background, ofColor foreground, ofColor secondary, ofColor accent, ofColor text)
    {
        backgroundColour = background;
        foregroundColour = foreground;
        secondaryForegroundColour = secondary;
        accentColour = accent;
        textColour = text;
    }
};

#endif

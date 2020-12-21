//  Ensemble
//  Created by David Spry on 21/12/20.

#ifndef UICOLOURSCHEME_H
#define UICOLOURSCHEME_H

#include "ofMain.h"
#include "ofxRisographColours.hpp"

/// @brief A colour scheme to be used by a `UIComponent`.

struct UIColourScheme
{
    ofColor backgroundColour = {225};
    
    ofColor foregroundColour = {15};
    
    ofColor accentColour     = {ofxRisographColours::ivy};
    
    ofColor textColour       = {15};
};

#endif

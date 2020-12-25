#include "ofMain.h"
#include "Themes.h"
#include "Commander.hpp"
#include "ofxWindowOptions.h"

constexpr int W = 900;
constexpr int H = 700;

int main()
{
    ofSetupOpenGL(W, H, OF_WINDOW);
    
    ofxWindowOptions::setMovableByWindowBackground(true);
    ofxWindowOptions::setTitleBarVisibility(false);
    ofxWindowOptions::setResizable(false);
    
    ofSetWindowPosition(35, 65); 
    ofSetCircleResolution(256);
    ofDisableAlphaBlending();
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofBackground(Themes::theme.backgroundColour);

    ofSetEscapeQuitsApp(false);

    ofRunApp(new Commander());
}

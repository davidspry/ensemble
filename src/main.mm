#include "ofMain.h"
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
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofBackground(215);

    ofSetEscapeQuitsApp(false);

    ofRunApp(new Commander());
}

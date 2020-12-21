#pragma once

#include "Ensemble.h"
#include "Sequencer.hpp"

class Commander: public ofBaseApp
{
public:
    Commander();
    
public:
    void setup()  override;
    void update() override;
    void draw()   override;

public:
    void keyPressed (int key) override;
    void keyReleased(int key) override;
    
public:
    void mouseEntered (int x, int y) override;
    void mouseExited  (int x, int y) override;
    void mouseMoved   (int x, int y) override;
    void mousePressed (int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseDragged (int x, int y, int button) override;

public:
    void windowResized(int w, int h)    override;
    void dragEvent(ofDragInfo dragInfo) override;

public:
    void gotMessage(ofMessage msg) override;
    
private:
    UISize <int> size;
    UIPoint<int> centre;
    UIWindow ui;

private:
    Sequencer sequencer;
};

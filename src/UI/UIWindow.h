//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef UIWINDOW_H
#define UIWINDOW_H

#include "UITypes.h"
#include "UIComponent.h"

class UIWindow: public UIComponent
{
public:
    UIWindow():
    UIComponent(0, 0, ofGetWidth(), ofGetHeight())
    {
        const int W = ofGetWidth();
        const int H = ofGetHeight();

        buffer.allocate(W, H);
    }
    
    UIWindow(int x, int y, int width, int height):
    UIComponent(x, y, width, height)
    {
        buffer.allocate(width, height);
    }

    ~UIWindow()
    {
        for (UIComponent* component : childComponents)
        {
            delete component;

            component = nullptr;
        }
    }

public:
    void draw() override
    {
        ofPushStyle();
        buffer.begin();
        ofClear(0, 0);
        
        for (UIComponent* component : childComponents)
            component->draw();
        
        buffer.end();

        ofSetColor(255);
        buffer.draw(origin.x, origin.y, size.w, size.h);
        ofPopStyle();
    }

public:
    /// @brief Add a child UIComponent to the UIWindow.
    /// @param component The component to be added to the UIWindow.

    void addChildComponent(UIComponent* component)
    {
        childComponents.push_back(component);
    }
    
    /// @brief Remove an existing child UIComponent from the UIWindow.
    /// @param component The child component to be removed from the UIWindow.

    void removeChildComponent(UIComponent* component)
    {
        auto & cmp = childComponents;

        cmp.erase(std::remove(cmp.begin(), cmp.end(), component), cmp.end());
    }

private:
    ofFbo buffer;
    
private:
    std::vector<UIComponent*> childComponents;
};

#endif

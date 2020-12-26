//  Ensemble
//  Created by David Spry on 25/12/20.

#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include "Ensemble.h"

class Sequence: public UIComponent, public ClockListener
{
public:
    Sequence();
    
    
    
public:
    inline void tick() override
    {
        
    }
    
private:
    std::vector<SQPlayhead> playheads;
    std::vector<SQRedirect> redirects;
    std::vector<SQPortal>   portals;
};

#endif

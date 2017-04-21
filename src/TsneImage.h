//
//  TsneImage.hpp
//  example-images
//
//  Created by Roberto Fazio on 20/04/17.
//
//

#pragma once

#include "ofMain.h"


class TsneImage
{
public:
    
    //TsneImage();
    
    ofImage img;
    ofVec2f pt;
    
    void draw(float sc);
    
};


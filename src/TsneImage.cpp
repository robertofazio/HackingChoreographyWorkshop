//
//  TsneImage.cpp
//  example-images
//
//  Created by Roberto Fazio on 20/04/17.
//
//

#include "TsneImage.h"

void TsneImage::draw(float sc)
{
    img.draw(pt.x, pt.y, img.getWidth() * sc, img.getHeight() * sc);
    
}

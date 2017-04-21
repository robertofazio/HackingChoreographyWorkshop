#pragma once

#include "ofMain.h"
#include "ofxCcv.h"
#include "ofxTSNE.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "TsneImage.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void go();
		
    ofxCcv ccv;
    ofxTSNE tsne;
    
    ofImage tresh;
    
    int tresholdValue;
    
    ofShader shd;
    
    //vector<ofImage> images;
   // vector<vector<double> > imagePoints;
    //vector<vector<float> > encodings;
    
    ofxPanel gui;
    ofParameter<float> scale;
    ofParameter<float> imageSize;
    ofParameter<float> thr;
    
    int t;
    
    vector<TsneImage> imgs;
    
    ofVec2f pos;
    ofVec2f startPos;
    ofVec2f tgtPos;
    float startTime;
    float endTime;
    int imgI;
    bool bGoing;
    ofParameter<float> speed;
    float pct;
    ofSoundPlayer sound;
    ofTrueTypeFont font;
    
    
};

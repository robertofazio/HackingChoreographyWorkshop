#include "ofApp.h"

using namespace cv;
using namespace ofxCv;


//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(230);
    
    shd.setupShaderFromFile(GL_FRAGMENT_SHADER, "shaders/alphaMe.frag");
    shd.linkProgram();
    
    sound.load("music/music.mp3");
    sound.setLoop(true);
    font.load("font/OCRAStd.otf", 32);
    
    
//    vector<string> path;
//    
//  //   load all the images
//    ofLog() << "Gathering images...";
//    ofDirectory dir;
//    int nFiles = dir.listDir(ofToDataPath("images/"));
//    if(nFiles) {
//        for(int i=0; i<dir.size(); i++) {
//            if (i % 20 == 0)    ofLog() << " - loading image "<<i<<" / "<<dir.size();
//            string filePath = dir.getPath(i);
//            images.push_back(ofImage());
//            images.back().load(filePath);
//            
//            path.push_back(filePath);
//        }
//    }
//    
////     setup ofxCcv
//    ccv.setup("image-net-2012.sqlite3");
//
//    
////     encode all of the images with ofxCcv
//    ofLog() << "Encoding images...";
//    for (int i=0; i<images.size(); i++) {
//        if (i % 20 == 0)    ofLog() << " - encoding image "<<i<<" / "<<images.size();
//        vector<float> encoding = ccv.encode(images[i], ccv.numLayers()-1);
//        encodings.push_back(encoding);
//    }
//    
//    // run t-SNE and load image points to imagePoints
//    ofLog() << "Run t-SNE on images";
//    imagePoints = tsne.run(encodings, 2, 25, 0.1, true);
//    
//    string s = "";
//    for(int i = 0; i < images.size(); i++)
//    {
//        s += path[i];
//        s += ",";
//        s += ofToString(imagePoints[i][0], 6);
//        s += ",";
//        s += ofToString(imagePoints[i][1], 6);
//        s += "\n";
//    }
//    
//    ofBuffer buf(s);
//    ofBufferToFile("file.txt", buf);
    
    // ****************
    
    ofBuffer buf = ofBufferFromFile("file.txt");
    
    for(ofBuffer::Line it = buf.getLines().begin(), end = buf.getLines().end(); it != end; ++it)
    {
        string line = *it;
        vector<string> ss = ofSplitString(line, ",");
        if(ss[0] != "")
        {
            TsneImage ii;
            
            ii.img.load(ss[0]);
            ii.pt.x = ofToFloat(ss[1]);
            ii.pt.y = ofToFloat(ss[2]);
            
            imgs.push_back(ii);

        }
    }
    
    cout << imgs.size() << endl;
    
    // make the images the same size
    for (int i=0; i<imgs.size(); i++)
    {
        imgs[i].img.resize(100 * imgs[i].img.getWidth() / imgs[i].img.getHeight(), 100);

        imgs[i].img.update();
    }
    
    
    // setup gui
    gui.setup();
    gui.add(scale.set("scale", 6.75, 0.0, 10.0));
    gui.add(imageSize.set("imageSize", 2.0, 0.0, 2.0));
    gui.add(thr.set("thr", 0.3,0.0,1.0));
    gui.add(speed.set("speed", 1.25, 0.0, 2.0));
    
    bGoing = false;
    imgI = 0;
    pos = imgs[0].pt;
    
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    if(bGoing)
    {
        float now = ofGetElapsedTimef();
        pct = ofMap(ofGetElapsedTimef(), startTime, endTime, 0, 1);
        pos.x = ofLerp(startPos.x, tgtPos.x, pct);
        pos.y = ofLerp(startPos.y, tgtPos.y, pct);
        
        if(now > endTime)
        {
            bGoing = false;
            pos = tgtPos;
            go();
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw()
{

    ofEnableAlphaBlending();
    
    ofPushMatrix();
    ofTranslate(-(pos.x*ofGetWidth()) * (scale - 0.5), -(pos.y*ofGetHeight()) * (scale - 0.5));
    for (int i=0; i<imgs.size(); i++)
    {
        float x = ofMap(imgs[i].pt.x, 0, 1, 0, scale * ofGetWidth());
        float y = ofMap(imgs[i].pt.y, 0, 1, 0, scale * ofGetHeight());
        float map = ofMap(i, 0, imgs.size(), 0, 1.0);
        ofFloatColor cc;
        int bPhoto = 0;
        cc.r = map;
        cc.g = 0.0;
        cc.b = 1.0;
        if(i == imgI){
            float hue = cc.getHueAngle();
            hue += 140;
            hue = (int)hue%360;
            cc.setHueAngle(hue);
            cc.a = ofMap(pct, 0, 1, 0.3, 1);
            bPhoto=0;
        }else{
            cc.a = 0.3;
        }
        shd.begin();
        shd.setUniform1f("thr", thr);
        shd.setUniform3f("col", cc.r, cc.g, cc.b);
        shd.setUniform1f("alpha", cc.a);
        shd.setUniform1i("bPhoto", bPhoto);
        imgs[i].img.draw(x, y, imageSize * imgs[i].img.getWidth(), imageSize * imgs[i].img.getHeight());
        shd.end();
        
        ofSetColor(cc.r*255,cc.g*255,cc.b*255);
        ofDrawBitmapString(i, x + imageSize * imgs[i].img.getWidth()*0.67, y + imageSize * imgs[i].img.getHeight()*0.95);
        
    }
    ofPopMatrix();
    
    gui.draw();
    
    ofPushStyle();
   // ofSetColor(ofColor::orange);
   // font.drawString("EXECUTE", 20, ofGetHeight() - 40);
    ofPopStyle();
}

void ofApp::go()
{
    bGoing = true;
    startPos = pos;
    //imgI = ofRandom(imgs.size()-1);
    imgI += 1;
    if(imgI >= imgs.size()-1)
        imgI = ofRandom(imgs.size()-1);
    
    tgtPos = imgs[imgI].pt;
    startTime = ofGetElapsedTimef();
    endTime = startTime + speed;
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if(key == ' ')
    {
        go();
        sound.play();

    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

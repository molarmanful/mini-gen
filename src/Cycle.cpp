#include "Cycle.h"

ofColor getColor(ofColor a, ofColor b, float rot){
	return a.getLerped(b, fabs(rot - 180) / 180);
}

void drawGraded(ofColor color, int centerY, bool isSun, float rot){
	ofPushStyle();
		// different angle checks for sun vs moon
		int i = 1;
		if(isSun){
			if(rot >= 270) i = (rot - 270) / 10;
			else if(rot <= 90) i = (90 - rot) / 10;
		}
		else {
			if(rot <= 270 && rot >= 180) i = (270 - rot) / 10;
			else if(rot < 180 && rot >= 90) i = (rot - 90) / 10;
		}

		// draw all gradients
		for(i = ofClamp(i, 1, 9); i > 0; i--){
			ofSetColor(color, 255 / i);
			ofDrawCircle(0, centerY, i * 64);
		}
	ofPopStyle();
}

void drawMt(ofColor a, ofColor b, float r, int offset, int w, int h, float rot){
	ofPushMatrix();
		ofTranslate(0, 256);
		ofRotateDeg(r);

		ofPushStyle();
			ofSetColor(getColor(a, b, rot));
			ofDrawTriangle(-w / 2, -512 + offset, w / 2, -512 + offset, 0, -512 + offset - h);
		ofPopStyle();

	ofPopMatrix();
}

void Cycle::setup(){
	// add params
	params.setName("PARAMS");
	params.add(rotation.set("day/night cycle", 360, 0, 360));
	params.add(bend.set("river bend", -1, -1, 1));
	params.add(resetStars.set("reset stars"));

	// generate stars + bind button
	resetStars.addListener(this, &Cycle::resetStarsEvent);
	this->resetStarsEvent();

	// set colors
	day.r = 60; day.g = 145; day.b = 230;
	night.r = 44; night.g = 44; night.b = 84;
	sun.r = 245; sun.g = 183; sun.b = 39;
	moon.r = 179; moon.g = 236; moon.b = 245;
	land.r = 0; land.g = 145; land.b = 110;
	land_n.r = 52; land_n.g = 46; land_n.b = 55;
	water.r = 0; water.g = 126; water.b = 167;
	water_n.r = 0; water_n.g = 50; water_n.b = 73;
	mountain.r = 126; mountain.g = 107; mountain.b = 143;
	mountain_n.r = 33; mountain_n.g = 1; mountain_n.b = 36;
}

void Cycle::draw(){
	// sky
	ofSetBackgroundColor(getColor(night, day, rotation));

	ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight());

		ofPushMatrix();
			ofRotateDeg(rotation);

			// stars
			ofPushStyle();
				ofSetColor(moon);
				for(ofVec2f p : star_pos){
					ofDrawCircle(p.x, p.y, 1);
				}
			ofPopStyle();

			// moon
			drawGraded(moon, ofGetWidth() / 3, false, rotation);

		ofPopMatrix();

		// mountains
		drawMt(mountain_n, mountain, 5, 30, 256, 200, rotation);
		drawMt(mountain_n, mountain, -7, 10, 128, 100, rotation);

		// land
		ofPushStyle();
			ofSetColor(getColor(mountain_n, land, rotation));
			ofDrawCircle(0, 256, 512);
		ofPopStyle();

		float X = 32 * bend;
		float X1 = X - 16;
		float X2 = -X - 32;
		float X01 = X + 16;
		float X02 = -X + 32;

		// river
		ofPushStyle();
			ofSetColor(getColor(water_n, water, rotation));
			ofBeginShape();

				ofVertex(0, -253);
				ofBezierVertex(X1, -192, X1, -192, -24, -128);
				ofBezierVertex(X2, -64, X2, -64, -64, 0);

				ofVertex(64, 0);
				ofBezierVertex(X02, -64, X02, -64, 24, -128);
				ofBezierVertex(X01, -192, X01, -192, -0, -253);

			ofEndShape();
		ofPopStyle();

		// sun
		ofPushMatrix();
			ofRotateDeg(rotation);
			drawGraded(sun, -ofGetWidth() / 3, true, rotation);
		ofPopMatrix();

	ofPopMatrix();
}

void Cycle::resetStarsEvent(){
	int width = ofGetWidth();
	for(ofVec2f &p : star_pos){
		p.x = ofRandom(-width / 2, width / 2);
		p.y = ofRandom(width);
	}
}

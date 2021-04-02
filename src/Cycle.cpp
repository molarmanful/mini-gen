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

void Cycle::setup(){
	// add params
	params.setName("PARAMS");
	params.add(rotation.set("day/night cycle", 360, 0, 360));
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

		// land
		ofPushStyle();
			ofSetColor(getColor(land_n, land, rotation));
			ofDrawCircle(0, 256, 512);
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

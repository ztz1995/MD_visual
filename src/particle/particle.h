#pragma once
#include "ofMain.h"


class particle
{
public:
	particle(ofPoint);
	~particle();
	void update();
	void applyForce(ofPoint);//��
	virtual void display();
	bool isDead();


	ofPoint location;
	ofPoint velocity;
	ofPoint acceleration;
	float lifespan;
	float mass;

};


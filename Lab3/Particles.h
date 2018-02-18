#pragma once

#include "Physics.h"

class Particles {

public:
	Physics particles[20];
	Particles(int no);



	void updateState(float time);
	void applyForce();
	vec3 avPosNeighbours(Physics p);
	vec3 avVelNeighbours(Physics p);
	vec3 avForceNeighbours(Physics p);
	void updateNeighbours();
	void updateForce();
	void updatePosition();
	void updateVelocity();

	
};
#pragma once

#include "Physics.h"
#include "Particles.h"
#include "Vector.h"




	Particles::Particles(int no) {
		
	Physics particles[20];
		//particles = new Physics[no];
	};

	void Particles::updateState(float time) {
		for (int i = 0; i < (sizeof particles / sizeof Physics); i++) {
			particles[i].updateState(time);
		}
	};

	void Particles::applyForce() {


		for (int i = 0; i < (sizeof particles / sizeof Physics); i++) {
			vec3 force = vec3((rand() % 1500 - 750) / 10000.0f, (rand() % 1500 - 750) / 10000.0f, (rand() % 1500 - 750) / 10000.0f).unit();
			//vec3 force = vec3(0.0f, 0.0f, -20.0f);
			particles[i].applyForce(force);
		}
	};

	void Particles::updateNeighbours() {
		for (int i = 0; i < (sizeof particles / sizeof Physics); i++) {
			for (int j = 0; j < (sizeof particles / sizeof Physics); j++) {

				if (particles[i].getDistance(particles[j].position) < particles[i].radius 
					&& particles[i].id != particles[j].id) {

					particles[i].addNeighbour(particles[j].id);
				}
			}
		}
	};

	vec3 Particles::avPosNeighbours(Physics p) {
		vec3 sum = vec3(0.0f,0.0f,0.0f);
		for (int i = 0; i < (sizeof particles / sizeof Physics); i++) {

				for (int j = 0; j < sizeof p.neighbours / sizeof (int); j++) {
					if (particles[i].id == p.neighbours[j]) {
						sum = sum.operator+(particles[i].position);
					}
				}
		
		}
		return sum.operator/(sizeof p.neighbours / sizeof (int));
	};


	vec3 Particles::avVelNeighbours(Physics p) {
		vec3 sum = vec3(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < (sizeof particles / sizeof Physics); i++) {

			for (int j = 0; j < sizeof p.neighbours / sizeof(int); j++) {
				if (particles[i].id == p.neighbours[j]) {
					sum = sum.operator+(particles[i].getVelocity());
				}
			}

		}
		return sum.operator/(sizeof p.neighbours / sizeof(int));
	};

	vec3 Particles::avForceNeighbours(Physics p) {
		vec3 sum = vec3(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < (sizeof particles / sizeof Physics); i++) {

			for (int j = 0; j < sizeof p.neighbours / sizeof(int); j++) {
				if (particles[i].id == p.neighbours[j]) {
					sum = sum.operator+(particles[i].getForce());
				}
			}

		}
		return sum.operator/(sizeof p.neighbours / sizeof(int));
	};

	void Particles::updateForce() {
		for (int i = 0; i < (sizeof particles / sizeof Physics); i++) {
			vec3 t = particles[i].netForce.operator+(avForceNeighbours(particles[i]));
			vec3 unit = t / t.length();
			if (t == vec3(0.0f, 0.0f, 0.0f)) {
				particles[i].applyForce(vec3(0.0f,0.0f,0.0f));
			}
			else {
				particles[i].applyForce(unit.operator*(3));
			}
			

		}
	}
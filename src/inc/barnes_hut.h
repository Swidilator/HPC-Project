#ifndef _BARENES_HUT_H_
#define _BARENES_HUT_H_

#include "octree.h"

float calcDistance(Body *source, Body *target);
dim3float calcForce(Body *source, Body *target);
dim3float updateVelocity(dim3float *velocity, dim3float *force);
void setForces(Body *source, Node *target);
void simulateStep(array<Body, NUM_BODIES> *bodies, Octree *octree);

#endif
#include "barnes_hut.h"



void simulate(array<Body, NUM_BODIES>* bodies, Octree *octree)
{
    Node* headNode = octree->getHeadNode();
    
    for(int i = 0; i < NUM_BODIES; i++)
    {

    }


}

dim3float calcForce(Body *source, Body *target)
{
    float G = 6.674 * (pow((float)10, -11));

    return -G * (source->getMass() * target->getMass())/(pow)


}

float calcDistance(Body *source, Body *target)
{
    return sqrt(((target->setCentreOfMass() - source->setCentreOfMass())^2)++);
}
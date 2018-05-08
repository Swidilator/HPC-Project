#include "barnes_hut.h"



void simulateStep(array<Body, NUM_BODIES>* bodies, Octree *octree)
{
    Node* headNode = octree->getHeadNode();
    
    for(int i = 0; i < NUM_BODIES; i++)
    {
        
    }


}

float calcDistance(Body *source, Body *target)
{
    dim3float product = ((target->getCentreOfMass() - source->getCentreOfMass())^2);
    return sqrt(product.x + product.y + product.z);
}

dim3float calcForce(Body *source, Body *target)
{
    float G = 6.674 * (pow((float)10, -11));

    dim3float vector = (target->getCentreOfMass() - source->getCentreOfMass());

    float scalar = -G * (source->getMass() * target->getMass())/(pow(calcDistance(source,target),3));

    return vector * scalar;


}


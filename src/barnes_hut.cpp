#include "barnes_hut.h"

using namespace std;

float calcDistance(Body *source, Body *target)
{
    dim3float a = target->getCentreOfMass() - source->getCentreOfMass();
    dim3float b = ((a) ^ 2);
    float product = sqrt(b.x + b.y + b.z);
    return product;
}

dim3float calcForce(Body *source, Body *target)
{
    float G = 6.674 * (pow((float)10, -11));

    dim3float vector = (target->getCentreOfMass() - source->getCentreOfMass());

    float scalar = -G * (source->getMass() * target->getMass()) / (pow(calcDistance(source, target), 3));

    dim3float product = (vector | scalar);
    return product;
}

void setForces(Body *source, Node *target)
{
    float width = target->getWidth();
    Body *virtBod = target->getVirtualBody();

    float sd = width / calcDistance(source, virtBod);

    if (target->getSoleBody() != nullptr)
    {
        if (source == target->getSoleBody())
        {
            //Do nothing if it is trying to compare to itself
        }
        else
        {
            source->setForce(source->getForce() + calcForce(source, target->getSoleBody()));
        }
    }
    else if (sd < THETA)
    {
        source->setForce(source->getForce() + calcForce(source, virtBod));
    }
    else
    {
        array<Node, NUMCHILDREN> *children = target->getChildren();
        for (int i = 0; i < NUMCHILDREN; i++)
        {
            if ((*children)[i].getContainsBody())
            {
                setForces(source, &(*children)[i]);
            }
        }
    }
}

void simulateStep(array<Body, NUM_BODIES> *bodies, Octree *octree)
{
    Node *headNode = octree->getHeadNode();

    for (int i = 0; i < NUM_BODIES; i++)
    {
        dim3float vel = ((*bodies)[i].getVelocity());
        (*bodies)[i].setForce(dim3float(0));
        setForces(&(*bodies)[i], headNode);
        //(*bodies)[i].setVelocity(*vel + (*bodies)[i].getForce());
        dim3float d = vel + (*bodies)[i].getForce() | (0.5);
        (*bodies)[i].setCentreOfMass((*bodies)[i].getCentreOfMass() + d);
    
    }
    octree->freeOctree(octree->getHeadNode());
}

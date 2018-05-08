#include <iostream>

#include "octree.h"
#include "barnes_hut.h"

using namespace std;

int main()
{
    array<Body, NUM_BODIES> *bodies = new array<Body, NUM_BODIES>;

    cout << "Width: " << MAX_WIDTH << endl;
    cout << "Bodies: " << NUM_BODIES << endl;

    dim3float test = (dim3float(1, 2, 3) + dim3float(1, 2, 3)) ^ 2;
    test ^ 2;
    cout << test.x << ":" << test.y << ":" << test.z << endl;

    Octree *octree = new Octree(dim3float(0, 0, 0), MAX_WIDTH);
    Node *headNode = octree->getHeadNode();

    for (int i = 0; i < NUM_BODIES; i++)
    {
        (*bodies)[i].setMass((float)(rand() % 100000000) + 100);
        (*bodies)[i].setCentreOfMass(dim3float(((float)(rand() % (MAX_WIDTH * 100))) / 100, ((float)(rand() % (MAX_WIDTH * 100))) / 100, ((float)(rand() % (MAX_WIDTH * 100))) / 100));
        //octree.insertBody(headNode, &((*bodies)[i]), MAX_WIDTH);
    }

    //octree.buildOctree(bodies);

    //cout << calcDistance(&(*bodies)[1], &(*bodies)[2]) << endl;

    //cout << " 0: " <<octree.getHeadNode()->getSoleBody() << " " << endl;
    //octree.printTree(octree.getHeadNode(), 1);
    for (int i = 0; i < 1000; i++)
    {
        octree->buildOctree(bodies);
        simulateStep(bodies, octree);
    }

    return 0;
}
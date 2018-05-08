#include <iostream>

#include "octree.h"

#define NUM_BODIES 300000
#define MAX_WIDTH 524288

using namespace std;

int main(){
    array<Body, NUM_BODIES>* bodies = new array<Body, NUM_BODIES>;
    
    cout << "Width: " << MAX_WIDTH << endl;
    cout << "Bodies: " << NUM_BODIES << endl;

    Octree octree(dim3float(0, 0, 0), MAX_WIDTH);
    Node * headNode = octree.getHeadNode();

    for(int i = 0; i < NUM_BODIES; i++){
        (*bodies)[i].setMass((float)(rand() % 10));
        (*bodies)[i].setCentreOfMass(dim3float(((float)(rand() % (MAX_WIDTH*100)))/100,((float)(rand() % (MAX_WIDTH*100)))/100,((float)(rand() % (MAX_WIDTH*100)))/100));
        octree.insertBody(headNode,&((*bodies)[i]),MAX_WIDTH);
    }
    
    cout << " 0: " <<octree.getHeadNode()->getSoleBody() << " " << endl;
    //octree.printTree(octree.getHeadNode(), 1);
    return 0;
}
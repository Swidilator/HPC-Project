#include "octree.h"

using namespace std;

dim3float delinearise(int i, int width, dim3float parentOrigin)
{
    dim3float out = dim3float(parentOrigin.x + (i % 2) * (width / 2), parentOrigin.y + ((i % 4) / 2) * (width / 2), parentOrigin.z + (i / 4) * (width / 2));
    return out;
}

int linearise(dim3float dim, int width, dim3float parentOrigin)
{
    int x = (dim.x - parentOrigin.x)/(width/2);
    int y = (dim.y - parentOrigin.y)/(width/2);
    int z = (dim.z - parentOrigin.z)/(width/2);
    
    return (x + 2 * (y + 2 * z));
}

//----------------------------------------------------
// Body
//----------------------------------------------------

Body::Body()
{
    dim3float COM(0, 0, 0);
    centreOfMass = COM;
    mass = 0;
}

Body::Body(dim3float com, float mass)
{
    this->mass = mass;
    centreOfMass = com;
}

void Body::setContainerNode(Node *node)
{
    containerNode = node;
}

Node *Body::getContainerNode()
{
    return containerNode;
}

void Body::setCentreOfMass(dim3float centre)
{
    centreOfMass = centre;
}

dim3float Body::getCentreOfMass()
{
    return centreOfMass;
}

float Body::getMass()
{
    return mass;
}

void Body::setMass(float mass)
{
    this->mass = mass;
}

//----------------------------------------------------
// Node
//----------------------------------------------------

Node::Node()
{
    //virtualBody = new Body;
    containsBody = false;
}

Node::Node(bool containsBody, Body *virtualBody, dim3float origin, float width)
{
    this->containsBody = containsBody;
    this->virtualBody = virtualBody;
    this->origin = origin;
    this->width = width;
}

array<Node, NUMCHILDREN> *Node::getChildren()
{
    return children;
}
void Node::setChildren(array<Node, NUMCHILDREN> *newChildren)
{
    children = newChildren;
}

Node *Node::getParent()
{
    return parent;
}

void Node::setParent(Node *parent)
{
    this->parent = parent;
}

void Node::setSoleBody(Body *body)
{
    soleBody = body;

    if (body != nullptr)
    {
        containsBody = true;
        body->setContainerNode(this);
    }
}

Body *Node::getSoleBody()
{
    return soleBody;
}

bool Node::getContainsBody()
{
    return containsBody;
}

void Node::setContainsBody(bool flag)
{
    containsBody = flag;
}

void Node::setOrigin(dim3float origin)
{
    this->origin = origin;
}

dim3float Node::getOrigin()
{
    return origin;
}

void Node::setWidth(float width)
{
    this->width = width;
}

int Node::getWidth()
{
    return width;
}

Body *Node::getVirtualBody()
{
    return virtualBody;
}

void Node::setVirtualBody(Body *body)
{
    virtualBody = body;
}

//----------------------------------------------------
// Octree
//----------------------------------------------------

Octree::Octree(dim3float origin, float width)
{
    headNode = new Node(false, new Body, origin, width);
}

Node *Octree::getHeadNode()
{
    return headNode;
}

void Octree::insertBody(Node *startNode, Body *newBody, float width)
{
    array<Node, NUMCHILDREN> *nodeChildren = startNode->getChildren();
    Body *virtBody = startNode->getVirtualBody();

    dim3float centreOfMass = virtBody->getCentreOfMass();
    dim3float newBodyCentreOfMass = newBody->getCentreOfMass();
    float vMass = virtBody->getMass();
    float nMass = newBody->getMass();
    float tMass = vMass + nMass;

    // Update virtual centre of mass & mass
    virtBody->setCentreOfMass(dim3float(
        (centreOfMass.x * vMass + newBodyCentreOfMass.x * nMass) / tMass,
        (centreOfMass.y * vMass + newBodyCentreOfMass.y * nMass) / tMass,
        (centreOfMass.z * vMass + newBodyCentreOfMass.z * nMass) / tMass));
    virtBody->setMass(tMass);

    // Node not empty
    if (startNode->getContainsBody())
    {
        // Node has no children, so must be a leaf node, therefore either
        // create children if populated, or populate with a body
        if (nodeChildren == nullptr)
        {
            Body *sBody = startNode->getSoleBody();
            if (sBody == nullptr)
            {
                startNode->setSoleBody(newBody);
            }
            else
            {
                array<Node, NUMCHILDREN> *newChildren = new array<Node, NUMCHILDREN>;
                startNode->setChildren(newChildren);
                nodeChildren = startNode->getChildren(); //Update to new pointer

                for (int i = 0; i < NUMCHILDREN; i++)
                {
                    dim3float ori = delinearise(i, width, startNode->getOrigin());
                    (*nodeChildren)[i].setOrigin(ori);
                    (*nodeChildren)[i].setWidth(width / 2);
                    (*nodeChildren)[i].setVirtualBody(new Body);
                    (*nodeChildren)[i].setParent(startNode);
                }

                int oldIndex = linearise(sBody->getCentreOfMass(), width, startNode->getOrigin());
                int newIndex = linearise(newBody->getCentreOfMass(), width, startNode->getOrigin());

                insertBody(&((*nodeChildren)[oldIndex]), sBody, width / 2);
                insertBody(&((*nodeChildren)[newIndex]), newBody, width / 2);

                startNode->setSoleBody(nullptr);
            }
        }
        // Node has children
        else
        {
            int newIndex = linearise(newBody->getCentreOfMass(), width, startNode->getOrigin());
            insertBody(&((*nodeChildren)[newIndex]), newBody, width / 2);
        }
    }
    // Node empty
    else
    {
        startNode->setSoleBody(newBody);
    }
}

void Octree::printTree(Node *root, int depth)
{

    if (root->getChildren() != nullptr)
    {
        cout << depth;
        array<Node, NUMCHILDREN> *children = root->getChildren();
        for (int i = 0; i < NUMCHILDREN; i++)
        {
            cout << " " << i << ": " << ((*children)[i]).getSoleBody() << " \t\t";
            
        }
        cout << endl;
        for (int i = 0; i < NUMCHILDREN; i++)
        {
            printTree(&((*children)[i]), depth + 1);
        }
    }
    //cout << endl;
}





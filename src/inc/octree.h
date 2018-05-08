#ifndef _OCTREE_H_
#define _OCTREE_H_

#define NUMCHILDREN 8
#define NUM_BODIES 30
#define MAX_WIDTH 524288

class Body;
class Node;
class Octree;

#include <iostream>
#include <array>
#include <cmath>

using namespace std;

// Based on dim3 by Nvidia for use in CUDA, defined in "vector_types.h", adjusted for use with floats
//----
struct dim3float
{
  float x, y, z;
  dim3float(float vx = 0, float vy = 0, float vz = 0) : x(vx), y(vy), z(vz) {}

  dim3float operator+(const dim3float &a)
  {
    float vx = x + a.x;
    float vy = y + a.y;
    float vz = z + a.z;
    return dim3float(vx, vy, vz);
  }

  float operator++(void)
  {
    return x + y + z;
  }

  dim3float operator-(const dim3float &a)
  {
    float vx = x - a.x;
    float vy = y - a.y;
    float vz = z - a.z;
    return dim3float(vx, vy, vz);
  }

  dim3float operator*(const dim3float &a)
  {
    float vx = x * a.x;
    float vy = y * a.y;
    float vz = z * a.z;
    return dim3float(vx, vy, vz);
  }

  dim3float operator^(const int a)
  {
    int vx = pow(x,a);
    int vy = pow(y,a);
    int vz = pow(z,a);
    return dim3float(vx, vy, vz);
  }
  
};

typedef struct dim3float dim3float;

//----

class Body
{
private:
  dim3float centreOfMass;
  float mass;
  Node *containerNode;

public:
  Body();
  Body(dim3float com, float mass);
  void setContainerNode(Node *node);
  Node *getContainerNode();
  dim3float getCentreOfMass();
  void setCentreOfMass(dim3float centre);
  float getMass();
  void setMass(float mass);
};

class Node
{
private:
  array<Node, NUMCHILDREN> *children;
  bool containsBody;
  Body *virtualBody;
  Body *soleBody;
  dim3float origin;
  float width;
  Node *parent;

public:
  Node();
  Node(bool containsBody, Body *virtualBody, dim3float origin, float width);
  array<Node, NUMCHILDREN> *getChildren();
  Node *getParent();
  void setParent(Node *parent);
  void setChildren(array<Node, NUMCHILDREN> *newChildren);
  void setSoleBody(Body *body);
  Body *getSoleBody();
  bool getContainsBody();
  void setContainsBody(bool flag);
  void setOrigin(dim3float origin);
  dim3float getOrigin();
  void setWidth(float width);
  int getWidth();
  Body *getVirtualBody();
  void setVirtualBody(Body *body);
};

class Octree
{
private:
  Node *headNode;

public:
  Octree(dim3float origin, float width);
  Node *getHeadNode();
  void insertBody(Node *startPoint, Body *newBody, float width);
  void simulate(array<Body, NUM_BODIES> *bodies);
  void printTree(Node *root, int depth);
};

#endif
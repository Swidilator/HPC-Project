#ifndef _OCTREE_H_
#define _OCTREE_H_

#define NUMCHILDREN 8
#define NUM_BODIES 10000
//#define MAX_WIDTH 65536
#define MAX_WIDTH 8192
#define THETA 0.6

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

  float operator$()
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
    float vx = pow(x, a);
    float vy = pow(y, a);
    float vz = pow(z, a);
    return dim3float(vx, vy, vz);
  }

  //Constant multiplication
  dim3float operator|(const float a)
  {
    float vx = x * a;
    float vy = y * a;
    float vz = z * a;
    return dim3float(vx, vy, vz);
  }
};

typedef struct dim3float dim3float;

//----

class Body
{
private:
  dim3float centreOfMass;
  dim3float force;
  dim3float velocity;
  float mass;
  Node *containerNode;

public:
  Body();
  Body(dim3float com, float mass);

  void setContainerNode(Node *node);
  Node *getContainerNode();

  void setCentreOfMass(dim3float centre);
  dim3float getCentreOfMass();

  void setMass(float mass);
  float getMass();

  void setForce(dim3float force);
  dim3float getForce();

  void setVelocity(dim3float velocity);
  dim3float getVelocity();
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
  void buildOctree(array<Body, NUM_BODIES> *bodies);
  void freeOctree(Node *node);
  void printTree(Node *root, int depth);
};

#endif
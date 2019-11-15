#include "QuadTree.h"

QuadTree_Node::QuadTree_Node(math::AABB& boundingBox)
{
	this->bounding_Box = boundingBox;
}

QuadTree_Node::~QuadTree_Node()
{


}

void QT_Render(QuadTree_Node* node) 
{

}

void QT_Create(math::AABB parameters) 
{

}

void QT_Clear()
{

}


void QT_Insert(GameObject* object) 
{

}

void QT_Remove(GameObject* object)
{

}

//If it is within the limits of Quadtree
//Add it to the root node:
//If you run out of Bucket spaceand you are a leaf, subdivide yourself in 4
//Add it node’s list
//Redistribute all GameObjects to proper childs based on their position in space

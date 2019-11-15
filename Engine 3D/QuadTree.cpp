#include "QuadTree.h"

QuadTree_Node::QuadTree_Node(math::AABB& boundingBox)
{
	this->bounding_Box = boundingBox;
}

QuadTree_Node::~QuadTree_Node()
{
	if (HasChilds())
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (childs[i] != nullptr)
			{
				delete childs[i];
				childs[i] = nullptr;
			}
		}
	}

}


bool QuadTree_Node::HasChilds() 
{
	if (childs[0] == nullptr)
		return false;
	return true;
}

void QuadTree_Node::Subdivide()
{

}

void QuadTree_Node::InsertGameObject(GameObject* object)
{

}

void QuadTree_Node::RedistributeChilds()
{

}

void QuadTree_Node::DeleteGameObjet(GameObject* object)
{

}


Quad_Tree::Quad_Tree()
{
	
}

Quad_Tree::~Quad_Tree()
{
	QT_Clear();
}

void Quad_Tree::QT_Render(QuadTree_Node* node)
{

}

void Quad_Tree::QT_Create(math::AABB parameters)
{
	QT_Clear();
	root = new QuadTree_Node(parameters);
}

void Quad_Tree::QT_Clear()
{
	if (root != nullptr)
	{
		delete root;
	}
}


void Quad_Tree::QT_Insert(GameObject* object)
{
	if (object->boundingBox.Intersects(root->bounding_Box))
	{
		root->InsertGameObject(object);
	}
}



//If it is within the limits of Quadtree
//Add it to the root node:
//If you run out of Bucket spaceand you are a leaf, subdivide yourself in 4
//Add it node’s list
//Redistribute all GameObjects to proper childs based on their position in space

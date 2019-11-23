#include "QuadTree.h"

QuadTree_Node::QuadTree_Node(math::AABB& boundingBox)
{
	this->bounding_Box = boundingBox;
}

QuadTree_Node::~QuadTree_Node()
{
	if (HasChilds())
	{
		for (int i = 0; i < 4; i++)
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

	const math::float3 size = bounding_Box.Size();
	const math::float3 center = bounding_Box.CenterPoint();
	const math::float3 divedeSize(size.x / 2.0f, size.y, size.z / 2.0f);
	const math::float3 divedex4Size(size.x / 4.0f, size.y, size.z / 4.0f);


	//Each Quadtree has 4 childs, and every child can divide in 4 childs more
	math::float3 oneFourCenter;
	math::AABB oneFour;

	oneFourCenter = { center.x + divedex4Size.x, center.y, center.z - oneFourCenter.z };
	oneFour.SetFromCenterAndSize(oneFourCenter, divedeSize);
	childs[0] = new QuadTree_Node(oneFour);

	oneFourCenter = { center.x - divedex4Size.x, center.y, center.z - oneFourCenter.z };
	oneFour.SetFromCenterAndSize(oneFourCenter, divedeSize);
	childs[1] = new QuadTree_Node(oneFour);

	oneFourCenter = { center.x + divedex4Size.x, center.y, center.z + oneFourCenter.z };
	oneFour.SetFromCenterAndSize(oneFourCenter, divedeSize);
	childs[2] = new QuadTree_Node(oneFour);

	oneFourCenter = { center.x - divedex4Size.x, center.y, center.z + oneFourCenter.z };
	oneFour.SetFromCenterAndSize(oneFourCenter, divedeSize);
	childs[3] = new QuadTree_Node(oneFour);

}

void QuadTree_Node::InsertGameObject(GameObject* object)
{
	if (objects.size() < MAX_NODE_ELEMENTS && !HasChilds())
		objects.push_back(object);

	else
	{
		if (!HasChilds())
			Subdivide();

		objects.push_back(object);
		RedistributeChilds();
	}
}

void QuadTree_Node::RedistributeChilds()
{
	std::list<GameObject*>::iterator it = objects.begin();

	while (it != objects.end())
	{
		uint totalIntersections = 0u;
		uint lastIntersection = 0u;
		for (int i = 0; i < 4; i++)
		{
			if ((*it)->boundingBox.Intersects(childs[i]->bounding_Box))
			{
				totalIntersections++;
				lastIntersection = i;
			}
		}
		if (totalIntersections == 4)
		{
			it++;
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				if ((*it)->boundingBox.Intersects(childs[i]->bounding_Box))
				{
					childs[i]->InsertGameObject((*it));
				}
			}
			it = objects.erase(it);
		}
	}
}

void QuadTree_Node::DeleteGameObjet(GameObject* object)
{
	std::list<GameObject*>::iterator it = objects.begin();
	while (it != objects.end())
	{
		if ((*it) == object)
		{
			it = objects.erase(it);
			RedistributeChilds();
		}
		else
		{
			it++;
		}
	}
	if (HasChilds())
	{
		for (int i = 0; i < 4; i++)
		{
			childs[i]->DeleteGameObjet(object);
			childs[i]->RedistributeChilds();
		}
	}
}

void QuadTree_Node::GetBoxes(std::vector<math::AABB>& node)
{

	node.push_back(bounding_Box);

	if (HasChilds())
	{
		for (int i = 0; i < 4; i++)
		{
			childs[i]->GetBoxes(node);

		}

	}


}

Quad_Tree::Quad_Tree()
{
	
}

Quad_Tree::~Quad_Tree()
{
	QT_Clear();
}

void Quad_Tree::QT_GetBoxes(std::vector<math::AABB>& node)
{

	if (root != nullptr)
		root->GetBoxes(node);

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

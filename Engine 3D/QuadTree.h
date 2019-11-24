#include <vector>
#include "MathGeoLib/Geometry/AABB.h"
#include "GameObject.h"
#include <list>
#include "Primitive.h"


#define MAX_NODE_ELEMENTS 5


class QuadTree_Node
{
public:
	QuadTree_Node(math::AABB& boundingBox);
	~QuadTree_Node();


	bool HasChilds();
	void Subdivide();
	void InsertGameObject(GameObject* object);
	void RedistributeChilds();
	void DeleteGameObjet(GameObject* object);
	void GetBoxes(std::vector<math::AABB>& node);
	template<typename TYPE>
	inline void Intersects(std::vector<GameObject*>& objects, const TYPE& primitive) const
	{
		if (primitive.Intersects(bounding_box))
		{
			for (std::list<GameObject*>::const_iterator iterator = objects_quad.begin(); iterator != objects_quad.end(); ++iterator)
			{
				if(primitive.Intersects((*iterator)->boundingBox))
					objects.push_back((*iterator));
			}
			for (int i = 0; i < 4; ++i)
			{
				if (childs[i] != nullptr)
					childs[i]->Intersects(objects, primitive);
			}
		}
	}

	

public:

	math::AABB bounding_box;

	QuadTree_Node* parent = nullptr;
	QuadTree_Node* childs[4] = { nullptr, nullptr, nullptr, nullptr };
	
	std::list<GameObject*> objects_quad;
	int subdivision = 0;
};


class Quad_Tree
{
public:

	Quad_Tree();
	~Quad_Tree();
	
	void QT_GetBoxes(std::vector<math::AABB>& node);

	void QT_Create(math::AABB parameters);
	void QT_Clear();

	void QT_Insert(GameObject* object);
	template<typename TYPE>
	inline void QT_Intersect(std::vector<GameObject*>& objects, const TYPE& primitive)
	{
		if (root != nullptr)
		{
			root->Intersects(objects, primitive);
			UniqueObjects(objects);
		}
	}
	void UniqueObjects(std::vector<GameObject*>& objects) const;

public:

	QuadTree_Node* root = nullptr;
	

};

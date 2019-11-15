#include <vector>
#include "MathGeoLib/Geometry/AABB.h"
#include "GameObject.h"
#include <list>
#include "Primitive.h"

class QuadTree_Node
{
public:
	QuadTree_Node(math::AABB& boundingBox);
	~QuadTree_Node();


	bool HasChilds();
	void Subdivide();
	void IntersectGameObject(GameObject* object);
	void RedistributeChilds();
	void DeleteGameObjet(GameObject* object);


public:

	math::AABB bounding_Box;

	QuadTree_Node* parent = nullptr;
	QuadTree_Node* children[4] = { nullptr, nullptr, nullptr, nullptr };
	
	std::list<GameObject*> objects;
	unsigned int subdivision = 0;
};


class Quad_Tree
{
public:

	Quad_Tree();
	~Quad_Tree();
	
	void QT_Render(QuadTree_Node* node);

	void QT_Create(math::AABB parameters);
	void QT_Clear();

	void QT_Insert(GameObject* object);
	void QT_Remove(GameObject* object);
	//void QT_Intersect(std::vector<GameObject*>& , PRIMITIVE);

public:

	QuadTree_Node* root = nullptr;
};

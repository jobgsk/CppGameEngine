

#ifndef NODE_MODEL_H_
#define NODE_MODEL_H_

#include "../GameObject.h"

class NodeModel : public GameObject {
public:
	CollisionBox * cbox;
	int index_next_node;

	NodeModel(int i, Vector3 pos, float scale) :GameObject()
	{
		m_id = i;
		half_size = Vector3(1, 1, 1);
		float shift_to_center = 2;

		RigidBody * b1 = new RigidBody();
		b1->setPosition(pos.x*shift_to_center, pos.y + half_size.y, pos.z*shift_to_center);
		b1->calculateDerivedData();
		m_body = b1;

		cbox = new BoxBody(b1, half_size);
		cbox->calculateInternals();

		if (m_id == 0)
			index_next_node = 2;
		else
			index_next_node = 0;
		
	};

	virtual void render()
	{

	}

};

#endif /* NODE_MODEL_H_ */

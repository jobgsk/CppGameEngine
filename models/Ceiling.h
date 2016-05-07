
#ifndef CEILING_MODEL_H_
#define CEILING_MODEL_H_

#include "../GameObject.h"

class CeilingModel : public GameObject {
public:
	CeilingModel(int i, Vector3 pos, float scale) :GameObject()
	{
		m_id = i;
		float shift_to_center = 2;

		RigidBody * b1 = new RigidBody();
		b1->setPosition(pos.x*shift_to_center, 4.0, pos.z*shift_to_center);
		b1->calculateDerivedData();
		m_body = b1;

		m_render = MeshFactory::getCeiling(scale);
	};

};

#endif /* CEILING_MODEL_H_ */


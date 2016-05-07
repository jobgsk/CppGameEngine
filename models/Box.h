#ifndef BOX_MODEL_H_
#define BOX_MODEL_H_

#include "../GameObject.h"
#include "../factories/ObjectsFactory.h"

class BoxModel : public GameObject {
public:
	CollisionBox * cbox;

	BoxModel(int i, Vector3 pos, float scale, Quaternion q1) :GameObject()
	{
		m_render = MeshFactory::getBox1(scale);

		m_id = i;
		half_size = Vector3(m_render->rx, m_render->ry, m_render->rz);

		RigidBody * b1 = new RigidBody();
		b1->setPosition(pos.x, pos.y + half_size.y, pos.z);
		b1->setOrientation(q1);

		real mass = half_size.x * half_size.y * half_size.z * 4.0f;
		b1->setMass(mass);

		Matrix3 tensor;
		tensor.setBlockInertiaTensor((half_size * 1), mass);
		b1->setInertiaTensor(tensor);

		b1->setDamping(0.001, 0.001);
		b1->setAcceleration(0, -10.0f, 0);
		b1->calculateDerivedData();
		m_body = b1;

		cbox = new BoxBody(b1, half_size);
		cbox->calculateInternals();
	};

	virtual void update(float duration)
	{
		GameObject::update(duration);
		cbox->calculateInternals();

		if (CollisionDetector::boxAndHalfSpace(
			*cbox, *ObjectsFactory::instance()->get_plane(),
			ObjectsFactory::instance()->get_collision_data()))
		{

		}
	}

};

#endif /* BOX_MODEL_H_ */

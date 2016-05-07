#ifndef BULLET_MODEL_H_
#define BULLET_MODEL_H_

#include "../GameObject.h"
#include "../factories/ObjectsFactory.h"

class BulletModel : public GameObject {
public:
	CollisionSphere * cspher;

	BulletModel(int i, Vector3 pos) :GameObject()
	{
		m_render = MeshFactory::getBullet(0.1, glm::vec4(1, 0, 0, 1));

		m_id = i;
		state = GameObject::ObjectState::DESTROYED;
		half_size = Vector3(m_render->rx, m_render->ry, m_render->rz);

		RigidBody * b1 = new RigidBody();
		b1->setPosition(pos.x, pos.y, pos.z);

		real mass = half_size.x * half_size.y * half_size.z * 400.0f;
		real radius = half_size.x;
		b1->setMass(mass);

		b1->setDamping(0.1, 0.1);
		b1->setAcceleration(0, -10.0f, 0);

		//Matrix3 tensor;
		//real coeff = 0.4f*b1->getMass()*radius*radius;
		//tensor.setInertiaTensorCoeffs(coeff, coeff, coeff);
		//b1->setInertiaTensor(tensor);


		b1->calculateDerivedData();
		m_body = b1;

		cspher = new SphereBody(b1, radius);
		cspher->calculateInternals();
	};

	void shoot(Vector3 pos, Vector3 dir)
	{
		Vector3 velocity = dir * 200;

		m_body->setPosition(pos.x, pos.y, pos.z);
		m_body->setVelocity(velocity);
		state = GameObject::ObjectState::ACTIVE;

		// Run the physics
		m_body->calculateDerivedData();
	};

	void update(float duration);
};

#endif /* BULLET_MODEL_H_ */


#ifndef PANEL_MODEL_H_
#define PANEL_MODEL_H_

#include "../GameObject.h"
#include "../factories/ObjectsFactory.h"
#include "../Camera.h"

class PanelModel : public GameObject {
public:
	CollisionBox * cbox;
	//Camera::CameraPosition m_cpos;

	PanelModel(int i, Vector3 pos, float scale, Quaternion q1) :GameObject()
	{
		m_render = MeshFactory::getPanel1(scale);

		m_id = i;
		half_size = Vector3(m_render->rx, m_render->ry, m_render->rz);

		float shift_to_center = 2;
		std::cout << "panel " << pos.x << " " << pos.y << " " << pos.z << std::endl;

		RigidBody * b1 = new RigidBody();
		b1->setPosition(pos.x*shift_to_center, pos.y + half_size.y, pos.z*shift_to_center);
		b1->setOrientation(q1);
		b1->calculateDerivedData();
		m_body = b1;

		cbox = new BoxBody(b1, half_size);
		cbox->calculateInternals();
	};

	virtual void update(float duration)
	{
		GameObject::update(duration);
		cbox->calculateInternals();
	}

};

#endif /* PANEL_MODEL_H_ */

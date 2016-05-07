#ifndef PLAYER_MODEL_H_
#define PLAYER_MODEL_H_

#include "../GameObject.h"
#include "../amodels/PlayerAnime.h"
#include "../factories/ObjectsFactory.h"
#include "Box.h"
#include "Bullet.h"
#include "Panel.h"

class PlayerModel : public GameObject {
public:
	
	CollisionBox * cbox;
	AnimationClip * shoot_anim;

	PlayerModel(int i, Vector3 pos, float scale, Quaternion q1) :GameObject()
	{
		m_id = i;
		half_size = Vector3(0.2, 1.0, 0.2);

		RigidBody * b1 = new RigidBody();
		b1->setPosition(pos.x, pos.y + half_size.y, pos.z);
		b1->setOrientation(q1);
		//b1->setVelocity(0, 0, 0);
		//b1->setRotation(Vector3(0, 0, 0));

		real mass = half_size.x * half_size.y * half_size.z * 8.0f;
		b1->setMass(mass);

		//Matrix3 tensor;
		//tensor.setBlockInertiaTensor((half_size * 1), mass);
		//b1->setInertiaTensor(tensor);

		b1->setDamping(0.001, 0.001);
		b1->setAcceleration(0, -10.0f, 0);
		b1->calculateDerivedData();
		m_body = b1;

		cbox = new BoxBody(b1, half_size);
		cbox->calculateInternals();

		shoot_anim = new PlayerAnime(this);
	};

	virtual void update(float duration)
	{
		GameObject::update(duration);
		cbox->calculateInternals();
		shoot_anim->update(duration);

		std::vector<GameObject*> obstacles = ObjectsFactory::instance()->get_obstacles();
		
		if (CollisionDetector::boxAndHalfSpace(
			*cbox, *ObjectsFactory::instance()->get_plane(), 
			ObjectsFactory::instance()->get_collision_data()))
		{

		}

		for (int i = 0; i < obstacles.size(); i++)
		{
			GameObject * go = obstacles[i];
			if (!dynamic_cast<BoxModel*>(go) &&
				!dynamic_cast<PanelModel*>(go))
				continue;

			if (dynamic_cast<BoxModel*>(go) && CollisionDetector::boxAndBox(
				*cbox, *((BoxModel*)go)->cbox, ObjectsFactory::instance()->get_collision_data()))
			{
				continue;
			}

			if (dynamic_cast<PanelModel*>(go) && CollisionDetector::boxAndBox(
				*cbox, *((PanelModel*)go)->cbox, ObjectsFactory::instance()->get_collision_data()))
			{
				continue;
			}
		}
	}

	virtual void shoot()
	{
		BulletModel * bullet = ((BulletModel*) ObjectsFactory::instance()->get_bulets()[0]);
		if (!bullet)
			return;

		Vector3 pos = get_pos();
		bullet->shoot(Vector3(pos.x, pos.y + 0.4, pos.z), get_dir());
		shoot_anim->play_animation(true);
	}

	void jump()
	{
		Vector3 dir = get_dir();
		Vector3 velocity =  Vector3(dir.x*5, 15, dir.z*5);
		m_body->setVelocity(velocity);
	}

	void play_animation(bool play)
	{
		shoot_anim->play_animation(play);
	}

	void render()
	{
		Vector3 pos = get_pos();
		//Graphics::light_position = glm::vec4(pos.x, pos.y, pos.z, 1);
		//GameObject::render();
		shoot_anim->render();
	}

};

#endif /* PLAYER_MODEL_H_ */

#ifndef VICTIM_MODEL_H_
#define VICTIM_MODEL_H_

#include "../GameObject.h"
#include "../amodels/MMAnime.h"
#include "../factories/ObjectsFactory.h"
#include "../behaviors/Tasks.h"

#include "Box.h"
#include "Bullet.h"
#include "Panel.h"

//#include "../behaviors/CastTrace.h"

class VictimBehave {
	BehaviourTask * behaviour_task;
public:
	FindClosesNode * task_find_closes_node;
	FindNextNode * task_find_next_node;
	TurnToTarget * task_turn_to_target;
	MoveToTarget * task_move_to_target;
	FireToTarget * task_fire_to_target;

	//CastTrace * cast_trace;

	VictimBehave(GameObject* current_object);
	void update(float duration)
	{
		behaviour_task = behaviour_task->task(duration);
	};
	void begin_task();

};

class VictimModel : public GameObject {
public:

	CollisionBox * cbox;
	AnimationClip * walk_anim;

	/*
	ai
	*/
	VictimBehave * m_actor;
	//GameObject * target;
	float start_time;
	float delta_time;

	VictimModel(int i, Vector3 pos, float scale, Quaternion q1) :GameObject()
	{
		m_id = i;
		half_size = Vector3(0.1, 0.25, 0.1);

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

		walk_anim = new MMAnime(this);

		/*
		ai
		*/
		start_time = m_id * 2;
		delta_time = 0;
		m_actor = new VictimBehave(this);
	};

	virtual void update(float duration)
	{
		if (delta_time > start_time)
		{
			m_actor->update(duration);
			GameObject::update(duration);
			cbox->calculateInternals();
			walk_anim->update(duration);

			/*
			collisions with plain
			*/
			if (CollisionDetector::boxAndHalfSpace(
				*cbox, *ObjectsFactory::instance()->get_plane(),
				ObjectsFactory::instance()->get_collision_data()))
			{
			}
		}

		delta_time += duration;
		return;

		std::vector<GameObject*> obstacles = ObjectsFactory::instance()->get_obstacles();
		for (int i = 0; i < obstacles.size(); i++)
		{
			GameObject * go = obstacles[i];
			if (!dynamic_cast<BoxModel*>(go) ||
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

	virtual void translate(bool up, float force)
	{
		GameObject::translate(up, force);
		walk_anim->play_animation(true);
	}

	virtual void rotate(bool up, float force)
	{
		GameObject::rotate(up, force);
		walk_anim->play_animation(true);
	}

	void play_animation(bool play)
	{
		walk_anim->play_animation(play);
	}

	void render()
	{
		//GameObject::render();
		walk_anim->render();
	}

};

#endif /* VICTIM_MODEL_H_ */



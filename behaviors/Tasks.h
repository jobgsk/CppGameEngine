#ifndef TASKS_H_
#define TASKS_H_

#include "../GameObject.h"

class BehaviourTask {
public:
	GameObject * m_game_object;
	BehaviourTask(GameObject * game_object)
	{
		m_game_object = game_object;
	}
	virtual BehaviourTask * task(float duration) = 0;
};


class FindClosesNode : public BehaviourTask {
public:
	//BehaviourTask * task_move_to_target;
	BehaviourTask * task_turn_to_target;

	FindClosesNode(GameObject* game_object)
		: BehaviourTask(game_object)
	{
	
	};
	
	virtual BehaviourTask * task(float duration);
};

class FindNextNode : public BehaviourTask {
public:
	BehaviourTask * task_find_closes_node;
	BehaviourTask * task_turn_to_target;

	FindNextNode(GameObject* game_object)
		: BehaviourTask(game_object){};
	virtual BehaviourTask * task(float duration);
};

class TurnToTarget : public BehaviourTask {
public:
	BehaviourTask * task_move_to_target;
	BehaviourTask * task_find_closes_node;
	
	TurnToTarget(GameObject* game_object)
		: BehaviourTask(game_object)
	{

	};

	virtual BehaviourTask * task(float duration);
};

class MoveToTarget : public BehaviourTask {
public:
	BehaviourTask * task_turn_to_target;
	BehaviourTask * task_find_next_node;
	BehaviourTask * task_fire_to_target;

	MoveToTarget(GameObject* game_object)
		: BehaviourTask(game_object)
	{

	};

	virtual BehaviourTask * task(float duration);
};

class FireToTarget : public BehaviourTask {
public:
	BehaviourTask * task_turn_to_target;
	BehaviourTask * task_find_closes_node;
	
	FireToTarget(GameObject* game_object)
		: BehaviourTask(game_object)
	{

	};

	virtual BehaviourTask * task(float duration);
};
#endif /* TASKS_H_ */

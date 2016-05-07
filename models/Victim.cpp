#include "Victim.h"


VictimBehave::VictimBehave(GameObject* current_object)
{

	//cast_trace = new CastTrace(current_object, 10.0f);

	ObjectsFactory * fact = ObjectsFactory::instance();
	std::vector<GameObject*> interacts = fact->get_obstacles();
	GameObject* target = fact->get_player();

	//for (int i = 0; i < interacts.size(); i++)
	//	cast_trace->set_obstacles(interacts[i]);

	//cast_trace->set_target(target);

	/*
	set up behaviour tree
	*/
	task_find_closes_node = new FindClosesNode(current_object);
	task_find_next_node = new FindNextNode(current_object);
	task_turn_to_target = new TurnToTarget(current_object);
	task_move_to_target = new MoveToTarget(current_object);
	task_fire_to_target = new FireToTarget(current_object);

	task_find_closes_node->task_turn_to_target = task_turn_to_target;

	task_find_next_node->task_find_closes_node = task_find_closes_node;
	task_find_next_node->task_turn_to_target = task_turn_to_target;

	task_turn_to_target->task_find_closes_node = task_find_closes_node;
	task_turn_to_target->task_move_to_target = task_move_to_target;

	task_move_to_target->task_find_next_node = task_find_next_node;
	task_move_to_target->task_turn_to_target = task_turn_to_target;
	task_move_to_target->task_fire_to_target = task_fire_to_target;

	task_fire_to_target->task_find_closes_node = task_find_closes_node;
	task_fire_to_target->task_turn_to_target = task_turn_to_target;

	/*
	set up init task
	*/
	begin_task();
};

void VictimBehave::begin_task()
{
	behaviour_task = task_find_closes_node;
};
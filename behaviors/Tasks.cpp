
#include "Tasks.h"
#include "../models/Enemy.h"
#include "../models/Victim.h"
#include "../models/Player.h"


BehaviourTask * FindClosesNode::task(float duration)
{
	//std::cout << " Task Find Closes Node" << std::endl;

	ObjectsFactory * fact = ObjectsFactory::instance();
	std::vector<GameObject*> nodes = fact->get_nodes();
	NodeModel * nmodel = ((NodeModel*)nodes[0]);
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->get_pos().magnitude() < nmodel->get_pos().magnitude())
			nmodel = ((NodeModel*)nodes[i]);
	}

	m_game_object->m_target = nmodel;
		
	return task_turn_to_target;
};

BehaviourTask * FindNextNode::task(float duration)
{
	//std::cout << " Task Find Next Node" << std::endl;

	if (!dynamic_cast<NodeModel*>(m_game_object->m_target))
		return task_find_closes_node;
	
	ObjectsFactory * fact = ObjectsFactory::instance();
	std::vector<GameObject*> nodes = fact->get_nodes();

	GameObject * player = fact->get_player();
	//int idx = ((NodeModel*)(m_game_object->m_target))->index_next_node;
	m_game_object->m_target = player;
	return task_turn_to_target;
};

BehaviourTask * TurnToTarget::task(float duration)
{
	//std::cout << " Task Turn To Target" << std::endl;

	if (!m_game_object->m_target)
		return task_find_closes_node;

	float angle_between = tanks::get_angle_between_objects(
		m_game_object->get_pos(), m_game_object->get_dir(), 
		m_game_object->m_target->get_pos());
	if (angle_between < 10)
		return task_move_to_target;

	//std::cout << " angle between " << angle_between << std::endl;
	m_game_object->rotate(true, 1);
	return this;
};

BehaviourTask * MoveToTarget::task(float duration)
{
	//std::cout << " Task Move To Target" << std::endl;

	//if (((PlayerModel *)(((EnemyModel*)m_game_object)->target)) &&
	//	(((EnemyModel*)m_game_object)->target->get_pos().magnitude() -
	//		m_game_object->get_pos().magnitude()) <= 5)
	//	return task_fire_to_target;

	if (((NodeModel *)(m_game_object->m_target) &&
		abs(m_game_object->m_target->get_pos().magnitude() - m_game_object->get_pos().magnitude()) <= 2))
		return task_find_next_node;


	m_game_object->translate(true, 2);
	return this;
};

BehaviourTask * FireToTarget::task(float duration)
{
	//std::cout << " Task Fire To Target" << std::endl;
	return this;
};
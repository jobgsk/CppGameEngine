#include "CastTrace.h"

bool CastTrace::collide(GameObject* o, float angle_can_see)
{
	float grad_angle_betwen = tanks::get_angle_between_objects(
		m_go->get_pos(), m_go->get_dir(), o->get_pos());
	if (grad_angle_betwen < angle_can_see)
		return true;
	return false;
};

bool CastTrace::overlap(GameObject* target, GameObject* obstacle)
{
	Vector3 target_position = target->get_pos();
	Vector3 obstacle_position = obstacle->get_pos();
	Vector3 current_position = m_go->get_pos();

	float target_distance = (target_position - current_position).magnitude();
	float obstacle_distace = (obstacle_position - current_position).magnitude();

	if (obstacle_distace < target_distance)
		return true;
	return false;
};

bool CastTrace::find_target()
{
	if (!collide(m_target, m_angle_can_see))
		return false;

	for (int i = 0; i < m_obstacles.size(); i++)
	{
		if (!collide(m_obstacles[i], m_angle_can_see))
			continue;

		if (overlap(m_target, m_obstacles[i]))
			return false;
	}
	return true;
};
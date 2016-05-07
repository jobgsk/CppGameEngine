#ifndef RAY_TRACE_H_
#define RAY_TRACE_H_

#include <vector>
#include "../GameObject.h"

class CastTrace
{
protected:
	GameObject * m_go;
	std::vector<GameObject*> m_obstacles;

public:
	GameObject* m_target;
	float m_angle_can_see;

	CastTrace() {};
	CastTrace(GameObject *go, float angle_can_see)
	{
		m_go = go;
		m_angle_can_see = angle_can_see;
	};

	void set_target(GameObject* target)
	{
		m_target = target;
	}

	void set_obstacles(GameObject* obj)
	{
		m_obstacles.push_back(obj);
	};

	bool find_target();
	bool collide(GameObject* o, float angle_can_see);
	bool overlap(GameObject* target, GameObject* obstacle);
};

#endif /* RAY_TRACE_H_ */
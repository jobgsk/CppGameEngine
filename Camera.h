#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.h"

class Camera  {


public:
	glm::vec3 m_position;
	glm::vec3 m_direction;

	float m_distance;
	GameObject *m_target;

	enum CameraPosition
	{
		BEHIND,
		ONTOP,
		INFRONT
	};
	CameraPosition m_camera_position;

	Camera(GameObject *target, float distance)
	{
		m_distance = distance;
		m_target = target;

	};

	//TODO: instead of calling set_behind every time, 
	//remove update, create methods getPosition, getDirection
	//calculate position and direction depend of m_camera_position
	void update()
	{
		if (m_camera_position == CameraPosition::BEHIND)
			set_behind();
		if (m_camera_position == CameraPosition::INFRONT)
			set_infront();
	};
		
	void set_behind()
	{
		Vector3 t_pos = m_target->get_pos();
		Vector3 t_dir = m_target->get_dir();
		glm::vec3 t_position = glm::vec3(t_pos.x, t_pos.y, t_pos.z);
		glm::vec3 t_direct = glm::vec3(t_dir.x, t_dir.y, t_dir.z);
		t_direct *= -1;
		
		
		glm::vec3 behind_position = (t_direct * m_distance) + t_position;
		m_position = glm::vec3(behind_position.x, behind_position.y+1.5, behind_position.z);
		m_direction = glm::vec3(t_position.x, t_position.y+1.5, t_position.z);

		m_camera_position = CameraPosition::BEHIND;
	};

	void set_ontop()
	{
		std::cout << " set_ontop " << std::endl;
		m_position = glm::vec3(0.01, m_distance+80, 0.01);
		m_direction = glm::vec3(0.0, 0.1, 0.0);
		m_camera_position = CameraPosition::ONTOP;
	};

	void set_infront()
	{
		Vector3 t_pos = m_target->get_pos();
		Vector3 t_dir = m_target->get_dir() * m_distance + t_pos;

		std::cout << " set_infront " << t_dir.x << " " << t_dir.y << " " << t_dir.z << std::endl;

		m_position = glm::vec3(t_pos.x, t_pos.y+5, t_pos.z);
		m_direction = glm::vec3(t_dir.x, t_dir.y-0.9, t_dir.z);
		m_camera_position = CameraPosition::INFRONT;
	};

};

#endif /* CAMERA_H_ */
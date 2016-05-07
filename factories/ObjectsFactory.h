#ifndef OBJECTS_FACTORY_H_
#define OBJECTS_FACTORY_H_

#include <vector>
#include "../GameObject.h"
#include "../Camera.h"

class ObjectsFactory {
private:
	std::vector<GameObject*> m_game_objects;

	std::vector<GameObject*> m_enemies;
	std::vector<GameObject*> m_victims;
	std::vector<GameObject*> m_obstacles;
	std::vector<GameObject*> m_bulets;
	std::vector<GameObject*> m_flores;
	std::vector<GameObject*> m_nodes;
	
	GameObject * m_player;
	Camera * m_camera;

	CollisionPlane * m_plane;
	CollisionData * m_collision_data;

	static ObjectsFactory *s_instance;
	ObjectsFactory() { };

public:
	static ObjectsFactory *instance()
	{
		if (!s_instance)
			s_instance = new ObjectsFactory();
		return s_instance;
	}

	std::vector<GameObject*> get_game_objects()
	{
		return m_game_objects;
	};

	int num_game_objects()
	{
		return m_game_objects.size();
	};

	/*
		enemies
	*/
	void add_enemy(GameObject * enemy)
	{
		m_enemies.push_back(enemy);
		m_game_objects.push_back(enemy);
	};

	GameObject * get_enemy(int id)
	{
		for (int i = 0; i < m_enemies.size(); i++)
			if (m_enemies[i]->m_id == id)
				return m_enemies[i];
		return NULL;
	};

	int num_enemies()
	{
		return m_enemies.size();
	};

	/*
		victims
	*/
	void add_victim(GameObject * victim)
	{
		m_victims.push_back(victim);
		m_game_objects.push_back(victim);
	};

	GameObject * get_victim(int id)
	{
		for (int i = 0; i < m_victims.size(); i++)
			if (m_victims[i]->m_id == id)
				return m_victims[i];
		return NULL;
	};

	int num_victims()
	{
		return m_victims.size();
	};

	/*
		obstacles
	*/
	void add_obstacle(GameObject * obstacle)
	{
		m_obstacles.push_back(obstacle);
		m_game_objects.push_back(obstacle);
	};

	GameObject * get_obstacle(int id)
	{
		for (int i = 0; i < m_obstacles.size(); i++)
			if (m_obstacles[i]->m_id == id)
				return m_obstacles[i];
		return NULL;
	};

	std::vector<GameObject*> get_obstacles()
	{
		return m_obstacles;
	};

	int num_obstacles()
	{
		return m_obstacles.size();
	};

	/*
		bulets
	*/
	void add_bulet(GameObject * bulet)
	{
		m_bulets.push_back(bulet);
		m_game_objects.push_back(bulet);
	};

	std::vector<GameObject*> get_bulets()
	{
		return m_bulets;
	};

	int num_bulets()
	{
		return m_bulets.size();
	};

	/*
	flore
	*/
	void add_flore(GameObject * flore)
	{
		m_flores.push_back(flore);
		m_game_objects.push_back(flore);
	};

	std::vector<GameObject*> get_flores()
	{
		return m_flores;
	};

	int num_flores()
	{
		return m_flores.size();
	};

	/*
	path nodes
	*/
	void add_node(GameObject * node)
	{
		m_nodes.push_back(node);
	};

	std::vector<GameObject*> get_nodes()
	{
		return m_nodes;
	};

	int num_nodes()
	{
		return m_nodes.size();
	};

	/*
		camera
	*/
	void add_camera(Camera * camera)
	{
		m_camera = camera;
	};

	Camera * get_camera()
	{
		return m_camera;
	};

	/*
		player
	*/
	void add_player(GameObject * player)
	{
		m_player = player;
		m_game_objects.push_back(player);
	};

	GameObject * get_player()
	{
		return m_player;
	};

	/*
		plain
	*/
	void set_plane(CollisionPlane * plane)
	{
		m_plane = plane;
	};

	CollisionPlane * get_plane()
	{
		return m_plane;
	};

	/*
		collisions
	*/
	void set_collision_data(CollisionData * collision_data)
	{
		m_collision_data = collision_data;
	};

	CollisionData * get_collision_data()
	{
		return m_collision_data;
	};
};
#endif /* OBJECTS_FACTORY_H_ */
#ifndef SCENELEVEL_H_
#define SCENELEVEL_H_	

#include <iostream>
#include <deque>

#include "Scene.h"


class SceneLevel : public Scene
{
private:
	/** Holds the maximum number of contacts. */
	const static unsigned maxContacts = 256;

	/** Holds the array of contacts. */
	Contact contacts[maxContacts];

	/** Holds the collision data structure for collision detection. */
	CollisionData cData;

	/** Holds the contact resolver. */
	ContactResolver resolver;

	// Create the ground plane data
	CollisionPlane plane;
public:
	//GameObject* floor;
	//GameObject* panel1;
	//GameObject* panel2;
	GameObject* player;
	GameObject* enemy;

	//std::vector<GameObject*> game_objects;
	//std::vector<GameObject*> bullets;
	GameObject* bullet;

	enum LevelStatus
	{
		PLAY,
		WIN,
		LOSE,
		PAUSE
	};
	LevelStatus lstatus;

	SceneLevel(SceneType level)
		:Scene(level),
		resolver(maxContacts * 8, 0.001, 0.001)
	{
		cData.contactArray = contacts;
		cData.friction = (real)0.99;
		cData.restitution = (real)0.1;
		cData.tolerance = (real)0.1;

		plane.direction = Vector3(0, 1, 0);
		plane.offset = 0;
	};
	~SceneLevel()
	{
		Scene::~Scene();
	};
	void init();

	void display();
	void update(float duration);
	void redefine();
	void keyboard(tanks::ButtonControlls button);

	LevelStatus getLstatus() 
	{ 
		return lstatus; 
	};
};

#endif /* SCENELEVEL_H_ */
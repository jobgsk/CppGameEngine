
#include "SceneLevel.h"
#include "../models/Panel.h"
#include "../models/Plain.h"
#include "../models/Player.h"
#include "../models/Box.h"
#include "../models/Bullet.h"
#include "../models/Enemy.h"
#include "../factories/ObjectsFactory.h"
#include "../factories/MapParser.h"

void SceneLevel::init()
{
	if (inited)
		return;

	ParseMap("media/maps/map2.txt");
	ObjectsFactory * fact = ObjectsFactory::instance();

	player = fact->get_player();
	//enemy = fact->get_enemy(0);

	//GameObject* panel1 = new PanelModel(0, Vector3(-3.5, 0.0, 0), 0.7);
	//GameObject* panel2  = new PanelModel(1, Vector3(3.5, 0.0, 0), 0.7);
	//GameObject* floor = new PlainModel(2, 0.7);
	//GameObject* box1 = new BoxModel(3, Vector3(2.5, 1.0, 2.5), 1);

	//player = new PlayerModel(4);
	bullet = new BulletModel(5, Vector3(1.0, 1.0, 1.0));
	//enemy = new EnemyModel(6);

	//game_objects.push_back(panel1);
	//game_objects.push_back(panel2);
	//game_objects.push_back(floor);
	//game_objects.push_back(box1);
	//game_objects.push_back(player);
	//game_objects.push_back(bullet);
	//game_objects.push_back(enemy);

	camera = new Camera(player, 1.2);
	camera->set_behind();
	//camera->set_infront();
	//camera->set_ontop();

	//game_objects, &plane, &cData, camera

	
	//fact->add_obstacle(panel1);
	//fact->add_obstacle(panel2);
	//fact->add_obstacle(floor);
	//fact->add_obstacle(box1);

	//fact->add_player(player);
	//fact->add_enemy(enemy);
	fact->add_bulet(bullet);
	fact->add_camera(camera);

	fact->set_plane(&plane);
	fact->set_collision_data(&cData);


	set_init();
	lstatus = LevelStatus::PLAY;
};

void SceneLevel::display()
{
	std::vector<GameObject*> game_objects = ObjectsFactory::instance()->get_game_objects();
	for (int i = 0; i < game_objects.size(); i++)
	{
		if (game_objects[i]->state != GameObject::ObjectState::ACTIVE)
			continue;

		game_objects[i]->render();
	}
};


void SceneLevel::redefine()
{
	lstatus = LevelStatus::PLAY;

};

void SceneLevel::update(float duration)
{
	if (lstatus != LevelStatus::PLAY)
		return;

	cData.reset(maxContacts);

	std::vector<GameObject*> game_objects = ObjectsFactory::instance()->get_game_objects();
	for (int i = 0; i < game_objects.size(); i++)
	{
		if (game_objects[i]->state != GameObject::ObjectState::ACTIVE)
			continue;

		game_objects[i]->update(duration);
	}

	// Resolve detected contacts
	resolver.resolveContacts(cData.contactArray, cData.contactCount, duration);

	camera->update();
};

void SceneLevel::keyboard(tanks::ButtonControlls button)
{
	if (button == tanks::ButtonControlls::MOVE_UP)
	{
		((PlayerModel*)player)->translate(true, 5);
		//((EnemyModel*)enemy)->translate(true);
		return;
	}

	if (button == tanks::ButtonControlls::MOVE_DOWN)
	{
		((PlayerModel*)player)->translate(false, 5);
		//((EnemyModel*)enemy)->translate(false);
		return;
	}

	if (button == tanks::ButtonControlls::TURN_LEFT)
	{
		((PlayerModel*)player)->rotate(false, 1);
		//((EnemyModel*)enemy)->rotate(false);
		return;
	}

	if (button == tanks::ButtonControlls::TURN_RIGHT)
	{
		((PlayerModel*)player)->rotate(true, 1);
		//((EnemyModel*)enemy)->rotate(true);
		return;
	}

	if (button == tanks::ButtonControlls::SHOOT)
	{
		((PlayerModel*)player)->shoot();
		//((EnemyModel*)enemy)->shoot();
		return;
	}

	if (button == tanks::ButtonControlls::JUMP)
	{
		((PlayerModel*)player)->jump();
		//((EnemyModel*)enemy)->jump();
		return;
	}

	if (button == tanks::ButtonControlls::NONE)
	{
		((PlayerModel*)player)->play_animation(false);
		//((EnemyModel*)enemy)->play_animation(false);
		return;
	}

	

	if (button == tanks::ButtonControlls::SHOW_MAP)
	{
		//camera->set_atside();
		camera->set_ontop();
		return;
	}
	
	if (button == tanks::ButtonControlls::SHOW_GAME)
	{
		camera->set_behind();
		return;
	}
};
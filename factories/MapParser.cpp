
#include "MapParser.h"
#include "../models/Panel.h"
#include "../models/Plain.h"
#include "../models/Ceiling.h"
#include "../models/Box.h"
#include "../models/Player.h"
#include "../models/Enemy.h"
#include "../models/Victim.h"
#include "../models/Node.h"

#include "../factories/ObjectsFactory.h"

bool ParseWall(const char *ch, float px, float pz)
{
	if (*ch != 'a' && *ch != 'b' && *ch != 'c')
		return false;

	Quaternion q1 = Quaternion(1, 0, 0, 0); // b
	Quaternion q2 = Quaternion(90, Vector3(0, 1, 0)); // a

	float scale = 2;
	Vector3 pos = Vector3(px, 0, pz);
	if (*ch == 'b')
	{
		ObjectsFactory::instance()->add_obstacle(
			new PanelModel(ObjectsFactory::instance()->num_obstacles(), pos, scale, q1));
	}
	else if (*ch == 'a')
	{
		ObjectsFactory::instance()->add_obstacle(
			new PanelModel(ObjectsFactory::instance()->num_obstacles(), pos, scale, q2));
	}
	else if (*ch == 'c')
	{
		ObjectsFactory::instance()->add_obstacle(
			new PanelModel(ObjectsFactory::instance()->num_obstacles(), pos, scale, q1));
		ObjectsFactory::instance()->add_obstacle(
			new PanelModel(ObjectsFactory::instance()->num_obstacles(), pos, scale, q2));
	}
	return true;
};

bool ParseNode(const char *ch, float px, float pz)
{
	if (*ch != 'n')
		return false;

	Vector3 pos = Vector3(px, 0, pz);
	int num = ObjectsFactory::instance()->num_nodes();
	float scale = 2;
	GameObject* node = new NodeModel(num, pos, scale);
	ObjectsFactory::instance()->add_node(node);
	return true;
};

bool ParseFlore(const char *ch, float px, float pz)
{
	Vector3 pos = Vector3(px, 0, pz);
	int num = ObjectsFactory::instance()->num_flores();
	float scale = 2;
	GameObject* floor = new PlainModel(num, pos, scale);
	GameObject* ceiling = new CeilingModel(num, pos, scale);

	ObjectsFactory::instance()->add_flore(floor);
	ObjectsFactory::instance()->add_flore(ceiling);
	return true;
}
bool ParseBox(const char *ch, float px, float pz)
{
	if (*ch != 'o')
		return false;

	Quaternion q1 = Quaternion(1, 0, 0, 0);
	int num = ObjectsFactory::instance()->num_obstacles();
	float scale = 1;
	Vector3 pos = Vector3(px, 0, pz);

	BoxModel* box1 = new BoxModel(num, pos, scale, q1);
	ObjectsFactory::instance()->add_obstacle(box1);
	return true;
};

bool ParsePlayer(const char *ch, float px, float pz)
{
	if (*ch != 'p')
		return false;

	Quaternion q1 = Quaternion(90, Vector3(0, 1, 0));
	int num = 1;
	float scale = 1;
	Vector3 pos = Vector3(px, 0, pz);
	PlayerModel * player = new PlayerModel(num, pos, scale, q1);
	ObjectsFactory::instance()->add_player(player);
	return true;
};

bool ParseEnemy(const char *ch, float px, float pz)
{
	if (*ch != 'e')
		return false;

	int num = ObjectsFactory::instance()->num_enemies();
	float scale = 2;
	Vector3 pos = Vector3(px, 0, pz);
	Quaternion q1 = Quaternion(90, Vector3(0, 1, 0));
	EnemyModel * enemy = new EnemyModel(num, pos, scale, q1);
	ObjectsFactory::instance()->add_enemy(enemy);
	return true;
};

bool ParseGirl(const char *ch, float px, float pz)
{
	if (*ch != 'g')
		return false;

	int num = ObjectsFactory::instance()->num_victims();
	float scale = 2;
	Vector3 pos = Vector3(px, 0, pz);
	Quaternion q1 = Quaternion(90, Vector3(0, 1, 0));
	VictimModel * vmodel = new VictimModel(num, pos, scale, q1);
	ObjectsFactory::instance()->add_victim(vmodel);
	return true;
};

void ParseMap(string filename)
{
	string input;
	ifstream inFile;

	inFile.open(filename, fstream::in);
	if (!inFile)
	{
		cout << "Cannot open map file!" << endl;
	}

	int x = 0, z = 0, x_delta = 0, z_delta = 0;
	while (getline(inFile, input)) // Loops through file line-by-line until the eof() is reached.
	{
		//cout << "Read line: " << input << endl;
		// get first char
		const char *ch = input.c_str();

		x = 0;
		while (*ch != '\0')
		{
			
			float px = (x - x_delta);
			float pz = (z - z_delta);

			ParseFlore(ch, px, pz);

			if (*ch == 'a' || *ch == 'b' || *ch == 'c')
			{
				ParseWall(ch, px, pz);
			}

			else if (*ch == 'o')
			{
				ParseBox(ch, px, pz);
			}

			else if (*ch == 'p')
			{
				ParsePlayer(ch, px, pz);
			}

			else if (*ch == 'e')
			{
				ParseEnemy(ch, px, pz);
			}
			else if (*ch == 'g')
			{
				ParseGirl(ch, px, pz);
			}

			else if (*ch == 'n')
			{
				ParseNode(ch, px, pz);
			}

			

			ch++, x++;
		}
		z++;
	}
	inFile.close();
};

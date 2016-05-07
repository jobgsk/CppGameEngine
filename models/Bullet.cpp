#include "Bullet.h"
#include "Box.h"
#include "Enemy.h"
#include "Player.h"

void BulletModel::update(float duration)
{
	GameObject::update(duration);
	cspher->calculateInternals();

	std::vector<GameObject*> game_objects = ObjectsFactory::instance()->get_game_objects();

	if (CollisionDetector::sphereAndHalfSpace(
		*cspher, *ObjectsFactory::instance()->get_plane(),
		ObjectsFactory::instance()->get_collision_data()))
	{

	}

	for (int i = 0; i < game_objects.size(); i++)
	{
		GameObject * go = game_objects[i];
		if (!dynamic_cast<BoxModel*>(go) &&
			!dynamic_cast<EnemyModel*>(go) &&
			!dynamic_cast<PlayerModel*>(go))
			continue;

		if (dynamic_cast<EnemyModel*>(go) && CollisionDetector::boxAndSphere(
			*((EnemyModel*)go)->cbox, *cspher, ObjectsFactory::instance()->get_collision_data()))
		{
			continue;
		}

		if (dynamic_cast<PlayerModel*>(go) && CollisionDetector::boxAndSphere(
			*((PlayerModel*)go)->cbox, *cspher, ObjectsFactory::instance()->get_collision_data()))
		{
			continue;
		}

		if (dynamic_cast<BoxModel*>(go) && CollisionDetector::boxAndSphere(
			*((BoxModel*)go)->cbox, *cspher, ObjectsFactory::instance()->get_collision_data()))
		{
			continue;
		}
	}
}

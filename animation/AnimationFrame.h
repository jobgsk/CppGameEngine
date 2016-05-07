#ifndef ANIMATION_FRAME_H_
#define ANIMATION_FRAME_H_

#include <vector>
#include "AnimationBone.h"
#include "../GameObject.h"

class AnimationFrame
{
public:
	std::vector<AnimationBone*> blist;
	int current;
	int m_id;
	GameObject * m_owner;

	AnimationFrame(int id, GameObject * owner): 
		m_id(id), m_owner(owner)
	{

	};

	void create_bone(
		int bid, std::string bname, int pid,
		float len,
		float px, float py, float pz,
		float w, float vx, float vy, float vz)
	{
		current = blist.size();
		blist.push_back(new AnimationBone(px, py, pz, w, vx, vy, vz, bid, bname));
	}

	AnimationBone * get_current()
	{
		if (blist.size() == 0)
			return NULL;
		return blist[current];
	}

	/*void test()
	{
		for (int i = 0; i < blist.size(); i++)
		{
			Quaternion orient = blist[i]->m_body->getOrientation();
			orient.get_euler();
			Vector3 pos = blist[i]->m_body->getPointInWorldSpace(Vector3(0, 0, 0));

			//Vector3 dir = blist[i]->m_body->getDirectionInWorldSpace(Vector3(1, 1, 1));

			//Matrix3 r_matrix = Matrix3();
			//r_matrix.setOrientation(blist[i]->m_body->getOrientation());
			//Vector3 dir = r_matrix.transform(Vector3(1, 1, 1));

			//Vector3 dir = blist[i]->m_body->
			std::cout
				<< "id " << blist[i]->m_id
				<< "pos " << pos.x << " " << pos.y << " " << pos.z
				<< " orient " << orient.alpha << " " << orient.axis.x << " " << orient.axis.y << " " << orient.axis.z
				<< std::endl;
		}
	}
	*/

	virtual void update(float duration)
	{
		Vector3 owner_pos = m_owner->get_pos();
		//owner_pos.y -= m_owner->half_size.y;
		Quaternion owner_orient = m_owner->get_orient();
		
		Matrix4 owner_trans = Matrix4();
		owner_trans.setOrientationAndPos(owner_orient, owner_pos);

		for (int i = 0; i < blist.size(); i++)
		{
			//Vector3 bone_pos = blist[i]->get_ini_pos();
			//Quaternion bone_orient = blist[i]->get_ini_orient();
			//Vector3 bone_dir = blist[i]->get_ini_dir();

			//bone_pos += owner_pos;
			//owner_orient *= bone_orient;
			
			blist[i]->m_transformation = owner_trans * blist[i]->m_init_transformation;

			//blist[i]->m_body->setPosition(bone_pos);
			//blist[i]->m_body->setOrientation(bone_orient);

			//blist[i]->m_body->calculateDerivedData();
			//blist[i]->m_body->integrate(duration);
		}
	}

	void render()
	{
		for (int i = 0; i < blist.size(); i++)
		{
			blist[i]->render();
		}
	};

};

#endif /* ANIMATION_FRAME_H_ */

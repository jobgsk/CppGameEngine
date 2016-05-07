#ifndef PLAYER_ANIMATION_H_
#define PLAYER_ANIMATION_H_

#include "../animation/AnimationClip.h"

class PlayerAnime : public AnimationClip {

public:
	float frame_duration;

	PlayerAnime(GameObject * owner) : AnimationClip()
	{
		float scale = 0.3;

		AnimationParser aparser = AnimationParser("media/animation/Player/in.txt", scale, Vector3(0, 0, 0), owner);
		mlist = aparser.load();

		//Render * r_gun = MeshFactory::get_player_gun_render(scale);//0
		Render * r_left_hend = MeshFactory::get_player_left_hend_render(scale); //1
		Render * r_right_hend = MeshFactory::get_player_right_hend_render(scale); //2
		

		for (int i = 0; i < mlist.size(); i++)
		{
			AnimationFrame * amodel = mlist[i];
			//std::cout << "animation " << amodel->m_id << " " << std::endl;
			//amodel->test();

			for (int j = 0; j < amodel->blist.size(); j++)
			{
				AnimationBone * bmodel = amodel->blist[j];
				//if (bmodel->m_id == 0) bmodel->m_render = r_gun;
				if (bmodel->m_id == 1)	bmodel->m_render = r_left_hend;
				else if (bmodel->m_id == 2)	bmodel->m_render = r_right_hend;
			}
		}
		frame_duration = 0;
	};

	virtual void update(float duration)
	{
		for (int i = 0; i < mlist.size(); i++)
		{
			mlist[i]->update(duration);
		}

		frame_duration += duration;
		if (frame_duration < 0.1)
			return;

		AnimationClip::update(duration);
		frame_duration = 0;
	}
};

#endif /* PLAYER_ANIMATION_H_ */


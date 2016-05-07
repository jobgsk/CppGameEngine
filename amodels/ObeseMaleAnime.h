#ifndef OBESE_MALE_ANIMATION_H_
#define OBESE_MALE_ANIMATION_H_

#include "../animation/AnimationClip.h"

class ObeseMaleAnime  : public AnimationClip {

public:
	float frame_duration;

	ObeseMaleAnime(GameObject * owner) : AnimationClip()
	{
		float scale = 0.45;

		AnimationParser aparser = AnimationParser("media/animation/ObeseMale/in.txt", scale, Vector3(0, -1.3, 0), owner);
		mlist = aparser.load();
		
		Render * r_head = MeshFactory::get_obese_male_head_render(scale); //0
		Render * r_top_left_hend = MeshFactory::get_obese_male_top_left_hend_render(scale); //1
		Render * r_down_left_hend = MeshFactory::get_obese_male_bottom_left_hend_render(scale); //2
		Render * r_top_right_hend = MeshFactory::get_obese_male_top_right_hend_render(scale); //3
		Render * r_down_right_hend = MeshFactory::get_obese_male_bottom_right_hend_render(scale); //4
		Render * r_body = MeshFactory::get_obese_male_body_render(scale); //5
		Render * r_top_left_leg = MeshFactory::get_obese_male_top_left_leg_render(scale); //6
		Render * r_down_left_leg = MeshFactory::get_obese_male_bottom_left_leg_render(scale); //7
		Render * r_top_right_leg = MeshFactory::get_obese_male_top_right_leg_render(scale); //8
		Render * r_down_right_leg = MeshFactory::get_obese_male_bottom_right_leg_render(scale); //9
		

		for (int i = 0; i < mlist.size(); i++)
		{
			AnimationFrame * amodel = mlist[i];
			//std::cout << "animation " << amodel->m_id << " " << std::endl;
			//amodel->test();

			for (int j = 0; j < amodel->blist.size(); j++)
			{
				AnimationBone * bmodel = amodel->blist[j];
				if		(bmodel->m_id == 0) bmodel->m_render = r_head;
				else if (bmodel->m_id == 1)	bmodel->m_render = r_top_left_hend;
				else if (bmodel->m_id == 2)	bmodel->m_render = r_down_left_hend;
				else if (bmodel->m_id == 3)	bmodel->m_render = r_top_right_hend;
				else if (bmodel->m_id == 4)	bmodel->m_render = r_down_right_hend;
				else if (bmodel->m_id == 5)	bmodel->m_render = r_body;
				else if (bmodel->m_id == 6)	bmodel->m_render = r_top_left_leg;
				else if (bmodel->m_id == 7)	bmodel->m_render = r_down_left_leg;
				else if (bmodel->m_id == 8)	bmodel->m_render = r_top_right_leg;
				else if (bmodel->m_id == 9)	bmodel->m_render = r_down_right_leg;

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
		if (frame_duration < 0.2)
			return;

		AnimationClip::update(duration);
		frame_duration = 0;
	}
};

#endif /* OBESE_MALE_ANIMATION_H_ */

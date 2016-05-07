#ifndef ANIMATION_CLIP_H_
#define ANIMATION_CLIP_H_

#include "AnimationParser.h"

class AnimationClip  {

public:
	std::vector<AnimationFrame*> mlist;
	int current;
	int default_frame;
	bool dinamic_animation;
	AnimationClip()
	{
		default_frame = 0;
		dinamic_animation = false;
	};

	AnimationFrame * get_current()
	{
		if (mlist.size() == 0)
			return NULL;
		return mlist[current];
	}

	/*void translate(Vector3 trans)
	{
		for (int i = 0; i < mlist.size(); i++)
		{
			mlist[i]->translate(trans);
		}
	}

	void rotate(Vector3 rot)
	{
		for (int i = 0; i < mlist.size(); i++)
		{
			mlist[i]->rotate(rot);
		}
	}
	*/

	virtual void play_animation(bool play)
	{
		dinamic_animation = play;
	}

	virtual void update(float duration)
	{
		// if the animation is not playing
		if (!dinamic_animation && current == default_frame)
			return;

		current++;
		if (current >= mlist.size())
			current = 0;
	}

	virtual void render()
	{
		AnimationFrame * cmodel = get_current();
		if (cmodel == NULL)
			return;

		cmodel->render();
	};

};

#endif /* OBESE_MALE_ANIM_H_ */

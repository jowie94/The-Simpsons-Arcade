#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>
#include "Sprite.h"

using namespace std;

template<typename T>
class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	vector<T> frames;

private:
	float current_frame = 0.0f;
	int loops = 0;

public:
	Animation()
	{}

	Animation(const Animation& anim) : loop(anim.loop), speed(anim.speed), frames(anim.frames)
	{}

	T& GetCurrentFrame()
	{
		float last_frame = (float) frames.size();

		current_frame += speed;
		if (current_frame >= last_frame)
		{
			current_frame = (loop) ? 0.0f : MAX(last_frame - 1.0f, 0.0f);
			loops++;
		} 

		return frames[(int)current_frame];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		current_frame = 0.0f;
	}
};

typedef Animation<SDL_Rect> RectAnimation;
typedef Animation<Sprite> SpriteAnimation;

#endif // __ANIMATION_H__

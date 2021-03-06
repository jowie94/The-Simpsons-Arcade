#ifndef __ROYD_H__
#define __ROYD_H__

#include "Enemy.h"

class Royd :
	public Enemy
{
public:
	Royd();
	~Royd();

	bool Start() override;
	void PreUpdate() override;
	void PostUpdate() override;

	bool OnCollision(Collider& origin, Collider& other) override;

protected:
	void prepare_input(Input& input) override;

private:
	Input _prepared_input = { KEY_IDLE, KEY_IDLE,0,0 };
	bool _touching_player = false;
	bool _attacking = false;
};

#endif // __ROYD_H__

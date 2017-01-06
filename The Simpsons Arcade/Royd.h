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
protected:
	void prepare_input(Input& input) override;
};

#endif // __ROYD_H__

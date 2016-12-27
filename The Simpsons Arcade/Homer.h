#ifndef __HOMER_H__
#define __HOMER_H__

#include "Player.h"
class Homer :
	public Player
{
public:
	Homer();
	~Homer();
	
	bool Start() override;
};

#endif // __HOMER_H__

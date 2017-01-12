#ifndef __LISA_H__
#define __LISA_H__

#include "Player.h"
class Lisa :
	public Player
{
public:
	Lisa();
	~Lisa();

	bool Start() override;
};

#endif

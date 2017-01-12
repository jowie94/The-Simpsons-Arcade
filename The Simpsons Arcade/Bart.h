#ifndef __BART_H__
#define __BART_H__

#include "Player.h"
class Bart :
	public Player
{
public:
	Bart();
	~Bart();

	bool Start() override;
};

#endif // __BART_H__

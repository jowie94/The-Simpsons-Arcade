#pragma once
#include "Player.h"
class Marge :
	public Player
{
public:
	Marge();
	~Marge();

	bool Start() override;
};


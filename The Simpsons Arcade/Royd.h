#ifndef __ROYD_H__
#define __ROYD_H__

#include "NPC.h"
class Royd :
	public NPC
{
public:
	Royd();
	~Royd();

	bool Start() override;
protected:
	void prepare_input(Input& input) override;
};

#endif // __ROYD_H__

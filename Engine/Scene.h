#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

class Scene : public Module
{
public:
	Scene(bool active) : Module(active) {}
	virtual ~Scene() {}

};

#endif // __SCENE_H__

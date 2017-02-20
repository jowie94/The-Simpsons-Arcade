#include "Engine.h"
#include "FirstScene.h"
#include "EntityFactory.h"
#include "ModuleRender.h"
#include "ModuleSceneManager.h"
#include "StartScene.h"

int main(int argc, char ** argv)
{
	ReportMemoryLeaks();

	LOG("Engine Creation --------------");
	Engine* App = new Engine();

	App->scene_manager->SetInitialScene(new StartScene(false));
	EntityFactory* factory = new EntityFactory();
	App->scene_manager->SetEntityFactory(factory);
	App->renderer->RenderingAngle = 20;

	int main_return = App->Loop();

	RELEASE(factory);
	RELEASE(App);
	LOG("Bye :)\n");
	return main_return;
}

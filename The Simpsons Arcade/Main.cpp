#include "Engine.h"
#include "FirstScene.h"
#include "EntityFactory.h"

int main(int argc, char ** argv)
{
	ReportMemoryLeaks();

	LOG("Engine Creation --------------");
	Engine* App = new Engine();

	App->scene_manager->SetInitialScene(new FirstScene(false));
	EntityFactory* factory = new EntityFactory();
	App->scene_manager->SetEntityFactory(factory);

	int main_return = App->Loop();

	RELEASE(factory);
	RELEASE(App);
	LOG("Bye :)\n");
	return main_return;
}

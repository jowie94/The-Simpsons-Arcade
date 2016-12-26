#include "Engine.h"
#include "FirstScene.h"
#include "EntityFactory.h"

int main(int argc, char ** argv)
{
	ReportMemoryLeaks();

	LOG("Engine Creation --------------");
	Engine* App = new Engine();

	App->scene_manager->SetInitialScene(new FirstScene(false));
	App->scene_manager->SetEntityFactory(new EntityFactory());

	int main_return = App->Loop();

	RELEASE(App);
	LOG("Bye :)\n");
	return main_return;
}

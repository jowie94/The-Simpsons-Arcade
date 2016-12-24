#include "Engine.h"
#include "FirstScene.h"

int main(int argc, char ** argv)
{
	ReportMemoryLeaks();

	LOG("Engine Creation --------------");
	Engine* App = new Engine();

	App->scene_manager->SetInitialScene(new FirstScene(false));

	int main_return = App->Loop();

	RELEASE(App);
	LOG("Bye :)\n");
	return main_return;
}

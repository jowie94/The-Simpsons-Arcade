#include "Engine.h"

int main(int argc, char ** argv)
{
	ReportMemoryLeaks();

	LOG("Engine Creation --------------");
	Engine* App = new Engine();

	int main_return = App->Loop();

	RELEASE(App);
	LOG("Bye :)\n");
	return main_return;
}
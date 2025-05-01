#include "Application.h"

using namespace bobcat;
using namespace std;

Application::Application() {
    window = new Window(100, 100, 400, 400, "Pain Application");

    window->show();
}
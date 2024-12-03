#include "Application.h"


int main()
{
	Application* app = Application::GetInstance();
    app->Run();
}
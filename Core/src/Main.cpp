#include "Application.h"


int main()
{
	Application* app = Application::GetInstance();

    while (true)
	    app->Update();
}
#include "Application.h"
#include <glad/glad.h>


int main()
{
	Application* app = Application::GetInstance();
    app->Run();
}
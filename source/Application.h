#pragma once
#include "Renderer.h"
#include "Audio.h"
#include "Input.h"
#include "Tester.h"


class Application 
{
public:
	Application();
	void Run();
	void Cleanup();
private:
	SDL_Window* window;
	Renderer renderer;
	Audio audio; 
	Tester tester;
};
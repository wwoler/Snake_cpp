#pragma once

#include "World.h"

class game
{
private:
	world*      __world;
	std::thread __thread;

public:
	game()
	{
		__world = new world(20, 20);
	}

	void run()
	{
		__world->initWorld();

		__thread = std::move(std::thread(&world::threaded_logic, __world));

		while (1)
		{
			__world->printWorld();
			__world->WorldLogic();
			Sleep(1.5);
			system("cls");
		}

		
	}

	~game()
	{
		delete __world;
		if (__thread.joinable())
			__thread.detach();
	}

};
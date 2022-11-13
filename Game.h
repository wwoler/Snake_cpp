#pragma once

#include "World.h"

class game
{
private:
	world*              _world;
	std::thread         _thread;

	bool                _isOver;

public:
	game()
	{
		_world = new world(55, 25);
		_isOver = false;
	}

	auto run() -> void
	{
		_world->initWorld();

		_thread = std::move(std::thread(&world::threaded_logic, _world));

		Sleep(100);

		while (_world->game_status())
		{
			_world->WorldLogic();
		}

		system("cls");
		std::wcout << "Game over\nYour score: " <<
			_world->get_score()->GetScore() << "\a\n\n\n\n";
		
	}

	~game()
	{
		delete _world;
		if (_thread.joinable())
			_thread.join();
	}

};
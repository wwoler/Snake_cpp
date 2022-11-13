#pragma once

#include "Fruits.h"
#include "Snake.h"
#include "Score.h"
#include <thread>
#include <chrono>
#include <Windows.h>


class world
{
private:
	uint16_t const      _width;
	uint16_t const      _height;
	fruits*             _fruit;
	snacke*             _snake;
	score*              _score;
	HANDLE              _hConsole;
	bool                _gameStatus;
	CONSOLE_CURSOR_INFO _cursorInfo;

	void printWorld()
	{

		for (int h = 0; h < _height; ++h)
		{

			for (int w = 0; w < _width; ++w)
			{
				if (h == 0 && w == 0)
					std::wcout << L'┌';
				else if (h == 0 && w == _width - 1)
					std::wcout << L'┐';
				else if (h == _height - 1 && w == 0)
					std::wcout << L'└';
				else if (h == _height - 1 && w == _width - 1)
					std::wcout << L'┘';
				else if (h == 0 || h == _height - 1)
					std::wcout << L'─';
				else if (w == 0 || w == _width - 1)
					std::wcout << L'│';
				else
					std::wcout << ' ';
			}
			std::wcout << std::endl;

		}
	}

public:
	world(uint16_t const& width_, uint16_t const& height_)
		:_width(width_), _height(height_) {}

	auto initWorld() -> void
	{
		_cursorInfo = { sizeof(_cursorInfo), false };
		_gameStatus = true;
		_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		_fruit = new fruits(_width, _height);
		_snake = new snacke(_width, _height);
		_score = new score();
		SetConsoleCursorInfo(_hConsole, &_cursorInfo);
		SetConsoleTextAttribute(_hConsole, 0xb);
		printWorld();
		printFruit();
		printSnake();
		printScore();
	}



	auto WorldLogic() -> bool
	{
		printSnake();
		_snake->SnakeLogic();
		objectLogic();
		Sleep(50);
		return _gameStatus;
	}


	auto objectLogic() -> void
	{
		if (_snake->getXcoord() == _fruit->getXcoord() &&
			_snake->getYcoord() == _fruit->getYcoord())
		{
			removeFruit();
			_snake->addTail();
			_score->addPoint();
			printScore();
			_fruit->FruitLogic();
			printFruit();
			while (true)
			{
				bool FruitOnSnake = false;
				for (uint16_t i = 0u; i < _snake->getNtail(); ++i)
				{
					if (_snake->getXtailCoord(i) == _fruit->getXcoord() &&
						_snake->getYtailCoord(i) == _fruit->getYcoord())
					{
						FruitOnSnake = true;
						removeFruit();
						break;
					}

				}
				if (!FruitOnSnake)
					break;
				_fruit->FruitLogic();
			}
			printFruit();
		}
	}
	

	auto threaded_logic() -> void
	{

		while (_gameStatus)
		{

			for (uint16_t i = 0; i < _snake->getNtail(); ++i)
			{
				if (_snake->getXcoord() == _snake->getXtailCoord(i) && _snake->getYcoord() == _snake->getYtailCoord(i))
				{
					_gameStatus = false;
					SetConsoleTextAttribute(_hConsole, 3);
				}
			}

			_snake->threaded_logic();
			Sleep(10);

		}

	}


	auto printFruit() -> void
	{
		SetConsoleTextAttribute(_hConsole, 0xC);
		_fruit->get_console_coord().X = _fruit->getXcoord();
		_fruit->get_console_coord().Y = _fruit->getYcoord();
		SetConsoleCursorPosition(_hConsole, _fruit->get_console_coord());
		std::wcout << '$';

	}

	auto removeFruit() -> void
	{
		_fruit->get_console_coord().X = _fruit->getXcoord();
		_fruit->get_console_coord().Y = _fruit->getYcoord();
		SetConsoleCursorPosition(_hConsole, _fruit->get_console_coord());
		std::wcout << ' ';
	}

	auto printSnake() -> void
	{
		SetConsoleTextAttribute(_hConsole, 0xA);
		SetConsoleCursorPosition(_hConsole, _snake->get_console_coord());
		std::wcout << ' ';
		if (_snake->getNtail() > 0)
		{

			for (int i = 0; i < _snake->getNtail(); ++i)
			{
				_snake->get_console_coord().X = _snake->getXtailCoord(i); 
				_snake->get_console_coord().Y = _snake->getYtailCoord(i);
				if (_snake->get_console_coord().X == 0 && _snake->get_console_coord().Y == 0)
					continue;
				SetConsoleCursorPosition(_hConsole, _snake->get_console_coord());
				std::wcout << 'o';
			}

			_snake->get_console_coord().X = _snake->getOXcoord();
			_snake->get_console_coord().Y = _snake->getOYcoord();
			if (!(_snake->get_console_coord().X == 0 && _snake->get_console_coord().Y == 0))
			{
				SetConsoleCursorPosition(_hConsole, _snake->get_console_coord());
				std::wcout << ' ';
			}
		}

		_snake->get_console_coord().X = _snake->getXcoord();
		_snake->get_console_coord().Y = _snake->getYcoord();
		SetConsoleCursorPosition(_hConsole, _snake->get_console_coord());
		std::wcout << _snake->get_symbol();
	}

	auto printScore() -> void
	{
		SetConsoleTextAttribute(_hConsole, 0xb);
		COORD coord;
		coord.X = _width + 10;
		coord.Y = 0;
		SetConsoleCursorPosition(_hConsole, coord);
		std::wcout << L"Snake 2.0\n";
		coord.Y = 1;
		SetConsoleCursorPosition(_hConsole, coord);
		std::wcout << L"Score: " << _score->GetScore();
	

	}

	bool game_status()
	{
		return _gameStatus;
	}

	score* get_score()
	{
		return _score;
	}

	~world()
	{
		delete _score;
		delete _snake;
		delete _fruit;
		CloseHandle(_hConsole);
	}

};

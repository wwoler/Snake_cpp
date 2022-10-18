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
	uint16_t const __width;
	uint16_t const __height;
	fruits*        __fruit;
	snacke*        __snake;
	score*         __score;
	HANDLE         __hConsole;

public:
	world(uint16_t const& width_, uint16_t const& height_)
		:__width(width_), __height(height_) {}

	void initWorld()
	{
		__fruit = new fruits(__width, __height);
		__snake = new snacke(__width, __height);
		__score = new score();
		__hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	}


	void printWorld() const
	{
		SetConsoleTextAttribute(__hConsole, 0xb);

		wchar_t const* symbol1 = L"\u005F";
		wchar_t const* symbol2 = L"\u203E";

		std::wstring str;
		str.reserve(__width + 1);
		for (uint16_t i = 0; i < __width; ++i)
			str.append(symbol1);

		std::wcout << L" " + str << '\n';


		for (uint16_t h = 0; h < __height; ++h)
		{
			std::wcout << L'|';
			for (uint16_t w = 0; w < __width; ++w)
			{
				if (__fruit->getYcoord() == h && __fruit->getXcoord() == w)
				{
					SetConsoleTextAttribute(__hConsole, 0xa);
					__fruit->printFruit();
					SetConsoleTextAttribute(__hConsole, 0xb);
				}
				else if (__snake->getYcoord() == h && __snake->getXcoord() == w)
				{
					SetConsoleTextAttribute(__hConsole, 0xc);
					__snake->printSnacke();
					SetConsoleTextAttribute(__hConsole, 0xb);
				}

				else 
				{
					bool bFind = false;
					for (uint16_t t = 0; t < __snake->getNtail(); ++t)
					{
						if (__snake->getXtailCoord(t) == w && __snake->getYtailCoord(t) == h)
						{
							bFind = !bFind;
							SetConsoleTextAttribute(__hConsole, 0xc);
							std::wcout << L'+';
							SetConsoleTextAttribute(__hConsole, 0xb);
							break;
						}
					}
					if (!bFind)
						std::wcout << L" ";
	
				}
			}
			std::wcout << L'|';
			std::wcout << std::endl;
		}

		str.clear();
		for (uint16_t i = 0; i < __width; ++i)
			str.append(symbol2);
		std::wcout << L" " + str << std::endl;
		std::wcout << L"Score: " << __score->GetScore() << std::endl;
		
	}



	void WorldLogic()
	{
		__snake->SnackeLogic();
	}

	
	void threaded_logic()
	{
		while (true)
		{
			__snake->threaded_logic();

			if (__fruit->getXcoord() == __snake->getXcoord() &&
				__fruit->getYcoord() == __snake->getYcoord())
			{
				__snake->addTail();
				__fruit->FruitLogic();
				__score->addPoint();
			}

		}

	}


	~world()
	{
		delete __score;
		delete __snake;
		delete __fruit;
		CloseHandle(__hConsole);
	}

};

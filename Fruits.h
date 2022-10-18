#pragma once

#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>

class fruits
{
private:
	uint16_t const __width;
	uint16_t const __height;
	uint16_t       __x;
	uint16_t       __y;
	wchar_t        __ch;

	void newSpawn()
	{
		srand(time(NULL));
		__x = std::rand() % __width;
		__y = std::rand() % __height;
	}


public:
	fruits(uint16_t const& xr, uint16_t const& yr) :
		__width(xr), __height(yr)
	{
		srand(time(NULL));
		__x = std::rand() % __width;
		__y = std::rand() % __height;
		__ch = L'*';
	}

	void printFruit()
	{
		std::wcout << __ch;
	}

	uint16_t const getXcoord() const
	{
		return __x;
	}

	uint16_t const getYcoord() const
	{
		return __y;
	}

	void FruitLogic()
	{
		newSpawn();
	}

		
};
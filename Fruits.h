#pragma once

#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>

class fruits
{
private:
	uint16_t const _width;
	uint16_t const _height;
	uint16_t       _x;
	uint16_t       _y;
	wchar_t        _ch;
	COORD          _coord;


	auto newSpawn() -> void
	{
		while (((_x = std::rand() % (_width - 1)) <= 0) || ((_y = std::rand() % (_height - 1)) <= 0));
	}

public:
	fruits(uint16_t const& xr, uint16_t const& yr) :
		_width(xr), _height(yr)
	{
		while (((_x = std::rand() % (_width - 1)) <= 0) || ((_y = std::rand() % (_height - 1)) <= 0));

		_coord.X = _x;
		_coord.Y = _y;
	}

	auto get_console_coord() -> COORD&
	{
		return _coord;
	}

	auto getXcoord() const -> uint16_t const
	{
		return _x;
	}

	auto getYcoord() const -> uint16_t const
	{
		return _y;
	}

	auto FruitLogic() -> void
	{
		newSpawn();
	}

		
};
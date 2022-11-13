#pragma once
#include <stdio.h>
#include <stdint.h>
#include <iostream>

class score
{
private:
	uint16_t _points;
public:
	score() : _points(0) {}

	auto addPoint() -> void
	{
		++_points;

	}

	auto GetScore() const -> uint16_t const&
	{
		return _points;
	}

};
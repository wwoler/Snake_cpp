#pragma once
#include <stdio.h>
#include <stdint.h>
#include <iostream>

class score
{
private:
	uint16_t __points;
public:
	score() = default;

	void addPoint()
	{
		++__points;
	}

	uint16_t const& GetScore() const
	{
		return __points;
	}

};
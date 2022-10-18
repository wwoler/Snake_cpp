#pragma once

#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <conio.h>

#define UP    72
#define DOWN  80
#define RIGHT 77
#define LEFT  75

class snacke
{
private:
	
	uint16_t  __tailX[100];
	uint16_t  __tailY[100];
	uint16_t  __nTail = 0;


	uint16_t  __x;
	uint16_t  __y;
	uint16_t  __width;
	uint16_t  __height;
	wchar_t   __ch;

	bool      __up;
	bool      __down;
	bool      __right;
	bool      __left;
	bool      __stop;
	bool*     __prev_move;

	uint16_t  __speed = 1;

	void move_up()
	{
		__y -= __speed;
	}

	void move_down()
	{
		__y += __speed;
	}

	void move_left()
	{
		__x -= __speed;
	}

	void move_right()
	{
		__x += __speed;
	}

public:
	snacke(uint16_t x_, uint16_t y_)
	{
		__width     = x_;
		__height    = y_;
		__x         = x_ / 2 - 1;
		__y         = y_ / 2 - 1;
		__ch        = L'@';

		__up        = false;
		__down      = false;
		__right     = false;
		__left      = false;
		__stop      = true;
		__prev_move = &__stop;	
	}

	void printSnacke() const
	{ 
		std::wcout << __ch;
	}

	void addTail()
	{
		++__nTail;
	}

	uint16_t getNtail() const
	{
		return __nTail;
	}

	uint16_t const getXcoord() const
	{
		return __x;
	}

	uint16_t const getYcoord() const
	{
		return __y;
	}

	uint16_t const getXtailCoord(uint16_t const& i) const
	{
		return __tailX[i];
	}

	uint16_t const getYtailCoord(uint16_t const& i) const
	{
		return __tailY[i];
	}


	void SnackeLogic()
	{
		int16_t nTailX1, nTailY1, nTailX2, nTailY2;

		
		
		nTailX1 = __tailX[0];
		nTailY1 = __tailY[0];
		__tailX[0] = __x;
		__tailY[0] = __y;
		

		
		for (uint16_t i = 1; i < __nTail; ++i)
		{
			nTailX2 = __tailX[i];
			nTailY2 = __tailY[i];
			__tailX[i] = nTailX1;
			__tailY[i] = nTailY1;
			nTailX1 = nTailX2;
			nTailY1 = nTailY2;

		}


		if (__up)
			move_up();
		else if (__down)
			move_down();
		else if (__left)
			move_left();
		else if (__right)
			move_right();

		for (uint16_t i = 0; i < __nTail; ++i)
		{
			if (__x == __tailX[i] && __y == __tailY[i])
				exit(1);
		}


	}


	void threaded_logic()
	{

		if (__x >= __width)
			__x = 0;
		else if (__x <= 0)
			__x = __width;
		if (__y <= 0)
			__y = __height;
		else if (__y >= __height)
			__y = 0;


		if (_kbhit())
		{
			switch (_getch())
			{
			case UP:
				if (__prev_move == &__down)
					break;
				__ch = L'\u02C4';
				*__prev_move = false;
				__up = true;
				__prev_move = &__up;
				break;

			case DOWN:
				if (__prev_move == &__up)
					break;
				__ch = L'\u02C5';
				*__prev_move = false;
				__down = true;
				__prev_move = &__down;
				break;

			case LEFT:
				if (__prev_move == &__right)
					break;
				__ch = L'\u003C';
				*__prev_move = false;
				__left = true;
				__prev_move = &__left;
				break;

			case RIGHT:
				if (__prev_move == &__left)
					break;
				__ch = L'\u02C3';
				*__prev_move = false;
				__right = true;
				__prev_move = &__right;
				break;

			default:
				break;
			}
		}


	}


};

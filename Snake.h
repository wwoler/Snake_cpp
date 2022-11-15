#pragma once

#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <vector>

#define UP    72
#define DOWN  80
#define RIGHT 77
#define LEFT  75


class snacke
{
private:

	uint16_t  _tailX[100];
	uint16_t  _tailY[100];
	uint16_t  _nTail;
	uint16_t  _OtailX;
	uint16_t  _OtailY;

	COORD     _coord;

	uint16_t  _x;
	uint16_t  _y;
	uint16_t  _width;
	uint16_t  _height;
	wchar_t   _ch;

	bool      _up;
	bool      _down;
	bool      _right;
	bool      _left;
	bool      _stop;
	bool*     _prev_move;

	uint16_t const  _move = 1;

	auto move_up() -> void
	{
		_y -= _move;
	}

	auto move_down() -> void
	{
		_y += _move;
	}

	auto move_left() -> void
	{
		_x -= _move;
	}

	auto move_right() -> void
	{
		_x += _move;
	}

public:

	snacke(uint16_t x_, uint16_t y_)
	{
		_width = x_;
		_height = y_;
		_x = x_ / 2;
		_y = y_ / 2 - 1;
		_ch = L'@';
		_nTail = 0;
		
		_coord.X = _x;
		_coord.Y = _y;

		_up    = false;
		_down  = false;
		_right = false;
		_left  = false;
		_stop  = true;
		_prev_move = &_stop;
	}

	auto get_symbol() -> wchar_t
	{
		return _ch;
	}

	auto addTail() -> void
	{
		++_nTail;
	}

	auto getNtail() const -> uint16_t const
	{
		return _nTail;
	}

	auto getXcoord() const -> uint16_t const
	{
		return _x;
	}

	auto getYcoord() const -> uint16_t const
	{
		return _y;
	}

	auto getOXcoord() const -> uint16_t const
	{
		return _OtailX;
	}

	auto getOYcoord() const -> uint16_t const
	{
		return _OtailY;
	}

	auto getXtailCoord(uint16_t const& i) const -> uint16_t const
	{
		return _tailX[i];
	}

	auto getYtailCoord(uint16_t const& i) const -> uint16_t const
	{
		return _tailY[i];
	}


	auto SnakeLogic() -> void
	{

		int16_t nTailX1, nTailY1, nTailX2, nTailY2;

		
		_OtailX = _tailX[_nTail - 1];
		_OtailY = _tailY[_nTail - 1];

		nTailX1 = _tailX[0];
		nTailY1 = _tailY[0];
		_tailX[0] = _x;
		_tailY[0] = _y;

		for (uint16_t i = 1; i < _nTail; ++i)
		{
			nTailX2 = _tailX[i];
			nTailY2 = _tailY[i];
			_tailX[i] = nTailX1;
			_tailY[i] = nTailY1;
			nTailX1 = nTailX2;
			nTailY1 = nTailY2;

		}


		if (_up)
			move_up();
		else if (_down)
			move_down();
		else if (_left)
			move_left();
		else if (_right)
			move_right();

	}

	auto get_console_coord() -> COORD&
	{
		return _coord;
	}

	auto threaded_logic()    -> void
	{

		if (_x >= _width - 1)
			_x = 1;
		else if (_x < 1)
			_x = _width - 2;

		if (_y >= _height - 1)
			_y = 1;
		else if (_y < 1)
			_y = _height - 2;


		if (_kbhit())
		{
			switch (_getch())
			{
			case UP:
				if (_prev_move == &_down)
					break;
				*_prev_move = false;
				_up = true;
				_prev_move = &_up;
				break;

			case DOWN:
				if (_prev_move == &_up)
					break;
				*_prev_move = false;
				_down = true;
				_prev_move = &_down;
				break;

			case LEFT:
				if (_prev_move == &_right)
					break;
				*_prev_move = false;
				_left = true;
				_prev_move = &_left;
				break;

			case RIGHT:
				if (_prev_move == &_left)
					break;
				*_prev_move = false;
				_right = true;
				_prev_move = &_right;
				break;
				

			default:
				break;
			}
		}


	}


};
#include "Game.h"

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	game* game_ = new game();
	game_->run();

	delete game_;
	
	return 0;
}
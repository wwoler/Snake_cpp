#include "Game.h"

auto main() -> int
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	srand(time(NULL));
	game* game_ = new game();
	try
	{
		game_->run();
	}
	catch (...)
	{

	}

	delete game_;

	return EXIT_SUCCESS;
}


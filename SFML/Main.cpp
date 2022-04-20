#include "stdafx.h"

#include <iostream>

#include "Game.h"

int main() 
{
	try
	{
		Game game("Template");
		game.Run();
	}
	catch (const std::exception& ex)
	{
		std::cout << "What occurred: " << ex.what();
	}
	return 0;
}

#include "stdafx.h"

#include <iostream>

#include "Application.h"

int main() 
{
	try
	{
		Application App("Template");
		App.Run();		
	}
	catch (const std::exception& ex)
	{
		std::cout << "What occurred: " << ex.what();
	}
	return 0;
}

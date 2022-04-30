#include "Engine.h"
#include <ctime>

int main()
{
	srand(time(NULL));

	Engine e;

	e.CreateWindow();
		
	return 0;
}
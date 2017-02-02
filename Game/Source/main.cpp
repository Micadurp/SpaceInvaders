#include "System.hpp"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Piece of shit SFML will show some memory leaks that don't exist
	System system;

	if (system.Initialize())
	{
		system.Run();
	}	

	system.Shutdown();

	return 0;
}
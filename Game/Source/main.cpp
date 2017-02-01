#include "System.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	System system = System();

	if (system.Initialize())
	{
		system.Run();
	}	

	return 0;
}
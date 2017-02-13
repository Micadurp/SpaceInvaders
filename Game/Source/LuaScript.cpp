#include <LuaScript.hpp>

LuaScript::LuaScript() : L(nullptr), validState(false) {}

LuaScript::~LuaScript() 
{
	LuaScript::Unload();
}

void LuaScript::Load(Game * game)
{
	L = luaL_newstate();
	luaL_openlibs(L);
	LuaGame::registerFunctions(L, game);

	if (luaL_dofile(L, "Scripts/main.lua"))
		std::cout << lua_tostring(L, -1) << std::endl;
	else
	{
		lua_getglobal(L, "Load");
		if (lua_isfunction(L, -1))
		{
			if (lua_pcall(L, 0, 0, 0))
				std::cout << lua_tostring(L, -1) << std::endl;
			else
			{
				// Get update function and store it as a reference.
				// This provides a faster lookup than calling lua_getglobal every frame.
				lua_getglobal(L, "Update");
				if (lua_isfunction(L, -1))
				{
					updateReference = luaL_ref(L, LUA_REGISTRYINDEX);
					validState = true;
				}
			}
		}
	}
}

void LuaScript::Unload()
{
	if (validState)
	{
		lua_getglobal(L, "Unload");
		if (lua_isfunction(L, -1))
		{
			if (lua_pcall(L, 0, 0, 0))
				std::cout << lua_tostring(L, -1) << std::endl;
		}
	}

	if (L)
	{
		lua_close(L);
		L = nullptr;
	}

	validState = false;
}

void LuaScript::Update(float deltaTime)
{
	if (validState)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, updateReference);
		lua_pushnumber(L, deltaTime);
		if (lua_pcall(L, 1, 0, 0))
		{
			std::cout << lua_tostring(L, -1) << std::endl;
			validState = false;
		}
	}
}


void LuaScript::LoadData(const std::string& filename)
{
	L = luaL_newstate();
	if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0))
	{
		std::cout << "Error: script not loaded (" << filename << ")" << std::endl;
		L = 0;
	}
}

void LuaScript::PrintError(const std::string& variableName, const std::string& reason) 
{
	std::cout << "Error: can't get [" << variableName << "]. " << reason << std::endl;
}

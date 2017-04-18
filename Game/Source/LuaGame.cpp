#include "LuaGame.hpp"

namespace LuaGame
{
	static Game* g_game = nullptr;

	void registerFunctions(lua_State * lua, Game * game)
	{
		g_game = game;
		luaL_newmetatable(lua, "gameMeta");
		luaL_Reg regs[] =
		{
			{ "PlaceWall", PlaceWall },
			{ "CreatePlayer", CreatePlayer },
			{ "CreateEnemy", CreateEnemy },
			{ "InputCheck", InputCheck },
			{ "GetTotalEnemies", GetTotalEnemies },
			{ "GetTotalWalls", GetTotalWalls },
			{ "GetTotalBullets", GetTotalBullets },
			{ NULL, NULL }
		};

		luaL_setfuncs(lua, regs, 0);
		lua_pushvalue(lua, -1);
		lua_setfield(lua, -2, "__index");

		lua_setglobal(lua, "Game");
	}

	int PlaceWall(lua_State* lua)
	{
		int posX = lua_tointeger(lua, -2);
		int posY = lua_tointeger(lua, -1);
		g_game->PlaceWall(posX, posY);
		return 0;
	}

	int CreatePlayer(lua_State* lua)
	{
		int posX = lua_tointeger(lua, -2);
		int posY = lua_tointeger(lua, -1);
		g_game->CreatePlayer(posX, posY);
		return 0;
	}

	int CreateEnemy(lua_State* lua)
	{
		int posX = lua_tointeger(lua, -2);
		int posY = lua_tointeger(lua, -1);
		g_game->CreateEnemy(posX, posY);
		return 0;
	}

	int InputCheck(lua_State* lua)
	{
		float dt = lua_tonumber(lua, -1);
		g_game->InputCheck(dt);
		return 0;
	}

	int GetTotalEnemies(lua_State* lua)
	{
		lua_pushnumber(lua, g_game->GetTotalEnemies());
		return 1;
	}

	int GetTotalWalls(lua_State* lua)
	{
		lua_pushnumber(lua, g_game->GetTotalWalls());
		return 1;
	}

	int GetTotalBullets(lua_State* lua)
	{
		lua_pushnumber(lua, g_game->GetTotalBullets());
		return 1;
	}

}

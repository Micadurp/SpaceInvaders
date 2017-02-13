#ifndef LUAGAME_HPP
#define LUAGAME_HPP

#include "lua.hpp"
#include "Game.hpp"

namespace LuaGame
{
	void registerFunctions(lua_State* lua, Game* game);
	int PlaceWall(lua_State* lua);
	int CreatePlayer(lua_State* lua);
	int CreateEnemy(lua_State* lua);
	int InputCheck(lua_State* lua);
}

#endif

#ifndef LUASCRIPT_HPP
#define LUASCRIPT_HPP

#include "lua.hpp"

#include <string>
#include <vector>
#include <iostream>
#include "LuaGame.hpp"
#include "Game.hpp"


class LuaScript 
{
public:
	LuaScript();
	virtual ~LuaScript();

	void Load(Game * game);
	void Unload();
	void Update(float deltaTime);

	void LoadData(const std::string& filename);

	template<typename T>
	T GetVariable(const std::string& variableName) 
	{
		if (!L) 
		{
			PrintError(variableName, "Script is not loaded");
			return lua_getdefault<T>();
		}

		T result;
		if (lua_gettostack(variableName)) 
		{ // variable succesfully on top of stack
			result = lua_get<T>(variableName);
		}
		else 
		{
			result = lua_getdefault<T>();
		}

		lua_pop(L, level + 1); // pop all existing elements from stack
		return result;
	}
private:

	void PrintError(const std::string& variableName, const std::string& reason);

	bool lua_gettostack(const std::string& variableName) 
	{
		level = 0;
		std::string var = "";
		for (unsigned int i = 0; i < variableName.size(); i++) {
			if (variableName.at(i) == '.') {
				if (level == 0) {
					lua_getglobal(L, var.c_str());
				}
				else {
					lua_getfield(L, -1, var.c_str());
				}

				if (lua_isnil(L, -1)) {
					PrintError(variableName, var + " is not defined");
					return false;
				}
				else {
					var = "";
					level++;
				}
			}
			else {
				var += variableName.at(i);
			}
		}
		if (level == 0) {
			lua_getglobal(L, var.c_str());
		}
		else {
			lua_getfield(L, -1, var.c_str());
		}
		if (lua_isnil(L, -1)) {
			PrintError(variableName, var + " is not defined");
			return false;
		}

		return true;
	}

	// Generic get
	template<typename T>
	T lua_get(const std::string& variableName) 
	{
		return 0;
	}

	// Generic default get
	template<typename T>
	T lua_getdefault() 
	{
		return 0;
	}


	lua_State* L;
	int level;
	bool validState;
	int updateReference;
};

template <>
inline bool LuaScript::lua_get<bool>(const std::string& variableName)
{
	return (bool)lua_toboolean(L, -1);
}

template <>
inline float LuaScript::lua_get<float>(const std::string& variableName) 
{
	if (!lua_isnumber(L, -1))
	{
		PrintError(variableName, "Not a number");
	}
	return (float)lua_tonumber(L, -1);
}

template <>
inline int LuaScript::lua_get<int>(const std::string& variableName) 
{
	if (!lua_isnumber(L, -1)) 
	{
		PrintError(variableName, "Not a number");
	}
	return (int)lua_tonumber(L, -1);
}

template <>
inline std::string LuaScript::lua_get<std::string>(const std::string& variableName) 
{
	std::string s = "null";
	if (lua_isstring(L, -1)) 
	{
		s = std::string(lua_tostring(L, -1));
	}
	else 
	{
		PrintError(variableName, "Not a string");
	}
	return s;
}

template<>
inline std::string LuaScript::lua_getdefault() 
{
	return "null";
}

#endif
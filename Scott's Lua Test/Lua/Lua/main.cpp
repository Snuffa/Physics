#include <iostream>

using namespace std;

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

// global
double g_iNumber = 0;

typedef int (*lua_CFunction) (lua_State *L);
int my_function(lua_State *L);



int main()
{

	cout << "Enter a number to obtain it's factors: ";
	cin >> g_iNumber;

	// create lua interpreter
	lua_State* luaInt;

	// Open interpreter
	luaInt = lua_open();

	// open lua standard libraires
	luaL_openlibs(luaInt);


	my_function(luaInt);

	// register the function so lua can access the function from its global name
	lua_register(luaInt, "my_function", my_function);

	// load a given file
	luaL_dofile(luaInt, "basic.lua");

	// close the interpreter
	lua_close(luaInt);
	
	// keep window open
	int i = 0;
	cin >> i;

	return (0);
}

int my_function(lua_State *L)
{
	// return value
	lua_pushnumber(L, g_iNumber);

	return(1);
}
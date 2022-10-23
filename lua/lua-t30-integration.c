#include <lauxlib.h>
#include <lualib.h>

// gcc -I to/lua/include -O2 t30-integration.c -L to/lua/lib/ -llua -lm -ldl

int main() {
  lua_State *L = luaL_newstate();
  luaopen_base(L);
  //luaL_openlibs(L);  // open all core libs
  luaL_dostring(L, "print(\"lua: 1+2=\", 1+2)");
  lua_close(L);
}

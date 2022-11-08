
#include <lua.hpp>

#include <string>

class LuaMachine {
    lua_State *lua_st;
public:
    LuaMachine() {
        lua_st = luaL_newstate();
        luaopen_base(lua_st);
    }
    ~LuaMachine() {
        lua_close(lua_st);
    }
    lua_State *get() { return lua_st; }

    int doString(const std::string &str) {
        return luaL_dostring(lua_st, str.c_str());
    }
    int doFile(const std::string &filename) {
        return luaL_dofile(lua_st, filename.c_str());
    }
};

// ============ Test: Call C Function =================
int cfun_no_arg(lua_State*) {
    printf("in %s\n", __func__);
    return 0;
}
void test_call_cfun_no_arg(LuaMachine &lm) {
    printf("===> %s:\n", __func__);
    lua_register(lm.get(), "cfun_no_arg", cfun_no_arg);
    lm.doString("cfun_no_arg()");
}

// ============ Test: with int, double, string argument ==========
int cfun_int_double_string(lua_State *L) {
    // see luaconf.h
    lua_Integer arg1 = lua_tointegerx(L, 1, nullptr); // default type long long
    lua_Number  arg2 = lua_tonumberx(L, 2, nullptr);  // default type double
    const char *arg3 = lua_tolstring(L, 3, nullptr);  // do strdup if need to keep the string
    int narg = lua_gettop(L);
    printf("%d args: %lld, %f, %s\n", narg, arg1, arg2, arg3);
    return 0;
}
void test_call_cfun_int_double_string(LuaMachine &lm) {
    printf("===> %s:\n", __func__);
    lua_register(lm.get(), "cfun_int_double_string", cfun_int_double_string);
    lm.doString("cfun_int_double_string(123, 1.23, \"string arg\")");
}

#define LUA_REG_FUN(L, F) lua_register(L, #F, F)

// =========== Test: with return int ==============
int cfun_power_int(lua_State *L) {
    lua_Integer x = lua_tointeger(L, 1);
    lua_Integer p = lua_tointeger(L, 2);
    lua_Integer res = 1;
    for (int i = 0; i < p; i++) {
        res *= x;
    }
    lua_pushinteger(L, res);
    return 1;  // number of result
}
void test_call_cfun_power_int(LuaMachine &lm) {
    printf("===> %s:\n", __func__);
    LUA_REG_FUN(lm.get(), cfun_power_int);
    lm.doString("print(\"power(2,3)=\" .. cfun_power_int(2, 3))");
}

// =========== Test: with table/array argument ==========
int cfun_arg_table(lua_State *L) {
    int arg_tp = lua_type(L, 1);
    if (arg_tp == LUA_TTABLE) {
        //const void *tab = lua_topointer(L, 1);
        lua_pushnil(L);
        while (lua_next(L, 1)) {
            printf("key-type: %s, value-type: %s\n",
                    lua_typename(L, lua_type(L, -2)),
                    lua_typename(L, lua_type(L, -1)));
            lua_pop(L, 1);
        }
    }
    return 0;
}
void test_call_cfun_arg_table(LuaMachine &lm) {
    printf("===> %s:\n", __func__);
    LUA_REG_FUN(lm.get(), cfun_arg_table);
    lm.doString("cfun_arg_table({ a = 1, b = \"22\", 33 })"); 
}



int main(int argc, const char *argv[]) {
  LuaMachine lm;
  lm.doString("print(\"hello lua\")");
  if (argc > 1) {
      printf("load&execute lua file %s\n", argv[1]);
      lm.doFile(argv[1]);
  }
  test_call_cfun_no_arg(lm);
  test_call_cfun_int_double_string(lm);
  test_call_cfun_power_int(lm);
  test_call_cfun_arg_table(lm);
}


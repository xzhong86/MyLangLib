
CXX = g++

LUA_INC = $(HOME)/opt/lua-5.3.5/include
LUA_LIB = $(HOME)/opt/lua-5.3.5/lib

CXXFLAGS = -I$(LUA_INC) -L$(LUA_LIB)
LDFLAGS  = -llua -lm

test-lua : main.cpp
	$(CXX) $(CXXFLAGS) -O2 -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm test-lua


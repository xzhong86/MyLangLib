#!/usr/bin/env lua
-- t10-class-hello.lua

Obj = { name = "noname" }
function Obj.say(word)
    print(Obj.name.." say: "..word)
end

Obj.say("hello")

obj = Obj
obj.name = "myname"
obj.say("hello")
Obj.say("hello")

obj.say2 = function(world)
  print("say2 "..world)
end

obj.say3 = function(self, world)
  print(self.name.." say3 "..world)
end

obj.say2("hello")
obj.say3(obj, "hello")  -- works

for key, value in pairs(obj) do
  print(key, value)
end

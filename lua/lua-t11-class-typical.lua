#!/usr/bin/env lua

Test = { name = "noname" }

function Test:new (name)
  o = {}
  setmetatable(o, self)
  self.__index = self
  --o.__index = self  -- wrong
  --self.name = name  -- wrong
  o.name = name or Test.name  -- right, change instance
  print("Test:new self:"..type(self)..", o:"..type(o))
  --print("Test:new self:"..self..", o:"..o)
  print(self)
  print(o)
  return o
end

function Test:say (world)
  print(self.name.." say "..world)
end

t = Test:new("aaa")
t:say("hello")      -- aaa say hello
--t.say("hello")      -- wrong
t.say(t, "hello")     -- aaa say hello
t.say(Test, "hello")  -- noname say hello
Test:say("hello")   -- noname say hello

print(type(Test))
print(type(t))
print(type(getmetatable(Test)))
print(type(getmetatable(t)))

print(Test)
print(getmetatable(t))

t.ccc = function(self, v) print("name:"..self.name..", v="..v) end
t:ccc(12)

function pr_table(table)
  for k, v in pairs(table) do
    print(k, v)
  end
end

print(">> pr_table(t)")
pr_table(t)
print(">> pr_table(getmetatable(t))")
pr_table(getmetatable(t))


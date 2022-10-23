#!/usr/bin/env lua
-- t11-class-typical.lua

Test = { name = "noname" }

function Test:new (name)
  o = {}
  setmetatable(o, self)
  self.__index = self
  --o.__index = self  -- wrong
  --self.name = name  -- wrong
  o.name = name or Test.name  -- right, change instance
  return o
end

function Test:say (world)
  print(self.name.." say "..world)
end

t = Test:new("aaa")
t:say("hello")
t.say(t, "hello")
Test:say("hello")

print(type(Test))
print(type(t))
print(type(getmetatable(Test)))
print(type(getmetatable(t)))

function pr_table(table)
  for k, v in pairs(table) do
    print(k, v)
  end
end

pr_table(getmetatable(t))


Module = { }

Module.param_type = "ModuleParameter"
Module.param = function(def, ct, c)
  local p = { default = def, ctype = ct, comment = c }
  p._type = Module.param_type
  return p
end
Module.is_param = function(p)
  return type(p) == "table" and p._type == Module.param_type
end


Module.deepcopy = function(from)
  local to = {}
  for k, v in pairs(from) do
    local vt = type(v)
    if vt == "number" or vt == "string" then
      to[k] = v
    elseif vt == "table" then
      to[k] = Module.deepcopy(v)
    end
  end
  return to
end

Module.instantiate = function(mod)
  local ins = { }
  for k, v in pairs(mod) do
    if type(v) == "number" or type(v) == "string" then
      ins[k] = v
    elseif type(v) == "table" then
      if v.instance then
        local mod = v.instance
        if type(mod) == "string" then
          mod = _ENV[mod]
        end
        ins[k] = Module.instantiate(mod)
      else 
        ins[k] = Module.deepcopy(v)
      end
    end
  end
  return ins
end

Module.instance_of = function(mod)
  return { instance = mod }
end

Module.declare = function(mod)
  mod.new = Module.instantiate
  mod._type = "ModuleDecl"
end

ModuleA = {
  debug   = true,
  width   = 12,
  logfile = "test.log",
  height  = Module.param(123, "uint16", "height?")
}

Module.declare(ModuleA)

ModuleB = {
  --ma = "@ModuleA"
  height  = 120,
  width   = Module.param(8, "uint8", "some width"),
  ma      = Module.instance_of(ModuleA),
}

Module.declare(ModuleB)

b = ModuleB:new()

Module.dump = function(tab, depth)
  for k, v in pairs(tab) do
    io.write(string.rep("  ", depth))
    if type(v) == "number" or type(v) == "string" then
      print(tostring(k).." : "..tostring(v))
    elseif type(v) == "table" then
      print(k .. " : {" )
      Module.dump(v, depth+1)
      print(string.rep("  ", depth) .. "}")
    else
      --skip
    end
  end
end

Module.dump({ module = b }, 0)


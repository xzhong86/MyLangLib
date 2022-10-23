#!/usr/bin/env lua

function is_prime(val)
    i = 2
    while i * i < val do
        if val % i == 0 then
            return false
        end
        i = i + 1
    end
    return true
end


n = 0
sum = 0
for i = 1000, 10000 do
    if is_prime(i) then
        sum = sum + 1
    else
        n = n + 1
    end
end

print(sum, n)

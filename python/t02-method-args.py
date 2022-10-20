#!/usr/bin/env python3

def fun_args_list(aa, *args, dd):
    print(aa, args, dd)

fun_args_list(1,2,3,4,dd=5)  # keyword arg must be at last, print 1 (2 3 4) 5

def fun2(aa, bb=1, cc=2):
    print(aa, bb, cc)

fun2(1, 2, 3)  # => 1 2 3
fun2(1, cc=2, bb=3)  # => 1 3 2
fun2(1, 2, bb=3) # error, multi values for bb
fun2(1, cc=2, 3) # error, position arg follows keyword arg

def func3(aa, **kwargs):
    print(aa, kwargs)

func3(1, b=2, c=3) # => 1 {'b': 2, 'c': 3}
func3(1, 2, 3) # error, take 1 position arg, but give 3

def func4(aa, *args, **kwargs):
    print(aa, args, kwargs)

func4(1,2,3,a=5,b=6)  # => 1 (2, 3) {'a': 5, 'b': 6}


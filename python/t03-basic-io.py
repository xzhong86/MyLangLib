#!/usr/bin/env python3

import os
import glob

def basic_print():
    a, b = 1, 2
    print(a, b)
    # print with named argument, see help(print)
    print(a, b, sep=',,', end=" ^^end\n", file=sys.stderr)

    print("%3d : %-4d" % (a, b))  # format like c-style printf

    print("{}, {}".format(a,b))  # str.format()
    print("{1}, {0}".format(a,b))  # str.format()
    print("{x}, {y}".format(x=a,y=b))  # named place
    print("{x:3d}, {y:.2f}".format(x=a,y=b)) # with formatting

def filesystem_access():
    os.listdir('.')
    os.getcwd() # cwd, 
    # more methods see doc: https://docs.python.org/3/library/os.html

    import datetime
    atime = os.stat('tmp').st_atime
    dt_atime = datetime.datetime.fromtimestamp(atime)
    dt_atime.isoformat() # return time string in ISO format
    dt_atime.ctime()     # e, human readable time string, like 'Thu Oct 20 01:14:24 2022'
    dt_atime.strftime("%y %m %d") # custom format

    os.path.isfile('.')  # false
    os.path.isdir('.')   # true. other: isabs islink ismount

    for path, dirs, files in os.walk('geek/prog/lang-lib'):
        # path: path of current dir visiting
        # dirs: list of directories in current dir
        # files: list of files in current dir
        print(path, dirs, files)

    print(glob.glob("*.sh"))  # glob, need to import glob

def read_regular_file():
    fh = open('test.txt', 'r', encoding='utf-8') # or open('text.txt')
    # return type is IOBase, or say TextIOBase
    # doc: https://docs.python.org/3/library/io.html


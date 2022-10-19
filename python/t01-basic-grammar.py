#!/usr/bin/env python3

def internal_types():
    arr = [ 0, 1, 'aa', "bb" ]  # list
    print(type(arr), arr)
    for v in arr:
        print(v)
    
    atm = (arr, hsh)   # tuple
    print(type(atm), atm)


    # python dict

    hsh = { 'aa' : 1, 'bb' : 'cc' }  # dict
    print(type(hsh), hsh)
 
    if 'vv' in hsh:  # check contains key
        print("hash has 'vv'")

    print(hsh.keys(), hsh.values(), hsh.items())

    print(len(hsh), str(hsh))

    del hsh['aa'] # delete key, del is keyword
    del hsh  # delete var, hsh is undefined now.




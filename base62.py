# -*- coding: utf-8 -*-
import os
import sys
import math

digits='0123456789'+\
       'abcdefghijklmnopqrstuvwxyz'+\
       'ABCDEFGHIJKLMNOPARSTUVWXYZ'

def encode(num):
    if num==0:
        return '0'
    s=''
    while num>0:
        rem = num % 62
        s = digits[rem] + s
        num = num / 62
    return s

def decode(s):
    if num=='0':
        return 0
    p=0
    dec=0
    for c in s[-1::-1]:
        dec += digits.find(c) * int(math.pow(62, p))
        p += 1
    return dec

if __name__=="__main__":
    if len(sys.argv)==1:
        print "use: %s" % os.path.basename(sys.argv[0])
        raise SystemExit

    num = int(sys.argv[1])
    enc = encode(num)
    print enc
    dec = decode(enc)
    print dec


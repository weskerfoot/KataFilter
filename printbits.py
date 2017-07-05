#! /usr/bin/env python2

def printbits(n):
    if n < 2:
        return str(n & 1)
    rest = n >> 1
    d = n & 1
    return printbits(rest) + str(d)

def modifybit(n):
    return 1 << n

test = 0b10010101111

print bin(test)
print bin(test | modifybit(3))

# bin((1 << 6) - 2)

#print bin(1292002343)
#print printbits(1292002343)

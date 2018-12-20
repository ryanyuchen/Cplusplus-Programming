import math

class Complex(object):
    def __init__(self, real, imag):
        self.r = real
        self.i = imag

    def Print(self):
        print("{}+{}i".format(self.r, self.i))

    def __add__(self, other):
        return Complex(self.r+other.r, self.i-other.i)

    def __sub__(self, other):
        return Complex(self.r-other.r, self.i-other.i)


a = Complex(3, 4)
a.Print()
b = Complex(5, 6)
b.Print()
c = a + b
c.Print()
d = a - b
d.Print()

## shallow copy

la = ['red', 'black']
lb = la
lb[1] = 'blue'
print lb
print la

## deep copy
from copy import deepcopy
la = ['red', 'black']
lb = deepcopy(la)
lb[1] = 'blue'
print lb
print la

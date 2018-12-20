class A(object):
    def __init__(self, n = 0):
        self.val = n

a = A()
print a.val
a = A(5)
print a.val

class Sample(object):
    def __init__(self, n):
        self.v = n
    def copy(self):
        return type(self)(self.v * 2)

aa = Sample(5)
print aa.v
bb = aa.copy()
print bb.v

class Base(object):
    def __init__(self, n):
        self.k = n

class Big(object):
    def __init__(self, n):
        self.v = n
        self.b = Base(n)

a1 = Big(5)
print("{} , {}".format(a1.v, a1.b.k))
a2 = a1
print("{} , {}".format(a2.v, a2.b.k))
        

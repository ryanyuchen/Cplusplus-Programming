class Student:
    def __init__(self, nm, ag, xh, year1, year2, year3, year4):
        self.name = nm
        self.age = ag
        self.id = xh
        self.sc1 = year1
        self.sc2 = year2
        self.sc3 = year3
        self.sc4 = year4

    def printname(self):
        return self.name

    def printage(self):
        return self.age

    def printid(self):
        return self.id

    def printavgsc(self):
        return (self.sc1 + self.sc2 + self.sc3 + self.sc4) /4


stdnm, stdage, stdid, scy1, scy2, scy3, scy4 = raw_input('Enter Student Information').split(',')
newstd = Student(stdnm, int(stdage), stdid, int(scy1), int(scy2), int(scy3), int(scy4))
print('{}, {}, {}, {}'.format(newstd.printname(), newstd.printage(), newstd.printid(), newstd.printavgsc()))

    

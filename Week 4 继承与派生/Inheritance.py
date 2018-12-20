class Person:
    def __init__(self, first, last):
        self.firstname = first
        self.lastname = last

    def getName(self):
        return self.firstname + " " + self.lastname

    def __str__(self):
        return self.firstname + " " + self.lastname

class Employee(Person):
    def __init__(self, first, last, staffnum):
        Person.__init__(self, first, last)
        self.staffnumber = staffnum

    def getEmployee(self):
        return self.getName() + ", " + self.staffnumber

    def __str__(self):
        return Person.__str__(self) + ", " + self.staffnumber


x = Person("Marge", "Simpson")
y = Employee("Homer", "Simpson", "1007")

print(x.getName)
print(y.getEmployee)

print(x)
print(y)



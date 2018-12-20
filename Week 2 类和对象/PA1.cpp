#include <iostream>
using namespace std;

class A {
public:
    int val;
	A(int n = 0){
		val = n;}

	A& GetObj(){
		return *this;
	}
};

class Sample{
public:
    int v;
    Sample(int n):v(n) { }
	Sample(const Sample& s)
	{
		v = 2 * s.v;
	}
};

class Base {
public:
    int k;
    Base(int n):k(n) { }
};
class Big {
public:
    int v; Base b;
	Big(int x):v(x),b(x){}
	Big(const Big& z):v(z.v),b(z.b){}
};

void main() {
    A a;
    cout << a.val << endl;
    a.GetObj() = 5;
    cout << a.val << endl;

	Sample aa(5);
    Sample bb = aa;
    cout << bb.v << endl;

    Big a1(5); Big a2 = a1;
    cout << a1.v << "," << a1.b.k << endl;
    cout << a2.v << "," << a2.b.k << endl;

	system("pause");
}
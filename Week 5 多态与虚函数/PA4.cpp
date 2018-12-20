#include <iostream>
using namespace std;

class A {
    private:
        int nVal;
    public:
        void Fun()
        { cout << "A::Fun" << endl; }
        void Do()
        { cout << "A::Do" << endl; }
};
class B:public A {
    public:
        virtual void Do()
        { cout << "B::Do" << endl; }
};
class C:public B {
    public:
    void Do( )
    { cout << "C::Do" <<endl; }
    void Fun()
    { cout << "C::Fun" << endl; }
};
void Call(B &p) {
    p.Fun(); p.Do();
}
void Call1(A *p) {
    p->Fun(); p->Do();
}

class A1 {
public:
	virtual ~A1() { cout << "destructor A" << endl; }
};
class B1:public A1 {
    public:
        ~B1() { cout << "destructor B" << endl; }
};

int main() {
    C c; Call(c);

    A1 * pa;
    pa = new B1;
    delete pa;

    Call1( new A() );
    Call1( new C() );

	system("pause");
    return 0;
}
#include <iostream>
using namespace std;
class Number {
public:
    int num;
    Number(int n): num(n) {
    }
	Number &operator=(const Number& nn){
		num = nn.num;
		return *this;
	}
	Number &operator+(const Number& nn){
		num += nn.num;
		return *this;
	}
	int& value() {
		return num;
	}

};
int main() {
    Number a(2);
    Number b = a;
    cout << a.value() << endl;
    cout << b.value() << endl;
    a.value() = 8;
    cout << a.value() << endl;
    a+b;
    cout << a.value() << endl;

	system("pause");
    return 0;
}
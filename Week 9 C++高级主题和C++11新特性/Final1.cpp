#include<iostream>
using namespace std;
class Number {
public:
	int num;
	Number(int n=0): num(n) {}
	int operator*(const Number& nn){
		return num*nn.num;
	}
	Number &operator=(const Number& nn){
		num = nn.num;
		return *this;
	}
	operator int(){
		return num;
	}
};
int main() {
	Number n1(10), n2(20);
	Number n3; n3 = n1*n2;
	cout << int(n3) << endl;
	
	system("pause");
	return 0;
}
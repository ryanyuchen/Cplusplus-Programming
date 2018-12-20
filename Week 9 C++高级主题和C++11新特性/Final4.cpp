#include <iostream>
using namespace std;

class CType{
private:
	int num;
public:
	CType():num(0) {};
	void setvalue(const int& nn) {num = nn;}
	CType &operator++(int){
		static CType tmp = CType();
		tmp.num = num;
		num *= num;
		return tmp;
	}
	friend ostream& operator<<(ostream& o, CType& c){
		o<<c.num;
		return o;
	}
};

int main(int argc, char* argv[]) {
        CType obj;
        int n;
        cin>>n;
        while ( n ) {
                obj.setvalue(n);
                cout<<obj++<<" "<<obj<<endl;
                cin>>n;
        }

		system("pause");
        return 0;
}
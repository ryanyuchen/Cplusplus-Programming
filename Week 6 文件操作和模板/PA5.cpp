#include <iostream>
#include <iomanip>
using namespace std;

template <class T> 
class CArray3D {
	template <class T> 
	class CArray2D {
		template <class T> 
		class CArray1D {
		public:
			CArray1D():p1(NULL){}
			void set(T a_)
			{
				a = a_;
				p1 = new T[a];				
			}
			inline T& operator[]( long elem ) const 
			{ 
				return p1[elem]; 
			} 
			~CArray1D()
			{
				if (p1 != NULL) delete[] p1;
			}
		private:
			T* p1;
			T a;
		};
		public:
			CArray2D():p2(NULL){}
			void set(T a_, T b_){
				b = b_;
				p2 = new CArray1D<T>[a_];
				for(int i=0; i<a_; i++){
					p2[i].set(b);
				}
			}
			inline CArray1D<T>& operator[]( long elem ) const 
			{ 
				return p2[elem]; 
			} 
			~CArray2D()
			{
				if (p2 != NULL) delete[] p2;
			}
		private:
			CArray1D<T>* p2;
			T b;
	};
public:
	CArray3D(T a_, T b_, T c_){
		c = c_;
		p3 = new CArray2D<T>[a_]; 
		for(int i=0; i<a_; i++){
			p3[i].set(b_, c);
		}
	}
	inline CArray2D<T>& operator[]( long elem ) const 
	{ 
		return p3[elem]; 
	} 
	~CArray3D()
	{
		if (p3 != NULL) delete[] p3;
	}
private:
	CArray2D<T>* p3;
	T c;
};

int main()
{
    CArray3D<int> a(3,4,5);
    int No = 0;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                cout << a[i][j][k] << ",";
	cout << endl;

    double n;
    cin >> n;
    cout.setf(ios::fixed);
    cout.precision(5);
    cout << n << endl;
    cout.unsetf(ios::fixed);
    cout.setf(ios::scientific);
    cout.precision(7);
    cout << n << endl;

    int n1;
    cin >> n1;
    cout << hex << n1 << endl;
    cout.fill('0');
    cout << dec << setw(10) << n1 << endl;

	system("pause");
	return 0;
}
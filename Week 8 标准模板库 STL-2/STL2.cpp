#include <iostream>
#include <vector>
#include <algorithm>

#include <string>
#include <iterator>

#include <set>

#include <map>
#include <cmath>

using namespace std;
typedef map<int, int> MAP;

struct Point {
	int x;
	int y;
	Point(int x_,int y_):x(x_),y(y_) { }
};
bool operator < ( const Point & p1, const Point & p2)
{
	if( p1.y < p2.y )
		return true;
	else if( p1.y == p2.y )
		return p1.x < p2.x;
	else
		return false;
}

template<class T>
class CMyistream_iterator{
private:
	T a;
	istream &is;
public:
	CMyistream_iterator(istream &i): is(i) { is>>a; };
	void operator ++(int){ is >>a; };
	T &operator*() {return a;};
	T &operator=(const T& val) { is>>val; return *this;}
};

int main()
{
	/*Problem1*/
	int t;
	int x,y;
	cin >> t;
	vector<Point> v;
	while( t -- ) {
		cin >> x >> y;
		v.push_back(Point(x,y));
	}
	vector<Point>::iterator i,j;
	int nTotalNum = 0;
	sort(v.begin(),v.end());
	for(i = v.begin();i < v.end() - 1; i++)
		for(j = i + 1; j < v.end(); j++){
			if(binary_search(v.begin(), v.end(), Point(j->x, i->y)) && binary_search(v.begin(), v.end(), Point(i->x, j->y)) && i->x != j->x && i->y != j->y )
				nTotalNum ++;
		}
	cout << nTotalNum / 2;
	cout << endl;

	CMyistream_iterator<int> inputInt(cin);
	int n1,n2,n3;
	n1 = * inputInt; //∂¡»Î n1
	int tmp = * inputInt;
	cout << tmp << endl;
	inputInt ++;
	n2 = * inputInt; //∂¡»Î n2
	inputInt ++;
	n3 = * inputInt; //∂¡»Î n3
	cout << n1 << "," << n2<< "," << n3 << endl;
	CMyistream_iterator<string> inputStr(cin);
	string s1,s2;
	s1 = * inputStr;
	inputStr ++;
	s2 = * inputStr;
	cout << s1 << "," << s2 << endl;

	/*Problem3*/
	int n;
	cin>>n;

	multiset<int> mset;
	set<int> st;

	while(n--){
		string cmd;
		cin>>cmd;
		
		if(cmd == "add"){
			int x;
			cin>>x;
			mset.insert(x);
			st.insert(x);
			cout<<mset.count(x)<<endl;
		}
		else if (cmd == "del"){
			int x;
			cin>>x;
			cout<<mset.count(x)<<endl;
			mset.erase(mset.lower_bound(x), mset.upper_bound(x));
		}
		else if (cmd == "ask"){
			int x;
			cin>>x;
			if(st.count(x) == 1) cout<<"1 ";
			else cout<<"0 ";
			cout<<mset.count(x)<<endl;
		}
	}

	/*Problem5*/
    int num;
    cin>>num;
    typedef map<int, int> MAP;
    MAP mp;
    mp.insert(MAP::value_type(1000000000, 1));
    pair<MAP::iterator, bool> pairs;
    while(num--){
        int id;
        int power;
        cin>>id>>power;
        pairs = mp.insert(make_pair(power, id));
        MAP::iterator i = pairs.first;
        MAP::iterator i2 = pairs.first;
        int minId;
        if(i==mp.begin()) {
            i++;
            minId = i->second;
        } else if(i==mp.end()){
            i--;
            minId = i->second;
        }else {
            i--;
            i2++;
            minId = i->second;
            if(abs(i->first-power) > abs(i2->first-power)) minId = i2->second;
        }
        cout<<id<<" "<<minId<<endl;;
    }


	system("pause");
	return 0;
}
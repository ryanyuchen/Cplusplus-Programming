#include <iostream> 
#include <iterator> 
#include <set>
#include <map>
#include <list>
#include <vector>
#include <string>
using namespace std;

int main() { 
    /*Problem 1*/
	int a[] = {8,7,8,9,6,2,1}; 
	set<int> v(a, a+7);
	ostream_iterator<int> o(cout," ");
    copy(v.begin(),v.end(),o); 
	cout<<endl;

	/*Problem 2*/
	int n;
	cin>>n;

	map<int, list<int>> mp;

	while (n--){
		string cmd;
		cin>>cmd;

		if(cmd == "new"){
			int id;
			cin>>id;
			mp[id] = list<int>();
		}
		else if(cmd == "add"){
			int id;
			int num;
			cin>>id>>num;
			mp[id].push_back(num);
		}
		else if(cmd == "merge"){
			int id1, id2;
			cin>>id1>>id2;
			mp[id1].merge(mp[id2]);
		}
		else if(cmd == "unique"){
			int id;
			cin>>id;
			mp[id].sort();
			mp[id].unique();
		}
		else if(cmd == "out"){
			int id;
			cin>>id;
			mp[id].sort();
			list<int>::iterator i;
			for(i=mp[id].begin(); i!=mp[id].end(); i++)
				cout<<*i<<" ";
			cout<<endl;
		}
	}

	system("pause");
    return 0;
}
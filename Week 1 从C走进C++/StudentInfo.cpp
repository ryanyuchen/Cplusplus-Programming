#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

#define MAXLEN 100

class Student{
private:
	char name[MAXLEN];
	int age;
	char id[MAXLEN];
	int avgsc1, avgsc2, avgsc3, avgsc4;
public:
	Student(char nm[], int ag, char xh[], int avg1, int avg2, int avg3, int avg4){
		strcpy(name, nm);
		age = ag;
		strcpy(id, xh);
		avgsc1 = avg1;
		avgsc2 = avg2;
		avgsc3 = avg3;
		avgsc4 = avg4;
	}
	
	char* printname(){
		return name;}
	
	int printage(){
		return age;}

	char* printid(){
		return id;}

	int printavgsc(){
		return (avgsc1 + avgsc2 + avgsc3 + avgsc4) / 4;}

};

void main(){
	char nm[MAXLEN];
	int ag;
	char xh[MAXLEN];
	int sc1, sc2, sc3, sc4;
	char next;
	cin.getline(nm, MAXLEN, ',');
	cin >> ag;
	next = getchar();
	cin.getline(xh, MAXLEN, ',');
	cin >> sc1 >> next >> sc2 >> next >> sc3 >> next >> sc4;
	Student std(nm, ag, xh, sc1, sc2, sc3, sc4);
	cout << std.printname() << ", " << std.printage() << ", " << std.printid() << ", " << std.printavgsc() << "\n";

	system("pause");
}


#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
const int WARRIOR_NUM = 5;
const int WEAPON_NUM = 3;

/* 
string Warrior::names[WARRIOR_NUM] = { "dragon","ninja","iceman","lion","wolf" }; 
红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。 
蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。 
*/  

class Headquarter;
class Warrior{
private:
	Headquarter * pHQ;
	int kindNo; //0 dragon 1 ninja 2 iceman 3 lion 4 wolf
	int no;
	int weaponNum;
	int weaponNo[2];
	double morale;
	int loyalty;
public:
	static string names[WARRIOR_NUM];
	static string weapons[WEAPON_NUM];
	static int initLifeValue[WARRIOR_NUM];
	Warrior(Headquarter * p, int no_, int kindNo_);
	void PrintResult(int nTime);
	void PrintInfomation();
};

class Headquarter{
private:
	int totalLifeValue;
	bool stopflag;
	int totalWarriorNum;
	int color;
	int SeqIdx; //sequence index to product warrior
	int warriorNum[WARRIOR_NUM]; // each warrior's number
	Warrior * pW[100];
public:
	friend class Warrior; // Warrior is a friend class of Headquarter
	static int makingSeq[2][WARRIOR_NUM]; // sequence to product warrior for red and blue headquarter
	void Init(int color_, int lv){
		color = color_;
		totalLifeValue = lv;
		totalWarriorNum = 0;
		stopflag = false;
		SeqIdx = 0;
		for (int i = 0; i < WARRIOR_NUM; i++)
			warriorNum[i] = 0;
	}
	~Headquarter(){
		for (int i = 0; i < totalWarriorNum; i++)
			delete pW[i];
	}
	int Produce(int nTime);
	string GetColor();
};

Warrior::Warrior(Headquarter *p,int no_,int kindNo_){
	no = no_;
	kindNo = kindNo_;
	pHQ = p;

	if(kindNo != 3 && kindNo != 4){
		if(kindNo == 1) weaponNum = 2;
		else weaponNum = 1;
	}
	else weaponNum = 0;

	for(int i = 0; i < weaponNum; i++) weaponNo[i] = (no + i) % 3;

	if(kindNo == 0) morale = (double)p->totalLifeValue/initLifeValue[0];
	else morale = 0;

	if(kindNo == 3) loyalty = p->totalLifeValue;
	else loyalty = 0;
}

void Warrior::PrintResult(int nTime)  
{  
    string color =  pHQ->GetColor();  
    printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n"  ,  
        nTime, color.c_str(), names[kindNo].c_str(), no, initLifeValue[kindNo],  
        pHQ->warriorNum[kindNo],names[kindNo].c_str(),color.c_str());  
}

void Warrior::PrintInfomation()  
{  
    if(kindNo == 0) printf("It has a %s,and it's morale is %.2f\n",weapons[weaponNo[0]].c_str(),morale);  
    if(kindNo == 1) printf("It has a %s and a %s\n",weapons[weaponNo[0]].c_str(),weapons[weaponNo[1]].c_str());  
    if(kindNo == 2) printf("It has a %s\n",weapons[weaponNo[0]].c_str());  
    if(kindNo == 3) printf("It's loyalty is %d\n",loyalty);  
}  

int Headquarter::Produce(int nTime)
{
	if(stopflag)
		return 0;
	int searchTimes = 0;
	while(Warrior::initLifeValue[makingSeq[color][SeqIdx]] > totalLifeValue && searchTimes < WARRIOR_NUM){
		SeqIdx = (SeqIdx + 1) % WARRIOR_NUM;
		searchTimes++;
	}
	int kindNo = makingSeq[color][SeqIdx];
	if(Warrior::initLifeValue[kindNo] > totalLifeValue){
		stopflag = true;
		if( color == 0)  
            printf("%03d red headquarter stops making warriors\n",nTime);  
        else  
            printf("%03d blue headquarter stops making warriors\n",nTime);  
        return 0;
	}
	//produce warrior
	totalLifeValue -= Warrior::initLifeValue[kindNo];
	SeqIdx = (SeqIdx + 1) % WARRIOR_NUM;
	pW[totalWarriorNum] = new Warrior(this, totalWarriorNum+1, kindNo);
	warriorNum[kindNo]++;
	pW[totalWarriorNum]->PrintResult(nTime);
	pW[totalWarriorNum]->PrintInfomation();
	totalWarriorNum++;
	return 1;
}

string Headquarter::GetColor()  
{  
    if( color == 0)  
        return "red";  
    else  
        return "blue";  
}  

string Warrior::names[WARRIOR_NUM] = { "dragon","ninja","iceman","lion","wolf" };  
string Warrior::weapons[WEAPON_NUM] = { "sword","bomb","arrow" };  
int Warrior::initLifeValue [WARRIOR_NUM];  
int Headquarter::makingSeq[2][WARRIOR_NUM] = { { 2,3,4,1,0 },{3,0,1,2,4} }; //两个司令部武士的制作顺序序列  

int main()
{
	int t;
	int m;
	Headquarter Red, Blue;
	scanf("%d", &t);
	int nCaseNo = 1;
	while (t--) {
		printf("Case:%d\n", nCaseNo++);
		scanf("%d", &m);
		for(int i = 0; i < WARRIOR_NUM; i++)
			scanf("%d", &Warrior::initLifeValue[i]);
		Red.Init(0, m);
		Blue.Init(1, m);
		int nTime = 0;
		while(true){
			int tmp1 = Red.Produce(nTime);
			int tmp2 = Blue.Produce(nTime);
			if(tmp1 == 0 && tmp2 ==0)
				break;
			nTime++;
		}
	}
	system("pause");
	return 0;
}

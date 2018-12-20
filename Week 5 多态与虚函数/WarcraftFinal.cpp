#include <iostream>
#include <iomanip>
using namespace std;
const int WARRIOR_NUM = 5;
const int WEAPON_NUM = 3;
const int CITY_NUM = 20;
/*
 char * Warrior::product_s[WARRIOR_NUM] = { "dragon","ninja","iceman","lion","wolf" };
 �췽˾����� iceman��lion��wolf��ninja��dragon ��˳��������ʿ��
 ����˾����� lion��dragon��ninja��iceman��wolf ��˳��������ʿ��
 */

class Headquarter;
class Warrior;

class Weapon
{
private:
    int wKindNo;                // �������
    Warrior * wpwarrior;        // ӵ����������ʿ
    bool useful;                // �����Ƿ�����
public:
    Weapon(int wKindNo_, Warrior * wpwarrior_) : wKindNo(wKindNo_), wpwarrior(wpwarrior_) { useful = true; }
    static char * weapon_list[WEAPON_NUM];
    virtual bool getWeaponUseful() { return useful; }
    int getWeaponNo() { return wKindNo; }
    char * getWeaponName() { return weapon_list[wKindNo]; }
    virtual void afterFight() {}
    virtual int getWeaponPower() { return 0; }
    void setWeaponuse(bool use) { useful = use; }
};

class Sword :public Weapon
{
private:
    int swordPower;             // sword������
public:
    Sword(int wKindNo_, Warrior * wpwarrior_, int swordPower_) :Weapon(wKindNo_, wpwarrior_), swordPower(swordPower_) {}
    virtual bool getWeaponUseful() { return (swordPower != 0); }                // �Ƿ��й�����
    virtual void afterFight() { swordPower = swordPower * 4 / 5; }
    virtual int getWeaponPower() { return swordPower; }
};

class Arrow :public Weapon
{
private:
    int arrowuse;               // Arrow ��ʣ�Ĵ���
public:
    static int arrowPower;
    Arrow(int wKindNo_, Warrior * wpwarrior_, int arrowuse_ = 3) : Weapon(wKindNo_, wpwarrior_) { arrowuse = arrowuse_; }
    virtual void afterFight() { if (arrowuse > 0) arrowuse -= 1; }
    virtual bool getWeaponUseful() { return (arrowuse > 0); }
    virtual int getWeaponPower() { return arrowuse; }
};

class Bomb : public Weapon
{
    bool bombuse;
public:
    Bomb(int wKindNo_, Warrior * wpwarrior_) : Weapon(wKindNo_, wpwarrior_) { bombuse = true; }
    virtual bool getWeaponUseful() { return bombuse; }
    virtual void afterFight() { bombuse = false; }
    virtual int getWeaponPower() { return bombuse; }
};

class Warrior
{
protected:
    Headquarter * pHeadquarter;
    int element;
    int force;
    int kindNo;                         // ��ʿ�������� 0 dragon 1 ninja 2 iceman 3 lion 4 wolf
    int no;
    Weapon * weapon[3];					// Wolf��Ϊ�нɻ���, �������п�������������
    int weaponCount;                    // ��ʿ����������
    int addrCity;                       // �ߵ��ĳ���
    int addrForward;					// �߹��Ĳ���
    bool notReached;
public:
    static char * product_s[WARRIOR_NUM];
    static int initialLifeValue[WARRIOR_NUM];
    static int initialForce[WARRIOR_NUM];
    Warrior(Headquarter * p, int no_, int kindNo_);
    void WarriorPrintPre(int nHour, int nMinute);
    void WarriorPrintInfo();
    virtual void PrintProduce(int nHour, int nMinute);
    void PrintWarriorPreAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum);
    virtual int WarriorAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum);
    virtual int Hurted(int nPower);
    void PrintWarriorFightBack(Warrior * uFpwarrior, int cityNum, int nHour, int nMinute);
    virtual int FightBack(Warrior * uFpwarrior);
    void PrintWarriorDown(int cityNum, int nHour, int nMinute);
    int getKindNo() { return kindNo; }
    virtual int getLoyalty() { return 0; }
    int getWeaponCount() { return weaponCount; }
    int getWarriorWeaponNo(int weapon_num) { if (weapon_num < weaponCount) return weapon[weapon_num]->getWeaponNo(); else return -1; }
    int getWarriorWeaponPower(int weapon_num) { if (weapon_num < weaponCount) return weapon[weapon_num]->getWeaponPower(); else return -1; }
    int getAddrCity() { return addrCity; }
    bool isOutAddrCity() { return (addrCity == 100); }
    void setAddrCity(int address = 100) { addrCity = address; }
    void PrintRunAway(int nHour, int nMinute);
    int WarriorMarch(int nHour, int nMinute);
    void PrintMarch(int nHour, int nMinute);
    void EarnForHead(int EarnLife_);
    void PrintEarnForHead(int EarnLife_, int nHour, int nMinute);
    int WarriorGetAward();
    int warriorActivePotentialHurt();			// ��������������ɵ��˺�
    int warriorBackPotentialHurt();				// ����������ɵ��˺�
    int warriorHasArrow();
    int warriorHasBomb();
    int warriorHasSword();
    int warriorArrowAttack(Warrior * uAAwarrior, int weaponnum, int nHour, int nMinute);	// -1: �����Է�; 1: û�������Է�
    void warriorBombAttack(Warrior * uBAwarrior, int weaponnum, int nHour, int nMinute);
    void PrintArrowAttack(Warrior * uAAwarrior, int attackResult, int nHour, int nMinute);
    void PrintBombAttack(Warrior * uBAwarrior, int nHour, int nMinute);
    int getElement() { return element; }	// ȡ�����е�����ֵ
    int getForce() { return force; }
    void setElement(int element_) { element += element_; }
    void WarriorReportWeapon(int nHour, int nMinute);
    bool getNotReached() { return notReached; }
    void setNotReached(bool notReached_) { notReached = notReached_; }
    void updateWeapon(int updateMode = 0);
    //* Dragon virtual
    virtual double getMorale() { return 0.0; }
    virtual void DragonYell(int cityNum, int nHour, int nMinute) {}
    virtual void setMorale(int setMode = 0, double morale_ = 0.2) {}
    //* Iceman virtual
    virtual void IcemanDec() {}
    //* Lion virtual
    virtual void setLoyalty(int setMode = 0) {}
    //* Wolf virtual
    virtual void WolfCaptureWeapon(Warrior * uAwarrior) {}
    
    void PrintExec();
};

class Dragon :public Warrior
{
private:
    double morale;
public:
    Dragon(Headquarter * p, int no_, int kindNo_, double morale_) : Warrior(p, no_, kindNo_), morale(morale_) {}
    virtual void PrintProduce(int nHour, int nMinute);
    virtual int WarriorAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum);
    virtual int Hurted(int nPower);
    virtual int FightBack(Warrior * uFpwarrior);
    virtual double getMorale() { return morale; }
    virtual void DragonYell(int cityNum, int nHour, int nMinute) { WarriorPrintPre(nHour, nMinute); cout << " yelled in city " << cityNum << endl; }
    virtual void setMorale(int setMode = 0, double morale_ = 0.2) { if (setMode == 0) morale += morale_; else morale -= morale_; }
};

class Ninjia :public Warrior
{
public:
    Ninjia(Headquarter * p, int no_, int kindNo_) : Warrior(p, no_, kindNo_) {}
    virtual void PrintProduce(int nHour, int nMinute);
    virtual int WarriorAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum);
    virtual int Hurted(int nPower);
    virtual int FightBack(Warrior * uFpwarrior);
};

class Iceman : public Warrior
{
public:
    Iceman(Headquarter * p, int no_, int kindNo_) : Warrior(p, no_, kindNo_) {}
    virtual void PrintProduce(int nHour, int nMinute);
    virtual int WarriorAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum);
    virtual int Hurted(int nPower);
    virtual int FightBack(Warrior * uFpwarrior);
    virtual void IcemanDec()
    {
        if (element > 9) element -= 9; else element = 1;
        force += 20;
    }
};

class Lion : public Warrior
{
private:
    int loyalty;
public:
    Lion(Headquarter * p, int no_, int kindNo_, int loyalty_) : Warrior(p, no_, kindNo_), loyalty(loyalty_) {}
    virtual void PrintProduce(int nHour, int nMinute);
    virtual int WarriorAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum);
    virtual int Hurted(int nPower);
    virtual int FightBack(Warrior * uFpwarrior);
    virtual int getLoyalty() { return loyalty; }
    virtual void setLoyalty(int setMode = 0) { if (setMode == 0) loyalty -= Lion::decreaseLoyalty; }
    static int decreaseLoyalty;
};

class Wolf : public Warrior
{
public:
    Wolf(Headquarter * p, int no_, int kindNo_) : Warrior(p, no_, kindNo_) {}
    virtual void PrintProduce(int nHour, int nMinute);
    virtual int WarriorAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum);
    virtual int Hurted(int nPower);
    virtual int FightBack(Warrior * uFpwarrior);
    virtual void WolfCaptureWeapon(Warrior * uAwarrior)
    {
        /*cout << "����captureWeapon" << endl;
         cout << "����������" << getWeaponCount() << "������" << "\t" << "����������" << uAwarrior->getWeaponCount() << "������" << endl;*/
        for (int i = 0; i < uAwarrior->getWeaponCount(); i++)
        {
            int j = 0;
            int uAWeaponNo = uAwarrior->getWarriorWeaponNo(i);
            while (j < this->weaponCount && uAWeaponNo != this->getWarriorWeaponNo(j))
                j++;
            if (j == this->weaponCount)
            {
                if (uAWeaponNo == 0) weapon[j] = new Sword(uAWeaponNo, this, uAwarrior->getWarriorWeaponPower(i));
                else if (uAWeaponNo == 1) weapon[j] = new Bomb(uAWeaponNo, this);
                else if (uAWeaponNo == 2) weapon[j] = new Arrow(uAWeaponNo, this, uAwarrior->getWarriorWeaponPower(i));
                weaponCount += 1;
            }
        }
    }
};

void Warrior::WarriorReportWeapon(int nHour, int nMinute) // �����������ʱ�����������ǣ�arrow,bomb,sword
{
    int count = 0;
    WarriorPrintPre(nHour, nMinute);
    cout << " has ";
    int hasArrow = warriorHasArrow();
    int hasBomb = warriorHasBomb();
    int hasSword = warriorHasSword();
    if (count < weaponCount && hasArrow != -1)   // ����й���, ���������
    {
        cout << Weapon::weapon_list[2] << "(" << weapon[hasArrow]->getWeaponPower() << ")";
        count++;
    }
    if (count < weaponCount && hasBomb != -1)
    {
        if (count >= 1)
            cout << ",";
        cout << Weapon::weapon_list[1];
        count++;
    }
    if (count < weaponCount && hasSword != -1)
    {
        if (count >= 1)
            cout << ",";
        cout << Weapon::weapon_list[0] << "(" << weapon[hasSword]->getWeaponPower() << ")";
    }
    if (weaponCount == 0)
        cout << "no weapon";
    cout << endl;
}

void Warrior::updateWeapon(int updateMode) // updateMode = 0: ����sword; updateMode = 1: ����Bomb; updateMode = 2: ����Arrow; updateMode = 3: ����ʱ����
{
    bool updateFlag = false;									// ������¼�Ƿ���Ҫ�����Ѿ�û���õ�����
    int updateModeTmp = updateMode;
    if ( updateMode == 3 )
        updateModeTmp = 0;
    for (int i = 0; i < this->weaponCount; i++)
    {
        if (weapon[i]->getWeaponNo() == updateModeTmp)				// �����updateMode��Ӧ������
        {
            if (updateMode != 3)
                weapon[i]->afterFight();
            if (!weapon[i]->getWeaponUseful())					// �������ʧȥ������, ����Ϊ��
            {
                weapon[i] = NULL;
                updateFlag = true;
            }
            break;				// �����ض���һ��ʹ������, �����ǹ�������, ը����������Sword����, ��ֻ��ʹ��һ������
        }
    }
    if (updateFlag)												// �����Ҫ�����Ѿ�û���õ�����
    {
        int weaponcountnew = 0;
        for (int i = 0; i < this->weaponCount; i++)
        {
            if (weapon[i] != NULL)
            {
                weapon[weaponcountnew] = weapon[i];
                weaponcountnew += 1;
            }
        }
        this->weaponCount = weaponcountnew;
    }
}

class City
{
private:
    int cityLifeValue;
    int cityNum;
    Warrior * redWarrior;
    Warrior * blueWarrior;
    int flag;                                  // flag = -1: û������; flag = 0: ����; flag = 1: ����
    int BattleResult;						   // ��¼��һ��ս���Ľ��
public:
    City(int cityLifeValue_, int cityNum_);
    void Init(int cityLifeValue_, int cityNum_);
    void CityAddLife(int cityAddValue_ = 10) { cityLifeValue += cityAddValue_; }
    void setCityLifeValue(int cityLifeValue_) { cityLifeValue = cityLifeValue_; }
    void EarnLifeForHead(int nHour, int nMinute, int Post = 0);	// Post = 0: ��Ҫ��ӡӮȡ����Ԫ����Ϊ; Post = 1: ����Ҫ��ӡ
    int CityAwardWarrior(int color = 0); // color = 0: ������ɫ��ʿ��, color = 1: ������ɫ��ʿ��; ����ֵ = -1: ˾�û���㹻����Ԫ��������; ����ֵ = 1: ˾������㹻������Ԫ��������
    void setredWarrior(Warrior * redWarrior_) { redWarrior = redWarrior_; }
    void setblueWarrior(Warrior * blueWarrior_) { blueWarrior = blueWarrior_; }
    Warrior * getblueWarrior() { return blueWarrior; }
    int getCityNum() { return cityNum; }
    int getCityLifeValue() { return cityLifeValue; }
    static int citytotal;
    void CityRunAway(int nHour, int nMinute);
    int CityMarch(City * nexcity, int nHour, int nMinute);		// = 0: ����ʿʤ��; = 1: ����ʿʤ��; = -1: ���߾�û���������˵���
    void CityArrowAttack(City * Bcity, City * ACity, int nHour, int nMinute);
    bool ActiveAttack();
    int CityBattlePotential();							// = 0: ����ʿʤ; = 1: ����ʿʤ; = -1: û����ʿ����
    bool CityBombAttack(int nHour, int nMinute);		// = true: ˫��ͬ���ھ�; = false: û��ʹ��bomb
    void updateBattleResult(int nHour, int nMinute, int afterBattle);
    void PrintFlagRaise(int nHour, int nMinute);
    int CityBattle(int nHour, int nMinute);				// = 0: ����ʿʤ; = 1: ����ʿʤ; = -1: û����ʿ����
    void CityReportWeapon(int nHour, int nMinute, int color);		// �����������
    
    void PrintEachCityAfterExec();						// ������, ��ӡ������ʿ��Ϣ
};

City::City(int cityLifeValue_, int cityNum_)
{
    cityNum = cityNum_;
    cityLifeValue = cityLifeValue_;
    flag = -1;
    BattleResult = -1;
    redWarrior = NULL;
    blueWarrior = NULL;
}

void City::Init(int cityLifeValue_, int cityNum_)
{
    cityNum = cityNum_;
    cityLifeValue = cityLifeValue_;
    flag = -1;
    BattleResult = -1;
    redWarrior = NULL;
    blueWarrior = NULL;
}

void City::CityRunAway(int nHour, int nMinute)
{
    if (redWarrior != NULL && redWarrior->getKindNo() == 3 && redWarrior->getLoyalty() <= 0)
    {
        if (redWarrior->getAddrCity() != (City::citytotal + 1))
        {
            redWarrior->PrintRunAway(nHour, nMinute);
            redWarrior->setAddrCity();										// addrCity�ܴ�(Ĭ��100), ��ʾ�ӵ�����
            redWarrior = NULL;
        }
    }
    if (blueWarrior != NULL && blueWarrior->getKindNo() == 3 && blueWarrior->getLoyalty() <= 0)
    {
        if (blueWarrior->getAddrCity() != 0)
        {
            blueWarrior->PrintRunAway(nHour, nMinute);
            blueWarrior->setAddrCity();
            blueWarrior = NULL;
        }
    }
}

int City::CityMarch(City * nextcity, int nHour, int nMinute)
{
    int occupationFlag = -1;
    int occupationFlagTmp = -1;
    if (nextcity->blueWarrior != NULL && nextcity->blueWarrior->getAddrCity() != 0)
    {
        occupationFlagTmp = nextcity->blueWarrior->WarriorMarch(nHour, nMinute);
        if (occupationFlagTmp == 1)
        {
            occupationFlag = 1;
            cout << setfill('0') << setw(3) << nHour << ":" << setw(2) << nMinute << " ";
            cout << "red headquarter was taken" << endl;
        }
        else if (occupationFlagTmp == 3) // �����һ������ʿ����췽˾�
        {
            // Ҫsetcity[0]��bluewarrior
            this->setblueWarrior(nextcity->blueWarrior);
        }
        nextcity->blueWarrior = NULL;
    }
    if (redWarrior != NULL && redWarrior->getAddrCity() != (City::citytotal + 1)) // �췽ǰ��
    {
        occupationFlagTmp = redWarrior->WarriorMarch(nHour, nMinute);
        if (occupationFlagTmp == 0)
        {
            occupationFlag = 0;
            cout << setfill('0') << setw(3) << nHour << ":" << setw(2) << nMinute << " ";
            cout << "blue headquarter was taken" << endl;
        }
        if (occupationFlagTmp == 2) // �����һ������ʿ��������˾�
        {
            // Ҫsetcity[N]�ĺ���ʿ;
            nextcity->setredWarrior(this->redWarrior);
        }
        redWarrior = NULL;
    }
    if ( occupationFlag == -1 )
        occupationFlag = occupationFlagTmp;
    return occupationFlag;
}

void City::EarnLifeForHead(int nHour, int nMinute, int Post)
{
    if (redWarrior != NULL && blueWarrior == NULL && cityLifeValue != 0)
    {
        redWarrior->EarnForHead(cityLifeValue);
        if (Post == 0)
            redWarrior->PrintEarnForHead(cityLifeValue, nHour, nMinute);
        setCityLifeValue(0);
    }
    else if (redWarrior == NULL && blueWarrior != NULL && cityLifeValue != 0)
    {
        blueWarrior->EarnForHead(cityLifeValue);
        if (Post == 0)
            blueWarrior->PrintEarnForHead(cityLifeValue, nHour, nMinute);
        setCityLifeValue(0);
    }
}

int City::CityAwardWarrior(int color) // color = 0: ������ɫ��ʿ��, color = 1: ������ɫ��ʿ��; ����ֵ = -1: ˾�û���㹻����Ԫ��������; ����ֵ = 1: ˾������㹻������Ԫ��������
{
    int AwardResult = 1;
    if (color == 0 && redWarrior != NULL && blueWarrior == NULL && cityLifeValue != 0)
        AwardResult = redWarrior->WarriorGetAward();
    else if (color == 1 && blueWarrior != NULL && redWarrior == NULL && cityLifeValue != 0)
        AwardResult = blueWarrior->WarriorGetAward();
    return AwardResult;
}

void City::CityArrowAttack(City * Bcity, City * Acity, int nHour, int nMinute)
{
    int redArrow = 1, blueArrow = 1;
    if (redWarrior != NULL && Acity->blueWarrior != NULL)
    {
        if (cityNum < City::citytotal && redWarrior->warriorHasArrow() != -1)
            redArrow = redWarrior->warriorArrowAttack(Acity->blueWarrior, redWarrior->warriorHasArrow(), nHour, nMinute);
    }
    if ( blueWarrior != NULL && Bcity->redWarrior != NULL)
    {
        if (cityNum > 1 && blueWarrior->warriorHasArrow() != -1)
            blueArrow = blueWarrior->warriorArrowAttack(Bcity->redWarrior, blueWarrior->warriorHasArrow(), nHour, nMinute);
    }
    
    if (redArrow == -1)
        Acity->blueWarrior->setAddrCity();										// addrCity�ܴ�(Ĭ��100), ��ʾ��ɱ��
    if (blueArrow == -1)
        Bcity->redWarrior->setAddrCity();                                       // addrCity�ܴ�(Ĭ��100), ��ʾ��ɱ��
}

bool City::ActiveAttack()
{
    if ((flag == -1 && cityNum % 2 == 1) || flag == 0)				// �ɺ���ʿ�ȷ������
        return true;
    return false;
}

void City::updateBattleResult(int nHour, int nMinute, int afterBattle)	// afterBattle = 0: ����ʿʤ; = 1: ����ʿʤ; = -1: ƽ��
{
    if (afterBattle != BattleResult)
        BattleResult = afterBattle;
    else if (BattleResult != -1 && afterBattle == BattleResult && flag != afterBattle)
    {
        flag = afterBattle;
        this->PrintFlagRaise(nHour, nMinute);
    }
}
void City::PrintFlagRaise(int nHour, int nMinute)
{
    cout << setfill('0') << setw(3) << nHour << ":" << setw(2) << nMinute << " ";
    if (flag == 0) cout << "red"; else cout << "blue";
    cout << " flag raised in city " << cityNum << endl;
}

int City::CityBattle(int nHour, int nMinute)						// = 0: ����ʿʤ; = 1: ����ʿʤ; = -1: û����ʿ��������û�з���ս��
{
    int cityBattlePotential = CityBattlePotential(); // �ж�ս�����, = 0: ����ʿʤ; = 1: ����ʿʤ; = -1: û�н�ս; = 2: ����ʿսǰ�Ѿ�������, ����ʿ�൱��ʤ��; = 3: ����ʿսǰ�Ѿ�������, ����ʿ�൱��ʤ��; = 4: ����ʿ������ʿսǰ����������ը��; = 5: ˫���Ҵ�
    int battleResult = -1; // = -1: û���κ�һ������; = 0: ����������ʤ��, ������������; = 1: ����������ʤ��, ��������������; = 2: սǰ����������; = 3: սǰ����������
    if (redWarrior != NULL && redWarrior->isOutAddrCity() && blueWarrior == NULL)		// һ��������, һ��ΪNULL
    {
        redWarrior->setAddrCity();
        redWarrior = NULL;
    }
    else if (blueWarrior != NULL && blueWarrior->isOutAddrCity() && redWarrior == NULL)	// һ��������, һ��ΪNULL
    {
        blueWarrior->setAddrCity();
        blueWarrior = NULL;
    }
    if (redWarrior == NULL || blueWarrior == NULL)
        return -1;
    if (ActiveAttack())												// �ɺ���ʿ�ȷ������
        battleResult = redWarrior->WarriorAttack(nHour, nMinute, blueWarrior, cityNum);
    else
        battleResult = blueWarrior->WarriorAttack(nHour, nMinute, redWarrior, cityNum);		// ������ʿ�ȷ������
    if (cityBattlePotential == 0 || cityBattlePotential == 3)
    {
        redWarrior->PrintEarnForHead(cityLifeValue, nHour, nMinute);	// �ȴ�ӡΪheadquarterӮ������Ԫ, ֮����ʵ���Եļ�����Щ����Ԫ
        blueWarrior->setAddrCity();
        blueWarrior = NULL;
        this->updateBattleResult(nHour, nMinute, 0); // ����ս�����BattleResult, ����ʿʤ;
    }
    else if (cityBattlePotential == 1 || cityBattlePotential == 2)
    {
        blueWarrior->PrintEarnForHead(cityLifeValue, nHour, nMinute);	// �ȴ�ӡΪheadquarterӮ������Ԫ, ֮����ʵ���Եļ�����Щ����Ԫ
        redWarrior->setAddrCity();
        redWarrior = NULL;
        this->updateBattleResult(nHour, nMinute, 1); // ����ս�����BattleResult, ����ʿʤ;
    }
    else if (cityBattlePotential == 4)	// սǰ���߾�����
    {
        redWarrior = NULL;
        blueWarrior = NULL;
    }
    else if (cityBattlePotential == 5)	// ˫��ս����Ҵ�
        this->updateBattleResult(nHour, nMinute, -1); // ����ս�����BattleResult, ˫��ƽ��;
    return cityBattlePotential;
}

int City::CityBattlePotential()												// �ж�ս�����, = 0: ����ʿʤ; = 1: ����ʿʤ; = -1: û����ʿ��������û�н�ս
{																			// = 2: ����ʿսǰ�Ѿ�������, ����ʿ�൱��ʤ��; = 3: ����ʿսǰ�Ѿ�������, ����ʿ�൱��ʤ��
    if (redWarrior == NULL || blueWarrior == NULL)							// = 4: ����ʿ������ʿսǰ����������ը��; = 5: ˫���Ҵ�
        return -1;
    if (redWarrior->isOutAddrCity() && !blueWarrior->isOutAddrCity())		// ���ս����ʼǰ����ʿ�Ѿ���������;
        return 2;
    else if (blueWarrior->isOutAddrCity() && !redWarrior->isOutAddrCity())	// ���ս����ʼǰ����ʿ�Ѿ���������;
        return 3;
    else if (redWarrior->isOutAddrCity() && blueWarrior->isOutAddrCity())	// ���ս����ʼǰ����ʿ������ʿ��������
        return 4;
    if (ActiveAttack())														// �ɺ���ʿ�ȷ������
    {
        if (redWarrior->warriorActivePotentialHurt() >= blueWarrior->getElement())
            return 0;
        else if (blueWarrior->getKindNo() != 1 && blueWarrior->warriorBackPotentialHurt() >= redWarrior->getElement()) // �������ninjia�Żᷴ��
            return 1;
    }
    else
    {
        if (blueWarrior->warriorActivePotentialHurt() >= redWarrior->getElement())
            return 1;
        else if (redWarrior->getKindNo() != 1 && redWarrior->warriorBackPotentialHurt() >= blueWarrior->getElement()) // �������ninjia�Żᷴ��
            return 0;
    }
    
    return 5;	// ˫���Ҵ�
}

bool City::CityBombAttack(int nHour, int nMinute)				// = true: ����ͬ���ھ�; = false: û�з���bomb�¼�
{
    bool bombflag = false;
    int cBT = CityBattlePotential();	// = 0: ��ʤ; = 1: ��ʤ; = 2: ��սǰ��; = 3: ��սǰ��; = 4: սǰ����; = 5: ˫���Ҵ�
    if (cBT == -1 || cBT == 5)
        return false;
    else if (cBT == 0 && blueWarrior->warriorHasBomb() != -1)
    {
        blueWarrior->warriorBombAttack(redWarrior, blueWarrior->warriorHasBomb(), nHour, nMinute);
        bombflag = true;
    }
    else if (cBT == 1 && redWarrior->warriorHasBomb() != -1)
    {
        redWarrior->warriorBombAttack(blueWarrior, redWarrior->warriorHasBomb(), nHour, nMinute);
        bombflag = true;
    }
    if (bombflag)
    {
        redWarrior->setAddrCity();												// addrCity�ܴ�(Ĭ��100), ��ʾ��ɱ��
        //redWarrior = NULL;
        blueWarrior->setAddrCity();												// addrCity�ܴ�(Ĭ��100), ��ʾ��ɱ��
        //blueWarrior = NULL;
        return true;
    }
    return false;
}

void City::CityReportWeapon(int nHour, int nMinute, int color)
{
    if (color == 0 && redWarrior != NULL)
        redWarrior->WarriorReportWeapon(nHour, nMinute);
    if (color == 1 && blueWarrior != NULL)
        blueWarrior->WarriorReportWeapon(nHour, nMinute);
}

void City::PrintEachCityAfterExec()
{
    if (cityNum == 0)
        cout << "(����" << ":";
    else if (cityNum == (City::citytotal + 1))
        cout << "(����" << ":";
    else
        cout << "(����" << cityNum << ":";
    cout << "��";
    if (redWarrior != NULL)
    {
        redWarrior->PrintExec();
        cout << ", ";
    }
    else
        cout << "��" << ", ";
    cout << "��";
    if (blueWarrior != NULL)
    {
        blueWarrior->PrintExec();
        cout << ")";
    }
    else
        cout << "��" << ")";
}

class Headquarter
{
private:
    int totalLifeValue;
    bool stopped;
    int totalWarriorNum;
    int Color_C;
    int curMakingSeqIdx;                            //��ǰҪ�������ʿ�����������еĵڼ���
    int warriorNum[WARRIOR_NUM];                    //���ÿ����ʿ������
    Warrior * pWarriors[1000];
    int occupation;									// ����Է�˾�����ʿ����
public:
    friend class Warrior;
    static int makingSeq[2][WARRIOR_NUM];           //��ʿ������˳������
    void Init(int color_, int lifevalue_);
    ~Headquarter();
    int Produce(int nHour, int nMinute);
    void UpdateCityWarrior();
    char * GetColor();
    int getColor() { return Color_C; }
    static char * color[2];
    static City * cityN[CITY_NUM + 2];
    static int citiesN[CITY_NUM];					// ��������ÿ������ս�����ʤ����; = 0: û��ʤ����; = 1: �췽ʤ; = 2: ����ʤ
    Warrior * getpwarrior(int id) { return pWarriors[id - 1]; }
    void AddLife(int addLifeValue_) { totalLifeValue += addLifeValue_; }
    int getTotalLifeValue() { return totalLifeValue; }
    void setTotalLifeValue(int lifeValue_) { totalLifeValue -= lifeValue_; }
    void PrintLifeValue(int nHour, int nMinute);
    int getOccupation() { return occupation; }
};

Warrior::Warrior(Headquarter * p, int no_, int kindNo_)
{
    no = no_;
    kindNo = kindNo_;
    pHeadquarter = p;
    force = initialForce[kindNo_];
    element = initialLifeValue[kindNo_];
    addrForward = 0;
    notReached = true;
    if (p->getColor() == 0) addrCity = 0;
    else if (p->getColor() == 1) addrCity = City::citytotal + 1;
    if (kindNo == 0) weaponCount = 1;
    else if (kindNo == 1) weaponCount = 2;
    else if (kindNo == 2) weaponCount = 1;
    else if (kindNo == 3) weaponCount = 0;
    else if (kindNo == 4) weaponCount = 0;
    for (int i = 0; i < weaponCount; i++)
    {
        int weapon_num = (no_ + i) % 3;
        if (weapon_num == 0) weapon[i] = new Sword(weapon_num, this, force / 5);
        else if (weapon_num == 1) weapon[i] = new Bomb(weapon_num, this);
        else if (weapon_num == 2) weapon[i] = new Arrow(weapon_num, this);
    }
    updateWeapon(3);
}

int Warrior::warriorActivePotentialHurt()
{
    int forceTmp = this->force;
    for (int i = 0; i < weaponCount; i++)
    {
        if (weapon[i]->getWeaponUseful() && weapon[i]->getWeaponNo() == 0)
            forceTmp += weapon[i]->getWeaponPower();
    }
    return forceTmp;
}
int Warrior::warriorBackPotentialHurt()
{
    int forceTmp = this->force / 2;
    for (int i = 0; i < weaponCount; i++)
    {
        if (weapon[i]->getWeaponUseful() && weapon[i]->getWeaponNo() == 0)
            forceTmp += weapon[i]->getWeaponPower();
    }
    return forceTmp;
}

void Warrior::PrintWarriorPreAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum)
{
    WarriorPrintPre(nHour, nMinute);
    cout << " attacked ";
    uApwarrior->WarriorPrintInfo();
    cout << " in city " << cityNum << " with " << element << " elements and force " << force << endl;
}
int Warrior::WarriorAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum)
{
    int attackResult = -1; // = -1: û���κ�һ������; = 0: ����������ʤ��, ������������; = 1: ����������ʤ��, ��������������; = 2: սǰ����������; = 3: սǰ����������
    if (this->isOutAddrCity() && uApwarrior->isOutAddrCity())	// սǰ������
    {
        attackResult = 4;
        return attackResult;
    }
    if (this->isOutAddrCity() && !uApwarrior->isOutAddrCity())	// սǰ��������������
        attackResult = 2;
    else if (!this->isOutAddrCity() && uApwarrior->isOutAddrCity())	// սǰ������������
        attackResult = 3;
    //* ���ս����ʼǰû����ʿ����������˫��ͬ���ھ�, ��ô�ᷢ�������ս��
    if (attackResult == -1)
    {
        //cout << "���������� = " << this->getElement() << "; arrCity = " << this->getAddrCity() << "; attackResult = " << attackResult << endl;
        PrintWarriorPreAttack(nHour, nMinute, uApwarrior, cityNum);
        int APreElement = element;									// ս��ǰ���������ߵ�����ֵ
        int uAPreElement = uApwarrior->element;						// ս��ǰ���������ߵ�����ֵ
        int hurted = uApwarrior->Hurted(warriorActivePotentialHurt());
        this->updateWeapon();										// �����Sword, ��Ҫ����Sword������
        if (hurted == 1 && uApwarrior->kindNo != 1)					// �����������û��ս�����ұ������߲���Ninjia, ��Ҫ����
        {
            uApwarrior->PrintWarriorFightBack(this, cityNum, nHour, nMinute);
            hurted = uApwarrior->FightBack(this);
            uApwarrior->updateWeapon();							// �����Sword, ��Ҫ����Sword������
            if (hurted == -1)									// ������ʤ��, ����������ս��
            {
                attackResult = 1;
                this->PrintWarriorDown(cityNum, nHour, nMinute);
                if (kindNo == 3)								// ���ս������Lion, ����ս��ǰ������ֵ�ͻ�ת�Ƶ���������
                    uApwarrior->setElement(APreElement);
            }
        }
        else if (hurted == -1)								// ����������ʤ��, ��������ս��
        {
            uApwarrior->PrintWarriorDown(cityNum, nHour, nMinute);
            attackResult = 0;
            if (uApwarrior->kindNo == 3)					// ���ս������Lion, ����ս��ǰ������ֵ�ͻ�ת�Ƶ���������
                this->setElement(uAPreElement);
        }
    }
    
    if (attackResult == -1)	// ���û����ʿս��, ��ô���۹����߻��Ǳ������������Dragonʿ���ͼ���0.2, �����Lion���ҳ϶Ƚ���Lion::decreaseLoyalty
    {
        if (this->kindNo == 0)
            this->setMorale(1);
        if (this->kindNo == 3)
            this->setLoyalty();
        if (uApwarrior->kindNo == 0)
            uApwarrior->setMorale(1);
        else if (uApwarrior->kindNo == 3)
            uApwarrior->setLoyalty();
    }
    else if (attackResult == 1 || attackResult == 2)	// սǰ����������������ս��ս��
    {
        // ����һ�б�������ս��ʤ���÷���������;
        if (uApwarrior->kindNo == 0)					// ���սʤ����Dragon, ��ôʿ������0.2
            uApwarrior->setMorale();
        else if (uApwarrior->kindNo == 4)				// ���ʤ������Wolf, ��ôҪ�ɻ�ս���ߵ�����
            uApwarrior->WolfCaptureWeapon(this);
    }
    else if (attackResult == 0 || attackResult == 3)	// սǰ��������������ս��ս��
    {
        // ����һ������������ʤ���ᷢ��������;
        if (this->kindNo == 0)							// ���������������Dragon, ��ʿ������0.2
            this->setMorale();
        else if (this->kindNo == 4)						// ���ʤ������Wolf, ��ôҪ�ɻ�ս���ߵ�����
            this->WolfCaptureWeapon(uApwarrior);
    }
    
    if (this->kindNo == 0 && this->element > 0 && this->getMorale() > 0.8)	// ���������������Dragon����ս������û��ս������ʿ������0.8, �ͻỶ��
        this->DragonYell(cityNum, nHour, nMinute);
    return attackResult;
}

int Dragon::WarriorAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum)
{
    return Warrior::WarriorAttack(nHour, nMinute, uApwarrior, cityNum);
}
int Ninjia::WarriorAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum)
{
    return Warrior::WarriorAttack(nHour, nMinute, uApwarrior, cityNum);
}
int Iceman::WarriorAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum)
{
    return Warrior::WarriorAttack(nHour, nMinute, uApwarrior, cityNum);
}
int Lion::WarriorAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum)
{
    return Warrior::WarriorAttack(nHour, nMinute, uApwarrior, cityNum);
}
int Wolf::WarriorAttack(int nHour, int nMinute, Warrior * uApwarrior, int cityNum)
{
    return Warrior::WarriorAttack(nHour, nMinute, uApwarrior, cityNum);
}


int Warrior::Hurted(int nPower)
{
    element -= nPower;
    if (element <= 0)
        return -1;
    
    return 1;
}
int Dragon::Hurted(int nPower)
{
    return Warrior::Hurted(nPower);
}
int Ninjia::Hurted(int nPower)
{
    return Warrior::Hurted(nPower);
}
int Iceman::Hurted(int nPower)
{
    return Warrior::Hurted(nPower);
}
int Lion::Hurted(int nPower)
{
    return Warrior::Hurted(nPower);
}
int Wolf::Hurted(int nPower)
{
    return Warrior::Hurted(nPower);
}

void Warrior::PrintWarriorFightBack(Warrior * uFpwarrior, int cityNum, int nHour, int nMinute)
{
    WarriorPrintPre(nHour, nMinute);
    cout << " fought back against ";
    uFpwarrior->WarriorPrintInfo();
    cout << " in city " << cityNum << endl;
}
int Warrior::FightBack(Warrior * uFpwarrior)
{
    return (uFpwarrior->Hurted(warriorBackPotentialHurt()));
}
int Dragon::FightBack(Warrior *uFpwarrior)
{
    return (uFpwarrior->Hurted(warriorBackPotentialHurt()));
}
int Ninjia::FightBack(Warrior *uFpwarrior)
{
    return (uFpwarrior->Hurted(warriorBackPotentialHurt()));
}
int Iceman::FightBack(Warrior *uFpwarrior)
{
    return (uFpwarrior->Hurted(warriorBackPotentialHurt()));
}
int Lion::FightBack(Warrior *uFpwarrior)
{
    return (uFpwarrior->Hurted(warriorBackPotentialHurt()));
}
int Wolf::FightBack(Warrior *uFpwarrior)
{
    return (uFpwarrior->Hurted(warriorBackPotentialHurt()));
}

void Warrior::PrintWarriorDown(int cityNum, int nHour, int nMinute)
{
    WarriorPrintPre(nHour, nMinute);
    cout << " was killed in city " << cityNum << endl;
}

void Warrior::WarriorPrintPre(int nHour, int nMinute)
{
    cout << setfill('0') << setw(3) << nHour << ":" << setw(2) << nMinute << " ";
    cout << pHeadquarter->GetColor() << " " << product_s[kindNo] << " " << no;
}

void Warrior::WarriorPrintInfo()
{
    cout << pHeadquarter->GetColor() << " " << product_s[kindNo] << " " << no;
}

void Warrior::PrintProduce(int nHour, int nMinute)
{
    WarriorPrintPre(nHour, nMinute);
    cout << " born" << endl;
}

void Warrior::PrintExec()
{
    cout << product_s[kindNo] << " " << no;
}

void Dragon::PrintProduce(int nHour, int nMinute)
{
    Warrior::PrintProduce(nHour, nMinute);
    cout << "Its morale is ";
    cout << fixed << setprecision(2) << morale << endl;
}

void Ninjia::PrintProduce(int nHour, int nMinute)
{
    Warrior::PrintProduce(nHour, nMinute);
}

void Iceman::PrintProduce(int nHour, int nMinute)
{
    Warrior::PrintProduce(nHour, nMinute);
}

void Lion::PrintProduce(int nHour, int nMinute)
{
    Warrior::PrintProduce(nHour, nMinute);
    cout << "Its loyalty is " << loyalty << endl;
}

void Wolf::PrintProduce(int nHour, int nMinute)
{
    Warrior::PrintProduce(nHour, nMinute);
}

void Warrior::PrintRunAway(int nHour, int nMinute)
{
    WarriorPrintPre(nHour, nMinute);
    cout << " ran away" << endl;
}

void Warrior::PrintMarch(int nHour, int nMinute)
{
    WarriorPrintPre(nHour, nMinute);
    if (pHeadquarter->getColor() == 0 && addrCity == (City::citytotal + 1))
        cout << " reached blue headquarter with " << element << " elements and force " << force << endl;
    else if (pHeadquarter->getColor() == 1 && addrCity == 0)
        cout << " reached red headquarter with " << element << " elements and force " << force << endl;
    else
        cout << " marched to city " << addrCity << " with " << element << " elements and force " << force << endl;
}

int Warrior::WarriorMarch(int nHour, int nMinute)
{
    int occupationFlag = -1;
    if (pHeadquarter->getColor() == 0 && addrCity != (City::citytotal + 1))
    {
        addrCity += 1;
        if (addrCity == (City::citytotal + 1) && pHeadquarter->getOccupation() == 1)
            occupationFlag = 0;		// ������������ʿ��������˾�
        else if (addrCity == (City::citytotal + 1) && pHeadquarter->getOccupation() == 0)
            occupationFlag = 2;		// ��ʾ��һ������ʿ��������˾�
    }
    else if (pHeadquarter->getColor() == 1 && addrCity != 0)
    {
        addrCity -= 1;
        if (addrCity == 0 && pHeadquarter->getOccupation() == 1)
            occupationFlag = 1;		// ������������ʿ����췽˾�
        else if (addrCity == 0 && pHeadquarter->getOccupation() == 0)
            occupationFlag = 3;		// ��ʾ��һ������ʿ����췽˾�
    }
    addrForward += 1;										// �߹��Ĳ�����1
    if (addrForward % 2 == 0 && kindNo == 2)				// �����Iceman����ÿǰ������, ��ôִ��Iceman��������
        IcemanDec();
    PrintMarch(nHour, nMinute);
    return occupationFlag;
}

void Warrior::EarnForHead(int EarnLife_)
{
    pHeadquarter->AddLife(EarnLife_);
}

void Warrior::PrintEarnForHead(int EarnLife_, int nHour, int nMinute)
{
    WarriorPrintPre(nHour, nMinute);
    cout << " earned " << EarnLife_ << " elements for his headquarter" << endl;
}

int Warrior::WarriorGetAward()
{
    int enough = 1;
    if (pHeadquarter->getTotalLifeValue() >= 8)
    {
        pHeadquarter->setTotalLifeValue(8);
        this->setElement(8);
    }
    if (pHeadquarter->getTotalLifeValue() < 8)
        enough = -1;
    return enough;
}

int Warrior::warriorHasArrow()
{
    for (int i = 0; i < weaponCount; i++)
    {
        if (weapon[i]->getWeaponUseful() && weapon[i]->getWeaponNo() == 2)
            return i;
    }
    return -1;
}

int Warrior::warriorArrowAttack(Warrior * uAAwarrior, int weaponnum, int nHour, int nMinute)
{
    int attackResult = uAAwarrior->Hurted(Arrow::arrowPower);
    updateWeapon(2);
    PrintArrowAttack(uAAwarrior, attackResult, nHour, nMinute);
    return attackResult;
}

void Warrior::PrintArrowAttack(Warrior * uAAwarrior, int attackResult, int nHour, int nMinute)
{
    WarriorPrintPre(nHour, nMinute);
    cout << " shot";
    if (attackResult == -1)		//  ������������
        cout << " and killed " << (uAAwarrior->pHeadquarter)->GetColor() << " " << product_s[uAAwarrior->kindNo] << " " << uAAwarrior->no;
    cout << endl;
}

int Warrior::warriorHasBomb()
{
    for (int i = 0; i < weaponCount; i++)
    {
        if (weapon[i]->getWeaponUseful() && weapon[i]->getWeaponNo() == 1)
            return i;
    }
    return -1;
}

void Warrior::warriorBombAttack(Warrior * uBAwarrior, int weaponnum, int nHour, int nMinute)
{
    updateWeapon(1);
    this->element -= this->element;
    uBAwarrior->element -= this->element;
    PrintBombAttack(uBAwarrior, nHour, nMinute);
}

void Warrior::PrintBombAttack(Warrior * uBAwarrior, int nHour, int nMinute)
{
    WarriorPrintPre(nHour, nMinute);
    cout << " used a bomb and killed " << (uBAwarrior->pHeadquarter)->GetColor();
    cout << " " << product_s[uBAwarrior->kindNo] << " " << uBAwarrior->no << endl;
}

int Warrior::warriorHasSword()
{
    for (int i = 0; i < weaponCount; i++)
    {
        if (weapon[i]->getWeaponUseful() && weapon[i]->getWeaponNo() == 0)
            return i;
    }
    return -1;
}

void Headquarter::Init(int color_, int lifevalue_)
{
    Color_C = color_;
    totalLifeValue = lifevalue_;
    totalWarriorNum = 0;
    stopped = false;
    curMakingSeqIdx = 0;
    occupation = 0;
    for (int i = 0; i < WARRIOR_NUM; i++)
        warriorNum[i] = 0;
}

Headquarter::~Headquarter()
{
    for (int i = 0; i < totalWarriorNum; i++)
        delete pWarriors[i];
}

int Headquarter::Produce(int nHour, int nMinute)
{
    int kindNo = makingSeq[Color_C][curMakingSeqIdx];
    
    if (Warrior::initialLifeValue[kindNo] > totalLifeValue)
        return 0;
    //����ʿ����
    totalLifeValue -= Warrior::initialLifeValue[kindNo];
    curMakingSeqIdx = (curMakingSeqIdx + 1) % WARRIOR_NUM;
    
    if (kindNo == 0)
        pWarriors[totalWarriorNum] = new Dragon(this, totalWarriorNum + 1, kindNo, (double)totalLifeValue / Warrior::initialLifeValue[kindNo]);
    else if (kindNo == 1)
        pWarriors[totalWarriorNum] = new Ninjia(this, totalWarriorNum + 1, kindNo);
    else if (kindNo == 2)
        pWarriors[totalWarriorNum] = new Iceman(this, totalWarriorNum + 1, kindNo);
    else if (kindNo == 3)
        pWarriors[totalWarriorNum] = new Lion(this, totalWarriorNum + 1, kindNo, totalLifeValue);
    else if (kindNo == 4)
        pWarriors[totalWarriorNum] = new Wolf(this, totalWarriorNum + 1, kindNo);
    
    if (Color_C == 0) Headquarter::cityN[0]->setredWarrior(pWarriors[totalWarriorNum]);
    else if (Color_C == 1) Headquarter::cityN[City::citytotal + 1]->setblueWarrior(pWarriors[totalWarriorNum]);
    
    warriorNum[kindNo]++;
    pWarriors[totalWarriorNum]->PrintProduce(nHour, nMinute);
    totalWarriorNum++;
    
    return 1;
}

void Headquarter::UpdateCityWarrior()								// ÿһ����ɾ����ʿ��������ʿ���н�, �����ʿ֮�����ʿ����city���и���
{
    for (int i = 0; i < totalWarriorNum; i++)
    {
        if (pWarriors[i] == NULL)
            continue;
        else if (pWarriors[i]->getAddrCity() < 0 || pWarriors[i]->getAddrCity() > (City::citytotal + 1))
        {
            pWarriors[i] = NULL;
            continue;
        }
        if (getColor() == 0 && pWarriors[i]->getAddrCity() <= City::citytotal)
            cityN[pWarriors[i]->getAddrCity()]->setredWarrior(pWarriors[i]);
        else if (getColor() == 1 && pWarriors[i]->getAddrCity() >= 1)
            cityN[pWarriors[i]->getAddrCity()]->setblueWarrior(pWarriors[i]);
        else if (getColor() == 0 && pWarriors[i]->getAddrCity() == (City::citytotal + 1) && pWarriors[i]->getNotReached())
        {
            occupation += 1;
            pWarriors[i]->setNotReached(false);
        }
        else if (getColor() == 1 && pWarriors[i]->getAddrCity() == 0 && pWarriors[i]->getNotReached())
        {
            occupation += 1;
            pWarriors[i]->setNotReached(false);
        }
    }
}

void Headquarter::PrintLifeValue(int nHour, int nMinute)
{
    cout << setfill('0') << setw(3) << nHour << ":" << setw(2) << nMinute << " ";
    cout << getTotalLifeValue() << " elements in " << GetColor() << " headquarter" << endl;
}

char * Headquarter::GetColor(void)
{
    return color[Color_C];
}

char * Weapon::weapon_list[WEAPON_NUM] = { (char *)"sword", (char *)"bomb", (char *)"arrow" };
char * Warrior::product_s[] = { (char *)"dragon", (char *)"ninja", (char *)"iceman", (char *)"lion", (char *)"wolf" };
int Warrior::initialLifeValue[WARRIOR_NUM];
int Warrior::initialForce[WARRIOR_NUM];
int Lion::decreaseLoyalty;
int City::citytotal;
City * Headquarter::cityN[CITY_NUM + 2];
int Headquarter::citiesN[CITY_NUM] = { 0 };
int Arrow::arrowPower;
int Headquarter::makingSeq[2][WARRIOR_NUM] = { { 2, 3, 4, 1, 0 },{ 3, 0, 1, 2, 4 } }; //����˾���ʿ������˳������
char * Headquarter::color[] = { (char *)"red", (char *)"blue" };

inline void Test_Print()
{
    for (int i = 0; i <= (City::citytotal + 1); i++)
        Headquarter::cityN[i]->PrintEachCityAfterExec();
    cout << endl;
}

int main()
{
    int t, M, N, nTime;
    int casecount = 1;
    Headquarter RedHead, BlueHead;
    
    cin >> t;
    //t = 1;
    
    while (t--)
    {
        cout << "Case " << casecount << ":" << endl;
        casecount++;
        
        cin >> M >> N >> Arrow::arrowPower >> Lion::decreaseLoyalty >> nTime;
        /*M = 1000; N = 2; Arrow::arrowPower = 10; Lion::decreaseLoyalty = 2100; nTime = 5000;*/
        /*Warrior::initialLifeValue[0] = 100; Warrior::initialLifeValue[1] = 100; Warrior::initialLifeValue[2] = 100;
         Warrior::initialLifeValue[3] = 100; Warrior::initialLifeValue[4] = 100;
         Warrior::initialForce[0] = 5; Warrior::initialForce[1] = 5; Warrior::initialForce[2] = 5; Warrior::initialForce[3] = 5;
         Warrior::initialForce[4] = 5;*/
        for (int i = 0; i < WARRIOR_NUM; i++)
            cin >> Warrior::initialLifeValue[i];
        for (int i = 0; i < WARRIOR_NUM; i++)
            cin >> Warrior::initialForce[i];
        
        RedHead.Init(0, M);
        BlueHead.Init(1, M);
        City::citytotal = N;
        for (int i = 0; i < (N + 2); i++)
            Headquarter::cityN[i] = new City(0, i);
        
        int nHour = 0;
        int nMinute = 0;
        int test = 0;
        bool end = true;
        
        /*cout << "һ��ʼ:" << endl;
         Test_Print();
         cout << endl;*/
        
        while (end && nTime >= 0)
        {
            if (nMinute == 0)													// (1) ��ʿ����
            {
                RedHead.Produce(nHour, nMinute);
                BlueHead.Produce(nHour, nMinute);
            }
            else if (nMinute == 5)												// (2) lion����
            {
                for (int i = 0; i <= N + 1; i++)
                    Headquarter::cityN[i]->CityRunAway(nHour, nMinute);
                
                RedHead.UpdateCityWarrior();
                BlueHead.UpdateCityWarrior();
            }
            else if (nMinute == 10)	// (3) ��ʿǰ����ĳһ����; (12) ��ʿ�ִ�о�˾�; (13) ˾���ռ��
            {
                int occupationFlag = -1;
                for (int i = 0; i <= N; i++)
                {
                    occupationFlag = Headquarter::cityN[i]->CityMarch(Headquarter::cityN[i + 1], nHour, nMinute);
                    if (occupationFlag == 0 || occupationFlag == 1)
                        end = false;
                }
                RedHead.UpdateCityWarrior();
                BlueHead.UpdateCityWarrior();
            }
            else if (nMinute == 20)												// ÿ�����в���10������Ԫ
            {
                for (int i = 1; i <= N; i++)
                    Headquarter::cityN[i]->CityAddLife();
            }
            else if (nMinute == 30)												// ���ĳ��������ֻ��һ����ʿ,��ô����ʿȡ�߸ó����е���������Ԫ,����������Щ����Ԫ���͵���������˾�
            {
                for (int i = 1; i <= N; i++)
                    Headquarter::cityN[i]->EarnLifeForHead(nHour, nMinute);
            }
            else if (nMinute == 35)												// (4) ��ʿ�ż�
            {
                for (int i = 1; i < N + 1; i++)
                    Headquarter::cityN[i]->CityArrowAttack(Headquarter::cityN[i - 1], Headquarter::cityN[i + 1], nHour, nMinute);
            }
            else if (nMinute == 38)												// (5) ��ʿʹ��bomb
            {
                for (int i = 1; i < N + 1; i++)
                    Headquarter::cityN[i]->CityBombAttack(nHour, nMinute);
            }
            else if (nMinute == 40)				// (6) ��ʿ��������; (7) ��ʿ����; (8) ��ʿս��; (9) ��ʿ����; (10) ��ʿ��ȡ����Ԫ; (11) ��������
            {
                for (int i = 0; i < N + 1; i++)
                    Headquarter::cityN[i]->CityBattle(nHour, nMinute); // �ж�ս�����, = 0: ����ʿʤ; = 1: ����ʿʤ; = -1: û����ʿ��������û�н�ս; = 2: ����ʿսǰ�Ѿ�������, ����ʿ�൱��ʤ��; = 3: ����ʿսǰ�Ѿ�������, ����ʿ�൱��ʤ��; = 4: ����ʿ������ʿսǰ����������ը��
                RedHead.UpdateCityWarrior();
                BlueHead.UpdateCityWarrior();
                int redAwardResult = 1;
                int blueAwardResult = 1;
                for (int i = 1; i <= N && blueAwardResult == 1; i++)	// ʵ���ԵĽ�����ʤ����ʿ, �����Ƚ���city��С����췽������ʿ; �췽�Ƚ���city�Ŵ�������������ʿ
                    blueAwardResult = Headquarter::cityN[i]->CityAwardWarrior(1);		// ���� = 0: ��������ʿ; = 1: ��������ʿ
                for (int i = N; i >= 1 && redAwardResult == 1; i--)
                    redAwardResult = Headquarter::cityN[i]->CityAwardWarrior(0);
                for (int i = 1; i <= N; i++)	// ʵ����ΪHeadquarterӮȡ����Ԫ
                    Headquarter::cityN[i]->EarnLifeForHead(nHour, nMinute, 1);
            }
            else if (nMinute == 50)												// (14) ˾���������Ԫ����
            {
                RedHead.PrintLifeValue(nHour, nMinute);
                BlueHead.PrintLifeValue(nHour, nMinute);
            }
            else if (nMinute == 55)												// (15) ��ʿ�����������
            {
                for (int i = 0; i < N + 2; i++)
                    Headquarter::cityN[i]->CityReportWeapon(nHour, nMinute, 0);
                for (int i = 0; i < N + 2; i++)
                    Headquarter::cityN[i]->CityReportWeapon(nHour, nMinute, 1);
            }
            
            nMinute += 1;
            nTime -= 1;
            test += 1;
            if (nMinute == 60)
            {
                nMinute = 0;
                nHour += 1;
            }
        }
    }
    system("pause");
    return 0;
}
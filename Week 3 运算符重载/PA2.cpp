#include<iostream>
#include<cstring>
#include<cstdlib>
#include <string>
#include <algorithm>//reverse函数所需添加的头文件
using namespace std;

class Complex {
private:
	double r, i;
public:
	Complex(double real = 0.0, double imag = 0.0): r(real), i(imag) {}

	void Print(){
		cout << r << "+" << i << "i" << endl;
	}

	Complex operator+(const Complex& );
	Complex operator-(const Complex& );

	Complex& operator=(const string &s){
		int pos = s.find("+", 0);
		string sTmp = s.substr(0, pos);
		r = atof(sTmp.c_str());
		sTmp = s.substr(pos+1, s.length()-pos-2);
		i = atof(sTmp.c_str());
		return *this;
	}
};
Complex Complex::operator+(const Complex& c){
	return Complex(r+c.r, i+c.i);
}
Complex Complex::operator-(const Complex& c){
	return Complex(r-c.r, i-c.i);
}

class MyInt {
    int nVal;
    public:
        MyInt(int n) { nVal = n; }
        int ReturnVal() { return nVal; }

		MyInt& operator-(int c){
			nVal -= c;
			return *this;
		}
};

class Array2
{
private:
    int row;
    int column;
    int* ptr;
public:
    Array2()
    {
        ptr = NULL;
    }
    Array2(int paraRow, int paraColumn):row(paraRow),column(paraColumn)
    {
        ptr = new int[row * column];
    }
    Array2(Array2& a):row(a.row),column(a.column)
    {
		if (!a.ptr){
			ptr = NULL;
			row = 0;
			column = 0;
			return;
		}
        ptr = new int[row * column];
        memcpy(ptr, a.ptr, sizeof(int)*row*column);
    }
    Array2& operator= (const Array2 &a)
    {
		if (ptr == a.ptr)
			return *this;
		if (a.ptr == NULL){
			if (ptr) delete []ptr;
			ptr = NULL;
			row = 0;
			column = 0;
			return *this;
		}
        if (ptr) delete[] ptr;
        row = a.row;
        column = a.column;
        ptr = new int[row * column];
        memcpy(ptr, a.ptr, sizeof(int)*row*column);
        return *this;
    }
    ~Array2()
    {
        if (ptr) delete[] ptr;
    }
    int* operator [] (int i)
    {
        return ptr + i*column;
    }
    int& operator() (int i, int j)
    {
        return ptr[i*column + j];
    }
};

class BigInt
{
private:
    string values;//保存所有位上的数字
    bool flag;//true表示正数，false表示负数，0默认为正数
    inline int compare(string s1, string s2)
    {
        if(s1.size() < s2.size())
            return -1;
        else if(s1.size() > s2.size())
            return 1;
        else
            return s1.compare(s2);
    }
public:
    BigInt():values("0"),flag(true){};
    BigInt(string str)//类型转换构造函数(默认为正整数)
    {
        values = str;
        flag = true;
    }
public:
    friend ostream& operator << (ostream& os, const BigInt& bigInt);//重载输出操作符
    friend istream& operator>>(istream& is, BigInt& bigInt);//输入操作符重载
    BigInt operator+(const BigInt& rhs);//加法操作重载
    BigInt operator-(const BigInt& rhs);//减法操作重载
    BigInt operator*(const BigInt& rhs);//乘法操作重载
    BigInt operator/(const BigInt& rhs);//除法操作重载
};
/* 重载流提取运算符'>>'，输出一个整数 */
ostream& operator << (ostream& os, const BigInt& bigInt)
{
    if (!bigInt.flag)
    {
        os << '-';
    }
    os << bigInt.values;
    return os;
}
/* 重载流插入运算符'>>'，输入一个正整数 */
istream& operator >> (istream& is, BigInt& bigInt)
{
    string str;
    is >> str;
    bigInt.values = str;
    bigInt.flag = true;
    return is;
}
/* 两个正整数相加 */
BigInt BigInt::operator+(const BigInt& rhs)
{
    BigInt ret;
    ret.flag = true;//正整数相加恒为正数
    string lvalues(values), rvalues(rhs.values);
    //处理特殊情况
    if (lvalues == "0")
    {
        ret.values = rvalues;
        return ret;
    }
    if (rvalues == "0")
    {
        ret.values = lvalues;
        return ret;
    }
    //调整s1与s2的长度
    unsigned int i, lsize, rsize;
    lsize = lvalues.size();
    rsize = rvalues.size();
    if (lsize < rsize)
    {
        for (i = 0; i < rsize - lsize; i++)//在lvalues左边补零
        {
            lvalues = "0" + lvalues;
        }
    }
    else
    {
        for (i = 0; i < lsize - rsize; i++)//在rvalues左边补零
        {
            rvalues = "0" + rvalues;
        }
    }
    
    int n1, n2;
    n2 = 0;
    lsize = lvalues.size();
    string res = "";
    reverse(lvalues.begin(), lvalues.end());//颠倒字符串，以方便从低位算起计算
    reverse(rvalues.begin(), rvalues.end());
    for (i = 0; i < lsize; i++)
    {
        n1 = (lvalues[i] - '0' + rvalues[i] - '0' + n2) % 10;//n1代表当前位的值
        n2 = (lvalues[i] - '0' + rvalues[i] - '0' + n2) / 10;//n2代表进位
        res = res + char(n1 + '0');
    }

    if (n2 == 1)
    {
        res = res + "1";
    }
    reverse(res.begin(), res.end());

    ret.values = res;
    return ret;
}
/* 两个正整数相减 */
BigInt BigInt::operator-(const BigInt& rhs)
{
    BigInt ret;
    string lvalues(values), rvalues(rhs.values);
    //处理特殊情况
    if (rvalues == "0")
    {
        ret.values = lvalues;
        ret.flag = true;
        return ret;
    }
    if (lvalues == "0")
    {
        ret.values = rvalues;
        ret.flag = false;
        return ret;
    }
    //调整s1与s2的长度
    unsigned int i, lsize, rsize;
    lsize = lvalues.size();
    rsize = rvalues.size();
    if (lsize < rsize)
    {
        for (i = 0; i < rsize - lsize; i++)//在lvalues左边补零
        {
            lvalues = "0" + lvalues;
        }
    }
    else
    {
        for (i = 0; i < lsize - rsize; i++)//在rvalues左边补零
        {
            rvalues = "0" + rvalues;
        }
    }
    //调整使‘-’号前边的数大于后边的数
    int t = lvalues.compare(rvalues);//相等返回0，str1<str2返回负数，str1>str2返回正数
    if (t < 0)
    {
        ret.flag = false;
        string tmp = lvalues;
        lvalues = rvalues;
        rvalues = tmp;      
    }
    else if (t == 0)
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }
    else
    {
        ret.flag = true;
    }
    
    unsigned int j;
    lsize = lvalues.size();
    string res = "";
    reverse(lvalues.begin(), lvalues.end());//颠倒字符串，以方便从低位算起计算
    reverse(rvalues.begin(), rvalues.end());
    for (i = 0; i < lsize; i++)
    {
        if (lvalues[i] < rvalues[i])//不足，向前借一维
        {
            j = 1;
            while(lvalues[i+j] == '0')
            {
                lvalues[i+j] = '9';
                j++;
            }
            lvalues[i+j] -= 1;
            res = res + char(lvalues[i] + ':' - rvalues[i]);
        } 
        else
        {
            res = res + char(lvalues[i] - rvalues[i] + '0');
        }
    }
    reverse(res.begin(), res.end());
    res.erase(0, res.find_first_not_of('0'));//去掉前导零

    ret.values = res;   
    return ret;
}
/* 两个正整数相乘 */
BigInt BigInt::operator*(const BigInt& rhs)
{
    BigInt ret;
    string lvalues(values), rvalues(rhs.values);
    //处理特殊情况
    if (lvalues == "0" || rvalues == "0")
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }

    unsigned int lsize, rsize;
    lsize = lvalues.size();
    rsize = rvalues.size();
    string temp;
    BigInt res, itemp; 
    //让lvalues的长度最长
    if (lvalues < rvalues)
    {
        temp = lvalues; 
        lvalues = rvalues; 
        rvalues = temp;
        lsize = lvalues.size(); 
        rsize = rvalues.size();
    }
    
    int i, j, n1, n2, n3, t;
    reverse(lvalues.begin(), lvalues.end());//颠倒字符串
    reverse(rvalues.begin(), rvalues.end());
    for (i = 0; i < rsize; i++)
    {
        temp = "";
        n1 = n2 = n3 = 0;
        for (j = 0; j < i; j++)
        {
            temp = temp + "0";
        }
        n3 = rvalues[i] - '0';
        for (j = 0; j < lsize; j++)
        {
            t = (n3*(lvalues[j] - '0') + n2);
            n1 = t % 10;//n1记录当前位置的值
            n2 = t / 10;//n2记录进位的值
            temp = temp + char(n1 + '0');
        }
        if (n2)
        {
            temp = temp + char(n2 + '0');
        }
        reverse(temp.begin(), temp.end());
        itemp.values = temp;
        res = res + itemp;
    }

    ret = res;
    return ret;
}
/* 两个正整数相除 */
BigInt BigInt::operator/(const BigInt& rhs)
{
    BigInt ret;
    string lvalues(values), rvalues(rhs.values);
    string quotient;
    //处理特殊情况
    if(rvalues == "0")
    {
        ret.values = "error";//输出错误
        ret.flag = true;
        return ret;
    }
    if(lvalues == "0")
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }

    if(compare(lvalues, rvalues) < 0)
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }
    else if(compare(lvalues, rvalues) == 0)
    {
        ret.values = "1";
        ret.flag = true;
        return ret;
    }
    else
    {
       
        string temp;
        unsigned int lsize, rsize;
        lsize = lvalues.size();
        rsize = rvalues.size();
        int i;
        if(rsize > 1) temp.append(lvalues, 0, rsize-1);
        for(i = rsize - 1; i < lsize; i++)
        {
            temp = temp + lvalues[i];
            //试商
            for(char c = '9'; c >= '0'; c--)
            {
                BigInt t = (BigInt)rvalues * (BigInt)string(1, c);
                BigInt s = (BigInt)temp - t;

                if(s.flag == true)
                {
                    temp = s.values;
                    quotient = quotient + c;
                    break;
                }
            }
        }
    }
    //去除前导零
    quotient.erase(0, quotient.find_first_not_of('0'));
    ret.values = quotient;
    ret.flag = true;
    return ret;
}

int main() {
    Complex a, b, c ,d;
    a = "3+4i"; a.Print();
    b = "5+6i"; b.Print();
	c = a + b; c.Print();
	d = a - b; d.Print();

    MyInt objInt(10);
    objInt-2-1-3;
    cout << objInt.ReturnVal();
    cout <<",";
    objInt-2-1;
    cout << objInt.ReturnVal() << endl;

    Array2 an(3,4);
    int i,j;
    for( i = 0;i < 3; ++i )
        for( j = 0; j < 4; j ++ )
            an[i][j] = i * 4 + j;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << an(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 bn; bn = an;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << bn[i][j] << ",";
        }
        cout << endl;
    }
	cout << "next" << endl;
	Array2 cn = Array2(an);
	for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << cn[i][j] << ",";
        }
        cout << endl;
    }

    BigInt am,bm,result;
    char op;
    cin >> am >> op >> bm;
    switch(op)
    {
        case '+':result = am + bm; break;
        case '-':result = am - bm; break;
        case '*':result = am * bm; break;
        case '/':result = am / bm; break;
        default:break;
    }
    cout << result << endl;

	system("pause");
    return 0;
}
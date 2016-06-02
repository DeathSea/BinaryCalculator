#include <string>
#include <stdexcept>

#define MAXDIGIT 256
bool baseBinAdd(bool Ai, bool Bi, bool Ci, bool &Cip1);
template <typename type>
inline type max(type A, type B){ return A > B ? A : B; }
template <typename type>
inline type min(type A, type B){ return A > B ? B : A; }
class BinNum
{
private:
	bool isZero();
	bool TestHighisZero();
public :
	bool sign;
	bool HighisZero;
	bool * Low;
	bool * High;
	BinNum(bool * N,unsigned int Length,bool sign = false);
	BinNum(BinNum &B);
	BinNum();
	~BinNum();
	BinNum Complement();
	//BinNum LeftShift(int shift);
	BinNum operator + (BinNum &B);
	BinNum operator - (BinNum &B);
	BinNum operator / (BinNum &B);
	BinNum operator * (BinNum &B);
	BinNum operator % (BinNum &B);
	BinNum operator << (int shift);
	BinNum operator >> (int shift);
	bool operator == (BinNum &B);
	friend int BinCmp(BinNum &A, BinNum&B);
	friend BinNum ExGCD(BinNum A, BinNum B,BinNum & x,BinNum &y);
	friend BinNum ModNsquare(BinNum &A, BinNum &B, BinNum &n);
	friend BinNum ModMutli(BinNum &A, BinNum &B, BinNum &n);
};
int BinCmp(BinNum &A,BinNum &B);
BinNum ExGCD(BinNum A, BinNum B,BinNum &x,BinNum &y);
BinNum ModNsquare(BinNum &A, BinNum &B, BinNum &n);

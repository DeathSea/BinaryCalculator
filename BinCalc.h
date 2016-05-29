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
	bool Low[MAXDIGIT];
	bool High[MAXDIGIT];
	bool HighisZero;
	bool sign;
	bool isZero();
public :
	BinNum(bool * N,unsigned int Length,bool sign = false);
	BinNum(BinNum &B);
	~BinNum();
	BinNum Complement();
	//BinNum LeftShift(int shift);
	BinNum operator + (BinNum &B);
	BinNum operator - (BinNum &B);
	BinNum operator / (BinNum &B);
	BinNum operator * (BinNum &B);
	BinNum operator % (BinNum &B);
	BinNum operator << (int shift);
	friend int BinCmp(BinNum &A, BinNum&B);
	friend BinNum ExGCD(BinNum A, BinNum B,BinNum & x,BinNum &y);
};
int BinCmp(BinNum &A,BinNum &B);
BinNum ExGCD(BinNum A, BinNum B,BinNum &x,BinNum &y);
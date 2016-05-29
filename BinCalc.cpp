#include "BinCalc.h"
int BinCmp(BinNum &A, BinNum &B)
{
	if (A.sign == false && B.sign == true)return 1;
	else if (A.sign == true && B.sign == false)return -1;
	int Aindex = 0; int Bindex = 0;
	if (!A.HighisZero && !B.HighisZero)
	{
		while (Aindex != MAXDIGIT)
		{
			if (A.High[Aindex] && !B.High[Bindex])return 1;
			if (!A.High[Aindex] && B.High[Bindex])return -1;
			Aindex++; Bindex++;
		}
	}
	else if (A.HighisZero && !B.HighisZero)
	{
		Bindex = 0;
		while (Bindex != MAXDIGIT)
		{
			if (B.High[Bindex])return -1;
			Bindex++;
		}
	}
	else if (!A.HighisZero && B.HighisZero)
	{
		Aindex = 0;
		while (Aindex != MAXDIGIT)
		{
			if (A.High[Aindex])return 1;
			Aindex++;
		}
	}
	else if (A.HighisZero && B.HighisZero)
	{
		Aindex = 0; Bindex = 0;
		while (Aindex != MAXDIGIT)
		{
			if (A.Low[Aindex] && !B.Low[Bindex])return 1;
			if (!A.Low[Aindex] && B.Low[Bindex])return -1;
			Aindex++; Bindex++;
		}
		return 0;
	}
	return 0;
}
bool baseBinAdd(bool Ai, bool Bi, bool Ci, bool &Cip1)
{
	bool S = Ai ^ Bi ^ Ci;
	Cip1 = (Ai & Bi) | (Bi & Ci) | (Ci & Ai);
	return S;
}
BinNum::BinNum(bool *Sour,unsigned int length, bool sign )
{
	if (length > MAXDIGIT)
	{
		throw std::length_error("Too Long Binary Num");
	}
	memset(this->Low, false, MAXDIGIT);
	memset(this->High, false, MAXDIGIT);
	this->HighisZero = true;
	if (Sour)
	{
		memmove_s(this->Low + MAXDIGIT - length, MAXDIGIT, Sour, length);
	}
	this->sign = sign;
}
BinNum::BinNum(BinNum&B)
{
	memmove_s(this->Low, MAXDIGIT, B.Low, MAXDIGIT);
	if (!this->HighisZero){ memmove_s(this->High, MAXDIGIT, B.High, MAXDIGIT); }
	else{ memset(this->High, false, MAXDIGIT); }
	this->sign = B.sign;
	this->HighisZero = B.HighisZero;
}
BinNum::~BinNum()
{
	memset(this->Low,false,MAXDIGIT);
	memset(this->High, false, MAXDIGIT);
	this->sign = false;
}
bool BinNum::isZero()
{
	bool t = false; int index = 0;
	while (index < MAXDIGIT){ t |= Low[index]; index++; }
	if (!this->HighisZero)
	{
		index = 0;
		while (index < MAXDIGIT){ t |= High[index]; index++; }
	}
	return !t;
}

BinNum BinNum::operator+(BinNum &B)
{
	bool * NewN = NULL;
	BinNum R = BinNum(NewN, MAXDIGIT);
	bool C = false;
	for (int index = MAXDIGIT - 1; index >= 0; index--)
	{
		R.Low[index] = baseBinAdd(this->Low[index], B.Low[index], C, C);
	}
	if (!this->HighisZero)
	{
		R.HighisZero = false;
		if (!B.HighisZero)
		{
			for (int index = MAXDIGIT - 1; index >= 0; index--)
			{
				R.High[index] = baseBinAdd(this->High[index], B.High[index], C, C);
			}
		}
		else
		{
			for (int index = MAXDIGIT - 1; index >= 0; index--)
			{
				R.High[index] = baseBinAdd(this->High[index], false, C, C);
			}
		}
	}
	R.sign = baseBinAdd(this->sign, B.sign, C, C);
	return R;
}
BinNum BinNum::Complement()
{
	if (this->sign == false)
	{
		BinNum R = BinNum(*this);
		return R;
	}
	else
	{
		BinNum R = BinNum(NULL, MAXDIGIT, true);
		bool C = true;
		for (int index = MAXDIGIT - 1; index >= 0; index--)
		{
			R.Low[index] = baseBinAdd(!this->Low[index], false, C, C);
		}
		if (!this->HighisZero)
		{
			R.HighisZero = false;
			for (int index = MAXDIGIT - 1; index >= 0; index--)
			{
				R.High[index] = baseBinAdd(!this->High[index], false, C, C);
			}
		}
		R.sign = this->sign;
		return R;
	}
}
BinNum BinNum::operator-(BinNum &B)
{
	BinNum CB = BinNum(B);
	CB.sign = true;
	CB = CB.Complement();
	return *this + CB;
}
BinNum BinNum::operator<<(int shift)
{
	BinNum R = BinNum(NULL,MAXDIGIT,this->sign);
	R.HighisZero = true;
	int index = 0;
	memmove_s(R.Low, MAXDIGIT, this->Low + shift, MAXDIGIT - shift);
	if (!this->HighisZero)
	{
		for (index = 0; index + shift < MAXDIGIT; index++)
		{
			R.High[index] = this->High[index + shift];
		}
	}
	for (int Lindex = 0, index = MAXDIGIT - shift; index < MAXDIGIT; index++, Lindex++)
	{
		R.High[index] = this->Low[Lindex];
	}
	return R;
}
BinNum BinNum::operator*(BinNum &B)
{
	BinNum Result = BinNum(NULL, MAXDIGIT);
	Result.HighisZero = false;
	BinNum RA = BinNum(*this); RA.HighisZero = false;
	BinNum RB = BinNum(B); RB.HighisZero = false;
	int Lindex = MAXDIGIT - 1;
	while (Lindex >= 0)
	{
		if (RB.Low[Lindex] == true)
		{
			Result = Result + RA;
		}
		RA = RA << 1;
		Lindex--;
	}
	return Result;
}
BinNum BinNum::operator/(BinNum &B)
{
	BinNum Result = BinNum(NULL, MAXDIGIT, false);
	if (this->isZero()){ return Result; }
	if (B.isZero()){ return Result; }
	if (BinCmp(*this, B) == -1)
	{
		return Result;
	}
	BinNum x = BinNum(B);
	BinNum y = BinNum(NULL, MAXDIGIT, false);
	y.Low[MAXDIGIT - 1] = true;
	while (BinCmp(*this, x << 1) != -1)
	{
		x = x << 1;
		y = y << 1;
	}
	return (*this - x) / B + y;
}
BinNum BinNum::operator%(BinNum &B)
{
	BinNum Result = BinNum(NULL, MAXDIGIT, false);
	if (this->isZero()){ return Result; }
	if (B.isZero()){ return *this; }
	if (BinCmp(*this, B) == -1)
	{
		return *this;
	}
	BinNum x = BinNum(B);
	while (BinCmp(*this, x << 1) != -1)
	{
		x = x << 1;
	}
	return (*this - x) % B;
}

BinNum ExGCD(BinNum A, BinNum B, BinNum &x, BinNum &y)
{
	if (B.isZero())
	{
		memset(x.Low, false, MAXDIGIT);
		x.Low[MAXDIGIT - 1] = true;
		memset(y.Low, false, MAXDIGIT);
		return A;
	}
	else
	{
		BinNum r = ExGCD(B, A%B, x, y);
		BinNum t = BinNum(x);
		x = BinNum(y);
		y = t - (A / B) * y;
		return r;
	}
}

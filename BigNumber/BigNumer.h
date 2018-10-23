#pragma once

#include <vector>
using namespace System;
typedef System::Numerics::BigInteger BI;

#define _base_num 1'000'000'000
#define _bbase_dn 100'000'000

class BigNumer
{
public:
	BigNumer();
	BigNumer(int);
	BigNumer(const BigNumer&);
	BigNumer(const char*);// обработать дробь
	~BigNumer();


	BigNumer& operator =(const char*);// обработать дробь
	BigNumer& operator =(const BigNumer&);

	BigNumer& operator ++();
	BigNumer& operator +(const BigNumer&);
	BigNumer& operator +=(const BigNumer&);

	BigNumer& operator -() const;
	BigNumer& operator -(const BigNumer&);
	BigNumer& operator -=(const BigNumer&);

	BigNumer& operator *(BigNumer&);
	BigNumer& operator *=(BigNumer&);

	BigNumer& operator /(int); // div short (int < base)
	BigNumer& operator /(BigNumer&);
	BigNumer& operator /=(BigNumer&);

	bool operator ==(BI) const;
	bool operator ==(char*) const;
	bool operator >=(const BigNumer&) const;

	char* c_str() const;
	static char* ToCString(System::String^);
	static char* substring(const char*, int, int);
	inline static char getVal(const char*, int);
	inline static bool max(int, int);
	bool sign() const;
	bool iszero() const;

	int percision;

private:
	BigNumer& sum(const BigNumer&, const BigNumer&);
	BigNumer& sub(const BigNumer&, const BigNumer&);
	BigNumer& mul(const BigNumer&, const BigNumer&);
	BigNumer& div(const BigNumer&, const BigNumer&);


	int countnumeral(int) const;
	void shifta(int);
	void shiftd(int, int);


	typedef std::vector<int> vn;

	vn a;
	vn d;
};


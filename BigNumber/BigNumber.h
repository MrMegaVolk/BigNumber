#pragma once

#include <vector>

#define _base_num 1'000'000'000
#define _digits_base_num 9
#define _bbase_dn 100'000'000

#define kuBase 1'000'000'000
#define kcchBase 9
#define kcbitUint 32

typedef unsigned int ui;
typedef unsigned long long int ull;

class BigNumber {

#ifdef __cplusplus_cli
	typedef System::Numerics::BigInteger BI;
#endif // __cplusplus_cli

#pragma region methods
public:
	BigNumber();
	BigNumber(int);
	BigNumber(BigNumber&);
	BigNumber(const char*);// обработать дробь
	~BigNumber();



	BigNumber& operator =(const char*);// обработать дробь
	BigNumber& operator =(BigNumber&);

	BigNumber& operator ++();
	BigNumber& operator ++(int);
	BigNumber& operator +(BigNumber&);
	BigNumber& operator +=(BigNumber&);

	BigNumber& operator -();
	BigNumber& operator -(BigNumber&);
	BigNumber& operator -=(BigNumber&);

	BigNumber& operator *(BigNumber&);
	BigNumber& operator *=(BigNumber&);

	//BigNumber& operator /(int); // div short (int < base)
	BigNumber& operator /(BigNumber&);
	BigNumber& operator /=(BigNumber&);



#ifdef __cplusplus_cli
	bool operator ==(BI) const;
#endif // ==(BI)
	bool operator ==(char*) const;
	bool operator >=(const BigNumber&) const;



	char* c_str() const;
#ifdef __cplusplus_cli
	static char* ToCString(System::String^);
#endif // ToCString(BI)
	static char* substring(const char*, int, int);
	inline static char getVal(const char*, int);
	inline static bool ___max(int, int);
	int size() const;
	int symbols() const;



	bool IsEven();
	bool IsOne();
	//bool IsPowerOfTwo();
	bool IsZero();
	bool Sing();


private:

	BigNumber& sum(BigNumber&); // +
	BigNumber& sumA(BigNumber&); // +=

	BigNumber& sub(BigNumber&); // -
	BigNumber& subA(BigNumber&); // -=

	BigNumber& mul(BigNumber&); // *
	BigNumber& mulA(BigNumber&); // *=

	BigNumber& div(BigNumber&); // /
	BigNumber& divA(BigNumber&);// /=


	void ReSizeTmpInteger(int&, int&, BigNumber&);
	void ReSizeTmpDecimal(int&, int&, BigNumber&);
	int countnumeral(int) const;
	void shifta(int);
	void shiftd(int, int);
#pragma endregion

#pragma region variables
public:
	static ui count;
	ui percision;

private:
	std::vector<ui> integer;
	std::vector<ui> decimal;

	int sign : 2;
	int _sign : 2;

	BigNumber* tmp;
#pragma endregion
};


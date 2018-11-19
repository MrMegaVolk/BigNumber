#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>

using namespace std;
typedef unsigned int ui;

#ifdef __cplusplus_cli
	using namespace System;
	using namespace System::Threading;
	typedef System::Numerics::BigInteger BI;
#endif // namspace System

#define i_f        12'395
#define i_s 2'147'483'647

#define sumstr1 "2147496042"
#define sumstr2 "-2147496042"
#define substr1 "2147471252"
#define substr2 "-2147471252"

#define mulstr1 "26618059804565"
#define mulstr2 "26618059804565"

#define divstr   "0.000005771871"
#define mdivstr "-0.000005771871"

#define SUMCOUNT  100'000
#define SUMCOUNTL 100'000
#define SUBCOUNT  100'000
#define SUBCOUNTL 100'00
#define MULCOUNT  1500
#define DIVCOUNT  15

#define _SUM_ 1
#define _SUB_ 0
#define _MUL_ 0
#define _DIV_ 0

// color
HANDLE hConsole;
#define Red 12
#define Green 10
#define Magenta 13

#pragma region BigNumber
	#include "BigNumber.h"

	template<typename T>
	void Color(T val, int color) {
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | color));
		cout << val;
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
	}

	void FillSpace(BigNumber& val) {
		int space = 10 - val.symbols();
		for (;--space >= 0;)
			cout << " ";
	}

	void FirstTest(char* str, BigNumber& rs1,
#ifdef __cplusplus_cli
	 BI& rs2, 
#endif // __cplusplus_cli
		char* cmp = NULL) {
		bool sign1 = str[4] == '+' ? false : true;
		bool sign2 = str[5] == '+' ? false : true;
	
		int sign;
		if (str[0] == 'S')
			if (str[2] == 'm')
				sign = 0;
			else
				sign = 1;
		else if (str[0] == 'M')
			sign = 2;
		else
			sign = 3;

		cout << str;
#ifdef __cplusplus_cli
		if ((cmp != NULL && rs1 == cmp) || rs1 == rs2) {
#else
		if (rs1 == cmp) {
#endif // __cplusplus_cli
			Color("success", Green);

			if (rs1.Sing())
				cout << ": ";
			else
				cout << ":  ";

			cout << rs1.c_str();
		}
		else {
			Color("failed", Red);

			if (rs1.Sing())
				cout << " : ";
			else
				cout << " :  ";

			FillSpace(rs1);
			cout << rs1.c_str();
		}

#pragma region nstr
		char nstr[19];
		nstr[0] = ' ';
		nstr[1] = '<';

		if (sign1)
			nstr[2] = '-';
		else
			nstr[2] = ' ';

		nstr[3] = '1';
		nstr[4] = ' ';

		if (sign == 0)
			nstr[5] = '+';
		else if (sign == 1)
			nstr[5] = '-';
		else if (sign == 2)
			nstr[5] = '*';
		else
			nstr[5] = '/';

		nstr[6] = ' ';

		if (sign2)
			nstr[7] = '-';
		else
			nstr[7] = ' ';

		nstr[8] = '3';
		nstr[9] = '|';

		if (sign1)
			nstr[10] = '-';
		else
			nstr[10] = ' ';

		nstr[11] = '2';
		nstr[12] = ' ';

		if (sign == 0)
			nstr[13] = '+';
		else if (sign == 1)
			nstr[13] = '-';
		else if (sign == 2)
			nstr[13] = '*';
		else
			nstr[13] = '/';

		nstr[14] = ' ';

		if (sign2)
			nstr[15] = '-';
		else
			nstr[15] = ' ';

		nstr[16] = '4';
		nstr[17] = '>';
		nstr[18] = 0;
#pragma endregion

		cout << nstr;
		if (cmp != NULL) {
			if (cmp[0] == '-')
				cout << " ";
			else
				cout << "  ";

			cout << cmp << endl;
		}
		else {
#ifdef __cplusplus_cli
			if (rs2.Sign < 0)
				cout << " ";
			else
				cout << "  ";

			cout << BigNumber::ToCString(rs2.ToString()) << endl;
#endif // __cplusplus_cli
		}
	}

	void Init() {
		BigNumber a(i_f);
		BigNumber b(i_s);

#ifdef __cplusplus_cli
		BI  c(i_f);
		BI  d(i_s);
#endif // __cplusplus_cli

		cout << "Init + ";
#ifdef __cplusplus_cli
		if (a == c && b == d)
#else  
		char* buf = new char[11];
		if (a == itoa(i_f, buf, 10) && b == itoa(i_s, buf, 10))
#endif // __cplusplus_cli
			Color("success", Green);
		else
			Color("failed", Red);
		cout << ": ";

#ifdef __cplusplus_cli
		cout << " " << a.c_str() << " <1|2>  " << BigNumber::ToCString(c.ToString()) << " <2|3> ";
		cout << " " << b.c_str() << " <3|4>  " << BigNumber::ToCString(d.ToString()) << endl;
#else  
		cout << a.c_str() << " <1|2";
		cout << b.c_str() << endl;
#endif // __cplusplus_cli

		BigNumber e(-i_f);
		BigNumber f(-i_s);

#ifdef __cplusplus_cli
		BI  g(-i_f);
		BI  h(-i_s);
#endif // __cplusplus_cli

		cout << "Init - ";
#ifdef __cplusplus_cli
		if (e == g && f == h)
#else  
		char* buf = new char[12];
		if (e == itoa(-i_f, buf, 10) && f == itoa(-i_s, buf, 10))
#endif // __cplusplus_cli
			Color("success", Green);
		else
			Color("failed", Red);
		cout << ": ";

#ifdef __cplusplus_cli
		cout << e.c_str() << " <1|2> " << BigNumber::ToCString(g.ToString()) << " <2|3> ";
		cout << f.c_str() << " <3|4> " << BigNumber::ToCString(h.ToString()) << endl;
#else  
		cout << e.c_str() << " <1|2";
		cout << f.c_str() << endl;
#endif // __cplusplus_cli
	}
	void Sum() {
#ifdef __cplusplus_cli
		BigNumber a(i_f);
		BigNumber b(i_s);
		BigNumber rs1;
		BI  c(i_f);
		BI  d(i_s);
		BI rs2;

		if (_SUM_) {
			rs1 = a + b;
			rs2 = BI::Add(c, d);
			FirstTest("Sum ++ ", rs1, rs2);
		}

		if (_SUB_) {
			rs1 = a + -b;
			rs2 = BI::Add(c, -d);
			FirstTest("Sum +- ", rs1, rs2);
		}

		if (_SUB_) {
			rs1 = -a + b;
			rs2 = BI::Add(-c, d);
			FirstTest("Sum -+ ", rs1, rs2);
		}

		if (_SUM_) {
			rs1 = -a + -b;
			rs2 = BI::Add(-c, -d);
			FirstTest("Sum -- ", rs1, rs2);
		}
#else  
		BigNumber a(i_f);
		BigNumber b(i_s);
		BigNumber rs1;

		rs1 = a + b;
		FirstTest("Sum ++ ", rs1, sumstr1);

		rs1 = a + -b;
		FirstTest("Sum +- ", rs1, substr1);

		rs1 = -a + b;
		FirstTest("Sum -+ ", rs1, substr2);

		rs1 = -a + -b;
		FirstTest("Sum -- ", rs1, sumstr1);
#endif // __cplusplus_cli
	}
	void Sub() {
#ifdef __cplusplus_cli
		BigNumber a(i_f);
		BigNumber b(i_s);
		BigNumber rs1;
		BI  c(i_f);
		BI  d(i_s);
		BI rs2;

		if (_SUB_) {
			rs1 = a - b;
			rs2 = BI::Subtract(c, d);
			FirstTest("Sub ++ ", rs1, rs2);
		}

		if (_SUM_) {
			rs1 = a - -b;
			rs2 = BI::Subtract(c, -d);
			FirstTest("Sub +- ", rs1, rs2);
		}

		if (_SUM_) {
			rs1 = -a - b;
			rs2 = BI::Subtract(-c, d);
			FirstTest("Sub -+ ", rs1, rs2);
		}

		if (_SUB_) {
			rs1 = -a - -b;
			rs2 = BI::Subtract(-c, -d);
			FirstTest("Sub -- ", rs1, rs2);
		}
#else  
		BigNumber a(i_f);
		BigNumber b(i_s);
		BigNumber rs1;

		rs1 = a - b;
		FirstTest("Sub ++ ", rs1, substr1);

		rs1 = a - -b;
		FirstTest("Sub +- ", rs1, sumstr1);

		rs1 = -a - b;
		FirstTest("Sub -+ ", rs1, sumstr2);

		rs1 = -a - -b;
		FirstTest("Sub -- ", rs1, substr2);
#endif // __cplusplus_cli
	}
	void Mul() {
#ifdef __cplusplus_cli
		BigNumber a(i_f);
		BigNumber b(i_s);
		BigNumber rs1;
		BI  c(i_f);
		BI  d(i_s);
		BI rs2;

		rs1 = a * b;
		rs2 = BI::Multiply(c, d);
		FirstTest("Mul ++ ", rs1, rs2);

		rs1 = a * -b;
		rs2 = BI::Multiply(c, -d);
		FirstTest("Mul +- ", rs1, rs2);

		rs1 = -a * b;
		rs2 = BI::Multiply(-c, d);
		FirstTest("Mul -+ ", rs1, rs2);

		rs1 = -a * -b;
		rs2 = BI::Multiply(-c, -d);
		FirstTest("Mul -- ", rs1, rs2);
#else  
		BigNumber a(i_f);
		BigNumber b(i_s);
		BigNumber rs1;

		rs1 = a * b;
		FirstTest("Mul ++ ", rs1, mulstr1);

		rs1 = a * -b;
		FirstTest("Mul +- ", rs1, mulstr2);

		rs1 = -a * b;
		FirstTest("Mul -+ ", rs1, mulstr2);

		rs1 = -a * -b;
		FirstTest("Mul -- ", rs1, mulstr1);
#endif // __cplusplus_cli
	}
	void Div() {
#ifdef __cplusplus_cli
		BigNumber a(i_f);
		BigNumber b(i_s);
		BigNumber rs1;
		BI rs2;

		rs1 = a / b;
		FirstTest("Div ++ ", rs1, rs2, divstr);

		rs1 = a / -b;
		FirstTest("Div +- ", rs1, rs2, mdivstr);


		rs1 = -a / b;
		FirstTest("Div -+ ", rs1, rs2, mdivstr);


		rs1 = -a / -b;
		FirstTest("Div -- ", rs1, rs2, divstr);
#else  
		BigNumber a(i_f);
		BigNumber b(i_s);
		BigNumber rs1;

		rs1 = a / b;
		FirstTest("Div ++ ", rs1, divstr);

		rs1 = a / -b;
		FirstTest("Div +- ", rs1, mdivstr);


		rs1 = -a / b;
		FirstTest("Div -+ ", rs1, mdivstr);


		rs1 = -a / -b;
		FirstTest("Div -- ", rs1, divstr);
#endif // __cplusplus_cli
	}
	void BNVector() {
		Init();
		Sum();
		Sub();
		if (_MUL_)
			Mul();
		if (_DIV_)
			Div();
	}

	void InitDecimal() {}
	void SumDecimal() {}
	void SubDecimal() {}
	void MulDecimal() {}
	void DivDecimal() {}
	void BNVectorDecimal() {
		InitDecimal();
		SumDecimal();
		SubDecimal();
		if (_MUL_)
			MulDecimal();
		if (_DIV_)
			DivDecimal();
	}
#pragma endregion

#ifdef __cplusplus_cli
#define threadcount 15
	void ThreadLoop() {
		for (int i = 0; i < threadcount; i++) {
			BigNumber s(1);
			BigNumber d(1);
			s += d;
		}
	}
	void CreateThreads() {
		for (int i = 0; i < threadcount; i++) {
			Thread^ tmp = gcnew Thread(gcnew ThreadStart(ThreadLoop));
			tmp->Name = "thread" + i;
			tmp->Start();
		}
	}
#endif // thread
	
#pragma region SpeedTest
	ui bntime = 0, bitime;
	char* ParseCount(ui count) {
		char* str = new char[10];
		itoa(count, str, 10);

		int buf = strlen(str);
		int separators = buf > 9 ? 3 : buf > 6 ? 2 : buf > 3 ? 1 : 0;
		if (separators == 0)
			return str;

		int i = buf + separators + 1;
		char* nstr = new char[i];

		nstr[--i] = 0;
		for (separators = 0; --i >= 0;) {
			if (separators == 3 ) {
				separators = 0;
				nstr[i] = '\'';
			}
			else {
				nstr[i] = str[--buf];
				separators++;
			}
		}

		return nstr;
	}

	void Result(BigNumber& a, BigNumber& b,
#ifdef __cplusplus_cli
	 BI& ba, BI& bb, 
#endif // __cplusplus_cli
		char* str) {
		cout << str;
#ifdef __cplusplus_cli
		if (a == ba && b == bb)
			Color("success", Green);
		else
			Color("failed", Red);
		cout << endl;
#endif // __cplusplus_cli

		if (bntime == 0)
			bntime = 1;
		if (bitime == 0)
			bitime = 1;

		if (bitime > 1)
			if (bntime > bitime)
				cout << "is slower " << ceil((double)bntime / (double)bitime) << " times" << endl;
			else if (bntime < bitime)
				cout << ceil((double)bitime / (double)bntime) << " times faster" << endl;
			else
				cout << "algorithms have the same speed" << endl;

		cout << "BigNumber size of vector:    "; Color(a.size(), Magenta);
		cout << endl;
		cout << "BigNumber symbols in vector: "; Color(a.symbols(), Magenta);
		cout << endl;
	}

	#pragma region SUM
		BigNumber sumshort() {
			BigNumber a(1);
			BigNumber b(1);

			cout << endl << "Count: " << ParseCount(SUMCOUNT) << endl;
			ui start_time = clock();
			for (int i = 0; i < SUMCOUNT; i++) {
				a += b;
				++b;
			}
			ui end_time = clock();
			bntime = end_time - start_time;

			cout << "Sum += short work time: ";
			Color(bntime, Magenta);
			cout << "\tms" << endl;

			return a;
		}
		BigNumber summshort() {
			BigNumber a(1);
			BigNumber b(1);

			ui start_time = clock();
			for (int i = 0; i < SUMCOUNT; i++) {
				a = a + b;
				++b;
			}
			ui end_time = clock();
			bntime = end_time - start_time;

			cout << "Sum +  short work time: ";
			Color(bntime, Magenta);
			cout << "\tms" << endl;

			return a;
		}
#ifdef __cplusplus_cli
		BI sumshortbi() {
			BI ba(1);
			BI bb(1);

			ui start_time = clock();
			for (int i = 0; i < SUMCOUNT; i++) {
				ba += bb;
				bb++;
			}
			ui end_time = clock();
			bitime = end_time - start_time;

			cout << "Sum += short work time: ";
			Color(bitime, Magenta);
			cout << "\tms BigInteger (C#)" << endl;

			return ba;
		}
		BI summshortbi() {
			BI ba(1);
			BI bb(1);

			ui start_time = clock();
			for (int i = 0; i < SUMCOUNT; i++) {
				ba = ba + bb;
				bb++;
			}
			ui end_time = clock();
			bitime = end_time - start_time;

			cout << "Sum +  short work time: ";
			Color(bitime, Magenta);
			cout << "\tms BigInteger (C#)" << endl;

			return ba;
		}
#endif // bi summ short
		BigNumber sumlong() {
			BigNumber a(1);

			cout << endl << "Count: " << ParseCount(SUMCOUNTL) << endl;
			ui start_time = clock();
			for (int i = 0; i < SUMCOUNTL; i++) {
				a += a;
			}
			ui end_time = clock();
			bntime = end_time - start_time;

			cout << "Sum += long work time: ";
			Color(bntime, Magenta);
			cout << "\tms" << endl;

			return a;
		}
		BigNumber summlong() {
			BigNumber a(1);

			ui start_time = clock();
			for (int i = 0; i < SUMCOUNTL; i++) {
				a = a + a;
			}
			ui end_time = clock();
			bntime = end_time - start_time;

			cout << "Sum +  long work time: ";
			Color(bntime, Magenta);
			cout << "\tms" << endl;

			return a;
		}
#ifdef __cplusplus_cli
		BI sumlongbi() {
			BI ba(1);

			ui start_time = clock();
			for (int i = 0; i < SUMCOUNTL; i++) {
				ba += ba;
			}
			ui end_time = clock();
			bitime = end_time - start_time;

			cout << "Sum += long work time: ";
			Color(bitime, Magenta);
			cout << "\tms BigInteger (C#)" << endl;

			return ba;
		}
		BI summlongbi() {
			BI ba(1);

			ui start_time = clock();
			for (int i = 0; i < SUMCOUNTL; i++) {
				ba = ba + ba;
			}
			ui end_time = clock();
			bitime = end_time - start_time;

			cout << "Sum +  long work time: ";
			Color(bitime, Magenta);
			cout << "\tms BigInteger (C#)" << endl;

			return ba;
		}
#endif // bi summ long
		void SPSUM() {
#ifdef __cplusplus_cli
			BigNumber a = sumshort();
			BigNumber b = summshort();
			BI ba = sumshortbi();
			BI bb = summshortbi();
			Result(a, b, ba, bb, "Sum ");

			a = sumlong();
			b = summlong();
			ba = sumlongbi();
			bb = summlongbi();

			Result(a, b, ba, bb, "Sum ");
#else
			BigNumber a = sumshort();
			BigNumber b = summshort();

			Result(a, b, "Sum ");

			a = sumlong();
			b = summlong();

			Result(a, b, "Sum ");
#endif // __cplusplus_cli
		}
	#pragma endregion

	#pragma region SUB
		BigNumber subshort() {
			BigNumber a(1);
			BigNumber b(1);

			cout << endl << "Count: " << ParseCount(SUBCOUNT) << endl;
			ui start_time = clock();
			for (int i = 0; i < SUBCOUNT; i++) {
				a -= b;
				b++;
			}
			ui end_time = clock();
			bntime = end_time - start_time;

			cout << "Sub -= short work time: ";
			Color(bntime, Magenta);
			cout << "\tms" << endl;

			return a;
		}
		BigNumber subbshort() {
			BigNumber a(1);
			BigNumber b(1);

			ui start_time = clock();
			for (int i = 0; i < SUBCOUNT; i++) {
				a = a - b;
				b++;
			}
			ui end_time = clock();
			bntime = end_time - start_time;

			cout << "Sub -  short work time: ";
			Color(bntime, Magenta);
			cout << "\tms" << endl;

			return a;
		}
#ifdef __cplusplus_cli
		BI subshortbi() {
			BI a(1);
			BI b(1);

			ui start_time = clock();
			for (int i = 0; i < SUBCOUNT; i++) {
				a -= b;
				b++;
			}
			ui end_time = clock();
			bitime = end_time - start_time;

			cout << "Sub -= short work time: ";
			Color(bitime, Magenta);
			cout << "\tms BigInteger (C#)" << endl;

			return a;
		}
		BI subbshortbi() {
			BI a(1);
			BI b(1);

			ui start_time = clock();
			for (int i = 0; i < SUBCOUNT; i++) {
				a = a - b;
				b++;
			}
			ui end_time = clock();
			bitime = end_time - start_time;

			cout << "Sub -  short work time: ";
			Color(bitime, Magenta);
			cout << "\tms BigInteger (C#)" << endl;

			return a;
		}
#endif // bi sub short
		BigNumber sublong() {
			BigNumber a(1);
			BigNumber b(1);

			cout << endl << "Count: " << ParseCount(SUBCOUNTL) << endl;
			ui start_time = clock();
			for (int i = 0; i < SUBCOUNTL; i++) {
				a -= b;
				b += b;
			}
			ui end_time = clock();
			bntime = end_time - start_time;

			cout << "Sub -= long work time: ";
			Color(bntime, Magenta);
			cout << "\tms" << endl;

			return a;
		}
		BigNumber subblong() {
			BigNumber a(1);
			BigNumber b(1);

			ui start_time = clock();
			for (int i = 0; i < SUBCOUNTL; i++) {
				a = a - b;
				b += b;
			}
			ui end_time = clock();
			bntime = end_time - start_time;

			cout << "Sub -  long work time: ";
			Color(bntime, Magenta);
			cout << "\tms" << endl;

			return a;
		}
#ifdef __cplusplus_cli
		BI sublongbi() {
			BI a(1);
			BI b(1);

			ui start_time = clock();
			for (int i = 0; i < SUBCOUNTL; i++) {
				a -= b;
				b += b;
			}
			ui end_time = clock();
			bitime = end_time - start_time;

			cout << "Sub -= long work time: ";
			Color(bitime, Magenta);
			cout << "\tms BigInteger (C#)" << endl;

			return a;
		}
		BI subblongbi() {
			BI a(1);
			BI b(1);

			ui start_time = clock();
			for (int i = 0; i < SUBCOUNTL; i++) {
				a = a - b;
				b += b;
			}
			ui end_time = clock();
			bitime = end_time - start_time;

			cout << "Sub -  long work time: ";
			Color(bitime, Magenta);
			cout << "\tms BigInteger (C#)" << endl;

			return a;
		}
#endif // bi sub long
		void SPSUB() {
#ifdef __cplusplus_cli
			BigNumber a = subshort();
			BigNumber b = subbshort();
			BI ba = subshortbi();
			BI bb = subbshortbi();

			Result(a, b, ba, bb, "Sub ");

			a = sublong();
			b = subblong();
			ba = sublongbi();
			bb = subblongbi();

			Result(a, b, ba, bb, "Sub ");
#else
			BigNumber a = subshort();
			BigNumber b = subbshort();

			Result(a, b, "Sub ");

			a = sublong();
			b = subblong();

			Result(a, b, "Sub ");
#endif // __cplusplus_cli
		}
	#pragma endregion

	#pragma region MUL
		BigNumber mul1() {
			BigNumber a(1);
			BigNumber b(2);

			cout << endl << endl << "Count: " << ParseCount(MULCOUNT) << endl;
			ui start_time = clock();
			for (int i = 0; i < MULCOUNT; i++) {
				a *= b;
				b++;
			}
			ui end_time = clock();
			bntime = end_time - start_time;

			cout << "Mul *= work time: ";
			Color(bntime, Magenta);
			cout << "\tms" << endl;

			return a;
		}
		BigNumber mul2() {
			BigNumber a(1);
			BigNumber b(2);

			ui start_time = clock();
			for (int i = 0; i < MULCOUNT; i++) {
				a = a * b;
				b++;
			}
			ui end_time = clock();
			bntime = end_time - start_time;

			cout << "Mul *  work time: ";
			Color(bntime, Magenta);
			cout << "\tms" << endl;

			return a;
		}
#ifdef __cplusplus_cli
		BI mulbi1() {
			BI a(1);
			BI b(2);

			ui start_time = clock();
			for (int i = 0; i < MULCOUNT; i++) {
				a *= b;
				b++;
			}
			ui end_time = clock();
			bitime = end_time - start_time;

			cout << "Mul *= work time: ";
			Color(bntime, Magenta);
			cout << "\tms BigInteger (C#)" << endl;

			return a;
		}
		BI mulbi2() {
			BI a(1);
			BI b(2);

			ui start_time = clock();
			for (int i = 0; i < MULCOUNT; i++) {
				a = BI::Multiply(a, b);
				b++;
			}
			ui end_time = clock();
			bitime = end_time - start_time;

			cout << "Mul *  work time: ";
			Color(bntime, Magenta);
			cout << "\tms BigInteger (C#)" << endl;

			return a;
		}
#endif // __cplusplus_cli
		void SPMUL() {
#ifdef __cplusplus_cli
			BigNumber a = mul1();
			BigNumber b = mul2();
			BI ba = mulbi1();
			BI bb = mulbi2();

			Result(a, b, ba, bb, "Mul ");
#else  
			BigNumber a = mul1();
			BigNumber b = mul2();

			Result(a, b, "Mul ");
#endif // __cplusplus_cli
		}
	#pragma endregion

	#pragma region DIV
		BigNumber div1() {
			BigNumber a(i_s);
			BigNumber b(2);

			cout << endl << endl << "Count: " << ParseCount(DIVCOUNT) << endl;
			ui start_time = clock();
			for (int i = 0; i < DIVCOUNT; i++) {
				a /= b;
			}
			ui end_time = clock();
			bntime = end_time - start_time;

			cout << "Div /= work time: ";
			Color(bntime, Magenta);
			cout << "\tms" << endl;

			return a;
		}
		BigNumber div2() {
			BigNumber a(i_s);
			BigNumber b(2);

			ui start_time = clock();
			for (int i = 0; i < DIVCOUNT; i++) {
				a = a / b;
			}
			ui end_time = clock();
			bntime = end_time - start_time;

			cout << "Div /  work time: ";
			Color(bntime, Magenta);
			cout << "\tms" << endl;

			return a;
		}
#ifdef __cplusplus_cli
		BI divbi1() {
			BI a(i_s);
			BI b(2);

			ui start_time = clock();
			for (int i = 0; i < DIVCOUNT; i++) {
				a /= b;
			}
			ui end_time = clock();
			bitime = end_time - start_time;

			cout << "Div /= work time: ";
			Color(bntime, Magenta);
			cout << "\tms BigInteger (C#)" << endl;

			return a;
		}
		BI divbi2() {
			BI a(i_s);
			BI b(2);

			ui start_time = clock();
			for (int i = 0; i < DIVCOUNT; i++) {
				a = BI::Divide(a, b);
			}
			ui end_time = clock();
			bitime = end_time - start_time;

			cout << "Div /  work time: ";
			Color(bntime, Magenta);
			cout << "\tms BigInteger (C#)" << endl;

			return a;
		}
#endif // __cplusplus_cli
		void SPDIV() {
#ifdef __cplusplus_cli
			BigNumber a = div1();
			BigNumber b = div2();
			BI ba = divbi1();
			BI bb = divbi2();

			Result(a, b, ba, bb, "Div ");
#else  
			BigNumber a = div1();
			BigNumber b = div2();

			Result(a, b, "Div ");
#endif // __cplusplus_cli
		}
	#pragma endregion

	void BNTestSpeed() {
		if (_SUM_)
			SPSUM();
		if (_SUB_)
			SPSUB();
		if (_MUL_)
			SPMUL();
		if (_DIV_)
			SPDIV();
	}
#pragma endregion
	
#include <deque>
#define VectCOUNT 3'345'000
void NewSpeedTest() {
	//cout << "new" << endl;
#pragma region new
	cout << "Count: " << ParseCount(VectCOUNT) << endl;
	ui start_time = clock();
	int* nw = new int[VectCOUNT];
	ui end_time = clock();
	bntime = end_time - start_time;

	cout << "New:\t"; Color(bntime, Magenta);
	cout << "\tms" << endl;
#pragma endregion

	//cout << "vector<ui>" << endl;
	vector<ui> nvect;
	vector<ui> nvect2;
	vector<ui> nvect3;
	vector<ui> nvect4;
	vector<ui> nvect5;
	vector<ui> nvect6;
	vector<ui> nvect7;
	vector<ui> nvect8;
#pragma region push_back(i)
	start_time = clock();
	for (int i = 0; i < VectCOUNT; i++)
		nvect.push_back(i);

	end_time = clock();
	bntime = end_time - start_time;

	cout << "Vector: "; Color(bntime, Magenta);
	cout << "\tms push back" << endl;
#pragma endregion
#pragma region pop_back&push again
	start_time = clock();
	for (int i = 0; i < VectCOUNT; i++)
		nvect.pop_back();

	end_time = clock();
	bntime = end_time - start_time;

	cout << "Vector: "; Color(bntime, Magenta);
	cout << "\tms pop back" << endl;


	start_time = clock();
	for (int i = 0; i < VectCOUNT; i++)
		nvect.push_back(i);

	end_time = clock();
	bntime = end_time - start_time;

	cout << "Vector: "; Color(bntime, Magenta);
	cout << "\tms push back" << endl;
#pragma endregion
#pragma region reserve[count]
	start_time = clock();
	nvect2.reserve(VectCOUNT);
	end_time = clock();
	bntime = end_time - start_time;

	cout << "Vector: "; Color(bntime, Magenta);
	cout << "\tms reserve[count]" << endl;
#pragma endregion
#pragma region reserve[count] push_back(i)
	start_time = clock();
	nvect3.reserve(VectCOUNT);
	for (int i = 0; i < VectCOUNT; i++)
		nvect3.push_back(i);

	end_time = clock();
	bntime = end_time - start_time;

	cout << "Vector: "; Color(bntime, Magenta);
	cout << "\tms reserve[count] push_back" << endl;
#pragma endregion
#pragma region reserve[count] resize[i + 1] [i] = i
	start_time = clock();
	nvect4.reserve(VectCOUNT);
	for (int i = 0; i < VectCOUNT; i++) {
		nvect4.resize(i + 1);
		nvect4[i] = i;
	}
	end_time = clock();
	bntime = end_time - start_time;

	cout << "Vector: "; Color(bntime, Magenta);
	cout << "\tms reserve[count] resize[i + 1] [i] = i" << endl;
#pragma endregion
#pragma region reserve[count] resize[count] [i] = i
	start_time = clock();
	nvect5.reserve(VectCOUNT);
	nvect5.resize(VectCOUNT);
	for (int i = 0; i < VectCOUNT; i++) {
		nvect5[i] = i;
	}
	end_time = clock();
	bntime = end_time - start_time;

	cout << "Vector: "; Color(bntime, Magenta);
	cout << "\tms reserve[count] resize[count] [i] = i" << endl;
#pragma endregion
#pragma region resize[count]
	start_time = clock();
	nvect6.resize(VectCOUNT);
	end_time = clock();
	bntime = end_time - start_time;
	cout << "Vector: "; Color(bntime, Magenta);
	cout << "\tms resize[count]" << endl;
#pragma endregion
#pragma region resize[count] [i] = i
	start_time = clock();
	nvect7.resize(VectCOUNT);
	for (int i = 0; i < VectCOUNT; i++)
		nvect7[i] = i;

	end_time = clock();
	bntime = end_time - start_time;

	cout << "Vector: "; Color(bntime, Magenta);
	cout << "\tms resize[count] [i] = i" << endl;
#pragma endregion
#pragma region resize[i + 1] [i] = i
	start_time = clock();
	for (int i = 0; i < VectCOUNT; i++) {
		nvect8.resize(i + 1);
		nvect8[i] = i;
	}

	end_time = clock();
	bntime = end_time - start_time;

	cout << "Vector: "; Color(bntime, Magenta);
	cout << "\tms resize[i + 1] [i] = i" << endl;
#pragma endregion

	//cout << "deque<ui>" << endl;
	deque<ui> deq1;
	deque<ui> deq2;
	deque<ui> deq3;
	deque<ui> deq4;

#pragma region push_back(i)
	start_time = clock();
	for (int i = 0; i < VectCOUNT; i++) {
		deq1.push_back(i);
	}

	end_time = clock();
	bntime = end_time - start_time;

	cout << "Deque: "; Color(bntime, Magenta);
	cout << "\tms push_back(i)" << endl;
#pragma endregion
#pragma region resize(count)
	start_time = clock();
	deq2.resize(VectCOUNT);

	end_time = clock();
	bntime = end_time - start_time;

	cout << "Deque: "; Color(bntime, Magenta);
	cout << "\tms resize(count)" << endl;
#pragma endregion
#pragma region resize(count) [i] = i
	start_time = clock();
	deq2.resize(VectCOUNT);
	for (int i = 0; i < VectCOUNT; i++) {
		deq2[i] = i;
	}

	end_time = clock();
	bntime = end_time - start_time;

	cout << "Deque: "; Color(bntime, Magenta);
	cout << "\tms resize(count) [i] = i" << endl;
#pragma endregion
#pragma region resize(i + 1) [i] = i
	start_time = clock();
	for (int i = 0; i < VectCOUNT; i++) {
		deq3.resize(i + 1);
		deq3[i] = i;
	}

	end_time = clock();
	bntime = end_time - start_time;

	cout << "Deque: "; Color(bntime, Magenta);
	cout << "\tms resize[i + 1] [i] = i" << endl;
#pragma endregion

	cout << endl;
}

int main() {
	system("color F0");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//NewSpeedTest();

	//BigNumber the integer part of vector
	BNVector();
	//BigNumber the decimal part of vector
	BNVectorDecimal();
	// speed tests
	BNTestSpeed();

	cout << endl << endl << "Count of object BigNumber = " << BigNumber::count;
	cout << endl << "Press any key to exit" << _getch();
	return 0;
}

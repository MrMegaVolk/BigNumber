#include <iostream>
#include <conio.h>
#include <ctime>

using namespace std;

#define i_f        12'395
#define i_s 2'147'483'647

#define divstr   "0.000005771871"
#define mdivstr "-0.000005771871"

#pragma region BigNumer
#include "BigNumer.h"

void Init() {
	BigNumer a(i_f);
	BigNumer b(i_s);
	BI  c(i_f);
	BI  d(i_s);

	if (a == c && b == d)
		cout << "Init success: ";
	else
		cout << "Init failed: ";
	cout << a.c_str() << " <1|2> " << BigNumer::ToCString(c.ToString()) << " <2|3> ";
	cout << b.c_str() << " <3|4> " << BigNumer::ToCString(d.ToString()) << endl;
}
void Sum() {
	BigNumer a(i_f);
	BigNumer b(i_s);
	BigNumer rs1;
	BI  c(i_f);
	BI  d(i_s);
	BI rs2;

	rs1 = a + b;
	rs2 = BI::Add(c, d);
	if (rs1 == rs2)
		cout << "Sum ++ success: ";
	else
		cout << "Sum ++ failed: ";
	cout << rs1.c_str() << " <1 + 3|2 + 4> " << BigNumer::ToCString(rs2.ToString()) << endl;


	rs1 = a + -b;
	rs2 = BI::Add(c, -d);
	if (rs1 == rs2)
		cout << "Sum +- success: ";
	else
		cout << "Sum +- failed: ";
	cout << rs1.c_str() << " <1 + -3|2 + -4> " << BigNumer::ToCString(rs2.ToString()) << endl;


	rs1 = -a + b;
	rs2 = BI::Add(-c, d);
	if (rs1 == rs2)
		cout << "Sum -+ success: ";
	else
		cout << "Sum -+ failed: ";
	cout << rs1.c_str() << " <-1 + 3|-2 + 4> " << BigNumer::ToCString(rs2.ToString()) << endl;


	rs1 = -a + -b;
	rs2 = BI::Add(-c, -d);
	if (rs1 == rs2)
		cout << "Sum -- success: ";
	else
		cout << "Sum -- failed: ";
	cout << rs1.c_str() << " <-1 + -3|-2 + -4> " << BigNumer::ToCString(rs2.ToString()) << endl;
}
void Sub() {
	BigNumer a(i_f);
	BigNumer b(i_s);
	BigNumer rs1;
	BI  c(i_f);
	BI  d(i_s);
	BI rs2;

	rs1 = a - b;
	rs2 = BI::Subtract(c, d);
	if (rs1 == rs2)
		cout << "Sub ++ success: ";
	else
		cout << "Sub ++ failed: ";
	cout << rs1.c_str() << " <1 - 3|2 - 4> " << BigNumer::ToCString(rs2.ToString()) << endl;


	rs1 = a - -b;
	rs2 = BI::Subtract(c, -d);
	if (rs1 == rs2)
		cout << "Sub +- success: ";
	else
		cout << "Sub +- failed: ";
	cout << rs1.c_str() << " <1 - -3|2 - -4> " << BigNumer::ToCString(rs2.ToString()) << endl;


	rs1 = -a - b;
	rs2 = BI::Subtract(-c, d);
	if (rs1 == rs2)
		cout << "Sub -+ success: ";
	else
		cout << "Sub -+ failed: ";
	cout << rs1.c_str() << " <-1 - 3|-2 - 4> " << BigNumer::ToCString(rs2.ToString()) << endl;


	rs1 = -a - -b;
	rs2 = BI::Subtract(-c, -d);
	if (rs1 == rs2)
		cout << "Sub -- success: ";
	else
		cout << "Sub -- failed: ";
	cout << rs1.c_str() << " <-1 - -3|-2 - -4> " << BigNumer::ToCString(rs2.ToString()) << endl;
}
void Mul() {
	BigNumer a(i_f);
	BigNumer b(i_s);
	BigNumer rs1;
	BI  c(i_f);
	BI  d(i_s);
	BI rs2;

	rs1 = a * b;
	rs2 = BI::Multiply(c, d);
	if (rs1 == rs2)
		cout << "Mul ++ success: ";
	else
		cout << "Mul ++ failed: ";
	cout << rs1.c_str() << " <1 * 3|2 * 4> " << BigNumer::ToCString(rs2.ToString()) << endl;


	rs1 = a * -b;
	rs2 = BI::Multiply(c, -d);
	if (rs1 == rs2)
		cout << "Mul +- success: ";
	else
		cout << "Mul +- failed: ";
	cout << rs1.c_str() << " <1 * -3|2 * -4> " << BigNumer::ToCString(rs2.ToString()) << endl;


	rs1 = -a * b;
	rs2 = BI::Multiply(-c, d);
	if (rs1 == rs2)
		cout << "Mul -+ success: ";
	else
		cout << "Mul -+ failed: ";
	cout << rs1.c_str() << " <-1 * 3|-2 * 4> " << BigNumer::ToCString(rs2.ToString()) << endl;


	rs1 = -a * -b;
	rs2 = BI::Multiply(-c, -d);
	if (rs1 == rs2)
		cout << "Mul -- success: ";
	else
		cout << "Mul -- failed: ";
	cout << rs1.c_str() << " <-1 * -3|-2 * -4> " << BigNumer::ToCString(rs2.ToString()) << endl;
}
void Div() {
	BigNumer a(i_f);
	BigNumer b(i_s);
	BigNumer rs1;

	rs1 = a / b;
	if (rs1 == divstr)
		cout << "Div ++ success: ";
	else
		cout << "Div ++ failed: ";
	cout << rs1.c_str() << " <1 / 3|2 / 4> " << divstr << endl;


	rs1 = a / -b;
	if (rs1 == mdivstr)
		cout << "Div +- success: ";
	else
		cout << "Div +- failed: ";
	cout << rs1.c_str() << " <1 / -3|2 / -4> " << mdivstr << endl;


	rs1 = -a / b;
	if (rs1 == mdivstr)
		cout << "Div -+ success: ";
	else
		cout << "Div -+ failed: ";
	cout << rs1.c_str() << " <-1 / 3|-2 / 4> " << mdivstr << endl;


	rs1 = -a / -b;
	if (rs1 == divstr)
		cout << "Div -- success: ";
	else
		cout << "Div -- failed: ";
	cout << rs1.c_str() << " <-1 / -3|-2 / -4> " << divstr << endl;
}
void BIVector() {
	Init();
	Sum();
	Sub();
	Mul();
	Div();
}

void InitDecimal() {}
void SumDecimal() {}
void SubDecimal() {}
void MulDecimal() {}
void DivDecimal() {}
void BIVectorDecimal() {
	InitDecimal();
	SumDecimal();
	SubDecimal();
	MulDecimal();
	DivDecimal();
}
#pragma endregion

#pragma region SpeedTest

#define SUMCOUNT 100'000
#define SUBCOUNT 100'000
#define MULCOUNT 1500
#define DIVCOUNT 15
typedef unsigned int ui;

void SPSUM() {
	BigNumer a(1);
	BigNumer b(1);

	ui start_time = clock();
	for (int i = 0; i < SUMCOUNT; i++) {
		a += b;
		b++;
	}
	ui end_time = clock();
	ui time = end_time - start_time;
	cout << endl << endl << "Sum work time: " << time << "ms" << endl;

	BI ba(1);
	BI bb(1);

	start_time = clock();
	for (int i = 0; i < SUMCOUNT; i++) {
		ba = ba.Add(ba, bb);
		bb++;
	}
	end_time = clock();
	ui btime = end_time - start_time;
	cout << "Sum BI work time: " << btime << "ms" << endl;

	if (a == ba)
		cout << "Sum success" << endl;
	else
		cout << "Sum failed" << endl;

	if (time == 0)
		time = 1;
	if (btime == 0)
		btime = 1;
	if (time > btime)
		cout << "amount is slower " << time / btime << " times" << endl;
	else if (time < btime)
		cout << "amount " << btime / time << " times faster" << endl;
	else
		cout << "algorithms have the same speed" << endl;
}
void SPSUB() {
	BigNumer a(1);
	BigNumer b(1);

	ui start_time = clock();
	for (int i = 0; i < SUMCOUNT; i++) {
		a -= b;
		b++;
	}
	ui end_time = clock();
	ui time = end_time - start_time;
	cout << endl << endl << "Sub work time: " << time << "ms" << endl;

	BI ba(1);
	BI bb(1);

	start_time = clock();
	for (int i = 0; i < SUMCOUNT; i++) {
		ba = ba.Subtract(ba, bb);
		bb++;
	}
	end_time = clock();
	ui btime = end_time - start_time;
	cout << "Sub BI work time: " << btime << "ms" << endl;

	if (a == ba)
		cout << "Sub success" << endl;
	else
		cout << "Sub failed" << endl;

	if (time == 0)
		time = 1;
	if (btime == 0)
		btime = 1;
	if (time > btime)
		cout << "amount is slower " << time / btime << " times" << endl;
	else if (time < btime)
		cout << "amount " << btime / time << " times faster" << endl;
	else
		cout << "algorithms have the same speed" << endl;
}
void SPMUL() {
	BigNumer a(1);
	BigNumer b(2);

	ui start_time = clock();
	int num = 1;
	for (int i = 0; i < MULCOUNT; i++) {
		a *= b;
		b++;
		num++;
	}
	ui end_time = clock();
	ui time = end_time - start_time;
	cout << endl << endl << "MUL work time: " << time << "ms" << endl;

	BI ba(1);
	BI bb(2);

	start_time = clock();
	for (int i = 0; i < MULCOUNT; i++) {
		ba *= bb;
		bb++;
	}
	end_time = clock();
	ui btime = end_time - start_time;
	cout << "MUL BI work time: " << btime << "ms" << endl;

	if (a == ba)
		cout << "MUL success" << endl;
	else
		cout << "MUL failed" << endl;

	if (time == 0)
		time = 1;
	if (btime == 0)
		btime = 1;
	if (time > btime)
		cout << "amount is slower " << time / btime << " times" << endl;
	else if (time < btime)
		cout << "amount " << btime / time << " times faster" << endl;
	else
		cout << "algorithms have the same speed" << endl;
}
void SPDIV() {
	BigNumer a(i_s);
	BigNumer b(2);

	ui start_time = clock();
	int num = 1;
	for (int i = 0; i < DIVCOUNT; i++) {
		a /= b;
		num++;
	}
	ui end_time = clock();
	ui time = end_time - start_time;
	cout << endl << endl << "Div work time: " << time << "ms" << endl;

	BI ba(i_s);
	BI bb(2);

	start_time = clock();
	for (int i = 0; i < DIVCOUNT; i++) {
		ba /= bb;
	}
	end_time = clock();
	ui btime = end_time - start_time;
	cout << "Div BI work time: " << btime << "ms" << endl;

	if (a == ba) // BI do not have a decimals, so if BigNumber have decimals, compare be failed
		cout << "Div success" << endl;
	else
		cout << "Div failed" << endl;

	if (time == 0)
		time = 1;
	if (btime == 0)
		btime = 1;
	if (time > btime)
		cout << "amount is slower " << time / btime << " times" << endl;
	else if (time < btime)
		cout << "amount " << btime / time << " times faster" << endl;
	else
		cout << "algorithms have the same speed" << endl;
}
#pragma endregion

int main() {
	//BigNumber the integer part of vector
	BIVector();
	//BigNumber the decimal part of vector
	BIVectorDecimal();

	// speed tests
	SPSUM();
	SPSUB();
	SPMUL();
	SPDIV();

	cout << endl << "Press any key to exit" << _getch();
	return 0;
}

#include <iostream>
#include <conio.h>
#include <ctime>

using namespace std;

#define i_f 12395
#define i_s 2147483647

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

BigNumer& factorial(int fact) {
	BigNumer a(1);
	BigNumer b(2);

	unsigned int start_time = clock();
	int num = 1;
	for (int i = 0; i < (fact - 1); i++) {
		a *= b;
		b++;
		num++;
	}
	unsigned int end_time = clock();
	cout << endl << endl << "Work time: " << end_time - start_time << "ms" << endl;
	start_time = clock();
	cout << endl << "factorial " << num << " = " << a.c_str() << endl;
	end_time = clock();
	cout << endl << "Print time: " << end_time - start_time << "ms" << endl;
	return a;
}
BI& factorialBI(int fact) {
	BI a(1);
	BI b(2);

	unsigned int start_time = clock();
	int num = 1;
	for (int i = 0; i < (fact - 1); i++) {
		a *= b;
		b++;
		num++;
	}
	unsigned int end_time = clock();
	cout << endl << endl << "BI Work time: " << end_time - start_time << "ms" << endl;
	return a;
}

int main() {
	//BigNumber the integer part of vector
	BIVector();
	//BigNumber the decimal part of vector
	BIVectorDecimal();

	BigNumer a = factorial(3000);
	BI b = factorialBI(3000);
	if (a == b)
		cout << "factorial success";
	else {
		// fuuuuuuuuuuuuu
		cout << "factorial failed";
	}
	cout << endl;

	cout << "Press any key to exit" << _getch();
	return 0;
}

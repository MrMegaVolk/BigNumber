#include "BigNumber.h"
#include <string>

// static init head
unsigned int BigNumber::count = 0;

BigNumber::BigNumber() {
	integer.clear();
	decimal.clear();

	sign = _sign = 1;

	percision = 12;
	count++;
	tmp = NULL;
}
BigNumber::BigNumber(int val) {
	integer.clear();
	decimal.clear();

	ui carry;
	if (val < 0) {
		sign = _sign = -1;
		carry = -val;
	}
	else {
		sign = _sign = 1;
		carry = val;
	}
	integer.push_back(carry);

	percision = 12;
	count++;
	tmp = NULL;
}
BigNumber::BigNumber(BigNumber& val) {
	operator=(val);
	count++;
	tmp = NULL;
}
BigNumber::BigNumber(const char* s) {
	operator=(s);

	percision = 12;
	count++;
	tmp = NULL;
}
BigNumber::~BigNumber() {
	if (tmp != NULL)
		delete tmp;
	count--;
}

// reserve
BigNumber& BigNumber::operator=(const char* val) {
	integer.clear();
	decimal.clear();

	for (int i = (int)strlen(val); i > 0; i -= 9) {
		if (i < 9)
			integer.push_back(atoi(substring(val, 0, i)));
		else
			integer.push_back(atoi(substring(val, i - 9, 9)));
	}

	while (integer.size() > 1 && integer.back() == 0)
		integer.pop_back();

	return *this;
}
BigNumber& BigNumber::operator=(BigNumber& val) {
	if (val.integer.size() < 25) {
		ui i = integer.size();
		ui j = val.integer.size();
		
		if (i != j) {
			integer.resize(j);
			i = j;
		}

		while (--i < j)
			integer[i] = val.integer[i];
	}
	else
		integer = val.integer;

	percision = val.percision;
	sign = _sign = val.sign;

	return *this;
}

BigNumber& BigNumber::operator++() {
	register int carry = 1;
	for (register int i = 0; carry; i++) {
		integer[i] += carry;
		carry = integer[i] > _base_num;
		if (carry)
			integer[i] -= _base_num;
	}
	if (carry)
		integer.push_back(carry);

	return *this;
}
BigNumber& BigNumber::operator++(int) {
	return operator++();
}
BigNumber& BigNumber::operator+(BigNumber& val) {
	if (_sign == val._sign)
		return sum(val);
	else
		return sub(val);
}
BigNumber& BigNumber::operator+=(BigNumber& val) {
	if (_sign == val._sign)
		return sumA(val);
	else
		return subA(val);
}

BigNumber& BigNumber::operator-() {
	_sign = -_sign;
	return *this;
}
BigNumber& BigNumber::operator-(BigNumber& val) {
	if (_sign != val._sign)
		return sum(val);
	else
		return sub(val);
}
BigNumber& BigNumber::operator-=(BigNumber& val) {
	if (_sign == val._sign)
		return sumA(val);
	else
		return subA(val);
}

BigNumber& BigNumber::operator*(BigNumber& val) {
	return mul(val);
}
BigNumber& BigNumber::operator*=(BigNumber& val) {
	return mulA(val);
}

//BigNumber & BigNumber::operator/(int val) {
//	if (val < _base_num && val != 0) {
//		BigNumber* CL = new BigNumber(*this);
//
//		int carry = 0;
//		for (int i = (int)CL->a.size() - 1; i >= 0; --i) {
//			long long cur = CL->a[i] + carry * 1ll * _base_num;
//			CL->a[i] = int(cur / val);
//			carry = int(cur % val);
//		}
//		while (CL->a.size() > 1 && CL->a.back() == 0)
//			CL->a.pop_back();
//
//		return *CL;
//	}
//	return *(new BigNumber(0));
//}
BigNumber& BigNumber::operator/(BigNumber& val) {
	return div(val);
}
BigNumber& BigNumber::operator/=(BigNumber& val) {
	return divA(val);
}

#ifdef __cplusplus_cli
bool BigNumber::operator==(BI b) const {
	return !(strcmp(c_str(), ToCString(b.ToString())));
}
#endif // ==(BI)
bool BigNumber::operator==(char* str) const {
	return !(strcmp(c_str(), str));
}
bool BigNumber::operator>=(const BigNumber& r) const {
	if (integer.size() > r.integer.size())
		return true;
	else if (r.integer.size() > integer.size())
		return false;

	for (int i = integer.size() - 1; i >= 0; i--) {
		if (integer[i] > r.integer[i])
			return true;
		else if (r.integer[i] > integer[i])
			return false;
	}
	return true;
}

// todo decimals
inline ull MakeUlong(ui uHi, ui uLo) {
	return ((ull)uHi << kcbitUint) | uLo;
}
char* BigNumber::c_str() const {
	/*
	// old for 9 digits in element vector
		if (!integer.empty() || decimal.empty()) {
		bool sgn = sign;
		char* str = new char[
			(sign < 0 ? 1 : 0) +
			(integer.size() ? integer.size() * 9 + 1 : 2) +
			(decimal.size() ? decimal.size() * 9 + 1 : 1)];
		char* buf = new char[11];

		int j = 0;
		if (integer.size() != 0) {
			if (sign > 0)
				itoa(integer.back(), buf, 10);
			else
				itoa(-(int)integer.back(), buf, 10);

			for (int i = 0; i < strlen(buf); i++)
				str[j++] = buf[i];

			for (int k = (int)integer.size() - 2; k >= 0; k--) {
					itoa(integer[k], buf, 10);

				int countzero = 9 - countnumeral(integer[k] < 0 ? integer[k] * -1 : integer[k]);
				for (int i = 0; i < countzero; i++)
					str[j++] = '0';

				for (int i = 0; i < strlen(buf); i++)
					str[j++] = buf[i];
			}
		}
		else {
			if (sign > 0)
				str[j++] = '0';
			else {
				str[j++] = '-';
				str[j++] = '0';
			}
			
			if (decimal.size() > 0)
				str[j++] = '.';
		}

		if (decimal.size()) {
			for (int i = 0; i < decimal.size(); i++) {
				itoa(decimal[i] < 0 ? decimal[i] * -1 : decimal[i], buf, 10);

				int countzero = 9 - countnumeral(decimal[i] < 0 ? decimal[i] * -1 : decimal[i]);
				for (int k = 0; k < countzero; k++)
					str[j++] = '0';
				for (int h = 0; h < strlen(buf); h++)
					str[j++] = buf[h];
			}
			str[j--] = 0;

			for (int i = strlen(str) - 1; i >= 0; i--) {
				if (str[i] == '0')
					str[j--] = 0;
				else break;
			}
		}
		str[j] = 0;

		return str;
	}
	else
		return "0";
	*/

	int digits = 0;
	ui cuSrc = integer.size();
	ui cuMax = cuSrc * 10 / 9 + 2; // check overflow

	std::vector<ui> rguDst;
	rguDst.resize(cuMax);
	ui cuDst = 0;

	for (int inSrc = cuSrc; --inSrc >= 0;) {
		ui uCarry = integer[inSrc];
		for (int iuDst = 0; iuDst < cuDst; iuDst++) {
			ull uuRes = MakeUlong(rguDst[iuDst], uCarry);
			rguDst[iuDst] = (ui)(uuRes % kuBase);
			uCarry = (ui)(uuRes / kuBase);
		}
		if (uCarry != 0) {
			rguDst[cuDst++] = uCarry % kuBase;
			uCarry /= kuBase;
			if (uCarry != 0)
				rguDst[cuDst++] = uCarry;
		}
	}

	ui cchMax = cuDst * kcchBase; // check overflow
	ui rgchBufSize;

	int i;
	for (i = cuMax; --i >= 0;) {
		if (rguDst[i]) {
			rgchBufSize = countnumeral(rguDst[i]);
			break;
		}
	}
	rgchBufSize += i * 9;
	if (sign < 0)
		rgchBufSize += 1;

	char* rgch = new char[rgchBufSize + 1];
	ui ichDst = rgchBufSize + 1;
	ui uDig;

	rgch[--ichDst] = 0;
	for (int iuDst = 0; iuDst < cuDst - 1; iuDst++) {
		uDig = rguDst[iuDst];
		for (int cch = kcchBase; --cch >= 0;) {
			rgch[--ichDst] = (char)('0' + uDig % 10);
			uDig /= 10;
		}
	}

	for (uDig = rguDst[cuDst - 1]; uDig != 0;) {
		rgch[--ichDst] = (char)('0' + uDig % 10);
		uDig /= 10;
	}


	if (_sign < 0) {
		rgch[--ichDst] = '-';
	}

	return rgch;
}


#ifdef __cplusplus_cli
char* BigNumber::ToCString(System::String^ str) {
	char* bstr = new char[str->Length + 1];
	for (int i = 0; i < str->Length; i++)
		bstr[i] = str[i];
	bstr[str->Length] = 0;

	return bstr;
}
#endif // ToCString(BI)
char* BigNumber::substring(const char* str, int pos, int count) {
	if (pos >= strlen(str))
		return "";

	char* nstr = new char[count + 1];
	int j = 0;
	for (int i = pos; i < (pos + count); i++)
		nstr[j++] = str[i];
	nstr[j] = 0;
	return nstr;
}
char BigNumber::getVal(const char* str, int pos) {
	return pos >= strlen(str) ? 0 : str[pos];
}
bool BigNumber::___max(int a, int b) {
	return a >= b ? a : b;
}
int BigNumber::size() const {
	ui cuSrc = integer.size();
	ui cuMax = cuSrc * 10 / 9 + 2; // check overflow

	std::vector<ui> rguDst;
	rguDst.resize(cuMax);
	ui cuDst = 0;

	for (int inSrc = cuSrc; --inSrc >= 0;) {
		ui uCarry = integer[inSrc];
		for (int iuDst = 0; iuDst < cuDst; iuDst++) {
			ull uuRes = MakeUlong(rguDst[iuDst], uCarry);
			rguDst[iuDst] = (ui)(uuRes % kuBase);
			uCarry = (ui)(uuRes / kuBase);
		}
		if (uCarry != 0) {
			rguDst[cuDst++] = uCarry % kuBase;
			uCarry /= kuBase;
			if (uCarry != 0)
				rguDst[cuDst++] = uCarry;
		}
	}

	return cuDst;
}
int BigNumber::symbols() const {
	ui cuSrc = integer.size();
	ui cuMax = cuSrc * 10 / 9 + 2; // check overflow

	std::vector<ui> rguDst;
	rguDst.resize(cuMax);
	ui cuDst = 0;

	for (int inSrc = cuSrc; --inSrc >= 0;) {
		ui uCarry = integer[inSrc];
		for (int iuDst = 0; iuDst < cuDst; iuDst++) {
			ull uuRes = MakeUlong(rguDst[iuDst], uCarry);
			rguDst[iuDst] = (ui)(uuRes % kuBase);
			uCarry = (ui)(uuRes / kuBase);
		}
		if (uCarry != 0) {
			rguDst[cuDst++] = uCarry % kuBase;
			uCarry /= kuBase;
			if (uCarry != 0)
				rguDst[cuDst++] = uCarry;
		}
	}

	return cuDst * 9 + (countnumeral(rguDst[cuDst -1]) - 9);
}



bool BigNumber::IsEven() {
	if (integer.size() > 0 && integer[0] % 2 == 0 && decimal.size() > 0 && decimal.back() % 2 == 0)
		return true;
	return false;
}
bool BigNumber::IsOne() {
	if (decimal.size() == 0 && integer.size() == 1 && integer[0] == 1)
		return true;
	return false;
}
bool BigNumber::IsZero() {
	if (integer.size() || decimal.size())
		return false;
	//else if (integer.size() == 1 && integer[0] == 0 && decimal.size() == 0 && decimal[0] == 0)
	return true;
}
bool BigNumber::Sing() {
	return sign < 0;
}



BigNumber& BigNumber::sum(BigNumber& val) {
	if (!tmp)
		tmp = new BigNumber();

	ui carry = 0;
	ui l = integer.size();
	ui r = val.integer.size();
	ui m = tmp->integer.size();
	ui i = 0;
	ull uu;

	if (l < r) {
		uu = (ull)val.integer.back() + 1;
		if (uu >> 32 > 0) {
			if (m != (r + 1)) {
				tmp->integer.resize(r + 1);
				m = r + 1;
			}
		}
		else
			if (m != r) {
				tmp->integer.resize(r);
				m = r;
			}

		while (i < l) {
			uu = (ull)integer[i] + val.integer[i] + carry;
			tmp->integer[i] = uu;
			carry = uu >> kcbitUint;
			i++;
		}
		while (i < r) {
			uu = (ull)val.integer[i] + carry;
			tmp->integer[i] = uu;
			carry = uu >> kcbitUint;
			i++;
		}
	}
	else {
		if (l == r)
			uu = (ull)integer.back() + val.integer.back();
		else
			uu = (ull)integer.back() + 1;

		if (uu >> 32 > 0) {
			if (m != (l + 1)) {
				tmp->integer.resize(l + 1);
				m = l + 1;
			}
		}
		else
			if (m != l) {
				tmp->integer.resize(l);
				m = l;
			}
		while (i < r) {
			uu = (ull)integer[i] + val.integer[i] + carry;
			tmp->integer[i] = uu;
			carry = uu >> kcbitUint;
			i++;
		}
		while (i < l) {
			uu = (ull)integer[i] + carry;
			tmp->integer[i] = uu;
			carry = uu >> kcbitUint;
			i++;
		}
	}
	if (carry)
		tmp->integer[i] = carry;
	
	if (tmp->sign != _sign)
		tmp->sign = _sign;
	if (tmp->_sign != _sign)
		tmp->_sign = _sign;

	if (_sign != sign)
		_sign = sign;
	if (val._sign != sign)
		val._sign = sign;
	return *tmp;
}
BigNumber& BigNumber::sumA(BigNumber& val) {
	ui carry = 0;
	ui l = integer.size();
	ui r = val.integer.size();
	ui i = 0;
	ull uu;

	if (l < r) {
		uu = (ull)val.integer.back() + 1;
		if (uu >> 32 > 0)
			integer.resize(r + 1);
		else
			integer.resize(r);
	}
	else {
		if (l == r)
			uu = (ull)integer.back() + val.integer.back();
		else
			uu = (ull)integer.back() + 1;

		if (uu >> 32 > 0)
			integer.resize(l + 1);
	}

	while (i < r) {
		uu = (ull)integer[i] + val.integer[i] + carry;
		integer[i++] = uu;
		carry = uu  >> kcbitUint;
	}

	while (carry) {
		uu = (ull)integer[i] + carry;
		integer[i++] = uu;
		carry = uu >> kcbitUint;
	}

	if (_sign != sign)
		_sign = sign;
	if (val._sign != sign)
		val._sign = sign;
	return *this;
}

BigNumber& BigNumber::sub(BigNumber& val) {
	return *this;
	if (tmp == NULL)
		tmp = new BigNumber();




	return *tmp;
}
BigNumber& BigNumber::subA(BigNumber& val) {
	return *this;
	/*
	
	int carry = 0;
	int l = integer.size();
	int r = val.integer.size();

	int i;
	if (l > r) {
		for (i = 0; i < r; i++) {
			integer[i] -= (carry + val.integer[i]);

			carry = (integer[i] >= _base_num);
			if (carry)
				integer[i] += _base_num;
		}
	}
	else {
		if (l == r) {

		}
		else {

		}

	}

	if (carry && l > r)
		for (; carry ; i++) {
			integer[i] -= carry;

			carry = (integer[i] >= _base_num);
			if (carry)
				integer[i] += _base_num;
		}
	else if (carry) {

	}

	register int m = 0;
	while (integer[i--] == 0)
		m++;
	if (m)
		integer.resize(l - m);

	*/

	if (_sign != sign)
		_sign = sign;
	if (val._sign != sign)
		val._sign = sign;
	return *this;
}

BigNumber& BigNumber::mul(BigNumber& val) {
	return *this;
	if (tmp == NULL)
		tmp = new BigNumber();

	return *tmp;
	/*
	tmp.a.clear();
	tmp.d.clear();
	int carry;
	tmp.a.resize(l.a.size() + r.a.size());

	for (int i = 0; i < l.a.size(); i++)
		for (int j = 0, carry = 0; j < r.a.size() || carry; j++) {
			long long cur = tmp.a[i + j] + l.a[i]
				* 1ll * (j < (int)r.a.size() ? r.a[j] : 0) + carry;

			tmp.a[i + j] = int(cur % _base_num);
			carry = int(cur / _base_num);
		}

	while (tmp.a.size() > 1 && tmp.a.back() == 0)
		tmp.a.pop_back();
	return tmp;*/

}
BigNumber& BigNumber::mulA(BigNumber& val) {
	return *this;
}

BigNumber& BigNumber::div(BigNumber& val) {
	return *this;
	if (tmp == NULL)
		tmp = new BigNumber();

	return *tmp;
	/*
	tmp.a.clear();
	tmp.d.clear();
	Ctmp.a.clear();
	Ctmp.d.clear();
	BigNumber tmp = *(new BigNumber());
	BigNumber Ctmp = *(new BigNumber());
	BigNumber L = l;
	BigNumber R = r;
	return L;

	int decimals = 0, count = 0, pos = 0;
	char num;
	bool dec = false;
	bool zeroes = false;

	// signfunct
	int neg = 1;
	if (L.signfunct()) {
		neg = -neg;
		L = -l;
	}
	if (R.signfunct()) {
		neg = -neg;
		R = -r;
	}
	char* lnum = L.c_str();
	int val = countnumeral(L.a.back());

	if (R.a.size() > 1)
		val += (R.a.size() - 1) * 9;

	Ctmp = substring(lnum, pos, val);
	pos += val;
	val = 1;

	while (true) {
		if (decimals > tmp.percision || Ctmp.iszero())
			break;

		while (!(Ctmp - R).signfunct()) {
			count++;
			
			Ctmp -= R;
		}

		if (!dec && count == 0 && zeroes)
			dec = true;
		if (dec)
			tmp.shiftd(count, decimals++);
		else
			tmp.shifta(count);

		if (zeroes) {
			Ctmp.shifta(0);
		}
		else {
			num = getVal(lnum, pos);
			if (num != 0)
				Ctmp.shifta(num - 48);
			else {
				zeroes = true;
				Ctmp.shifta(0);
			}
		}
		pos++;
		count = 0;
	}

	while (tmp.a.size() > 0 && tmp.a.back() == 0)
		tmp.a.pop_back();
	while (tmp.d.size() > 0 && tmp.d.back() == 0)
		tmp.d.pop_back();

	if (neg > 0)
		return tmp;
	else
		return -tmp;*/
}
BigNumber& BigNumber::divA(BigNumber& val) {
	return *this;
}

void BigNumber::ReSizeTmpInteger(int& l, int& r, BigNumber& val) {
	int sz = tmp->integer.size();
	if (l == r)
		if (integer.back() + val.integer.back() > _base_num)
			if (sz == (l + 1))
				return;
			else
				tmp->integer.resize(l + 1);
		else if (sz == l)
				return;
			else
				tmp->integer.resize(l);
	else if (l > r)
		if (integer.back() + 1 > _base_num)
			if (sz == (l + 1))
				return;
			else
				tmp->integer.resize(l + 1);
		else
			if (sz == l)
				return;
			else
				tmp->integer.resize(l);
	else if (val.integer.back() + 1 > _base_num)
		if (sz == (r + 1))
			return;
		else
			tmp->integer.resize(r + 1);
	else
		if (sz == r)
			return;
		else
			tmp->integer.resize(r);
}
void BigNumber::ReSizeTmpDecimal(int& l, int& r, BigNumber& val) {

}
int BigNumber::countnumeral(int anum) const {
	if (anum > 99999999)
		return 9;
	else if (anum > 9999999)
		return 8;
	else if (anum > 999999)
		return 7;
	else if (anum > 99999)
		return 6;
	else if (anum > 9999)
		return 5;
	else if (anum > 999)
		return 4;
	else if (anum > 99)
		return 3;
	else if (anum > 9)
		return 2;
	else
		return 1;
}
void BigNumber::shifta(int nval) {
	int top = 0, bot = nval;

	for (int i = 0; i < integer.size(); i++) {
		top = integer[i] / _bbase_dn;
		integer[i] = integer[i] % _bbase_dn;
		integer[i] *= 10;
		integer[i] += bot;

		bot = top;
	}
	
	if (bot)
		integer.push_back(bot);
}
void BigNumber::shiftd(int nval, int decimals) {
	int top = 0, bot = nval, dec = 1, i;
	
	for (i = 0, dec = 1; i < decimal.size(); i++) {
		if (decimals >= 9) {
			decimals -= 9;
			continue;
		}
		break;
	}

	for (int j = 8; j > decimals; j--) {
		dec *= 10;
	}
	bot *= dec;
	if (decimal.size() > i)
		decimal[i] += bot;
	else
		decimal.push_back(bot);
}


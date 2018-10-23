#include "BigNumer.h"
#include <string>

BigNumer::BigNumer() {
	a.clear();
	d.clear();

	percision = 11;
}
BigNumer::BigNumer(int val) {
	a.clear();
	d.clear();

	int m = val % _base_num;
	int d = val / _base_num;

	if (m != 0)
		a.push_back(m);
	if (d != 0)
		a.push_back(d);

	percision = 11;
}
BigNumer::BigNumer(const BigNumer& val) {
	operator=(val);
}
BigNumer::BigNumer(const char* s) {
	a.clear();
	d.clear();

	for (int i = (int)strlen(s); i > 0; i -= 9) {
		if (i < 9)
			a.push_back(atoi(substring(s, 0, i)));
		else
			a.push_back(atoi(substring(s, i - 9, 9)));
	}

	while (a.size() > 1 && a.back() == 0)
		a.pop_back();

	percision = 11;
}
BigNumer::~BigNumer() {

}


BigNumer& BigNumer::operator=(const char* val) {
	a.clear();
	d.clear();

	for (int i = (int)strlen(val); i > 0; i -= 9) {
		if (i < 9)
			a.push_back(atoi(substring(val, 0, i)));
		else
			a.push_back(atoi(substring(val, i - 9, 9)));
	}

	while (a.size() > 1 && a.back() == 0)
		a.pop_back();

	return *this;
}
BigNumer& BigNumer::operator=(const BigNumer& val) {
	a.clear();
	d.clear();

	for (int i = 0; i < val.a.size(); i++)
		a.push_back(val.a[i]);
	for (int i = 0; i < val.d.size(); i++)
		d.push_back(val.d[i]);

	percision = val.percision;

	return *this;
}

BigNumer & BigNumer::operator++() {
	int carry = 0;
	int num = 1;
	for (int i = 0; i < a.size(); i++) {
		a[i] += num + carry;
		carry = a[i] > _base_num;
		if (carry)
			a[i] -= _base_num;
		if (num)
			num = 0;
	}

	return *this;
}
BigNumer& BigNumer::operator+(const BigNumer& val) {
	if (!sign()) {
		if (!val.sign())
			return sum(*this, val);
		else
			return sub(*this, -val);
	}
	else {
		if (!val.sign())
			return -sub(-*this, val);
		else
			return sum(*this, val);
	}
}
BigNumer& BigNumer::operator+=(const BigNumer& val) {
	return operator=(operator+(val));
}

BigNumer& BigNumer::operator-() const {
	BigNumer* nb = new BigNumer();
	for (int i = 0; i < a.size(); i++)
		nb->a.push_back(-a[i]);
	for (int i = 0; i < d.size(); i++)
		nb->d.push_back(-d[i]);
	return *nb;
}
BigNumer& BigNumer::operator-(const BigNumer& val) {
	if (!sign()) {
		if (!val.sign())
			return sub(*this, val);
		else
			return sum(*this, -val);
	}
	else {
		if (!val.sign())
			return -sum(-*this, val);
		else
			return -sub(-*this, -val);
	}
}
BigNumer& BigNumer::operator-=(const BigNumer& val)
{
	return operator=(operator-(val));
}

BigNumer& BigNumer::operator*(BigNumer& val) {
	return mul(*this, val);
}
BigNumer& BigNumer::operator*=(BigNumer& val) {
	return operator=(operator*(val));
}

BigNumer & BigNumer::operator/(int val) {
	if (val < _base_num && val != 0) {
		BigNumer* CL = new BigNumer(*this);

		int carry = 0;
		for (int i = (int)CL->a.size() - 1; i >= 0; --i) {
			long long cur = CL->a[i] + carry * 1ll * _base_num;
			CL->a[i] = int(cur / val);
			carry = int(cur % val);
		}
		while (CL->a.size() > 1 && CL->a.back() == 0)
			CL->a.pop_back();

		return *CL;
	}
	return *(new BigNumer(0));
}
BigNumer& BigNumer::operator/(BigNumer& val) {
	return div(*this, val);
}
BigNumer& BigNumer::operator/=(BigNumer& val) {
	return operator=(operator/(val));
}

bool BigNumer::operator==(BI b) const {
	return !(strcmp(c_str(), ToCString(b.ToString())));
}
bool BigNumer::operator==(char* str) const {
	return !(strcmp(c_str(), str));
}
bool BigNumer::operator>=(const BigNumer& r) const {
	if (a.size() > r.a.size())
		return true;
	else if (r.a.size() > a.size())
		return false;

	for (int i = a.size() - 1; i >= 0; i--) {
		if (a[i] > r.a[i])
			return true;
		else if (r.a[i] > a[i])
			return false;
	}
	return true;
}

// todo decimals
char* BigNumer::c_str() const {
	if (!a.empty() || !d.empty()) {
		char* str = new char[
			(!sign() ? 0 : 1) +
			(a.size() ? a.size() * 9 + 1 : 2) +
			(d.size() ? d.size() * 9 + 1 : 1)];
		char* buf = new char[11];

		int j = 0;
		if (a.size() != 0) {
			itoa(a.back(), buf, 10);
			for (int i = 0; i < strlen(buf); i++)
				str[j++] = buf[i];

			for (int k = (int)a.size() - 2; k >= 0; k--) {
				itoa(a[k] < 0 ? a[k] * -1 : a[k], buf, 10);

				int countzero = 9 - countnumeral(a[k] < 0 ? a[k] * -1 : a[k]);
				for (int i = 0; i < countzero; i++)
					str[j++] = '0';

				for (int i = 0; i < strlen(buf); i++)
					str[j++] = buf[i];
			}
		}
		else {
			if (!sign()) {
				str[j++] = '0';
				str[j++] = '.';
			}
			else {
				str[j++] = '-';
				str[j++] = '0';
				str[j++] = '.';
			}
		}

		if (d.size()) {
			for (int i = 0; i < d.size(); i++) {
				itoa(d[i] < 0 ? d[i] * -1 : d[i], buf, 10);

				int countzero = 9 - countnumeral(d[i] < 0 ? d[i] * -1 : d[i]);
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
}
char* BigNumer::ToCString(System::String^ str) {
	char* bstr = new char[str->Length + 1];
	for (int i = 0; i < str->Length; i++)
		bstr[i] = str[i];
	bstr[str->Length] = 0;

	return bstr;
}
char* BigNumer::substring(const char* str, int pos, int count) {
	if (pos >= strlen(str))
		return "";

	char* nstr = new char[count + 1];
	int j = 0;
	for (int i = pos; i < (pos + count); i++)
		nstr[j++] = str[i];
	nstr[j] = 0;
	return nstr;
}
char BigNumer::getVal(const char* str, int pos) {
	return pos >= strlen(str) ? 0 : str[pos];
}
bool BigNumer::max(int a, int b) {
	return a >= b ? a : b;
}
bool BigNumer::sign() const { // negative == true
	if (a.size() > 0)
		return a[0] >= 0 ? false : true;
	if (d.size() > 0)
		return d[0] >= 0 ? false : true;
	return false;
}
bool BigNumer::iszero() const {
	for (int i = 0; i < a.size(); i++)
		if (a[i] != 0)
			return false;
	for (int i = 0; i < d.size(); i++)
		if (d[i] != 0)
			return false;

	return true;
}


BigNumer& BigNumer::sum(const BigNumer& l, const BigNumer& r) {
	BigNumer* nb = new BigNumer();
	int carry = 0, buf, m = max(l.a.size(), r.a.size());
	for (int i = 0; i <= m; i++) {
		buf = carry
			+ (i < l.a.size() ? l.a[i] : 0)
			+ (i < r.a.size() ? r.a[i] : 0);
		carry = (buf >= _base_num);
		if (carry)
			buf -= _base_num;
		
		if (buf)
			nb->a.push_back(buf);
	}

	return *nb;
}
BigNumer& BigNumer::sub(const BigNumer& l, const BigNumer& r) {
	BigNumer* nb = new BigNumer();
	int carry = 0, buf, m = max(l.a.size(), r.a.size());
	if (l >= r)
		for (int i = 0; i <= m; i++) {
			buf = (i < l.a.size() ? l.a[i] : 0) - (carry
				+ (i < r.a.size() ? r.a[i] : 0));
			carry = buf < 0;
			if (carry)
				buf += _base_num;
			if (buf > 0)
				nb->a.push_back(buf);
		}
	else
		for (int i = 0; i <= m; i++) {
			buf = (i < r.a.size() ? r.a[i] : 0) - (carry
				+ (i < l.a.size() ? l.a[i] : 0));
			carry = buf < 0;
			if (carry)
				buf += _base_num;
			if (buf > 0)
				nb->a.push_back(-buf);
		}

	return *nb;
}
BigNumer& BigNumer::mul(const BigNumer& l, const BigNumer& r) {
	BigNumer* nb = new BigNumer();
	int carry;
	nb->a.resize(l.a.size() + r.a.size());

	for (int i = 0; i < l.a.size(); i++)
		for (int j = 0, carry = 0; j < r.a.size() || carry; j++) {
			long long cur = nb->a[i + j] + l.a[i]
				* 1ll * (j < (int)r.a.size() ? r.a[j] : 0) + carry;

			nb->a[i + j] = int(cur % _base_num);
			carry = int(cur / _base_num);
		}

	while (nb->a.size() > 1 && nb->a.back() == 0)
		nb->a.pop_back();
	return *nb;
}
BigNumer& BigNumer::div(const BigNumer& l, const BigNumer& r) {
	BigNumer& NB = *(new BigNumer());
	BigNumer& CL = *(new BigNumer());
	BigNumer L = l;
	BigNumer R = r;
	int decimals = 0, count = 0, pos = 0;
	char num;
	bool dec = false;
	bool zeroes = false;

	// sign
	int neg = 1;
	if (L.sign()) {
		neg = -neg;
		L = -l;
	}
	if (R.sign()) {
		neg = -neg;
		R = -r;
	}
	char* lnum = L.c_str();
	int val = countnumeral(L.a.back());

	if (R.a.size() > 1)
		val += (R.a.size() - 1) * 9;

	CL = substring(lnum, pos, val);
	pos += val;
	val = 1;

	while (true) {
		if (decimals > NB.percision || CL.iszero())
			break;

		while (!(CL - R).sign()) {
			count++;
			
			CL -= R;
		}

		if (!dec && count == 0 && zeroes)
			dec = true;
		if (dec)
			NB.shiftd(count, decimals++);
		else
			NB.shifta(count);

		if (zeroes) {
			CL.shifta(0);
		}
		else {
			num = getVal(lnum, pos);
			if (num != 0)
				CL.shifta(num - 48);
			else {
				zeroes = true;
				CL.shifta(0);
			}
		}
		pos++;
		count = 0;
	}

	while (NB.a.size() > 0 && NB.a.back() == 0)
		NB.a.pop_back();
	while (NB.d.size() > 0 && NB.d.back() == 0)
		NB.d.pop_back();

	if (neg > 0)
		return NB;
	else
		return -NB;
}


int BigNumer::countnumeral(int anum) const {
	int num = anum;

	if (num > 99999999)
		return 9;
	else if (num > 9999999)
		return 8;
	else if (num > 999999)
		return 7;
	else if (num > 99999)
		return 6;
	else if (num > 9999)
		return 5;
	else if (num > 999)
		return 4;
	else if (num > 99)
		return 3;
	else if (num > 9)
		return 2;
	else
		return 1;
}
void BigNumer::shifta(int nval) {
	int top = 0, bot = nval;

	for (int i = 0; i < a.size(); i++) {
		top = a[i] / _bbase_dn;
		a[i] = a[i] % _bbase_dn;
		a[i] *= 10;
		a[i] += bot;

		bot = top;
	}
	
	if (bot)
		a.push_back(bot);
}
void BigNumer::shiftd(int nval, int decimals) {
	int top = 0, bot = nval, dec = 1, i;
	
	for (i = 0, dec = 1; i < d.size(); i++) {
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
	if (d.size() > i)
		d[i] += bot;
	else
		d.push_back(bot);
}


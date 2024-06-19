
#include "bignum.h"
#include <algorithm>
#include <string>

class BigNum {
public:
	BigNum() = default;
	BigNum(const std::string& num): number(num) {
		std::reverse(number.begin(), number.end());
		std::for_each(number.begin(), number.end(), [](char& c) { c -= '0'; });
	}
	~BigNum() = default;

	void print() {
		std::for_each(number.rbegin(), number.rend(), [](char c) { std::cout << static_cast<int>(c); });
		std::cout << std::endl;
	}

	friend BigNum operator+(const BigNum& lhs, const BigNum& rhs);
	friend BigNum operator*(const BigNum& lhs, const BigNum& rhs);
	friend bool operator>(const BigNum& lhs, const BigNum& rhs);
	friend bool operator<(const BigNum& lhs, const BigNum& rhs);
	friend bool operator==(const BigNum& lhs, const BigNum& rhs);

private:
	std::string number;
};

BigNum operator+(const BigNum& lhs, const BigNum& rhs) {
	BigNum result;

	int max_size = std::max(lhs.number.size(), rhs.number.size());
	result.number.resize(max_size + 1, 0);
    int carry = 0;

	int i;
	for (i = 0; i < max_size; ++i) {
		int sum = carry + (i < lhs.number.size() ? lhs.number[i] : 0) 
			            + (i < rhs.number.size() ? rhs.number[i] : 0);

		result.number[i] = sum % 10;
		carry = sum / 10;
	}

	if (carry) {
		result.number[i] = carry;
	}
	else {
		result.number.resize(i);
	}

	return result;
}

BigNum operator*(const BigNum& lhs, const BigNum& rhs) {
	BigNum result;
	result.number.resize(lhs.number.size() + rhs.number.size(), 0);

	for (int i = 0; i < lhs.number.size(); ++i) {
		for (int j = 0; j < rhs.number.size(); ++j) {
			int index = i + j;
			result.number[index] += lhs.number[i] * rhs.number[j];
			result.number[index + 1] += result.number[index] / 10;
			result.number[index] %= 10;
		}
	}

	result.number.erase(result.number.find_last_not_of('\0') + 1);

	return result;
}


bool operator>(const BigNum& lhs, const BigNum& rhs) {
	if (lhs.number.size() != rhs.number.size()) {
		return lhs.number.size() > rhs.number.size() ? true : false;
	}

	for (int i = lhs.number.size() - 1; i >= 0; --i) {
		if (lhs.number[i] != rhs.number[i]) {
			return lhs.number[i] > rhs.number[i] ? true : false;
		}
	}

	return false;
}

bool operator<(const BigNum& lhs, const BigNum& rhs) {
	if (lhs.number.size() != rhs.number.size()) {
		return lhs.number.size() < rhs.number.size() ? true : false;
	}

	for (int i = lhs.number.size() - 1; i >= 0; --i) {
		if (lhs.number[i] != rhs.number[i]) {
			return lhs.number[i] < rhs.number[i] ? true : false;
		}
	}

	return false;
}

bool operator==(const BigNum& lhs, const BigNum& rhs) {
	if (lhs.number.size() != rhs.number.size()) {
		return false;
	}

	for (int i = 0; i < lhs.number.size(); ++i) {
		if (lhs.number[i] != rhs.number[i]) {
			return false;
		}
	}

	return true;
}

int main()
{

	BigNum a("12345678901234567890");
	BigNum b("98765432109876543210");

	a.print();
	b.print();

	std::cout << (a > b) << std::endl;
	std::cout << (a < b) << std::endl;
	std::cout << (a == b) << std::endl;

	BigNum c = a + b;
	c.print();

	BigNum d = a * b;
	d.print();
	return 0;
}

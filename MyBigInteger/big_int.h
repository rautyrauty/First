/* Big Int work be like:
* 
 * Some BigInt: 567546564;
 *							  Front					  Back
 * His Digits:				   └>  5 6 7 5 4 6 5 6 4  <┘
 * His indexes of digits in array: 8 7 6 5 4 3 2 1 0
 *
*/


#pragma once
#include "digits_array.h"

class MyBigInt
{
	char sign_;
	DigitsArray digits_;

public:

	MyBigInt() noexcept;

	MyBigInt& operator = (const MyBigInt& value) noexcept;

	MyBigInt& operator = (MyBigInt&& value) noexcept;

	MyBigInt(const MyBigInt& value) noexcept;

	MyBigInt(MyBigInt&& value) noexcept;

	MyBigInt(const int& num) noexcept;

	MyBigInt(const char* num_str);


	MyBigInt GetMultiplyByDigit(const digit_t& digit) const;

	MyBigInt GetMultiplyBy10inPower(const size_t& power) const noexcept;

	friend std::ostream& operator << (std::ostream& strm, const MyBigInt& value);

	friend MyBigInt operator - (const MyBigInt& value) noexcept;

	friend MyBigInt operator + (const MyBigInt& left, const MyBigInt& right);

	friend MyBigInt operator - (const MyBigInt& left, const MyBigInt& right);

	friend MyBigInt operator * (const MyBigInt& left, const MyBigInt& right);

	friend MyBigInt operator / (const MyBigInt& left, const MyBigInt& right);

	friend MyBigInt operator % (const MyBigInt& left, const MyBigInt& right);

	friend MyBigInt& operator += (MyBigInt& left, const MyBigInt& right);

	friend MyBigInt& operator -= (MyBigInt& left, const MyBigInt& right);

	friend MyBigInt& operator *= (MyBigInt& left, const MyBigInt& right);

	friend MyBigInt& operator /= (MyBigInt& left, const MyBigInt& right);

	friend MyBigInt& operator %= (MyBigInt& left, const MyBigInt& right);

	friend bool operator > (const MyBigInt& left, const MyBigInt& right);

	friend bool operator < (const MyBigInt& left, const MyBigInt& right);

	friend bool operator == (const MyBigInt& left, const MyBigInt& right);

	friend bool operator != (const MyBigInt& left, const MyBigInt& right);

	friend bool operator >= (const MyBigInt& left, const MyBigInt& right);

	friend bool operator <= (const MyBigInt& left, const MyBigInt& right);
};

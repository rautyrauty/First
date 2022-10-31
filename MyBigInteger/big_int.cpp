#include "big_int.h"
#define SHIFT_FOR_CHAR_DIGITS 48

MyBigInt::MyBigInt() noexcept
{
	sign_ = 0;
}

MyBigInt& MyBigInt::operator = (const MyBigInt& value) noexcept
{
	sign_ = value.sign_;
	digits_ = value.digits_;
	return *this;
}

MyBigInt& MyBigInt::operator = (MyBigInt&& value) noexcept
{
	sign_ = value.sign_;
	value.sign_ = 0;
	digits_ = std::move(value.digits_);
	return *this;
}

MyBigInt::MyBigInt(const MyBigInt& value) noexcept
{
	*this = value;
}

MyBigInt::MyBigInt(MyBigInt&& value) noexcept
{
	*this = std::move(value);
}


MyBigInt::MyBigInt(const int& num) noexcept
{
	if (num == 0)
	{
		sign_ = 0;
		return;
	}

	if (num < 0)
	{
		sign_ = '-';
		digits_ = DigitsArray{ static_cast<uint64_t>(-num)};
	}
	else
	{
		sign_ = '+';
		digits_ = DigitsArray{ static_cast<uint64_t>(num) };
	}
}
MyBigInt::MyBigInt(const char* num_str)
{
	if ((num_str == nullptr) or (strlen(num_str) <= 2))
	{
		sign_ = 0; 
		return;
	}

	if (num_str[0] == '-')
	{
		sign_ = '-';
		digits_ = DigitsArray{ num_str + 1 };
	}
	else
	{
		sign_ = '+';
		digits_ = DigitsArray{ num_str };
	}

	digits_.RemoveFrontNulls();
	if (digits_.get_count() == 0) sign_ = 0;
}

MyBigInt MyBigInt::GetMultiplyByDigit(const digit_t& digit) const
{
	if (digit > 9) throw std::runtime_error({ "digit in func GetMultiplyByDigit of MyBigInt is more than 9" });
	MyBigInt answer{ *this };
	digit_t dolg = 0;
	for (int i = 0; i < answer.digits_.get_count(); i++)
	{
		answer.digits_[i] *= digit;
		answer.digits_[i] += dolg;
		dolg = answer.digits_[i] / 10;
		answer.digits_[i] %= 10;
	}
	if (dolg > 0) answer.digits_.PushFront(dolg);
	return answer;
}

MyBigInt MyBigInt::GetMultiplyBy10inPower(const size_t& power) const noexcept
{
	if ((power == 0) or (this->sign_ == 0)) return *this;
	MyBigInt answer{ *this };
	answer.digits_.PushBack(0,power);
	return answer;
}

std::ostream& operator << (std::ostream& strm, const MyBigInt& value)
{
	if (value.sign_ == 0) strm << 0;
	if (value.sign_ != '+') strm << '-';
	for (size_t i = value.digits_.get_count(); i > 0; i -= 1)
	{
		strm << char(value.digits_[i - 1] + SHIFT_FOR_CHAR_DIGITS);
	}
	return strm;
}

MyBigInt operator - (const MyBigInt& value) noexcept
{
	if (value.sign_ == 0) return value;
	MyBigInt answer = value;
	if (answer.sign_ == '-') answer.sign_ = '+';
	else answer.sign_ = '-';
	return answer;
}

MyBigInt operator + (const MyBigInt& left, const MyBigInt& right)
{
	if ((left.sign_ == '+') and (right.sign_ == '-')) return left - (-right);
	if ((left.sign_ == '-') and (right.sign_ == '+')) return right - (-left);
	if (left.sign_ == 0) return right;
	if (right.sign_ == 0) return left;

	MyBigInt answer;
	if ((left.sign_ == '+') and (right.sign_ == '+')) answer.sign_ = '+';
	else if ((left.sign_ == '-') and (right.sign_ == '-')) answer.sign_ = '-';

	const MyBigInt* min_term;
	if (left.digits_.get_count() > right.digits_.get_count())
	{
		answer.digits_ = left.digits_;
		min_term = &right;
	}
	else
	{
		answer.digits_ = right.digits_;
		min_term = &left;
	}

	uint8_t dolg = 0;
	for (size_t i = 0; i < answer.digits_.get_count(); i += 1)
	{
		if (i < min_term->digits_.get_count()) answer.digits_[i] += min_term->digits_[i];
		if (dolg) answer.digits_[i] += dolg;
		dolg = (answer.digits_[i] / 10);
		answer.digits_[i] %= 10;
	}

	if (dolg > 0) answer.digits_.PushFront(dolg);

	return answer;
}

MyBigInt operator - (const MyBigInt& left, const MyBigInt& right)
{
	if ((left.sign_ == '+') and (right.sign_ == '-')) return left + (-right);
	if ((left.sign_ == '-') and (right.sign_ == '+')) return left + (-right);
	if ((left.sign_ == '-') and (right.sign_ == '-')) return (-right) - (-left);

	if (left.digits_.get_count() == 0) return -right;
	if (right.digits_.get_count() == 0) return left;

	if (left == right) return MyBigInt{};

	MyBigInt answer;
	const MyBigInt* subtrahend;
	if (left > right)
	{
		answer.sign_ = '+';
		answer.digits_ = left.digits_;
		subtrahend = &right;
	}
	else
	{
		answer.sign_ = '-';
		answer.digits_ = right.digits_;
		subtrahend = &left;
	}

	uint8_t dolg = 0;
	for (size_t i = 0; i < subtrahend->digits_.get_count(); i += 1)
	{
		if (answer.digits_[i] < dolg + subtrahend->digits_[i])
		{
			answer.digits_[i] += 10;
			answer.digits_[i] -= (dolg + subtrahend->digits_[i]);
			dolg = 1;
		}
		else
		{
			answer.digits_[i] -= (dolg + subtrahend->digits_[i]);
			dolg = 0;
		}
	}
	for (size_t i = subtrahend->digits_.get_count(); dolg > 0; i += 1)
	{
		if (answer.digits_[i] < dolg)
		{
			answer.digits_[i] += 10;
			answer.digits_[i] -= dolg;
			dolg = 1;
		}
		else
		{
			answer.digits_[i] -= dolg;
			dolg = 0;
		}
	}
	answer.digits_.RemoveFrontNulls();
	return answer;
}

MyBigInt operator * (const MyBigInt& left, const MyBigInt& right)
{
	MyBigInt answer;
	if ((left.sign_ == 0) or (right.sign_ == 0)) return {};
	for (int i = 0; i < right.digits_.get_count(); i++)
	{
		MyBigInt tmp = left.GetMultiplyByDigit(right.digits_[i]);
		tmp = tmp.GetMultiplyBy10inPower(i);
		answer += tmp;
	}
	if (left.sign_ != right.sign_) answer.sign_ = '-';
	else answer.sign_ = '+';
	return answer;
}

MyBigInt operator / (const MyBigInt& left, const MyBigInt& right)
{
	if (right == MyBigInt{}) throw std::logic_error({ "division by zero is not allowed" });
	if ((left.digits_.get_count() < right.digits_.get_count()) or (left == MyBigInt{})) return MyBigInt{};
	if (left == right) return 1;

	MyBigInt answer{ left };
	for (size_t i = 0; i < answer.digits_.get_count(); i += 1) answer.digits_[i] = 0;

	if (left.sign_ == right.sign_) answer.sign_ = '+';
	else answer.sign_ = '-';

	MyBigInt positive_right_copy = (right.sign_ == '-' ? -right : right);

	MyBigInt tmp;
	size_t answer_digits_count = 0;
	for (size_t i = left.digits_.get_count(); i > 0; i -= 1)
	{
		tmp = tmp.GetMultiplyBy10inPower(1);
		tmp += MyBigInt{ left.digits_[i-1] };
		if (tmp >= positive_right_copy)
		{
			digit_t j = 1;
			for (; j < 10; j += 1)
			{
				if (positive_right_copy.GetMultiplyByDigit(j) > tmp)
				{
					j -= 1;
					break;
				}
			}
			if (j == 10) j -= 1;//throw std::runtime_error({"operator / MyBigInt was worked wrong. j==11 is true!?!1!!"});
			answer.digits_[answer.digits_.get_count() - 1 - answer_digits_count] = j;
			tmp -= positive_right_copy.GetMultiplyByDigit(j);
		}
		answer_digits_count += 1;
	}
	answer.digits_.RemoveFrontNulls();
	return answer;
}

MyBigInt operator % (const MyBigInt& left, const MyBigInt& right)
{
	return left - (right * (left / right));
}

MyBigInt& operator += (MyBigInt& left, const MyBigInt& right)
{
	left = (left + right);
	return left;
}

MyBigInt& operator -= (MyBigInt& left, const MyBigInt& right)
{
	left = (left - right);
	return left;
}

MyBigInt& operator *= (MyBigInt& left, const MyBigInt& right)
{
	left = (left * right);
	return left;
}

MyBigInt& operator /= (MyBigInt& left, const MyBigInt& right)
{
	left = (left / right);
	return left;
}

MyBigInt& operator %= (MyBigInt& left, const MyBigInt& right)
{
	left = (left % right);
	return left;
}

bool operator > (const MyBigInt& left, const MyBigInt& right)
{
	if ((left.sign_ == 0) and (right.sign_ == 0)) return false;
	if ((left.sign_ == 0) and (right.sign_ == '+')) return false;
	if ((left.sign_ == '-') and (right.sign_ == 0)) return false;
	if ((left.sign_ == '-') and (right.sign_ == '+')) return false;
	if ((left.sign_ == '+') and (right.sign_ == '-')) return true;
	if ((left.digits_.get_count() > right.digits_.get_count()))
	{
		if ((left.sign_ == '+') and (right.sign_ == '+')) return true;
		if ((left.sign_ == '-') and (right.sign_ == '-')) return false;
	}
	if ((left.digits_.get_count() < right.digits_.get_count()))
	{
		if ((left.sign_ == '+') and (right.sign_ == '+')) return false;
		if ((left.sign_ == '-') and (right.sign_ == '-')) return true;
	}

	for (size_t i = left.digits_.get_count(); i > 0; i -= 1)
	{
		if (left.digits_[i - 1] > right.digits_[i - 1])
		{
			if ((left.sign_ == '+') and (right.sign_ == '+')) return true;
			if ((left.sign_ == '-') and (right.sign_ == '-')) return false;
		}
		if (left.digits_[i - 1] < right.digits_[i - 1])
		{
			if ((left.sign_ == '+') and (right.sign_ == '+')) return false;
			if ((left.sign_ == '-') and (right.sign_ == '-')) return true;
		}
	}
	return false;
}

bool operator < (const MyBigInt& left, const MyBigInt& right)
{
	if ((left.sign_ == 0) and (right.sign_ == 0)) return false;
	if ((left.sign_ == 0) and (right.sign_ == '+')) return true;
	if ((left.sign_ == '-') and (right.sign_ == 0)) return true;
	if ((left.sign_ == '-') and (right.sign_ == '+')) return true;
	if ((left.sign_ == '+') and (right.sign_ == '-')) return false;
	if ((left.digits_.get_count() > right.digits_.get_count()))
	{
		if ((left.sign_ == '+') and (right.sign_ == '+')) return false;
		if ((left.sign_ == '-') and (right.sign_ == '-')) return true;
	}
	if ((left.digits_.get_count() < right.digits_.get_count()))
	{
		if ((left.sign_ == '+') and (right.sign_ == '+')) return true;
		if ((left.sign_ == '-') and (right.sign_ == '-')) return false;
	}

	for (size_t i = left.digits_.get_count(); i > 0; i -= 1)
	{
		if (left.digits_[i - 1] > right.digits_[i - 1])
		{
			if ((left.sign_ == '+') and (right.sign_ == '+')) return false;
			if ((left.sign_ == '-') and (right.sign_ == '-')) return true;
		}
		if (left.digits_[i - 1] < right.digits_[i - 1])
		{
			if ((left.sign_ == '+') and (right.sign_ == '+')) return true;
			if ((left.sign_ == '-') and (right.sign_ == '-')) return false;
		}
	}
	return false;
}

bool operator == (const MyBigInt& left, const MyBigInt& right)
{
	if ((left.sign_ == 0) and (right.sign_ == 0)) return true;
	if ((left.sign_ == 0) and (right.sign_ == '+')) return false;
	if ((left.sign_ == '-') and (right.sign_ == 0)) return false;
	if ((left.sign_ == '-') and (right.sign_ == '+')) return false;
	if ((left.sign_ == '+') and (right.sign_ == '-')) return false;
	if ((left.digits_.get_count() > right.digits_.get_count())) return false;
	if ((left.digits_.get_count() < right.digits_.get_count())) return false;

	for (size_t i = left.digits_.get_count(); i > 0; i -= 1) if (left.digits_[i - 1] != right.digits_[i - 1]) return false;
	return true;
}

bool operator != (const MyBigInt& left, const MyBigInt& right)
{
	return !(left == right);
}

bool operator >= (const MyBigInt& left, const MyBigInt& right)
{
	if ((left > right) or (left == right)) return true;
	else return false;
}

bool operator <= (const MyBigInt& left, const MyBigInt& right)
{
	if ((left < right) or (left == right)) return true;
	else return false;
}
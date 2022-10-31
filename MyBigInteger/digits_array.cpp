#include "digits_array.h"

#define SHIFT_FOR_CHAR_DIGITS 48
#define MAX_DIGITS_COUNT_OF_UINT64_T 20

DigitsArray::DigitsArray() noexcept
{
	array_ = nullptr;
	count_ = 0;
}

DigitsArray::~DigitsArray() noexcept
{
	if (array_)
	{
		delete[] array_;
		array_ = nullptr;
	}
}

DigitsArray& DigitsArray::operator =(const DigitsArray& value) noexcept
{
	if (array_) delete[] array_;
	if (value.array_)
	{
		count_ = value.count_;
		array_ = new digit_t[count_];
		for (size_t i = 0; i < count_; i += 1) array_[i] = value.array_[i];
	}
	else
	{
		count_ = 0;
		array_ = nullptr;
	}
	return *this;
}

DigitsArray& DigitsArray::operator =(DigitsArray&& value) noexcept
{
	if (array_) delete[] array_;
	if (value.array_)
	{
		count_ = value.count_;
		value.count_ = 0;
		array_ = value.array_;
		value.array_ = nullptr;
	}
	else
	{
		count_ = 0;
		array_ = nullptr;
	}
	return *this;
}

DigitsArray::DigitsArray(const DigitsArray& array__for_copy) noexcept
{
	*this = array__for_copy;
}

DigitsArray::DigitsArray(DigitsArray&& digits_array_for_move) noexcept
{
	*this = std::move(digits_array_for_move);
}

DigitsArray::DigitsArray(uint64_t num) noexcept
{
	count_ = MAX_DIGITS_COUNT_OF_UINT64_T;
	array_ = new digit_t[MAX_DIGITS_COUNT_OF_UINT64_T];
	for (size_t i = 0; i < MAX_DIGITS_COUNT_OF_UINT64_T; i += 1)
	{
		array_[i] = num % 10;
		num /= 10;
	}
	RemoveFrontNulls();
}

DigitsArray::DigitsArray(const char* digits_str)
{
	count_ = strlen(digits_str);
	array_ = new digit_t[count_];
	for (size_t i = 0; i < count_; i += 1)
	{
		if ((digits_str[i] < '0') or (digits_str[i] > '9'))
		{
			throw std::runtime_error({ "in conctuctor DigitsArray(const char* digits_str) digits_str wrong digits_str entered" });
		}
		array_[count_-1-i] = digits_str[i] - SHIFT_FOR_CHAR_DIGITS;
	}
}

DigitsArray DigitsArray::GetCopy() const noexcept 
{ 
	return *this;
}

size_t DigitsArray::get_count() const noexcept 
{ 
	return count_;
}

digit_t& DigitsArray::operator [](const size_t& num) const
{
	if (count_ <= num) throw std::runtime_error({ "num of digit in operator[] DigitsArray more than count_" });
	return array_[num];
}

void DigitsArray::PushBack(const digit_t& digit)
{
	if (digit > 9) throw std::runtime_error({ "digit for push in func push_back of DigitsArray is not digit" });
	digit_t* new_array = new digit_t[count_ + 1];
	new_array[0] = digit;
	for (size_t i = 0; i < count_; i += 1)
	{
		new_array[i + 1] = array_[i];
	}
	if (array_) delete[] array_;
	array_ = new_array;
	count_ += 1;
}

void DigitsArray::PushBack(const digit_t& digit, const size_t& times_count)
{
	if (digit > 9) throw std::runtime_error({ "digit for push in func push_back of DigitsArray is not digit" });
	digit_t* new_array = new digit_t[count_ + times_count];
	for (size_t i = 0; i < times_count; i += 1)
	{
		new_array[i] = digit;
	}
	for (size_t i = 0; i < count_; i += 1)
	{
		new_array[i + times_count] = array_[i];
	}
	if (array_) delete[] array_;
	array_ = new_array;
	count_ += times_count;
}

void DigitsArray::PushFront(const digit_t& digit)
{
	if (digit > 9) throw std::runtime_error({ "digit for push in func push_front of DigitsArray is not digit" });
	digit_t* new_array = new digit_t[count_ + 1];
	for (size_t i = 0; i < count_; i += 1)
	{
		new_array[i] = array_[i];
	}
	new_array[count_] = digit;
	if (array_) delete[] array_;
	array_ = new_array;
	count_ += 1;
}

void DigitsArray::PushFront(const digit_t& digit, const size_t& times_count)
{
	if (digit > 9) throw std::runtime_error({ "digit for push in func push_front of DigitsArray is not digit" });
	digit_t* new_array = new digit_t[count_ + times_count];
	for (size_t i = 0; i < count_; i += 1)
	{
		new_array[i] = array_[i];
	}
	for (size_t i = 0; i < times_count; i += 1)
	{
		new_array[i + count_] = digit;
	}
	if (array_) delete[] array_;
	array_ = new_array;
	count_ += times_count;
}

void DigitsArray::RemoveFront(const size_t& count)
{
	if (count_ < count) throw std::runtime_error({ "count for delete in func RemoveFront of DigitsArray is more than count_" });
	if (count_ = count)
	{
		*this = DigitsArray{};
		return;
	}
	digit_t* new_array = new digit_t[count_ - count];
	for (int i = count; i < count_; i += 1)
	{
		new_array[i - count] = array_[i];
	}
	delete[] array_;
	array_ = new_array;
	count_ -= count;
}

void DigitsArray::RemoveBack(const size_t& count)
{
	if (count_ < count) throw std::runtime_error({ "count for delete in func RemoveFront of DigitsArray is more than count_" });
	if (count_ = count)
	{
		*this = DigitsArray{};
		return;
	}
	digit_t* new_array = new digit_t[count_ - count];
	for (int i = 0; i < count_ - count; i += 1)
	{
		new_array[i] = array_[i];
	}
	delete[] array_;
	array_ = new_array;
	count_ -= count;
}

void DigitsArray::RemoveFrontNulls() noexcept
{
	size_t new_count = count_;
	while (new_count > 0)
	{
		if (array_[new_count - 1] != 0) break;
		new_count -= 1;
	}
	if (new_count == count_) return;
	if (new_count == 0)
	{
		if (array_)delete[] array_;
		this->array_ = nullptr;
		this->count_ = 0;
		return;
	}
	digit_t* new_array = new digit_t[new_count];
	for (int i = 0; i < new_count; i += 1)
	{
		new_array[i] = array_[i];
	}
	delete[] array_;
	array_ = new_array;
	count_ = new_count;
}
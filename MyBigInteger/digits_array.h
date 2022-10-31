#pragma once
#include <iostream>
#include <stdexcept>

typedef unsigned char digit_t;

class DigitsArray
{
	digit_t* array_;
	size_t count_;

public:

	DigitsArray() noexcept;

	~DigitsArray() noexcept;

	DigitsArray& operator =(const DigitsArray& value) noexcept;

	DigitsArray& operator =(DigitsArray&& value) noexcept;

	DigitsArray(const DigitsArray& value) noexcept;

	DigitsArray(DigitsArray&& value) noexcept;

	DigitsArray(uint64_t num) noexcept;

	DigitsArray(const char* digits_str);


	DigitsArray GetCopy() const noexcept;

	size_t get_count() const noexcept;

	digit_t& operator [](const size_t& num) const;

	void PushBack(const digit_t& digit);

	void PushBack(const digit_t& digit, const size_t& times_count);

	void PushFront(const digit_t& digit);

	void PushFront(const digit_t& digit, const size_t& times_count);

	void RemoveFront(const size_t& count);

	void RemoveBack(const size_t& count);

	void RemoveFrontNulls() noexcept;
};
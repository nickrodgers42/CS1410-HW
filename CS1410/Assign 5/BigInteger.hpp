#ifndef _BIGINTEGER_HPP_
#define _BIGINTEGER_HPP_

#include <cstdint>
#include <iostream>
#include <string>

class TestCases;

class BigInteger
{
public:
    BigInteger();
    BigInteger(int n);
    BigInteger(std::string str);
	~BigInteger();
	BigInteger(const BigInteger& rObj);

	// BigInteger add(const BigInteger& rhs);
	// BigInteger multiply(const BigInteger& rhs);
	void display();
	BigInteger& operator=(const BigInteger& rObj);
    BigInteger operator+(const BigInteger& rObj);
    BigInteger operator+(const int rObj);
    BigInteger operator+(const unsigned int rObj);
    BigInteger& operator+=(const BigInteger& robj);
    BigInteger operator++(int);
    BigInteger operator*(const BigInteger& rObj);
    BigInteger& operator*=(const BigInteger& rObj);
    bool operator<=(const BigInteger& rObj);
    bool operator==(const BigInteger& rObj);
    operator double();

    friend std::ostream& operator<<(std::ostream& output, const BigInteger& rObj);

	friend TestCases; // TODO Have students do this first thing

private:
	std::uint8_t* m_number;		// Internal representation of the number.
	unsigned int m_sizeReserved;	// Total size of the allocated space used to internally store the number
	unsigned int m_digitCount;	// How many digits are in the number.

	std::uint8_t getDigit(unsigned int position) const;
	void setDigit(unsigned int position, std::uint8_t digit);
};

#endif

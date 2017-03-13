
// Question: what is the difference between m_digitCount and m_sizeReserved

#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>

#include "BigInteger.hpp"

BigInteger::BigInteger()
{
    m_digitCount = 0;
    m_sizeReserved = 4;
    m_number = new uint8_t[m_sizeReserved];

    for (int i = 0; i < m_sizeReserved; ++i)
    {
        m_number[i] = 0;
    }

}

BigInteger::BigInteger(int n)
{

    std::string val = std::to_string(n);
    m_digitCount = val.size();
    m_sizeReserved = val.size();
    m_number = new uint8_t[m_sizeReserved];

    for (int i = 0; i < m_digitCount; ++i)
    {
        m_number[i] = val[m_digitCount - i - 1]-'0';
    }


}

BigInteger::BigInteger(std::string str)
{

    m_digitCount = str.size();
    m_sizeReserved = str.size();
    m_number = new uint8_t[m_sizeReserved];
    for (int i = 0; i < m_digitCount; ++i)
    {
        m_number[i] = str[m_digitCount - i - 1] - '0';
    }


}

BigInteger::~BigInteger()
{
    if (m_number != NULL)
    {
        delete[] m_number;
    }
    m_number = nullptr;
}

BigInteger::BigInteger(const BigInteger &rObj)
{
    m_digitCount = rObj.m_digitCount;
    m_sizeReserved = rObj.m_sizeReserved;

    if (rObj.m_number != NULL)
    {
        m_number = new uint8_t[rObj.m_sizeReserved];

        for (int i = 0; i < m_sizeReserved; ++i)
        {
            m_number[i] = rObj.m_number[i];
        }
        // m_number[m_sizeReserved +1] = 0;
    }
    else
    {
        m_number = 0;
    }
}

BigInteger& BigInteger::operator=(const BigInteger& rObj)
{

    m_digitCount = rObj.m_digitCount;
    m_sizeReserved = rObj.m_sizeReserved;
    if (m_number != NULL)
    {
        delete [] m_number;
        m_number = NULL;
    }
    if (rObj.m_number != 0)
    {
        m_number = new uint8_t[rObj.m_sizeReserved];
        for (int i = 0; i < m_digitCount; ++i)
        {
            m_number[i] = rObj.m_number[i];
        }
        // m_number[m_sizeReserved] = 0;
    }
    return (*this);
}

//BigInteger BigInteger::add(const BigInteger& rhs)
//{
//	BigInteger result;
//	unsigned int length = (this->m_digitCount > rhs.m_digitCount) ? this->m_digitCount : rhs.m_digitCount;
//
//	int carry = 0;
//	for (unsigned int digit = 0; digit < length; digit++)
//	{
//		int v1 = this->getDigit(digit);
//		int v2 = rhs.getDigit(digit);
//		int sum = v1 + v2 + carry;
//		int single = sum % 10;
//		carry = ((sum - single) > 0) ? (sum - single) / 10 : 0;
//
//		result.setDigit(digit, single);
//	}
//	if (carry > 0)
//	{
//		result.setDigit(length, carry);
//	}
//
//	return result;
//}
//
//BigInteger BigInteger::multiply(const BigInteger& rhs)
//{
//	BigInteger result;
//	const BigInteger& b = (this->m_digitCount < rhs.m_digitCount) ? *this : rhs;
//	const BigInteger& t = (this->m_digitCount < rhs.m_digitCount) ? rhs : *this;
//
//	for (unsigned int bDigit = 0; bDigit < b.m_digitCount; bDigit++)
//	{
//		BigInteger temp(0);
//		int v1 = b.getDigit(bDigit);
//		int carry = 0;
//		for (unsigned int tDigit = 0; tDigit < t.m_digitCount; tDigit++)
//		{
//			int v2 = t.getDigit(tDigit);
//			int sum = v1 * v2 + carry;
//			int single = sum % 10;
//			carry = ((sum - single) > 0) ? (sum - single) / 10 : 0;
//
//			temp.setDigit(bDigit + tDigit, single);
//		}
//		if (carry > 0)
//		{
//			temp.setDigit(bDigit + t.m_digitCount, carry);
//		}
//		BigInteger temp2 = result.add(temp);
//		result = temp2;
//	}
//
//	return result;
//}

void BigInteger::display()
{
	for (unsigned int digit = m_digitCount; digit > 0; digit--)
	{
		std::cout << static_cast<int>(m_number[digit - 1]);
	}
}

// ------------------------------------------------------------------
//
// Returns the digit as the specified positon.  If the position is greater
// that the number representation, a 0 is returned.
//
// ------------------------------------------------------------------
std::uint8_t BigInteger::getDigit(unsigned int position) const
{
	if (position < m_digitCount)
	{
		return m_number[position];
	}

	return 0;
}


void BigInteger::setDigit(unsigned int position, std::uint8_t digit)
{
    if (position >= m_sizeReserved)
    {
        int oldSize = m_sizeReserved;
        while (m_sizeReserved <= position)
        {
            m_sizeReserved = m_sizeReserved*2;
        }

        std::uint8_t* temp = new uint8_t[m_sizeReserved];
        for (int i = 0; i < m_sizeReserved; ++i)
        {
            temp[i] = 0;
        }

        for (int i = 0; i < oldSize; ++i)
        {
            temp[i] = m_number[i];
        }

        delete[] m_number;
        m_number = temp;
        temp = nullptr;
    }

    m_number[position] = digit;
    m_digitCount = position + 1;
}

BigInteger BigInteger::operator+(const BigInteger& rhs)
{
        BigInteger result;
        unsigned int length = (this->m_digitCount > rhs.m_digitCount) ? this->m_digitCount : rhs.m_digitCount;

        int carry = 0;
        for (unsigned int digit = 0; digit < length; digit++)
        {
            int v1 = this->getDigit(digit);
            int v2 = rhs.getDigit(digit);
            int sum = v1 + v2 + carry;
            int single = sum % 10;
            carry = ((sum - single) > 0) ? (sum - single) / 10 : 0;

            result.setDigit(digit, single);
        }
        if (carry > 0)
        {
            result.setDigit(length, carry);
        }

        return result;
}

BigInteger BigInteger::operator+(const int rObj)
{
    BigInteger temp(rObj);
    return (*this) + rObj;
}

BigInteger BigInteger::operator+(const unsigned int num)
{
    BigInteger temp(num);
    return (*this) + temp;
}

BigInteger& BigInteger::operator+=(const BigInteger& robj)
{
    (*this) = (*this) + robj;
    return *this;
}

BigInteger BigInteger::operator++(int)
{
    BigInteger temp = (*this);
    (*this) += 1;
    return temp;
}

BigInteger BigInteger::operator*(const BigInteger& rhs)
{
    BigInteger result;
    const BigInteger& b = (this->m_digitCount < rhs.m_digitCount) ? *this : rhs;
    const BigInteger& t = (this->m_digitCount < rhs.m_digitCount) ? rhs : *this;

    for (unsigned int bDigit = 0; bDigit < b.m_digitCount; bDigit++)
    {
        BigInteger temp(0);
        int v1 = b.getDigit(bDigit);
        int carry = 0;
        for (unsigned int tDigit = 0; tDigit < t.m_digitCount; tDigit++)
        {
            int v2 = t.getDigit(tDigit);
            int sum = v1 * v2 + carry;
            int single = sum % 10;
            carry = ((sum - single) > 0) ? (sum - single) / 10 : 0;

            temp.setDigit(bDigit + tDigit, single);
        }
        if (carry > 0)
        {
            temp.setDigit(bDigit + t.m_digitCount, carry);
        }
        result = result + temp;
    }
    return result;
}

BigInteger& BigInteger::operator*=(const BigInteger& rObj)
{
    (*this) = (*this) * rObj;
    return (*this);
}

bool BigInteger::operator<=(const BigInteger& rhs)
{
    {
        if (this->m_digitCount < rhs.m_digitCount) return true;
        if (this->m_digitCount > rhs.m_digitCount) return false;
        //
        // Have to go digit by digit
        for (int digit = m_digitCount - 1; digit >= 0; digit--)
        {
            if (this->m_number[digit] < rhs.m_number[digit]) return true;
            if (this->m_number[digit] > rhs.m_number[digit]) return false;
        }
        return true;
    }
}

bool BigInteger::operator==(const BigInteger& rObj)
{
    if (this->m_digitCount != rObj.m_digitCount)
    {
        return false;
    }
    else if ((this->m_number == NULL && rObj.m_number != NULL) || (this->m_number != NULL && rObj.m_number == NULL))
    {
        return false;
    }
    else if (this->m_number != NULL)
    {
        for (int i = 0; i < this->m_digitCount; ++i)
        {
            if (this->m_number[i] != rObj.m_number[i])
                return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& output, const BigInteger& rObj)
{
    for (unsigned int digit = rObj.m_digitCount; digit > 0; digit--)
    {
        output << static_cast<int>(rObj.m_number[digit - 1]);
    }
    return output;
}

BigInteger::operator double()
{
    double x = 0;
    if (this->m_number != NULL)
    {
        for (int i = 0; i < this->m_digitCount; ++i) {
            x *= 10;
            x += this->m_number[m_digitCount - 1 - i];
        }
    }
    return x;

//    double toDouble = 0;
//    double powTen = 0;
//
//    if (this->m_number != NULL)
//    {
//        for (int i = 0; i > m_digitCount; ++i)
//        {
//            powTen = pow(m_number[i], i);
//            toDouble += powTen;
//        }
//    }
//    return toDouble;
}

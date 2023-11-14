// File: BigReal.cpp
// Author 1: Abdallah Mohamed / 20220185
// Author 2: Yousef Mohamed / 20220405
// Author 3: Mohamed Sabry / 20221122
// Section: S5/S6
// TA: Nardeen/Maya

#include <iostream>
#include <regex>
#include "BigReal.h"
#include <string>
#include <algorithm>
#include <cstdlib>

// Check if the given string represents a valid real number
bool BigReal::isValid(string realNumber)
{
    if (regex_match(realNumber, regex("^[+-]?\\d+(\\.\\d*)?$")))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Constructor for BigReal class, initializes the object with the given real number string
BigReal::BigReal(string real)
{
    bool found_sign = false;

    // Check if the provided real number is valid
    if (isValid(real))
    {
        // Determine the sign of the number
        if (real[0] == '+')
        {
            sign = '+';
            found_sign = true;
        }
        else if (real[0] == '-')
        {
            sign = '-';
            found_sign = true;
        }

        // Parse the integer and fraction parts of the number
        if (!found_sign)
        {
            if (real.find('.') != string::npos)
            {
                integer = real.substr(0, real.find('.'));
                fraction = real.substr(real.find('.') + 1, real.size() - 1);
            }
            else
            {
                integer = real;
                fraction = "0";
            }
        }
        else
        {
            if (real.find('.') != string::npos)
            {
                integer = real.substr(1, real.find('.') - 1);
                fraction = real.substr(real.find('.') + 1, real.size() - 1);
            }
            else
            {
                integer = real.substr(1, real.size() - 1);
                fraction = "0";
            }
        }
    }
    else
    {
        // If the provided real number is not valid, set the object to represent 0.0
        real = "0.0";
        integer = "0";
        fraction = "0";
    }
}

// Print the BigReal number
void BigReal::print()
{
    // Remove leading zeros from the integer part
    integer.erase(0, min(integer.find_first_not_of('0'), integer.size() - 1));

    // Check if the integer part is zero and print accordingly
    if (integer.length() == 1 && integer[0] == '0')
    {
        cout << integer << "." << fraction << endl;
    }
    else
    {
        cout << sign << integer << "." << fraction << endl;
    }
}

// Overloaded equality operator for BigReal objects
bool BigReal::operator==(BigReal another)
{
    if (sign != '-' && another.sign != '-')
    {
        return (integer == another.integer) &&
               (fraction == another.fraction);
    }

    return (sign == another.sign) &&
           (integer == another.integer) &&
           (fraction == another.fraction);
}

// Pad the integer and fraction parts of the numbers with leading zeros for addition or subtraction
void BigReal::padding(BigReal &second)
{
    int pad_int = abs(static_cast<int>(integer.length() - second.integer.length()));
    int pad_fraction = abs(static_cast<int>(fraction.length() - second.fraction.length()));

    string padding_temp = "";

    // Add leading zeros to the smaller integer part
    for (int i = 0; i < pad_int; i++)
    {
        padding_temp += '0';
    }

    string temp = "";

    // Update the smaller integer part with leading zeros
    if (integer.length() < second.integer.length())
    {
        temp = padding_temp + integer;
        integer = temp;
    }
    else if (integer.length() > second.integer.length())
    {
        temp = padding_temp + second.integer;
        second.integer = temp;
    }

    padding_temp = "";

    // Add leading zeros to the smaller fraction part
    for (int i = 0; i < pad_fraction; i++)
    {
        padding_temp += '0';
    }

    // Update the smaller fraction part with leading zeros
    if (fraction.length() < second.fraction.length())
    {
        fraction += padding_temp;
    }
    else if (fraction.length() > second.fraction.length())
    {
        second.fraction += padding_temp;
    }
}

// Overloaded addition operator for BigReal objects
BigReal BigReal::operator+(BigReal &other)
{
    // Set the operator to addition
    if (op != '-')
        op = '+';

    // Initialize the result and first BigReal objects
    BigReal result(""), first("");

    // Initialize the carry and temp variables
    int carry = 0;
    string temp;

    // Copy the current BigReal object to the first object
    first.integer = integer;
    first.fraction = fraction;
    first.sign = sign;

    // Pad the integer and fraction parts of the numbers with leading zeros for addition
    first.padding(other);

    // Initialize the integer and fraction parts of the result
    result.integer = "";
    result.fraction = "";

    // Addition for positive numbers
    if ((first.sign != '-' && other.sign != '-') || (first.sign == '-' && other.sign == '-') && op == '+')
    {
        // Add the fractional parts
        for (int i = first.fraction.length() - 1; i >= 0; i--)
        {
            // Add the digits and the carry
            temp = to_string((first.fraction[i] - '0') + (other.fraction[i] - '0') + carry);

            // If the result is greater than 9, set the carry to 1 and add the last digit to the result
            if (temp.length() > 1)
            {
                // Set the carry to 1
                carry = int(temp[0] - '0');
                result.fraction = temp[1] + result.fraction;
            }
            else
            {
                // Set the carry to 0
                carry = 0;
                result.fraction = temp + result.fraction;
            }
        }

        // Add the integer parts
        for (int i = first.integer.length() - 1; i >= 0; i--)
        {
            // Add the digits and the carry
            temp = to_string((first.integer[i] - '0') + (other.integer[i] - '0') + carry);

            if (temp.length() > 1)
            {
                // Set the carry to 1
                carry = int(temp[0] - '0');
                result.integer = temp[1] + result.integer;
            }
            else
            {
                // Set the carry to 0
                carry = 0;
                result.integer = temp + result.integer;
            }
        }
    }
    else {
        if (first.sign == '-') {
            first.sign = '+';
            return (other - first);
        } else {
            other.sign = '+';
            return (first - other);
        }
    }
    // Set the sign of the result
    result.sign = first.sign;
    return result;
}

// Overloaded subtraction operator for BigReal objects
BigReal BigReal::operator-(BigReal &other)
{
    // Set the operator to subtraction
    if (op != '+')
        op = '-';


    BigReal result(""), first("");

    // Initialize the carry and temp variables
    int borrow = 0;
    string temp;

    // Copy the current BigReal object to the first object
    first.integer = integer;
    first.fraction = fraction;
    first.sign = sign;

    first.padding(other);

    result.integer = "";
    result.fraction = "";

    // If the second number is greater than the first, perform subtraction in reverse and negate the result
    if (other > first && first.sign != '-')
    {
        // Perform addition in reverse
        BigReal r1(other - first);
        // Negate the result
        if (other.sign != '-')
        {
            // If the second number is positive, set the sign to negative
            r1.sign = '-';
        }
        else
        {
            // If the second number is negative, set the sign to positive
            r1.sign = '+';
        }

        return r1;
    }

    // If signs are different, perform addition
    if (first.sign == '-' && other.sign != '-' ||
        other.sign == '-' && first.sign != '-' && op == '-')
    {
        char sign;
        // If the second number is negative, perform addition
        if (other.sign == '-')
        {
            // Perform addition
            sign = '+';
        }
        else
        {
            // If the second number is positive, perform subtraction
            sign = '-';
        }
        // Set the signs of the numbers to positive
        first.sign = '+';
        other.sign = '+';
        // Perform addition
        BigReal res(first + other);
        // Set the sign of the result
        res.sign = sign;
        return res;
    }
    else
    {
        // Perform subtraction for positive numbers
        for (int i = first.fraction.length() - 1; i >= 0; i--)
        {
            // Subtract the digits and the borrow
            int num1 = abs(first.fraction[i] - '0' - borrow);
            int num2 = other.fraction[i] - '0';
            // If the result is negative, set the borrow to 1 and add 10 to the result
            if (num1 < num2)
            {
                num1 += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            // Add the last digit to the result
            result.fraction = to_string(num1 - num2) + result.fraction;
        }
        // Subtract the integer parts
        for (int i = first.integer.length() - 1; i >= 0; i--)
        {
            // Subtract the digits and the borrow
            int num1 = abs(first.integer[i] - '0' - borrow);
            int num2 = other.integer[i] - '0';
            // If the result is negative, set the borrow to 1 and add 10 to the result
            if (num1 < num2)
            {
                num1 += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            // Add the last digit to the result
            result.integer = to_string(num1 - num2) + result.integer;
        }
    }

    // Determine the sign of the result
    if (first > other)
    {
        // If the first number is greater than the second, set the sign to positive
        result.sign = first.sign;
    }
    else if (other > first && other.sign != '-')
    {
        // If the second number is greater than the first and the second number is positive, set the sign to negative
        result.sign = '-';
    }
    else
    {
        // If the second number is greater than the first and the second number is negative, set the sign to positive
        result.sign = other.sign;
    }

    return result;
}

// Check if the current BigReal number is less than another BigReal number
bool BigReal::operator<(const BigReal &other) const
{
    // Check if the signs are different
    if (sign == '-' && other.sign != '-')
    {
        // If the current number is negative and the other number is positive, return true
        return true;
    }
    else if (sign != '-' && other.sign == '-')
    {
        // If the current number is positive and the other number is negative, return false
        return false;
    }
    else if (sign == '-' && other.sign == '-')
    {
        // If both numbers are negative, check if the current number is greater than the other number
        if (integer < other.integer)
        {
            return false;
        }
        else if (integer > other.integer)
        {
            return true;
        }
        
        else
        {
            if (fraction == other.fraction)
            {
                return false;
            }
            return !(fraction < other.fraction);
        }
    }
    else
    {
        // If both numbers are positive, check if the current number is less than the other number
        if (integer < other.integer)
        {
            return true;
        }
        else
        {
            return fraction < other.fraction;
        }
    }

    return false;
}

// Check if the current BigReal number is greater than another BigReal number
bool BigReal::operator>(const BigReal &other) const
{
    // Check if the signs are different
    if (sign == '-' && other.sign != '-')
    {
        // If the current number is negative and the other number is positive, return false
        return false;
    }
    else if (sign != '-' && other.sign == '-')
    {
        // If the current number is positive and the other number is negative, return true
        return true;
    }
    else if (sign == '-' && other.sign == '-')
    {
        if (integer > other.integer)
        {
            return false;
        }
        else if (integer < other.integer)
        {
            return true;
        }
        else
        {
            if (fraction == other.fraction)
            {
                return false;
            }
            return !(fraction > other.fraction);
        }
    }
    else
    {
        if (integer > other.integer)
        {
            return true;
        }
        else
        {
            return fraction > other.fraction;
        }
    }

    return false;
}

// Get the total number of digits in the BigReal number
int BigReal::size()
{
    return integer.length() + fraction.length();
}

// Overloaded stream insertion operator for outputting BigReal objects
std::ostream &operator<<(std::ostream &out, BigReal &num)
{
    // Remove leading zeros from the integer part
    num.integer.erase(0, min(num.integer.find_first_not_of('0'), num.integer.size() - 1));

    // Check if the integer part is zero and print accordingly
    if (num.integer.length() == 1 && num.integer[0] == '0')
    {
        // Print the BigReal number
        out << num.integer << "." << num.fraction;
    }
    else
    {
        // Print the BigReal number
        out << num.sign << num.integer << "." << num.fraction;
    }

    return out;
}

// File: BigReal.h
// Author 1: Abdallah Mohamed / 20220185
// Author 2: Yousef Mohamed / 20220405
// Author 3: Mohamed Sabry / 20221122
// Section: S5/S6
// TA: Nardeen/Maya


#include <iostream>

using namespace std;

class BigReal
{

private:

    string fraction, integer;

    char sign , op;

    bool isValid(string realnumber);

public:

    BigReal(string real);

    int size();

    void print();

    BigReal &operator=(BigReal &other);

    BigReal operator+(BigReal &other);

    BigReal operator-(BigReal &other);

    bool operator==(BigReal another);

    void padding(BigReal &second);

    bool operator<(const BigReal &other) const;

    bool operator>(const BigReal &other) const;

    friend std::ostream& operator<<(std::ostream& out,  BigReal& num);

};
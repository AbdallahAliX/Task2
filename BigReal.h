
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

    void print();

    BigReal &operator=(BigReal &other);

    BigReal operator+(BigReal &other);

    BigReal operator-(BigReal &other);

    bool operator==(BigReal another);

    void padding(BigReal &second);

    bool operator<(const BigReal &other) const;

    bool operator>(const BigReal &other) const;
};
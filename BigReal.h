
#include<iostream>
using namespace std; 

class BigReal {

    private:
        
        string fraction, integer;

        char sign;

        bool isValid (string realnumber) ;

    public:

        BigReal(string real);

        BigReal &operator=(BigReal &other); 

        BigReal operator+(BigReal &other); 

        BigReal operator- (BigReal &other);

        BigReal operator== (BigReal &other);
};
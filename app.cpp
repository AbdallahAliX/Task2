#include<iostream>
#include"imp.cpp"

using namespace std;

int main () {

    BigReal n1 ("22.5234141252536");

    BigReal n2 ( "478931.4011111");

    BigReal n3 = n1 + n2 ;

    n3.print();
    
}
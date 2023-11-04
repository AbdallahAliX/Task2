#include<iostream>
#include"imp.cpp"

using namespace std;

int main () {

   BigReal n1 ("23131.44231");

    BigReal n2 ("114412.525");

    BigReal n3 = n1 - n2;

    n3.print();



}
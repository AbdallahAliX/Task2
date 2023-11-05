#include <iostream>
#include "BigReal.cpp"

using namespace std;

int main()
{

   BigReal num1("1212312.22");
   // initalizing variables of type BigReeal
   BigReal num2("123123.22");

   BigReal num3 = num1 + num2; // add function

   BigReal num4 = num1 - num2; // substract function

   cout << "num1 + num2 = " << num3 << endl;

   cout << "num1 - num2 = " << num4 << endl;

   if (num1 > num2)
   {

      cout << "num1 is bigger\n";
   }

   else if (num1 < num2)
   {
      // compare functions
      cout << "num2 is bigger\n";
   }

   else if (num1 == num2)
   {

      cout << "equal\n";
   }

   cout << "num1 size is :" << num1.size() << endl
        << "num2 size is :" << num2.size() << endl;

   BigReal invalid(" -+23145ss15,222"); // invalid number will be turned to 0.0

   cout << invalid << endl;
}
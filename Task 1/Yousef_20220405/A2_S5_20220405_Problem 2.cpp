// File: problem2.cpp
// Purpose: program to convert male speech to inclusive speech
// Author: Youssef Mohamed Safwat.
// Section: 6
// ID: 20220405
// TA: MayaAhmed
// Date: 5 Nov 2023



#include <iostream>
using namespace std;


string check_word( string str , char qutation_mark) { 

    if ( str == "he") str = "he or she";

    else if (str == "He") str = "He or she";

    else if ( str == "him") str = "him or her";

    else if ( str == "his") str = "his or hers";

 return str + qutation_mark;
}

int main ()  {

string str;

getline (cin , str);

string new_string = "" , check_string = "";


for ( int i = 0 ; i < str.length() ; i++) {

    if ( str[i] == '!' || str[i] == '?' ||
         str[i] == '.' || str[i] == ' ' ||
         str[i] == ',' || str[i] == ';' ) {

        new_string += check_word(check_string , str[i]);
        check_string = "";
        
    }

    else { check_string += str[i];}
}


 cout << new_string;

}
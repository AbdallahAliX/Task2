#include<iostream>
#include<regex>
#include"BigReal.h"
#include<string>
#include<algorithm>
#include <cstdlib> 

bool BigReal :: isValid(string realNumber){

    if (regex_match(realNumber, regex("^[+-]?\\d+(\\.\\d*)?$"))) {

        return true;
    }

    else {

        return false;
    }

}

BigReal:: BigReal(string real) {

    bool found_sign = false;

        if (isValid(real)) {

            if (real[0] == '+') {

                sign = '+';

                found_sign = true;
            }


            else if (real[0] == '-') {
                
                sign = '-';

                found_sign = true;
            }

          

          if (!found_sign) {

                if ( real.find('.') != string::npos) {

                integer = real.substr(0 , real.find('.'));

                fraction = real.substr(real.find('.') + 1 , real.size() - 1 );
              }


              else { 

                    integer = real;

                    fraction = "0";
              }
          }


          else { 

                if ( real.find('.') != string::npos) {

                    integer = real.substr(1 , real.find('.') - 1);

                    fraction = real.substr(real.find('.') + 1 , real.size() - 1 );
              }


              else {

                    integer = real.substr(1 , real.size() - 1);
                    fraction = "0";
              }

          }

        }


        else {

            real = "0.0";
            integer = "0";
            fraction = "0";
        }

}



void BigReal ::print() {

    cout << sign << integer << "." << fraction << endl;
}


bool BigReal::operator==(BigReal another) {
    return (sign == another.sign) &&
           (integer == another.integer) &&
           (fraction == another.fraction);
}




void BigReal::padding(BigReal &second) { 

    int pad_int = abs(static_cast<int>(integer.length() - second.integer.length()));
    int pad_fraction = abs(static_cast<int>(fraction.length() - second.fraction.length()));

    string padding_temp = "";

    for ( int i = 0 ; i < pad_int; i++) {
        
        padding_temp += '0';
    }

    string temp = "";

    if ( integer.length() < second.integer.length()) {
         
         temp =  padding_temp +  integer;

         integer = temp;
    }

    else if (integer.length() > second.integer.length()) {
        
         temp =  padding_temp +  second.integer;

         second.integer = temp;
    }


    padding_temp = "";

    for ( int i = 0 ; i < pad_fraction; i++) {
        
        padding_temp += '0';
    }



      if ( fraction.length() < second.fraction.length()) {
         
             fraction += padding_temp;
    }

    else if (fraction.length() > second.fraction.length()) {
        
            second.fraction += padding_temp;
    }

}

    

BigReal BigReal::operator+(BigReal &other){
    
    BigReal result("") ,first("");

    int carry = 0;

    string temp ;

    first.integer = integer;  first.fraction = fraction;

    first.sign = sign;

    first.padding(other);

    result.integer = "";
    result.fraction ="";


    if ( first.sign != '-' && other.sign != '-') {
            
            for ( int i = first.fraction.length() - 1;  i >= 0 ; i--) {
                
                temp = to_string((first.fraction[i] - '0') + (other.fraction[i] - '0') + carry);

                
                 if (temp.length() > 1) {
                      
                      carry = int(temp[0]);
                      result.fraction += temp[1];
                 }

                 else {

                     carry = 0 ;
                     result.fraction += temp;
                 }
            }


            for ( int i = first.integer.length() - 1;  i >= 0 ; i--) {

                temp = to_string((first.integer[i] - '0') + (other.integer[i] - '0')+ carry);

                    if (temp.length() > 1) {
                      
                      carry = int(temp[0]);
                      result.integer += temp[1];
                 }

                 else {

                     carry = 0 ;
                     result.integer += temp;
                 }

            }
    }


    reverse( result.integer.begin() , result.integer.end());
    reverse(result.fraction.begin(), result.fraction.end());
    return result;  

}

bool BigReal::operator<(const BigReal& other) const {
    cout << "Debug: this sign=" << sign << " integer=" << integer << " fraction=" << fraction << endl;
    cout << "Debug: other sign=" << other.sign << " integer=" << other.integer << " fraction=" << other.fraction << endl;

    if (sign == '-' && other.sign == '+') {
        return true; // -x is always less than +x
    } else if (sign == '+' && other.sign == '-') {
        return false; // +x is always greater than -x
    } else if (sign == '+' && other.sign == '+') {
        // For positive numbers without explicit sign
        return integer.length() == other.integer.length() ? integer < other.integer : integer.length() < other.integer.length();
    }

    if (sign != other.sign) {
        return (sign == '-');
    }

    if (sign == '+') {
        if (integer.length() != other.integer.length()) {
            return integer.length() < other.integer.length();
        }
        if (integer != other.integer) {
            return integer < other.integer;
        }
    } else { // sign is '-'
        if (integer.length() != other.integer.length()) {
            return integer.length() > other.integer.length();
        }
        if (integer != other.integer) {
            return integer > other.integer;
        }
    }

    return fraction < other.fraction;
}

bool BigReal::operator>(const BigReal& other) const {
    cout << "Debug: this sign=" << sign << " integer=" << integer << " fraction=" << fraction << endl;
    cout << "Debug: other sign=" << other.sign << " integer=" << other.integer << " fraction=" << other.fraction << endl;

    if (sign == '-' && other.sign == '+') {
        return false; // -x is always less than +x
    } else if (sign == '+' && other.sign == '-') {
        return true; // +x is always greater than -x
    } else if (sign == '+' && other.sign == '+') {
        // For positive numbers without explicit sign
        return integer.length() == other.integer.length() ? integer > other.integer : integer.length() > other.integer.length();
    }
    
    return other < *this;
}





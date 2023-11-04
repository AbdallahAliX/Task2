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
    
    integer.erase(0, min(integer.find_first_not_of('0'),integer.size() - 1));
    cout << sign << integer << "." << fraction << endl;
}


bool BigReal::operator==(BigReal another) {
    
  
    if ( sign != '-' && another.sign != '-') {
         return 
           (integer == another.integer) &&
           (fraction == another.fraction);
    }
    
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
    
    if (op != '-')  op = '+';

    BigReal result("") ,first("");

    int carry = 0;

    string temp ;

    first.integer = integer;  first.fraction = fraction;

    first.sign = sign;

    first.padding(other);

    result.integer = "";
    result.fraction ="";


   


    if ( (first.sign != '-' && other.sign != '-') || (first.sign == '-' && other.sign == '-') && op == '+')  {
            
            for ( int i = first.fraction.length() - 1;  i >= 0 ; i--) {
                
                temp = to_string((first.fraction[i] - '0') + (other.fraction[i] - '0') + carry);

                
                 if (temp.length() > 1) {
                      
                      carry = int(temp[0] - '0');
                      result.fraction = temp[1] + result.fraction;
                 }

                 else {

                     carry = 0 ;
                     result.fraction = temp + result.fraction;
                 }
            }


            for ( int i = first.integer.length() - 1;  i >= 0 ; i--) {

                temp = to_string((first.integer[i] - '0') + (other.integer[i] - '0')+ carry);

                    if (temp.length() > 1) {
                      
                      carry = int(temp[0] - '0');
                      result.integer = temp[1] + result.integer;
                 }

                 else {

                     carry = 0 ;
                     result.integer = temp + result.integer;
                 }

            }
    }


    else {
       
       first.op = op;
       return (first - other);
    }

    result.sign = first.sign;
    return result;  

}




BigReal BigReal::operator-(BigReal &other) {

    if (op != '+') op = '-';


    BigReal result("") ,first("");

    int borrow = 0;

    string temp ;

    first.integer = integer;  first.fraction = fraction;

    first.sign = sign;

    first.padding(other);


    result.integer = "";
    result.fraction ="";


    if ( first < other) {

        BigReal r1 (other - first);
        r1.sign = '-';
        return r1;
   } 


    if ( first.sign == '-' && other.sign != '-'  || 
         other.sign == '-' && first.sign != '-' && op == '-') {
        
        char sign;

        if ( other.sign == '-' )  {
    
            sign = '+';
        }

        else {
            sign = '-';
        }

        first.sign = '+';
        other.sign = '+';
        BigReal res(first + other);
        res.sign = sign;
        return res;
    } 



    else {

        for ( int i = first.fraction.length() - 1  ; i >= 0 ; i--) {

            int num1 = abs(first.fraction[i] - '0' - borrow);
            int num2 = other.fraction[i] - '0';

            if (num1 < num2) {
                num1 += 10;
                borrow = 1;
            } 

            else {
                borrow = 0;
            }
                    
            result.fraction = to_string(num1 - num2) + result.fraction;    

        }


        for ( int i = first.integer.length() - 1 ; i >= 0 ; i--) {

            int num1 = abs(first.integer[i] - '0' - borrow);
            int num2 = other.integer[i] - '0';
            if (num1 < num2) {

                num1 += 10;
                borrow = 1;
            } 

            else {
                borrow = 0;
            }
            result.integer = to_string(num1 - num2) + result.integer;
        }

}

 if ( first > other) {result.sign = first.sign;}
 
 else {result.sign = other.sign;} 


return result;

}


bool BigReal::operator<(const BigReal& other) const {
  
     if ( sign == '-' && other.sign != '-' ) {

        return true;
    }

    else if ( sign != '-' && other.sign == '-') {
        return false;
    }

    else if ( sign == '-' && other.sign == '-') {

        if ( integer < other.integer ) { return false;}

        else {
            return !(fraction < other.fraction);
        }
    }


   else {

        if ( integer < other.integer) {return true;  }

        else {

            return fraction < other.fraction;
        }
   }


}



bool BigReal::operator>(const BigReal& other) const {
   
    if ( sign == '-' && other.sign != '-' ) {

        return false;
    }

    else if ( sign != '-' && other.sign == '-') {
        return true;
    }

    else if ( sign == '-' && other.sign == '-') {

        if ( integer > other.integer ) { return false;}

        else {
            return !(fraction > other.fraction);
        }
    }


   else {



        if ( integer > other.integer) {return true;  }

        else {

            return fraction > other.fraction;
        }
   }
    


}





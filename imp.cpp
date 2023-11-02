#include<iostream>
#include<regex>
#include"BigReal.h"
#include<string>

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

    cout << integer << endl << fraction;
}


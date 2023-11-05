// File: Problem8.cpp
// Purpose: program to print some pattern of stars
// Author: Youssef Mohamed Safwat.
// Section: 6
// ID: 20220405
// TA: MayaAhmed
// Date: 5 Nov 2023



#include <iostream>
using namespace std;

void printStars(int num, int offset) {
    
    for ( int i = 0 ; i < offset ; i++) {
        cout << "  ";
    }

    for (int j = 0 ; j < num ; j++ ) {
        cout << "* "; 
    }

    cout << endl;
}

void pattern(int n, int i) {

    if (n == 1) {
        printStars(1, i);
    }

    else {

        pattern(n / 2, i);               
        printStars(n, i);                
        pattern(n / 2, i + n / 2);     
    }
}

int main() {


    pattern(8, 0); // Adjust the parameters as needed
    return 0;
}
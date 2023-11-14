// File: Problem 6(A).cpp
// Author: Abdallah Mohamed Ali
// Section: S5/S6
// ID: 20220185
// TA: Nardeen/Maya


#include <iostream>

    using namespace std;
    int userInput;

    void binaryPrint(int n) {
        if (n > 1) {
            binaryPrint(n / 2);
        }
        cout << n % 2;
    }

    int main() {
        cout << "Enter a non-negative integer: ";
        cin >> userInput;
        cout << "Binary representation: ";
        binaryPrint(userInput);
        cout << endl;

        return 0;
    }
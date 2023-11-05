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
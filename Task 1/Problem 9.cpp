#include <iostream>

using namespace std;

bool bears(int n) {
    // Base case: if n is already 42, we win!
    if (n == 42) {
        return true;
    }


    // Rule 1: If n is even, return bears(n/2)
    if (n % 2 == 0) {
        if (bears(n / 2)) {
            return true;
        }
    }

    // Rule 2: If n is divisible by 3 or 4, return bears(n - last two digits * next-to-last digit)
    if (n % 3 == 0 || n % 4 == 0) {
        int lastDigit = n % 10;
        int secondLastDigit = (n % 100) / 10;
        int newBears = lastDigit * secondLastDigit;

        // Check if newBears is greater than 0 before making the recursive call
        if (newBears > 0 && bears(n - newBears)) {
            return true;
        }
    }

    // Rule 3: If n is divisible by 5 and greater than or equal to 42, return bears(n - 42)
    if (n >= 42 && n % 5 == 0) {
        if (bears(n - 42)) {
            return true;
        }
    }

    // If none of the rules apply, it's not possible to win
    return false;
}
int main() {
    int startingBears;
    cout << "Enter the initial number of bears: ";
    cin >> startingBears;

    // Check if it's possible to win the bear game
    if (bears(startingBears)) {
        cout << "It's possible to win the bear game with " << startingBears << " bears!" << endl;
    } else {
        cout << "It's not possible to win the bear game with " << startingBears << " bears." << endl;
    }

    return 0;
}
#include <iostream>
#include <string>

using namespace std;

void generateNumbers(const string& prefix, int k) {
    if (k == 0) {
        // Stopping case: print the prefix once by itself
        cout << prefix << endl;
    } else {
        // Recursive case: generate binary numbers with k-digit suffix
        // Generate all binary numbers with k - 1 digits
        generateNumbers(prefix + "0", k - 1);
        generateNumbers(prefix + "1", k - 1);
    }
}

int main() {
    // Get user input for prefix
    cout << "Enter the binary prefix: ";
    string prefix;
    cin >> prefix;

    // Get user input for k
    cout << "Enter the value of k (non-negative integer): ";
    int k;
    cin >> k;

    generateNumbers(prefix, k);

    return 0;
}
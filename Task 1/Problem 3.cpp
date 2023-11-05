#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
// Function to split a string into a vector of strings
vector<string> split(const string& target, const string& delimiter) {
    // Create a vector to store the result
    vector<string> result;
    // Create a string stream to read from the target string
    istringstream stringStream(target);
    // Read from the string stream until the end of the string
    for (string token; getline(stringStream, token, delimiter[0]); ) {
        // Add the token to the result vector
        result.push_back(token);
    }
    // Return the result
    return result;
}

int main() {
    string userInput, delimiter;

    // Get user input for the string and delimiter
    cout << "Enter a string: ";
    getline(cin, userInput);

    cout << "Enter a delimiter: ";
    getline(cin, delimiter);

    // Call the split function
    vector<string> result = split(userInput, delimiter);

    // Print the results
    cout << "Result: ";
    // Loop through the result vector
    for (const auto& str : result) {
        cout << "\"" << str << "\" ";
    }
    cout << endl;

    return 0;
}

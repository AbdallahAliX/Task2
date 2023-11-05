// File: Problem 12.cpp
// Author: Abdallah Mohamed Ali
// Section: S5/S6
// ID: 20220185
// TA: Nardeen/Maya


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Function to calculate points for each keyword or phrase
int calculatePoints(const string& word, const unordered_map<string, int>& keywordPoints) {
    // Convert the word to lowercase
    string lowercaseWord = word;
    transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);

    // Check if the lowercase word is a keyword and return the corresponding points
    auto it = keywordPoints.find(lowercaseWord);
    // If the word is not a keyword, return 0 points
    return (it != keywordPoints.end()) ? it->second : 0; // Return 0 if not found
}

int main() {
    // Map to store points for each keyword
        unordered_map<string, int> keywordPoints = {
        {"password", 3},
        {"account", 2},
        {"verify", 2},
        {"urgent", 3},
        {"update", 2},
        {"login", 3},
        {"confidential", 2},
        {"unusual", 2},
        {"suspicious", 1},
        {"confirm", 2},
        {"validate", 2},
        {"security", 1},
        {"unauthorized", 2},
        {"verification", 2},
        {"important", 2},
        {"information", 1},
        {"access", 1},
        {"expenses", 2},
        {"bank", 2},
        {"credit card", 3},
        {"payroll", 3},
        {"hello", 1},
        {"reset", 1},
        {"invoice", 3},
        {"purchase", 2},
        {"fraud", 3},
        {"request", 2},
        {"required", 1},
        {"action", 2},
        {"new", 1},
    };

    // Get file name from user input
    cout << "Enter the name of the text file: ";
    string fileName;
    cin >> fileName;

    // Open the file
    ifstream inputFile(fileName);
    // Check if the file was opened successfully
    if (!inputFile.is_open()) {
        // If the file was not opened successfully, output an error message and return 1
        cout << "Error opening file." << endl;
        return 1;
    }

    // Map to store actual occurrences of keywords in the file
    unordered_map<string, int> actualOccurrences;

    // Read the file line by line
    string line;
    // Loop through each line
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string word;
        // Loop through each word
        while (iss >> word) {
            // Remove non-alphabetic characters from the word
            word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }), word.end());

            // Convert the word to lowercase
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            // Increment actual occurrences for the keyword
            if (!word.empty() && keywordPoints.find(word) != keywordPoints.end()) {
                actualOccurrences[word]++;
            }
        }
    }

    // Output the results
    int totalPoints = 0;
    // Loop through each keyword
    for (const auto& entry : actualOccurrences) {
        // Output the keyword, number of occurrences, and points
        cout << entry.first << ": " << entry.second << " occurrences, " << entry.second * calculatePoints(entry.first, keywordPoints) << " points" << endl;
        // Add the points to the total points
        totalPoints += entry.second * calculatePoints(entry.first, keywordPoints);
    }

    cout << "Total Points: " << totalPoints << endl;

    // Close the file
    inputFile.close();

    return 0;
}
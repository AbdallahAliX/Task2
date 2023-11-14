// File: Problem 10.cpp
// Author: Mohamed Sabry
// Section: S5/S6
// ID: 20221122
// TA: Nardeen/Maya


#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

map<string, vector<string>> createWordAlternatives(const string &filename)
{
    map<string, vector<string>> wordAlternatives;
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string word;
            vector<string> alternatives;
            if (iss >> word)
            {
                string alternative;
                while (iss >> alternative)
                {
                    alternatives.push_back(alternative);
                }
                wordAlternatives[word] = alternatives;
            }
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open file" << endl;
    }
    return wordAlternatives;
}

string alterMessage(const string &message, const map<string, vector<string>> &wordAlternatives)
{
    string alteredMessage = message;
    for (const auto &pair : wordAlternatives)
    {
        size_t pos = 0;
        while ((pos = alteredMessage.find(pair.first, pos)) != string::npos)
        {
            const vector<string> &alternatives = pair.second;
            srand(time(0));
            string replacement = alternatives[rand() % alternatives.size()];
            alteredMessage.replace(pos, pair.first.length(), replacement);
            pos += replacement.length();
        }
    }
    return alteredMessage;
}

int main()
{
    string inputFile = "input.txt";
    string alternativesFile = "alternatives.txt";
    string outputFile = "output.txt";

    map<string, vector<string>> wordAlternatives = createWordAlternatives(alternativesFile);

    ifstream input(inputFile);
    ofstream output(outputFile);
    if (input.is_open() && output.is_open())
    {
        string message;
        while (getline(input, message))
        {
            string alteredMessage = alterMessage(message, wordAlternatives);
            output << alteredMessage << endl;
        }
        input.close();
        output.close();
    }
    else
    {
        cerr << "Error opening files." << endl;
    }

    return 0;
}
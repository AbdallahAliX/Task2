// File: problem11.cpp
// Purpose: program to compare two files either by word by word comparasion 
// or character by character comparasion
// Author: Youssef Mohamed Safwat.
// Section: 6
// ID: 20220405
// TA: MayaAhmed
// Date: 5 Nov 2023



#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

bool word_comp(string fil1 , string file2);
bool char_comp (string fil1 , string file2);


vector <string> vec1 , vec2;

int main () {

    string file1 , file2;
    char option ;

    cout << "enter file name : ";

    cin >> file1;

   
    cout << "enter second file name :";

    cin >> file2;

    
    
    cout << "choose c or w \n"
             "c - character by character compare\n"
             "w - word by word compare\n";

    cin >> option;


    if ( option == 'c' || option == 'C') { char_comp(file1 , file2);}

    else if ( option == 'w' || option == 'W') {word_comp(file1, file2);}


 }

bool char_comp(string file1 , string file2) {

    fstream f1 , f2;
    string line1 , line2;
    int linecount = 1;

    f1.open(file1 +".txt" , ios::in);
    f2.open(file2 + ".txt" , ios::in);

    if ( f1.is_open() && f2.is_open()) {

        while (getline(f1 , line1 ) && getline(f2 , line2)) {

            if ( line1 != line2) {

                cout << linecount << "-" << line1 << "\n" << linecount << "-" << line2;
                return false;
            }

            vec1.push_back(line1);
            vec2.push_back(line2);
            linecount++;
        }

    }

    if (getline(f1,line1) || getline(f2, line2)) {

        cout << "files have different lengths";
        return false;
    }


    cout << "identical.";
    return true;
}


bool  word_comp (string file1, string file2) {

    fstream f1 , f2;

    f1.open(file1 + ".txt" , ios::in);
    f2.open(file2 +".txt" , ios::in);
 
    string word1 , word2;
    string line1 , line2;


    while(getline(f1,line1)) {
        vec1.push_back(line1);
    }

    while (getline(f2 , line2)) {
        vec2.push_back(line2);
    }


    f1.close(); f2.close();
    f1.open(file1 + ".txt" , ios::in);
    f2.open(file2 +".txt" , ios::in);


    while (f1 >> word1 && f2 >> word2) {
        
        if ( word1 != word2) {
        
        for ( int i = 0 ; i < vec1.size() ; i++) {
    
            line1 = vec1[i];

            if ( line1.find(word1) != string::npos){

                cout << "file1 : \n" << "word :" << word1 << endl;
                cout << "line: " << line1 << endl;
            }
        }

        for ( int i = 0 ; i < vec2.size() ; i++) {
    
            line2 = vec2[i];

            if ( line2.find(word2) != string::npos){

                cout << "file2 : \n" << "word :" << word2 << endl;
                cout << "line: " << line2;
            }
        }

        return false;
    }
}


    if ( f1 >> word1 || f2 >> word2) {
         
         cout << "files have different lengths";
         return false;
    }

    cout << " identical" ;
    return true;
}
        

// File: 5.cpp
// Purpose: program to manages a list of 10 players
// Author: Youssef Mohamed Safwat.
// Section: 6
// ID: 20220405
// TA: MayaAhmed
// Date: 5 Nov 2023

#include <iostream>
#include <vector>
#include<set>
#include<algorithm>
using namespace std;

void output_players();
void input_players();
void search_players();

class players {

  public:
     string name;
     int score;

};

set < pair <int , string>> scores;

int main () { 

  bool state = true ;
  int operation;

  while (state)  { 
    
     cout << "\n choose number of operation you want :\n"
              "1- Add a new player score\n"
              "2- Look for a player score\n"
              "3- Print the top 10 players\n"
              "4- Exit\n";

    cin >> operation;

    switch (operation) {
    
    default:
        cout << "invalid number, try again.";
        break;

    case 1:
        input_players();
        break;
    
    
    case 2 :
        search_players();
        break;


    case 3:
        output_players();
        break;

    case 4:
        state = false;
        break;
    }
  }
}


void input_players() {

    players new_player;
    cout << "enter player name :";
    cin >> new_player.name; 
    cout << "\n" << "enter player score :";
    cin >> new_player.score;

    transform(new_player.name.begin(), new_player.name.end(), new_player.name.begin(), ::tolower); 

    if ( scores.size() == 10) {

        scores.erase(scores.begin());
 }

    scores.insert(make_pair(new_player.score , new_player.name));

}

void output_players() {

set< pair <int , string>> ::reverse_iterator rit; 

    for ( rit = scores.rbegin(); rit != scores.rend() ; rit++) {

        cout << "player name : " << rit->second << ", score : " 
        << rit->first  << "\n";
    }
}


void search_players() {

    string name;
    cout << "enter player name: ";
    cin >> name ;
    transform(name.begin(), name.end(), name.begin(), ::tolower); 

    bool found = false;

    for ( auto it : scores) {
        
        if ( it.second == name ) {
            found = true;
            cout << "player name : " << it.second << ", score : " 
            << it.first  << "\n";    
        }
    }

    if ( !found ) {
        cout << "player does not exist\n";
    }
}
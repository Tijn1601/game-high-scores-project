/**
* @author Valentijn van Overveld
*/

#include "Game.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/** Prints out the Game
* @param o the output
* @param g the game to be printed
* @return the output
*/
ostream& operator<<(ostream& o, const Game& g){
    if(g.name != "" && g.initials == ""){
        o << g.name;
        return o;
    }
    o << "Name: " << g.name << endl;
    o << "High Score: " << g.highScore << endl;
    o << "Initials: " << g.initials << endl;
    o << "Plays: " << g.plays << endl;
    o << fixed << setprecision(2) << "Revenue: $" << g.revenue;
    return o;
}

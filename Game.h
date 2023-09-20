/**
* @author Valentijn van Overveld
*/

#ifndef GAME_H
#define GAME_H
#include <string>
#include <iostream>

class Game
{
    public:
        std::string name = "";
        int highScore;
        std::string initials = "";
        int plays;
        double revenue;

        Game(){}
        Game(std::string n){name = n;}
        Game(std::string n, int hs, std::string i, int p, double r){name = n; highScore = hs; initials = i; plays = p; revenue = r;}
        friend std::ostream& operator<<(std::ostream&, const Game&);
        bool operator<(const Game& g){return name < g.name;}
        bool operator>(const Game& g){return name > g.name;}
        bool operator==(const Game& g){if(name == g.name || name.find(g.name) != std::string::npos)return true; return false;}
        virtual ~Game(){}
};

#endif // GAME_H

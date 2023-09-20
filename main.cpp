/**
* @author Valentijn van Overveld
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <iomanip>
#include "Game.h"
#include "Node.h"
#include "BinTree.h"
#include <queue>

using namespace std;

/** Prints out the nodes in the tree in ascending order
* @param curNode starting from the root, the node that will be printed
*/
void printAsc(Node<Game> *curNode){
    if(curNode->leftPtr)
        printAsc(curNode->leftPtr);
    Game g = curNode->payload;
    cout << g.name << ", " << g.highScore << ", " << g.initials << ", " << g.plays << ", $" << fixed << setprecision(2) << g.revenue << endl;
    if(curNode->rightPtr)
        printAsc(curNode->rightPtr);
}

/** Prints out the nodes in the tree in descending order
* @param curNode starting from the root, the node that will be printed
*/
void printDes(Node<Game> *curNode){
    if(curNode->rightPtr)
        printDes(curNode->rightPtr);
    Game g = curNode->payload;
    cout << g.name << ", " << g.highScore << ", " << g.initials << ", " << g.plays << ", $" << fixed << setprecision(2) << g.revenue << endl;
    if(curNode->leftPtr)
        printDes(curNode->leftPtr);
}

/** Converts a line to a Game
* @param str the string to be turned into a Game
* @return the newly made Game
*/
Game strToGame(string str){
    stringstream ss(str);
    string name, initials, revTemp;
    int highScore, plays;
    double revenue;
    ss >> name;

    //if it has not yet found the second ", it will keep looking for it
    while(name.find("\"", 1) == string::npos){
        string temp;
        ss >> temp;
        name += " ";
        name += temp;
    }
    ss >> highScore >> initials >> plays >> revTemp;
    name = name.substr(1, name.length() - 2);
    revTemp = revTemp.substr(1);
    revenue = stod(revTemp);
    Game g(name, highScore, initials, plays, revenue);
    return g;
}

/** Converts lines from database to Game objects
* @param data the string to be turned into a Game
* @return the newly made Game object
*/
Game dataToGame(string data){
    stringstream ss(data);
    string name, initials, temp;
    int highScore, plays;
    double revenue;
    ss >> name;

    //if it has not yet found the ",", it will keep looking for it
    while(name.find(",", 1) == string::npos){
        string temp;
        ss >> temp;
        name += " ";
        name += temp;
    }
    name = name.substr(0, name.length() - 1);
    //removing comma from highScore
    ss >> temp;
    temp = temp.substr(0, temp.length() - 1);
    highScore = stoi(temp);
    //removing comma from initials
    temp = "";
    ss >> temp;
    temp = temp.substr(0, temp.length() - 1);
    initials = temp;
    //removing comma from plays
    temp = "";
    ss >> temp;
    temp = temp.substr(0, temp.length() - 1);
    plays = stoi(temp);
    //removing the $ from revenue
    temp = "";
    ss >> temp;
    temp = temp.substr(1);
    revenue = stod(temp);
    Game g(name, highScore, initials, plays, revenue);
    return g;
}

/** Uses and tests Game, Node, and BinTree
* @return the status of the code
*/
int main()
{
    string file1, file2;
    cin >> file1 >> file2;
    ifstream firstInput(file1);
    ifstream input(file2);
    ofstream output;
    BinTree<Game> tree;

    //checks if the database exists and adds nodes
    if(firstInput.good()){
        //reads in text from the database and adds to the BinTree
        string line;
        while(getline(firstInput, line)){
            Game g = dataToGame(line);
            tree.root = tree.Insert(g, tree.root);
        }
    }
    firstInput.close();
    output.open(file1);

    //checks for correct input
    if(input.good() && output.good()){
        //reads in text from the update file
        string line;
        while(getline(input, line)){
            char str = line[0];
            //gets rid of the number and the space after it
            line = line.substr(2, line.length() - 2);

            //checks what the number is equal to
            //adds nodes to the tree
            if(str == '1'){
                Game g = strToGame(line);
                tree.root = tree.Insert(g, tree.root);
                cout << "RECORD ADDED" << endl << g << endl << endl;
            //searches for nodes in the tree
            } else if(str == '2'){
                Game g(line);
                Node<Game> *n = tree.Search(g, tree.root);
                if(n){
                    Node<Game> *nLeft = tree.Search(g, n->leftPtr);
                    if(nLeft)
                        cout << nLeft->payload.name << " FOUND" << endl << "High Score: " << nLeft->payload.highScore << endl << "Initials: " << nLeft->payload.initials << endl << "Plays: " << nLeft->payload.plays << endl << fixed << setprecision(2) << "Revenue: $" << nLeft->payload.revenue << endl << endl;
                    cout << n->payload.name << " FOUND" << endl << "High Score: " << n->payload.highScore << endl << "Initials: " << n->payload.initials << endl << "Plays: " << n->payload.plays << endl << fixed << setprecision(2) << "Revenue: $" << n->payload.revenue << endl << endl;
                    Node<Game> *nRight = tree.Search(g, n->rightPtr);
                    if(nRight)
                        cout << nRight->payload.name << " FOUND" << endl << "High Score: " << nRight->payload.highScore << endl << "Initials: " << nRight->payload.initials << endl << "Plays: " << nRight->payload.plays << endl << fixed << setprecision(2) << "Revenue: $" << nRight->payload.revenue << endl << endl;
                } else
                    cout << line << " NOT FOUND" << endl << endl;
                //checks n's left and right pointers for more

            //edits a node
            } else if(str == '3'){
                stringstream ss(line);
                string name;
                ss >> name;

                //if the second " is not found, it keeps looking for it
                while(name.find("\"", 1) == string::npos){
                    string temp;
                    ss >> temp;
                    name += " ";
                    name += temp;
                }
                name = name.substr(1, name.length() - 2);
                int num;
                string newVal;
                ss >> num >> newVal;
                Game g(name);

                //searches for the node whose name is given
                Node<Game> *n = tree.Search(g, tree.root);

                //if the node exists
                if(n){
                    cout << name <<" UPDATED" << endl;

                    //updates the high score
                    if(num == 1){
                        cout << "UPDATE TO high score - VALUE " << newVal << endl;
                        n->payload.highScore = stoi(newVal);
                    //updated the initials
                    } else if(num == 2){
                        cout << "UPDATE TO initials - VALUE " << newVal << endl;
                        n->payload.initials = newVal;
                    //updates the plays and revenue
                    } else if(num == 3){
                        cout << "UPDATE TO plays - VALUE " << newVal << endl;
                        n->payload.plays = stoi(newVal);
                        n->payload.revenue = (stod(newVal) / 4.0);
                    }
                    cout << "High Score: " << n->payload.highScore << endl << "Initials: " << n->payload.initials << endl << "Plays: " << n->payload.plays << endl << fixed << setprecision(2) << "Revenue: $" << n->payload.revenue << endl << endl;
                }
            //removes a node from the tree
            } else if(str == '4'){
                Game g(line);
                tree.root = tree.Delete(g, tree.root);
            //prints the nodes in ascending or descending order
            } else if(str == '5'){
                if(line == "asc"){
                    cout << "RECORDS SORTED ASCENDING" << endl;
                    printAsc(tree.root);
                    cout << endl;
                } else if(line == "des"){
                    cout << "RECORDS SORTED DESCENDING" << endl;
                    printDes(tree.root);
                    cout << endl;
                }
            }
            //clears line
            line = "";
        }

        //prints all of the nodes to the database using breadth first traversal
        if(output.good() && tree.root != nullptr){
            queue<Node<Game>> q;
            q.push(*tree.root);
            while(!q.empty()){
                Node<Game> *n = &q.front();
                Game g = n->payload;
                output << g.name << ", " << g.highScore << ", " << g.initials << ", " << g.plays << ", $" << g.revenue << endl;
                q.pop();
                if(n->leftPtr){
                    q.push(*n->leftPtr);
                }
                if(n->rightPtr){
                    q.push(*n->rightPtr);
                }
            }
        }
    }
    //closes input and output
    input.close();
    output.close();
    return 0;
}

# Game High Scores Project
## Description:
This project uses custom classes to store information about video game high scores. The scores are placed in a binary search tree based on the alphabetical order of the names of the games. Each Game object will store information about the game's name, high score, initials of the user who got the high score, how many times they played the machine, and the revenue the machine made off of the user. The tree will update based on the commands provided and will print the changed information to the console.

## Usage:
When running the program you will need to input the file name for the graph, and after that, you will need to input the file name for the commands that will be executed. For example, "samplegraph.txt update1.txt" will load the information about the current scores from "samplegraph.txt", and then will execute the commands on "update1.txt". Each different command in the commands file has a unique number associated with it, and each command must be separated with a new line. See "update1.txt" for reference.

## Commands:
1 (Game Name) (High Score) (Initials) (Number of Plays) (Revenue) - When using 1 in front of a command, a node with the information given will be added to the tree.

2 (Game Name) - When using 2 in front of a command, the tree will be searched and display the information found about the node.

3 (Game Name) (Any information to be changed) - When 3 is used in front of a command, the tree will update the game to the new information given. If the user wants to change more than one element, the changed elements should be listed after the first.

4 (Game Name) - When 4 is used in front of a command, the tree will delete this node and update the tree accordingly.

5 (asc/des) - When 5 is used in front of a command, the order of the tree will be printed out either in ascending or descending order, depending on what the user details.

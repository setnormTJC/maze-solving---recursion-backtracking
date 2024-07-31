#include <iostream>
#include <string>
#include <vector>
#include<fstream> 
#include<iomanip>

using namespace std;

void printMaze(const char theMaze[11][14])
{
    for (int row = 0; row < 11; row++)
    {
        for (int col = 0; col < 14; col++)
        {
            cout << theMaze[row][col]; 
        }
        cout << "\n";
    }
}

void walkThoughMaze_withUserInput(char maze[11][14], int currentRow, int currentColumn)
{
    while (true) //for now
    {
        char charAbove = maze[currentRow - 1][currentColumn];
        char charBelow = maze[currentRow + 1][currentColumn];

        char charToLeft = maze[currentRow][currentColumn - 1];
        char charToRight = maze[currentRow][currentColumn + 1];


        //cout << "\n\n";
        //cout << "Above is: " << charAbove << "\n";
        //cout << "Below is: " << charBelow << "\n";
        //cout << "To the left is: " << charToLeft << "\n";
        //cout << "To the right is: " << charToRight << "\n";

        cout << "\n\nEnter wasd (w is up, s is down, a is left, d is right) - c to clear screen\n";
        char input;
        cin >> input;

        switch (input)
        {
        case 'w': 
            if (charAbove != ' ')
            {
                cout << "Can't go up - there is a wall there!\n";
            }

            else
            {
                cout << "moving up ...\n";
                maze[currentRow][currentColumn] = ' '; //move from current position (make it an empty space)
                currentRow = currentRow - 1;
                maze[currentRow][currentColumn] = 'C'; //update current

                cout << "\n\nUpdated maze: \n";
                printMaze(maze);
            }
            break;
            

        case 's':
            if (charBelow != ' ')
            {
                cout << "Can't go down - there is a wall there!\n";
            }

            else
            {
                cout << "moving down ...\n";
                maze[currentRow][currentColumn] = ' ';
                currentRow = currentRow + 1;
                maze[currentRow][currentColumn] = 'C';

                cout << "\n\nUpdated maze: \n";
                printMaze(maze);
            }
            break;

        case 'a': 
            if (charToLeft != ' ')
            {
                cout << "Can't go left - there is a wall there!\n";
            }

            else
            {
                cout << "moving left ...\n";
                maze[currentRow][currentColumn] = ' ';
                currentColumn = currentColumn - 1;
                maze[currentRow][currentColumn] = 'C';

                cout << "\n\nUpdated maze: \n";
                printMaze(maze);
            }
            break; 

        case 'd': 
            if (charToRight != ' ')
            {
                cout << "Can't go right - there is a wall there!\n";
            }

            else
            {
                cout << "moving right ...\n";
                maze[currentRow][currentColumn] = ' ';
                currentColumn = currentColumn + 1;
                maze[currentRow][currentColumn] = 'C';

                cout << "\n\nUpdated maze: \n";
                printMaze(maze);
            }
            break; 


        case 'c':
            system("CLS");
            printMaze(maze); 
            break;

        default: 
            cout << "You entered something other than wasd .. or c!\n";
            break;

        }

    }
    
}



int main()
{
    //vector<string> maze = {
    //    "#############",
    //    "#C#         #",
    //    "# # # ### # #",
    //    "# # #   # # #",
    //    "# ### # # # #",
    //    "#     # #   #",
    //    "##### # #####",
    //    "#           #",
    //    "# ######### #",
    //    "#         #E#",
    //    "#############"
    //};1

    //11 rows, 14 columns - INCLUDING \0 char
    char friendlyMaze[11][14] = 
    {
        "TTTTTTTTTTTTT",
        "LC#         R", //C as in CURRENT (AKA: "start")
        "L # # ### # R",
        "L # #   # # R",
        "L ### # # # R",
        "L     # #   R",
        "L#### # ####R",
        "L           R",
        "L ######### R",
        "L         #ER", //E as in "end"
        "BBBBBBBBBBBBB"
    };

    printMaze(friendlyMaze);

    cout << "\n\n";
    //cout << "start is at: " << friendlyMaze[1][1] << "\n";
    int currentRow = 1; 
    int currentColumn = 1;

    //cout << "end? " << friendlyMaze[9][11] << "\n";
    

    ////above - decrement first index (currentRow) by 1
    //cout << "Above " << friendlyMaze[1][1] << " is "
    //    << friendlyMaze[0][1] << "\n";

    ////left - decrement second index (currentColumn) by 1
    //cout << "Left of " << friendlyMaze[1][1] << " is "
    //    << friendlyMaze[1][0] << "\n";

    ////right - INcrement second index (currentColumn) by 1
    //cout << "Right of " << friendlyMaze[currentRow][currentColumn] << " is "
    //    << friendlyMaze[currentRow][currentColumn + 1] << "\n";

    ////below - increment currentRow by 1: 
    //cout << "Below " << friendlyMaze[currentRow][currentColumn]
    //    << "  is " << friendlyMaze[currentRow + 1][currentColumn];

    //if (friendlyMaze[currentRow + 1][currentColumn] == ' ')
    //{
    //    cout << "(a blank space)\n";
    //}

    walkThoughMaze_withUserInput(friendlyMaze, currentRow, currentColumn);

}
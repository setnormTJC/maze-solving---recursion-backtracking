#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include<fstream> 
#include<iomanip>

#include<random>




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

/*
@returns the number of moves required to get to end of maze
*/
int walkThoughMaze_automated(char maze[11][14], int currentRow, int currentColumn, 
    int finishRow, int finishColumn)
{
    random_device rd; 
    std::mt19937 rng(time(0));
    uniform_int_distribution<int> distribution(0, 3);// 0 - 3 -> wasd 

    int moveCount = 0; 

    while ( currentRow != finishRow || currentColumn != finishColumn )
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

        cout << "\n\nRandomly picking direction ... (w is up, s is down, a is left, d is right)\n";
        char inputChoices[4] = { 'w', 'a', 's', 'd' };
        
        char input = inputChoices[distribution(rng)];

        
        //cin >> input;

        switch (input)
        {
        case 'w':

            if (charAbove == 'E') //the win condition 
            {
                maze[currentRow][currentColumn] = ' '; //move from current position (make it an empty space)
                currentRow = currentRow - 1;
                maze[currentRow][currentColumn] = 'C'; //update current

                moveCount++;

                cout << "Done!\n";
            }

            else if (charAbove != ' ')
            {
                //cout << "Can't go up - there is a wall there!\n";
            }

          
            else
            {
                //cout << "moving up ...\n";
                maze[currentRow][currentColumn] = ' '; //move from current position (make it an empty space)
                currentRow = currentRow - 1;
                maze[currentRow][currentColumn] = 'C'; //update current

                moveCount++; 

                //cout << "\n\nUpdated maze: \n";
                //printMaze(maze);
            }
            break;


        case 's':

            if (charBelow == 'E') //the win condition 
            {
                maze[currentRow][currentColumn] = ' ';
                currentRow = currentRow + 1;
                maze[currentRow][currentColumn] = 'C';

                moveCount++;

                cout << "Done!\n";
            }

            else if (charBelow != ' ')
            {
                //cout << "Can't go down - there is a wall there!\n";
            }


            else
            {
                //cout << "moving down ...\n";
                maze[currentRow][currentColumn] = ' ';
                currentRow = currentRow + 1;
                maze[currentRow][currentColumn] = 'C';

                moveCount++;

                //cout << "\n\nUpdated maze: \n";
                //printMaze(maze);
            }
            break;

        case 'a':

            if (charToLeft == 'E') //the win condition 
            {
                maze[currentRow][currentColumn] = ' ';
                currentColumn = currentColumn - 1;
                maze[currentRow][currentColumn] = 'C';

                moveCount++;

                cout << "Done!\n";
            }

            else if (charToLeft != ' ')
            {
                //cout << "Can't go left - there is a wall there!\n";
            }


            else
            {
                //cout << "moving left ...\n";
                maze[currentRow][currentColumn] = ' ';
                currentColumn = currentColumn - 1;
                maze[currentRow][currentColumn] = 'C';

                moveCount++;

                //cout << "\n\nUpdated maze: \n";
                //printMaze(maze);
            }
            break;

        case 'd':
            if (charToRight == 'E') //the win condition 
            {
                maze[currentRow][currentColumn] = ' ';
                currentColumn = currentColumn + 1;
                maze[currentRow][currentColumn] = 'C';

                moveCount++;

                cout << "Done!\n";
            }

            else if (charToRight != ' ')
            {
                //cout << "Can't go right - there is a wall there!\n";
            }


            else
            {
                //cout << "moving right ...\n";
                maze[currentRow][currentColumn] = ' ';
                currentColumn = currentColumn + 1;
                maze[currentRow][currentColumn] = 'C';

                moveCount++;

                //cout << "\n\nUpdated maze: \n";
                //printMaze(maze);
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

        //system("pause");

    }

    //system("cls")
    printMaze(maze);

    cout << "It took " << moveCount << " moves to get to the finish line\n";

    return moveCount; 
}

void walkThoughMaze_withUserInput(char maze[11][14], int currentRow, int currentColumn, 
    int finishRow, int finishColumn)
{
    while (currentRow != finishRow || currentColumn != finishColumn)
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

            if (charBelow == 'E')
            {
                cout << "Winnah!\n";
                maze[currentRow][currentColumn] = ' ';
                currentRow = currentRow + 1;
                maze[currentRow][currentColumn] = 'C';

            }

            else if (charBelow != ' ')
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

    //time_t
    time_t current;
    //cout << time(&current) << endl;
    //cout << ctime(&current) << endl;
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

    int finishRow = 9; 
    int finishColumn = 11;
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

    //walkThoughMaze_withUserInput(friendlyMaze, currentRow, currentColumn, 
    //    finishRow, finishColumn);
    //float averageMoveCount = 0.0; 

    //const int NUMBER_OF_EXPERIMENTS = 100; 
    //int sumMoveCount = 0; 
    //for (int i = 0; i < NUMBER_OF_EXPERIMENTS; i++)
    //{
/*        sumMoveCount += */walkThoughMaze_automated(friendlyMaze, currentRow, currentColumn,
                            finishRow, finishColumn);

        //reset to original position: 
    //    currentRow = 1;
    //    currentColumn = 1;
    //}
    
    // record of moveCounts needed: 
    //1900
    // 580
    // 950
    // 
    // 140
    // 386
    // 1494
    // 626
    // 1204
    
    //cout << "Average moves required: " << (double)sumMoveCount / NUMBER_OF_EXPERIMENTS << "\n";
}
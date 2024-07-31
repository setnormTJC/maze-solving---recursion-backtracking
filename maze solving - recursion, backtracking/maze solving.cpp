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
int randomlyWalkThroughMaze(char maze[11][14], int currentRow, int currentColumn, 
    int finishRow, int finishColumn)
{
    //random_device rd; //rd may be used instead of time(0)
    std::mt19937 rng(time(0)); //time(0) -> returns a long long -> ~number of seconds since the year 1970 
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


bool neighborIsWall(char neighbor)
{
    return neighbor == '#';
}

/*
ONE scenario: IF left, right, and below are a wall THEN charAbove's row and column have already been visited
ex: you fell into a "well" 
@param neighbors -> order of neighbors array is: above, below, left, right
*/
bool checkIfBacktrackingNeeded(bool alreadyVisitedGrid[11][14], vector<char> neighbors, int currentRow, int currentColumn)
{

    int numberOfNeighboringWalls = std::count_if(neighbors.begin(), neighbors.end(), neighborIsWall);

    int numberOfVisitedNeighbors = 0; //note: cannot visit a wall 
    if (alreadyVisitedGrid[currentRow - 1][currentColumn] == true) //already visited above 
    {
        numberOfVisitedNeighbors++; 
    }

    if (alreadyVisitedGrid[currentRow + 1][currentColumn] == true) //already visited below
    {
        numberOfVisitedNeighbors++;
    }

    if (alreadyVisitedGrid[currentRow][currentColumn - 1] == true) //ditto left
    {
        numberOfVisitedNeighbors++;
    }

    if (alreadyVisitedGrid[currentRow][currentColumn + 1] == true) //right
    {
        numberOfVisitedNeighbors++;
    }

    //cout << "Number of neighboring walls: " << numberOfNeighboringWalls << "\n";

     //If three neighbors are a wall, the remaining neighbor MUST have already been visited (if wasd movement only)
    // AND you have reached a dead end
    if (numberOfNeighboringWalls == 3)
    {
        std::cout << "\033[31m"; //red text 
        cout << "It seems you've hit a dead end - allowing backtracking for this \"turn\"\n";
        std::cout << "\033[0m";


        return true; 
    }

    //OR: if two are a wall and the remaining two have already been visited ... (I suppose the third case is unlikely?) 
    else if (numberOfNeighboringWalls == 2)
    {
        if (numberOfVisitedNeighbors == 2)
        {
            return true;
        }
        //example scenario for a dead end: 
        //left is wall, right is wall and up and down have both been visited: 

        //if () //handle "cycle type scenario" 
        //{

        //}
        //return false; 
    }


    else if (numberOfNeighboringWalls == 1 )
    {
        if (numberOfVisitedNeighbors == 3)
        {
            return true; 
        }
    }
    //may find other conditions for dead end

    //else
    //{

    //}
    return false;
    


}

void walkThroughMaze_withUserInput(char maze[11][14], int currentRow, int currentColumn, 
    int finishRow, int finishColumn)
{

    bool alreadyVisitedGrid[11][14]; 
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            alreadyVisitedGrid[i][j] = false; 
        }
    }
    alreadyVisitedGrid[currentRow][currentColumn] = true; 

    int moveCount = 0; 

    while (currentRow != finishRow || currentColumn != finishColumn)
    {
        char charAbove = maze[currentRow - 1][currentColumn];
        char charBelow = maze[currentRow + 1][currentColumn];

        char charToLeft = maze[currentRow][currentColumn - 1];
        char charToRight = maze[currentRow][currentColumn + 1];

        vector<char> neighbors = { charAbove, charBelow, charToLeft, charToRight };


        bool backtrackingNeeded = checkIfBacktrackingNeeded(alreadyVisitedGrid, neighbors, currentRow, currentColumn); 
        //ONE scenario: left, right, and below are a wall and charAbove's row and column have already been visited

        
        //backtracking SHOULD be allowed in THIS case
        if (moveCount > 1 && backtrackingNeeded) //moveCount > 1 because start position might be in a "corner" 
        {
            std::cout << "\033[31m"; //red text 
            cout << "Need for backtracking was detected - we'll allow it for this \"turn\"\n"; 
            system("pause");
            std::cout << "\033[0m";

        }


        cout << "\n\nEnter wasd (w is up, s is down, a is left, d is right) - c to clear screen\n";
        char input;
        cin >> input;		//backtrackingNeeded	true	bool


        switch (input)
        {
        case 'w': 

            if (charAbove == '#'
                || 
                (alreadyVisitedGrid[currentRow - 1][currentColumn] == true && !backtrackingNeeded))
            {
                std::cout << "\033[31m"; //red text 

                cout << "Either there is a wall there OR you've already been there - no backtracking until dead end!\n";
            }

            else
            {
                cout << "moving up ...\n";
                maze[currentRow][currentColumn] = ' '; //move from current position (make it an empty space)
                currentRow = currentRow - 1;
                maze[currentRow][currentColumn] = 'C'; //update current

            }
            break;
            

        case 's':
            if (charBelow == '#'
                     ||
               (alreadyVisitedGrid[currentRow + 1][currentColumn] == true && !backtrackingNeeded))
            {
                std::cout << "\033[31m"; //red text 
                cout << "Either there is a wall there OR you've already been there - no backtracking until dead end!\n";
            }

            else
            {
                cout << "moving down ...\n";
                maze[currentRow][currentColumn] = ' ';
                currentRow = currentRow + 1;
                maze[currentRow][currentColumn] = 'C';

            }
            break;

        case 'a': 
            if (charToLeft == '#'
                ||
                (alreadyVisitedGrid[currentRow][currentColumn - 1] == true && !backtrackingNeeded))
                
            {
                std::cout << "\033[31m"; //red text 
                cout << "Either there is a wall there OR you've already been there - no backtracking until dead end!\n";
            }

            else
            {
                cout << "moving left ...\n";
                maze[currentRow][currentColumn] = ' ';
                currentColumn = currentColumn - 1;
                maze[currentRow][currentColumn] = 'C';

            }
            break; 

        case 'd': 
            if (charToRight == '#' 
                ||
                (alreadyVisitedGrid[currentRow][currentColumn + 1] == true && !backtrackingNeeded))
            {
                std::cout << "\033[31m"; //red text 
                cout << "Either there is a wall there OR you've already been there - no backtracking until dead end!\n";
            }

            else
            {
                cout << "moving right ...\n";
                maze[currentRow][currentColumn] = ' ';
                currentColumn = currentColumn + 1;
                maze[currentRow][currentColumn] = 'C';

            }
            break; 


        case 'c':
            system("CLS");
            break;

        default: 
            cout << "You entered something other than wasd .. or c!\n";
            break;

        }

        std::cout << "\033[0m"; //resets to default terminal text color
        cout << "\n\nUpdated maze: \n";
        printMaze(maze);

        moveCount++; 

        //update the list of already visited locations
        alreadyVisitedGrid[currentRow][currentColumn] = true; 

    }

    std::cout << "\033[35m";
    cout << "Winnah!\n It took " << moveCount << " moves.\n";
    std::cout << "\033[0m";
}

//struct PositionPair
//{
//    int row; 
//    int col; 
//};



//void backtrack(char maze[11][14], vector<PositionPair> positions)
//{
//    if (positions[positions.size() - 1].row != 9
//        ||
//        positions[positions.size() - 1].col != 11)
//    {
//        return; //reject soln
//    }
//
//    if (positions[positions.size() - 1].row == 9
//        &&
//        positions[positions.size() - 1].col == 11)
//    {
//        cout << "Solution found\n";
//        for (auto& position : positions)
//        {
//            cout << "(" << position.row << " , " << position.col << "\n";
//        }
//    }
//
//
//}

int main()
{
    //vector<string> maze = {
        //"#############",
        //"#C#         #",
        //"# # # ### # #",
        //"# # #   # # #",
        //"# ### # # # #",
        //"#     # #   #",
        //"##### # #####",
        //"#           #",
        //"# ######### #",
        //"#         #E#",
        //"#############"
    //};1

    //time_t
    //time_t current;
    //cout << time(&current) << endl;
    //cout << ctime(&current) << endl;
    //11 rows, 14 columns - INCLUDING \0 char
    char friendlyMaze[11][14] = 
    {
        "#############",
        "#C#         #",
        "# # # ### # #",
        "# # #   # # #",
        "# ### # # # #",
        "#     # #   #",
        "##### # #####",
        "#           #",
        "# ######### #",
        "#         #E#",
        "#############"
    };

    printMaze(friendlyMaze);

    cout << "\n\n";
    //cout << "start is at: " << friendlyMaze[1][1] << "\n";
    int currentRow = 1; 
    int currentColumn = 1;

    int finishRow = 9; 
    int finishColumn = 11;


    //walkThroughMaze_withUserInput(friendlyMaze, currentRow, currentColumn,
    //    finishRow, finishColumn);



    //backtrackWalkthroughMaze(friendlyMaze, currentRow, currentColumn,
    //    finishRow, finishColumn);


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

    //walkThroughMaze_withUserInput(friendlyMaze, currentRow, currentColumn, 
    //    finishRow, finishColumn);
    //float averageMoveCount = 0.0; 

    //const int NUMBER_OF_EXPERIMENTS = 100; 
    //int sumMoveCount = 0; 
    //for (int i = 0; i < NUMBER_OF_EXPERIMENTS; i++)
    //{
///*        sumMoveCount += */randomlyWalkThroughMaze(friendlyMaze, currentRow, currentColumn,
//                            finishRow, finishColumn);

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
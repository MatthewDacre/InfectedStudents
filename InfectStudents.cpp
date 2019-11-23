#include <iostream>
#include <vector>
#include <utility>
using namespace std;
void printGrid(vector<vector<int>> grid)
{
    //cout << " - - - - - " << endl;
    for(auto i : grid)
    {
        for(auto j : i)
        {
            cout<< "|" << j << "|";
        }
        cout << endl;
        //cout<<" - - - - - " << endl;
    }
}

int countAdj(vector<vector<int>> grid, pair<int, int> coord)
{
    int row = coord.first;
    int col = coord.second;
    int matrixSize = grid.size() - 1;
    int count = 0;
    //Top left corner
    if(row == 0 && col == 0)
    {
        int right = grid[row][(col + 1)];
        int down = grid[row + 1][col];
        return right + down;
    }
    //Top right corner
    else if(row == 0 && col == matrixSize)
    {
        int left = grid[row][col - 1];
        int down = grid[row + 1][col];
        return left + down;
    }
    //Bottom left corner
    else if(row == matrixSize && col == 0)
    {
        int right = grid[row][(col + 1)];
        int up = grid[row - 1][col];
        return right + up;
    }
    //Bottom right corner
    else if(row == matrixSize && col == matrixSize)
    {
        int up = grid[row - 1][col];
        int left = grid[row][col - 1];
        return up + left;
    }
    //Top row, any position, not top left or right
    else if(row == 0)
    {
        int left = grid[row][col - 1];
        int right = grid[row][(col + 1)];
        int down = grid[row + 1][col];
        return left + right + down;
    }
    //Leftmost column, any position except top/bottom left
    else if(col == 0)
    {
        int down = grid[row + 1][col];
        int up = grid[row - 1][col];
        int right = grid[row][(col + 1)];
        return down + up + right;
    }
    //Bottom row, any position except bottom left/right
    else if(row == matrixSize)
    {
        int left = grid[row][col - 1];
        int right = grid[row][(col + 1)];
        int up = grid[row - 1][col];
        return left + right + up;
    }
    //Right most column, not including top/bottom right
    else if(col == matrixSize)
    {
        int up = grid[row - 1][col];
        int down = grid[row + 1][col];
        int left = grid[row][col - 1];
        return up + down + left;
    }
    //All other interior elements
    else
    {
        int up = grid[row - 1][col];
        int down = grid[row + 1][col];
        int left = grid[row][col - 1];
        int right = grid[row][(col + 1)];
        return up + down + left + right;
    }

}

vector<vector<int>> infectGrid(vector<vector<int>> grid)
{
    vector<vector<int>>pGrid = grid;
    for(int row = 0; row < pGrid.size(); row++)
    {
        for(int col = 0; col < pGrid[row].size(); col++)
        {
            if(pGrid[row][col] != 1 && countAdj(pGrid, make_pair(row, col)) > 1)
            {
                grid[row][col] = 1;
            }
        }
    }
    return grid;
}

bool totalInfect(vector<vector<int>> grid)
{
    for(int row = 0; row < grid.size(); row++)
    {
        for(int col = 0; col < grid[row].size(); col++)
        {
            if(grid[row][col] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

int main() {

        vector<vector<int>> grid;
        //Initialising a 5 by 5 grid of uninfected students. 0 = uninfected, 1 = infected
    //        {{0,0,0,0,0},
    //        {0,0,0,0,0},
    //        {0,0,0,0,0},
    //        {0,0,0,0,0},
    //        {0,0,0,0,0}};
        for(int row = 0; row < 5; row++)
        {
            vector<int>tempRow;
           for(int col = 0; col < 5; col++)
            {
               tempRow.push_back(0);
            }
           grid.push_back(tempRow);
        }
        //Random number between 5 and 7 (inclusive) of infected students
        int numInitInfect = 6;
        //int numInitInfect = 15;
        cout<<"<----------------------------------------------------------------------------->" << endl;
        cout << "Number of students infected initially: " <<numInitInfect << endl;
        //Initial Grid being set up
        for(int i = 0; i < numInitInfect; i++)
        {
            int randRow = rand() % 5;
            int randCol = rand() % 5;
            if(grid[randRow][randCol] == 1)
            {
                i--;
            }
            else
            {
                grid[randRow][randCol] = 1;
            }
        }
        cout<<"Initial grid:" << endl;
        printGrid(grid);
        vector<vector<int>> prevGrid;
        int countIter = 0;
        bool canInfect = true;
        while(!totalInfect(grid))
        {
            prevGrid = grid;
            grid = infectGrid(grid);
            if(prevGrid == grid)
            {
                canInfect = false;
                break;
            }
            else
            {
                countIter++;
                cout<<"Iteration " << countIter<<endl;
                printGrid(grid);
            }
        }
        if(canInfect)
        {
            cout<<"\n\n"<<"-----------------------------------------------------------------------------"<<endl;
            cout<<"FINAL GRID"<<endl;
            printGrid(grid);
            cout<<"Total number of Iterations: "<< countIter <<endl;
        }
        else
        {
            cout<<"\n\n"<<"-----------------------------------------------------------------------------"<<endl;
            cout<<"Could not totally infect grid"<<endl;
            cout<<"FINAL GRID"<<endl;
            printGrid(grid);
            cout<<"Total number of Iterations: "<< countIter <<endl;
        }
    return 0;
}
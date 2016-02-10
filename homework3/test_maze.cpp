#include <string>
#include <iostream>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
int main()
{
    string maze[10] = {
	"XXXXXXXXXX",
	"X........X",
	"XX.X.XXXXX",
	"X..X.X...X",
	"X..X...X.X",
	"XXXX.XXX.X",
	"X.X....XXX",
	"X..XX.XX.X",
	"X...X....X",
	"XXXXXXXXXX"
    };

    //if (pathExists(maze, 10,10, 6,4, 1,1))
    if (pathExists(maze, 10,10, 6,4, 8,3))
    //if (pathExists(maze, 10,10, 6,4, 5,8))
	cout << "Solvable!" << endl;
    else
	cout << "Out of luck!" << endl;

}

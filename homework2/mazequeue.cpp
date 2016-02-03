#include <queue>
#include <string>
#include <iostream>
using namespace std;
class Coord{
    public:
        Coord(int rr, int cc): m_r(rr), m_c(cc){}
	int r() const{ return m_r;}
	int c() const{ return m_c;}
    private:
        int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    queue<Coord> coordQueue;

    Coord start_point(sr, sc);
    Coord end_point(er, ec);
    coordQueue.push(start_point);
    maze[start_point.r()][start_point.c()] = 'O';

    while(!coordQueue.empty()){
        Coord curr = coordQueue.front();
	//cerr << "( " << curr.r() << ", " << curr.c() << " )" << endl;
	coordQueue.pop();

	int curr_r = curr.r();
	int curr_c = curr.c();
	if(curr_r == end_point.r() && curr_c == end_point.c()) 
	    return true;
	else{
	    if(curr_r - 1 >= 0 && maze[curr_r - 1][curr_c] == '.'){ // North
	        Coord next_point(curr_r - 1,  curr_c);
		maze[curr_r - 1] [curr_c] = 'O';
		coordQueue.push(next_point);
	    }
	    if(curr_c + 1 < nCols && maze[curr_r][curr_c + 1] == '.'){ // East
	        Coord next_point(curr_r,  curr_c + 1);
		maze[curr_r] [curr_c + 1] = 'O';
		coordQueue.push(next_point);
	    }   
	    if(curr_r + 1 < nRows && maze[curr_r + 1][curr_c] == '.'){ // South
	        Coord next_point(curr_r + 1,  curr_c);
		maze[curr_r + 1][curr_c] = 'O';
		coordQueue.push(next_point);
	    }
	    if(curr_c - 1 >= 0 && maze[curr_r ][curr_c - 1] == '.'){ // West
	        Coord next_point(curr_r,  curr_c - 1);
		maze[curr_r][curr_c - 1] = 'O';
		coordQueue.push(next_point);
	    }
	}
    }
    return false;
}

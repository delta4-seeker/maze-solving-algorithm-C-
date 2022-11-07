#include <iostream>

#include<vector> // vector is a dynamic array 

#define N 4

#define MAX 5 // size of array to define problem
using namespace std;

class TwoDirection {

  char movement[10]; // to store solution string 
  // function to check it current position is a valid move or not 
  bool positionIsValid(int problemazeProblemazeProblem[N][N], int x, int y) {

    if (x >= 0 && x < N && y >= 0 && y < N && problemazeProblemazeProblem[x][y] == 1) {
      return true;
    }
    return false;
  }
  // check if the current position is destination 
  bool positionIsDestination(int x, int y) {
    if (x == N - 1 && y == N - 1) return true;

    return false;

  }
  // avoid travelling same path because it might put our traversal into loops
  bool positionAlreadyTraveled(int x, int y, int solution[N][N]) {
    if (solution[x][y] == 1) {
      return true;
    }
    return false;
  }
  // function to print solution matrix 
  void printSolutionRoute(int SolutionMatrix[N][N]) {

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cout << "	" << SolutionMatrix[i][j];
      }
      cout << endl;
    }

  }
  // function to check adjacent position and choose next move with the help of recursion 
  bool findRoute(int mazeProblem[N][N], int positionX, int positionY, int solutionMatrix[N][N]) {

    if (positionIsDestination(positionX, positionY) == true) { // return true is position is destination 
      solutionMatrix[positionX][positionY] = 1;
      return true;
    }

    if (positionIsValid(mazeProblem, positionX, positionY) == true) { // check for position to be valid 
      if (positionAlreadyTraveled(positionX, positionY, solutionMatrix) == true) {
        return false; // if position is already traveled , no path is detected
      }
      solutionMatrix[positionX][positionY] = 1; // set the solution matrix position to 1 as the position is traversable

      // check for position right to current position 
      if (findRoute(mazeProblem, positionX + 1, positionY, solutionMatrix) == true) {
        movement[positionX + positionY] = 'D'; // if right position is valid, move to right and add D to movement.
        // we add D when we travel right because the algorithm is backtrack and reversing the path decodes moving right is moving down from end to start 

        return true;
      }

      if (findRoute(mazeProblem, positionX, positionY + 1, solutionMatrix) == true) {
        movement[positionX + positionY] = 'R'; // if right position is valid, move to right and add D to movement.

        return true;
      }
    }
    return false;
  }
  public:
    void solve(int mazeProblem[N][N], int positionX, int positionY) {

	
	int solutionMatrix[N][N] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}};
		

      //check if initial position is valid 

      if (positionIsValid(mazeProblem, positionX, positionY) == true) {

        bool solutionExist = findRoute(mazeProblem, positionX, positionY, solutionMatrix); // finding route
        if (solutionExist) { // if route exist 
          cout << "Given maze problem is : " << endl;
          printSolutionRoute(mazeProblem);
          cout << endl << "Using only two direction ";
          cout << "(D-Down and R-Right) : ";

          for (int i = 0; i < 2 * N - 2; i++) {
            cout << movement[i];
          }
          cout << endl;

          printSolutionRoute(solutionMatrix);
          // since array are passed by reference, SolutionMatrix is updated while assigning solutionExist variable.
        } else {
          cout << endl << "Solution Doesnt exist. No route Found.";
        }
      } else {
        cout << endl << "Invalid initial position. " << endl;
      }
    }

};

class FourDirection {

  // fucntion to check if the current position is within bound and not blocked in maze matrix.
  bool positionIsValid(int positionX, int positionY, int mazeProblem[][MAX], bool visited[][MAX]) {
    if (positionX == -1 || positionX == MAX || positionY == -1 ||
      positionY == MAX || visited[positionX][positionY] ||
      mazeProblem[positionX][positionY] == 0)
      return false;

    return true;
  }
  // function to check if the position has reached destination or not 
  bool positionIsDestination(int positionX, int positionY) {
    if (positionX == MAX - 1 && positionY == MAX - 1) {
      return true;
    }
    return false;
  }

  // function to check all possible path up, down, right , left and trace the possible path by pushing commands into string datatype
  void findRoute(int positionX, int positionY, int mazeProblem[][MAX], string & route, vector < string > & possibleRoutes, bool visited[][MAX]) {
    // checking if the initial position is vaild or not. 
    if (positionIsValid(positionX, positionY, mazeProblem, visited) == false) {
      return;
    }
    // checking if destination is reached 
    if (positionIsDestination(positionX, positionY)) {
      possibleRoutes.push_back(route);
      return;
    }
    // set the visited flag to avoid repeatation of routes
    visited[positionX][positionY] = true;

    // Check if downward position is valid
    if (positionIsValid(positionX + 1, positionY, mazeProblem, visited)) {
      route.push_back('D'); // store d is downward position is valid 
      findRoute(positionX + 1, positionY, mazeProblem,
        route, possibleRoutes, visited); //recursion funtion to move forward 
      route.pop_back(); // once the above recursion function returns, the character is popped so new possible route can be recorded
    }

    // Check if the left position is valid
    if (positionIsValid(positionX, positionY - 1, mazeProblem, visited)) {
      route.push_back('L');
      findRoute(positionX, positionY - 1, mazeProblem,
        route, possibleRoutes, visited);
      route.pop_back();
    }

    // Check if the right position is valid
    if (positionIsValid(positionX, positionY + 1, mazeProblem, visited)) {
      route.push_back('R');
      findRoute(positionX, positionY + 1, mazeProblem,
        route, possibleRoutes, visited);
      route.pop_back();
    }

    // Check if the upper position is valid
    if (positionIsValid(positionX - 1, positionY, mazeProblem, visited)) {
      route.push_back('U');
      findRoute(positionX - 1, positionY, mazeProblem,
        route, possibleRoutes, visited);
      route.pop_back();
    }

    visited[positionX][positionY] = false; // once the recursion for one path is completed, this position flag is reset for other possible path
  }

  // function to print the string from possible routes string array
  void printSolutionRoutes(vector < string > possibleRoutes) {
    for (int i = 0; i < possibleRoutes.size(); i++)
      cout << possibleRoutes[i] << " ";
  }

  // function to store data and initial solution of maze
  public:
    void solve(int mazeProblem[MAX][MAX]) {
      // vector, a dynamic array to store all the possible routes
      vector < string > possibleRoutes;
      string route;
      bool visited[MAX][MAX];
      memset(visited, false, sizeof(visited));

      findRoute(0, 0, mazeProblem, route,
        possibleRoutes, visited); // recursion function initial invoke

      cout << endl << "Given Problem is : " << endl; // print the maze matrix 
      for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
          cout << "	" << mazeProblem[i][j];
        }
        cout << endl;
      }
      cout << endl << "All possible Solutions are( D-Down R-Right L-Left U-Up) :" << endl;
      printSolutionRoutes(possibleRoutes);
      cout << endl;

    }

};

void TwoDirectionProblem() {

	int mazeProblem[N][N] = {
	{1, 0, 0, 0},
	{1, 1, 0, 1},
	{0, 1, 0, 0},
	{1, 1, 1, 1}};
	

  int positionX = 0, positionY = 0;
  TwoDirection maze2D;
  maze2D.solve(mazeProblem, positionX, positionY);
  // maze matrix problem 

}

void FourDirectionProblem() {

	int mazeProblem[MAX][MAX] = 
					{ {   1, 1, 1, 1, 0 },
						{ 0, 0, 0, 1, 0 },
						{ 1, 1, 0, 1, 0 },
						{ 1, 1, 0, 1, 0 },
						{ 1, 1, 0, 1, 1 } };
 
  FourDirection maze4D;
  // function to store temp data , initial recursion and print result 	

  maze4D.solve(mazeProblem);

}

int main()

{

  cout << "MAZE SOLVE !!!!" << endl;

  cout << "Select input : " << endl << "1) Two directional solution." << endl << "2) Four directional solution" << endl;
  int x;
  cin >> x;
  switch (x) {

  case 1:
    TwoDirectionProblem();
    break;

  case 2:
    FourDirectionProblem();
    break;

  default:
    break;

  }

  return 0;
}
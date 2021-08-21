// stack.h
// declare the 16 functions

#define DIMENSIONS 	50	

typedef struct {
	int x, y;
} coordinates;

void MARK(coordinates);
coordinates MOVE_U(coordinates);
coordinates MOVE_D(coordinates);
coordinates MOVE_L(coordinates);
coordinates MOVE_R(coordinates);
int CWU(coordinates, char maze[DIMENSIONS][DIMENSIONS]); // returns 1 if there is an inch, 0 otherwise
int CWD(coordinates, char maze[DIMENSIONS][DIMENSIONS]); // returns 1 if there is an inch, 0 otherwise
int CWL(coordinates, char maze[DIMENSIONS][DIMENSIONS]); // returns 1 if there is an inch, 0 otherwise
int CWR(coordinates, char maze[DIMENSIONS][DIMENSIONS]); // returns 1 if there is an inch, 0 otherwise
void PUSH(coordinates);
coordinates POP(); // as of now returns nothing. should we have pop to return a value? if so, what for?
coordinates PEEK(); // returns type coordinates
void CLEAR();
void BJPI(coordinates, char maze[DIMENSIONS][DIMENSIONS]);
void CJPI(coordinates, char maze[DIMENSIONS][DIMENSIONS]); // SKIPS 1 POSITION, MEANING MOVES 2 (AS OPPOSED TO MOVING 1 LIKE THE MOVE_U... FUNCTIONS)
coordinates BACKTRACK();

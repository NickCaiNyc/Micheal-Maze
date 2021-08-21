// stack.c
// define the 16 functions
// create the ant stack

#include <stdio.h>
#define STACK_SIZE 	1000

typedef struct {
	int x, y;
	// x is columns
	// y is rows
} coordinates;

// variables of the stack ADT

// should the type be coordinates?
static coordinates stack [STACK_SIZE];      // 1D array
static int top = 0;            

#define DIMENSIONS 	50	

void MARK(coordinates inputCoordinates){
	printf("You have called MARK\n");
}

coordinates MOVE_U(coordinates inputCoordinates){
	inputCoordinates.y = inputCoordinates.y - 1;
	printf("You have called MOVE_U\n");
	return inputCoordinates;
}

coordinates MOVE_D(coordinates inputCoordinates){
	inputCoordinates.y = inputCoordinates.y + 1;
	printf("You have called MOVE_D\n");
	return inputCoordinates;
}

coordinates MOVE_L(coordinates inputCoordinates){
	inputCoordinates.x = inputCoordinates.x - 1;
	printf("You have called MOVE_L\n");
	return inputCoordinates;
}

coordinates MOVE_R(coordinates inputCoordinates){
	inputCoordinates.x = inputCoordinates.x + 1;
	printf("You have called MOVE_R\n");
	return inputCoordinates;
}

int whereIsItch = 0;

// If we run into errors, we can check the logic for incrementing coordinate
int CWU(coordinates inputCoordinates, char maze[DIMENSIONS][DIMENSIONS]){ // returns 1 if there is an inch, 0 otherwise
	coordinates tempCoordinate = inputCoordinates;
	if ( maze[tempCoordinate.y - 1][tempCoordinate.x] == '*'){
		return 0;
	}
	while( maze[tempCoordinate.y - 1][tempCoordinate.x] != '*'){
        if( maze[tempCoordinate.y - 1][tempCoordinate.x] == 'P'){
            return 0;
        }
        tempCoordinate.y++;
    }
    whereIsItch = 1;
    return 1;
}

int CWD(coordinates inputCoordinates, char maze[DIMENSIONS][DIMENSIONS]){ // returns 2 if there is an inch, 0 otherwise
	coordinates tempCoordinate = inputCoordinates;
	if ( maze[tempCoordinate.y + 1][tempCoordinate.x] == '*'){
		return 0;
	}
	while( maze[tempCoordinate.y + 1][tempCoordinate.x] != '*'){
        if( maze[tempCoordinate.y + 1][tempCoordinate.x] == 'P'){
            return 0;
        }
        tempCoordinate.y--;
    }
    whereIsItch = 2;
    return 2;
}

int CWL(coordinates inputCoordinates, char maze[DIMENSIONS][DIMENSIONS]){ // returns 3 if there is an inch, 0 otherwise
	coordinates tempCoordinate = inputCoordinates;
	if ( maze[tempCoordinate.y][tempCoordinate.x - 1] == '*'){
		return 0;
	}
	while( maze[tempCoordinate.y][tempCoordinate.x - 1] != '*'){
        if( maze[tempCoordinate.y][tempCoordinate.x - 1] == 'P'){
            return 0;
        }
        tempCoordinate.x--;
    }
    whereIsItch = 3;
    return 3;
}

int CWR(coordinates inputCoordinates, char maze[DIMENSIONS][DIMENSIONS]){ // returns 4 if there is an inch, 0 otherwise
	coordinates tempCoordinate = inputCoordinates;
	if ( maze[tempCoordinate.y][tempCoordinate.x + 1] == '*'){
		return 0;
	}
	while( maze[tempCoordinate.y][tempCoordinate.x + 1] != '*'){
        if( maze[tempCoordinate.y][tempCoordinate.x + 1] == 'P'){
            return 0;
        }
        tempCoordinate.x++;
    }
    whereIsItch = 4;
    return 4;
}

void PUSH(coordinates inputCoordinates){
	stack [ top ] = inputCoordinates;
	top++;
	printf("You have called PUSH\n");
	printf("Coordinates: (%d,%d) has been pushed to the stack.\n", inputCoordinates.x, inputCoordinates.y);
}

coordinates POP(){ 
	coordinates temp;
	
	temp = stack [ top - 1];
	
	top--;                        // changes the top of the stack; removes the value on top
	
	return temp;
}

coordinates PEEK(){ // returns type coordinates
	printf("You have called PEEK\n");
	return stack [ top - 1];
}

void CLEAR(){
	top = 0;
	printf("You have called CLEAR\n");
}

void BJPI(coordinates inputCoordinates, char maze[DIMENSIONS][DIMENSIONS]){ 	
	coordinates tempCoordinate = inputCoordinates;
	int jumpDistance = 0;
	if (whereIsItch == 1){ // represent an up itch
		while (maze[tempCoordinate.y + 1][tempCoordinate.x] != '*'){ // while loop that incremenets jumpDistance until it is the distance closest to the wall
			tempCoordinate.y++;
			jumpDistance++;
		}
		inputCoordinates.y += jumpDistance;
		whereIsItch = 0;
	}
	else if (whereIsItch == 2){ // represent an up itch
		while (maze[tempCoordinate.y - 1][tempCoordinate.x] != '*'){ // while loop that incremenets jumpDistance until it is the distance closest to the wall
			tempCoordinate.y--;
			jumpDistance++;
		}
		inputCoordinates.y -= jumpDistance;
		whereIsItch = 0;
	}
	else if (whereIsItch == 3){ // represent an up itch
		while (maze[tempCoordinate.y][tempCoordinate.x - 1] != '*'){ // while loop that incremenets jumpDistance until it is the distance closest to the wall
			tempCoordinate.x--;
			jumpDistance++;
		}
		inputCoordinates.x -= jumpDistance;
		whereIsItch = 0;
	}
	else if (whereIsItch == 4){ // represent an up itch
		while (maze[tempCoordinate.y][tempCoordinate.x + 1] != '*'){ // while loop that incremenets jumpDistance until it is the distance closest to the wall
			tempCoordinate.x++;
			jumpDistance++;
		}
		inputCoordinates.x += jumpDistance;
		whereIsItch = 0;
	}
	
}

void CJPI(coordinates inputCoordinates, char maze[DIMENSIONS][DIMENSIONS]){ // SKIPS 1 POSITION, MEANING MOVES 2 (AS OPPOSED TO MOVING 1 LIKE THE MOVE_U... FUNCTIONS)
	if (whereIsItch == 1){ // represent an up itch
		if (maze[inputCoordinates.y + 2][inputCoordinates.x] != '*' || maze[inputCoordinates.y + 2][inputCoordinates.x] != 'P'){
			inputCoordinates.y += 2;
			whereIsItch = 0;
		}
		else{
			inputCoordinates.y += 1;
			whereIsItch = 0;
		}
	}
	else if (whereIsItch == 2){ // represent an up itch
		if (maze[inputCoordinates.y + 2][inputCoordinates.x] != '*' || maze[inputCoordinates.y + 2][inputCoordinates.x] != 'P'){
			inputCoordinates.y -= 2;
			whereIsItch = 0;
		}
		else{
			inputCoordinates.y -= 1;
			whereIsItch = 0;
		}
	}
	else if (whereIsItch == 3){ // represent an up itch
		if (maze[inputCoordinates.y + 2][inputCoordinates.x] != '*' || maze[inputCoordinates.y + 2][inputCoordinates.x] != 'P'){
			inputCoordinates.x -= 2;
			whereIsItch = 0;
		}
		else{
			inputCoordinates.x -= 1;
			whereIsItch = 0;
		}
	}
	else if (whereIsItch == 4){ // represent an up itch
		if (maze[inputCoordinates.y + 2][inputCoordinates.x] != '*' || maze[inputCoordinates.y + 2][inputCoordinates.x] != 'P'){
			inputCoordinates.x += 2;
			whereIsItch = 0;
		}
		else{
			inputCoordinates.x += 1;
			whereIsItch = 0;
		}
	}
	
}

coordinates BACKTRACK(){
	coordinates topCoordinate = stack[top-1];
	printf("You have called BACKTRACK\n");
	printf("Backtrack gives us (%d,%d)\n", topCoordinate.x, topCoordinate.y);
	return topCoordinate;
}

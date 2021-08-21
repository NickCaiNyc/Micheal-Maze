#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

// each letter of the state represents their corresponding action, except for state_A which is the current state
// ex: state_A represents currentState and state_B represents MARK and state_C represents move_U
#define STATE_A 	0
#define STATE_B 	1
#define STATE_C 	2
#define STATE_D 	3
#define STATE_E 	4
#define STATE_F 	5
#define STATE_G 	6
#define STATE_H 	7
#define STATE_I 	8
#define STATE_J 	9
#define STATE_K 	10
#define STATE_L 	11
#define STATE_M 	12
#define STATE_N 	13
#define STATE_O 	14
#define STATE_P 	15
#define STATE_Q 	16

/* run this program using the console pauser or add your own getch, system("pause") or input loop */	

int main(int argc, char *argv[]) {
	coordinates currentPosition; // starting position
	int foundGold = 0;
	// initial energy for ant is 100
	int MAX_ENERGY = 100;
	
	// use maze file to find starting position
	FILE *i_fp;
	if ((i_fp = fopen("maze_1.txt", "r")) == NULL){
		printf("Error: file cannot be opened.\n");
		exit(1);
	}
	
	// find out how many rows and columns there are in the maze so that I know the dimensions of the array to create
	int numbRows = 0, numbCols = 0;
	char c;
	while (fscanf(i_fp, "%c", &c) != EOF){
		if (c == '\n'){
			numbRows++;
			break;
		}
		else{
			numbCols++;
		}
	}
	while (fscanf(i_fp, "%c", &c) != EOF){
		if (c == '\n'){
			numbRows++;
		}
	}
	fclose(i_fp);
	printf("numbRows: %d\n", numbRows);
	printf("numbCols: %d\n", numbCols);
	// create array for maze and recreate the maze in the array
	char arr[numbRows][numbCols];
	int i = 0, j = 0;
	
	if ((i_fp = fopen("maze_1.txt", "r")) == NULL){
		printf("Error: file cannot be opened.\n");
	}
	
	while (fscanf(i_fp, "%c", &c) != EOF){
		if (c == '*' || c == ' ' || c == '@'){
			arr[i][j] = c;
			j++;
			if (j == numbCols){
				j=0;
			}
		}
		if (c == '\n'){
			i++;
		}
	}
	fclose(i_fp);
	
	// find starting position of arr (maze)
	for (i=0; i<numbRows; i++){
		for (j=0; j<numbCols; j++){
			// top perimeter
			if (arr[0][j] == ' '){
				currentPosition.x = j;
				currentPosition.y = 0;
				break;
			}
			// bottom perimeter
			else if (arr[numbRows-1][j] == ' '){
				currentPosition.x = j;
				currentPosition.y = numbRows-1;
				break;
			}
			// left perimeter
			else if (arr[i][0] == ' '){
				currentPosition.x = 0;
				currentPosition.y = i;
				break;
			}
			// right perimeter
			else if (arr[i][numbCols-1] == ' '){
				currentPosition.x = numbCols-1;
				currentPosition.y = i;
				break;
			}
		}
	} // now starting position is set with the x coordinate being the number of column and y coordinate being the number of row
	
	// create FSM
	int numbRowsFSM = 17; // because we have one state for each of the 16 actions, and 1 extra state for the current state
	
	int nextState [17] =                       {STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A,
												STATE_A};
	
	// read the intelligence file
	if ((i_fp = fopen("intelligenceFile.txt", "r")) == NULL){
		printf("Error: file cannot be opened");
		exit(1);
	}
	
	printf("initial starting position (x): %d\n", currentPosition.x);
	printf("initial starting position (y): %d\n", currentPosition.y);
	
	coordinates temp;
	int currentState = STATE_A;
	char str[64];
	int hasEnergy = 1;
	while (hasEnergy){
		while (fscanf(i_fp, "%s ", str) != EOF){
			if (strcmp(str,"MOVE_U") == 0){
				// check to see if spot is movable
				if (arr[currentPosition.y-1][currentPosition.x] == ' ' || arr[currentPosition.y-1][currentPosition.x] == '@'){
					temp = MOVE_U(currentPosition);
					currentState = nextState[currentState];
					currentPosition.x = temp.x;
					currentPosition.y = temp.y;
					// check with the maze array to see if the position we moved to has gold or not
					if (arr[currentPosition.y][currentPosition.x] == '@'){
						foundGold++;
						// after finding gold, remove it from the maze
						arr[currentPosition.y][currentPosition.x] = ' ';
					}
					// VA loses 3 energy for performing this action
					MAX_ENERGY -= 3;
					if (MAX_ENERGY <= 0){
						hasEnergy = 0;
						break;
					}
				}
			}
			else if (strcmp(str,"MOVE_D") == 0){
				// check to see if spot is movable
				if (arr[currentPosition.y+1][currentPosition.x] == ' ' || arr[currentPosition.y+1][currentPosition.x] == '@'){
					temp = MOVE_D(currentPosition);
					currentState = nextState[currentState];
					currentPosition.x = temp.x;
					currentPosition.y = temp.y;
					// check with the maze array to see if the position we moved to has gold or not
					if (arr[currentPosition.y][currentPosition.x] == '@'){
						foundGold++;
						// after finding gold, remove it from the maze
						arr[currentPosition.y][currentPosition.x] = ' ';
					}
					// VA loses 3 energy for performing this action
					MAX_ENERGY -= 3;
					if (MAX_ENERGY <= 0){
						hasEnergy = 0;
						break;
					}
				}
			}
			else if (strcmp(str,"MOVE_L") == 0){
				// check to see if spot is movable
				if (arr[currentPosition.y][currentPosition.x-1] == ' ' || arr[currentPosition.y][currentPosition.x-1] == '@'){
					temp = MOVE_L(currentPosition);
					currentState = nextState[currentState];
					currentPosition.x = temp.x;
					currentPosition.y = temp.y;
					// check with the maze array to see if the position we moved to has gold or not
					if (arr[currentPosition.y][currentPosition.x] == '@'){
						foundGold++;
						// after finding gold, remove it from the maze
						arr[currentPosition.y][currentPosition.x] = ' ';
					}
					// VA loses 3 energy for performing this action
					MAX_ENERGY -= 3;
					if (MAX_ENERGY <= 0){
						hasEnergy = 0;
						break;
					}
				}
			}
			else if (strcmp(str,"MOVE_R") == 0){
				// check to see if spot is movable
				if (arr[currentPosition.y][currentPosition.x+1] == ' ' || arr[currentPosition.y][currentPosition.x+1] == '@'){
					temp = MOVE_R(currentPosition);
					currentState = nextState[currentState];
					currentPosition.x = temp.x;
					currentPosition.y = temp.y;
					// check with the maze array to see if the position we moved to has gold or not
					if (arr[currentPosition.y][currentPosition.x] == '@'){
						foundGold++;
						// after finding gold, remove it from the maze
						arr[currentPosition.y][currentPosition.x] = ' ';
					}
					// VA loses 3 energy for performing this action
					MAX_ENERGY -= 3;
					if (MAX_ENERGY <= 0){
						hasEnergy = 0;
						break;
					}
				}
			}
			else if (strcmp(str,"PUSH") == 0){
				PUSH(currentPosition);
				currentState = nextState[currentState];
				// VA loses 4 energy for performing this action
				MAX_ENERGY -= 4;
				if (MAX_ENERGY <= 0){
					hasEnergy = 0;
					break;
				}
			}
			else if (strcmp(str,"PEEK") == 0){
				temp = PEEK();
				printf("You have peeked the coordinates: (%d,%d)\n", temp.x, temp.y);
				currentState = nextState[currentState];
				// VA loses 2 energy for performing this action
				MAX_ENERGY -= 2;
				if (MAX_ENERGY <= 0){
					hasEnergy = 0;
					break;
				}
			}
			else if (strcmp(str,"CLEAR") == 0){
				CLEAR();
				currentState = nextState[currentState];
				// VA loses 2 energy for performing this action
				MAX_ENERGY -= 2;
				if (MAX_ENERGY <= 0){
					hasEnergy = 0;
					break;
				}
			}
			else if (strcmp(str,"POP") == 0){
				temp = POP();
				currentState = nextState[currentState];
				printf("You have popped the coordinates: (%d,%d)\n", temp.x, temp.y);
				// VA loses 4 energy for performing this action
				MAX_ENERGY -= 4;
				if (MAX_ENERGY <= 0){
					hasEnergy = 0;
					break;
				}
			}
			else if (strcmp(str,"BACKTRACK") == 0){
				temp = BACKTRACK();
				currentState = nextState[currentState];
				currentPosition.x = temp.x;
				currentPosition.y = temp.y;
				printf("You have moved back to (%d,%d).\n", currentPosition.x, currentPosition.y);
			}
			else if (strcmp(str,"MARK") == 0){
				// if not already marked
				if (arr[currentPosition.y][currentPosition.x] != 'P'){
					arr[currentPosition.y][currentPosition.x] = 'P';
					MARK(currentPosition);
					currentState = nextState[currentState];
					// VA loses 3 energy for performing this action
					MAX_ENERGY -= 3;
					if (MAX_ENERGY <= 0){
						hasEnergy = 0;
						break;
					}
				}
	 		}	
	 		/*
			else if (strcmp(str,"CWU") == 0){
				CWU(currentPosition, arr[numbRows][numbCols]);
				currentState = nextState[currentState];
				// VA loses 1 energy for performing this action
				MAX_ENERGY -= 1;
				if (MAX_ENERGY <= 0){
					hasEnergy = 0;
					break;
				}
			}
			else if (strcmp(str,"CWD") == 0){
				CWD(currentPosition, arr[numbRows][numbCols]);
				currentState = nextState[currentState];
				// VA loses 1 energy for performing this action
				MAX_ENERGY -= 1;
				if (MAX_ENERGY <= 0){
					hasEnergy = 0;
					break;
				}
			}
			else if (strcmp(str,"CWL") == 0){
				CWL(currentPosition, arr[numbRows][numbCols]);
				currentState = nextState[currentState];
				// VA loses 1 energy for performing this action
				MAX_ENERGY -= 1;
				if (MAX_ENERGY <= 0){
					hasEnergy = 0;
					break;
				}
			}
			else if (strcmp(str,"CWR") == 0){
				CWR(currentPosition, arr[numbRows][numbCols]);
				currentState = nextState[currentState];
				// VA loses 1 energy for performing this action
				MAX_ENERGY -= 1;
				if (MAX_ENERGY <= 0){
					hasEnergy = 0;
					break;
				}
			}
			else if (strcmp(str,"BJPI") == 0){
				BJPI(currentPosition, arr[numbRows][numbCols]);
				currentState = nextState[currentState];
				// VA loses 5 energy for performing this action
				MAX_ENERGY -= 5;
				if (MAX_ENERGY <= 0){
					hasEnergy = 0;
					break;
				}
				// check with the maze array to see if the position we moved to has gold or not
				if (arr[currentPosition.y][currentPosition.x] == '@'){
					foundGold++;
					// after finding gold, remove it from the maze
					arr[currentPosition.y][currentPosition.x] = ' ';
				}
			}
			else if (strcmp(str,"CJPI") == 0){
				CJPI(currentPosition, arr[numbRows][numbCols]);
				currentState = nextState[currentState];
				// VA loses 3 energy for performing this action
				MAX_ENERGY -= 3;
				if (MAX_ENERGY <= 0){
					hasEnergy = 0;
					break;
				}
				// check with the maze array to see if the position we moved to has gold or not
				if (arr[currentPosition.y][currentPosition.x] == '@'){
					foundGold++;
					// after finding gold, remove it from the maze
					arr[currentPosition.y][currentPosition.x] = ' ';
				}
			}
			*/
		}
		// stops the outer while loop from running
		hasEnergy = 0;
	}
	
	printf("\n");
	printf("\n");
	printf("\nResults:\n");
	printf("Final x coordinate: %d\n", currentPosition.x);
	printf("Final y coordinate: %d\n", currentPosition.y);
	printf("%d pots of gold found.\n", foundGold);
	if (MAX_ENERGY > 0){
		printf("VA has %d energy left.\n", MAX_ENERGY);
	}
	else{
		printf("VA has ran out of energy. Therefore, it will stop performing actions.\n");
	}
	
	fclose(i_fp);

	printf("\nUpdated maze displayed below:\n");
	printf("Note: the updated maze includes the marked areas indicated by P, and also, the pots of gold found are removed.\n");
	// display maze after the program
	// that means that the maze should no longer show the pots of gold found
	// and the maze should show the marked areas indicated by P
	for (i=0; i<numbRows; i++){
		for (j=0;j<numbCols;j++){
			printf("%c",arr[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}


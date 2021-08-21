We used two mazes for our project. They are text files named as maze_1 and maze_2 in the zip folder we submitted.
We made it so that our program prints the VA's final coordinates, the number of pots of gold found, how much energy the VA had left (if any), and
the updated maze after the VA's actions. We printed the updated maze so that the pots of gold found are not shown, and also so that the areas in which our
VA marked using the MARK() function are labeled as 'P'.
For maze_1, our VA found 4 pots of gold. 
For maze_2, our VA found 5 pots of gold.

Regarding the code in each of the project-related files:
	stack.h:
		In the header file, we declared the functions that our VA would be able to execute. This involved us creating a structure that represented the VA's coordinates. 
		
	stack.c:
		In this file, we defined the functions that we declared in the stack.h file. We also created the VA's stack.
		
	main.c:
		In this file, we first decided to read through the text file containing our maze to create an identical copy of it in the form of an array.
		After that, we identified the exact coordinates of the starting position of our VA. Once we had the starting position of our VA, we were ready to program our FSM and read
		through the intellgience file so that our VA would be able to execute the expected actions. Our approach was like this:
			-While our ant has energy, we would read through the string of the intelligence file and check what function the string corresponded to. We did this check through
			comparing strings.
			-If the string corresponds to a function, our VA will execute the function, which was declared in the stack.h and defined in the stack.c. For every action,
			we made sure to factor in the energy cost and whether or not executing the function would result in finding a pot of gold. 
			-Once we had gone through either all of the energy our VA had, or all the actions in the intelligence file, we would display the final coordinates, the number of
			pots of gold found, and the updated maze. 
		Some of the functions would be commented out in our program because we were unable to have it execute properly. Therefore, we avoided using those functions.
		We believe that the code we had for those functions acheived our purpose but we were unable to implement the function because when we defined those specific functions,
		we had it update the coordinates of the maze that we passed as parameters. The problem with that was that the maze we passed as parameters was a copy of our maze. The function
		did not directly alter the array that we gave into the function. The function simply only affected a copy of the array that we gave it. We knew that the fix to that was 
		through pointers. We should have and could have used pointers to avoid this issue, but we were unable to successfully implement the approach with pointers, so we left
		part of the functions commented out so that you guys could see how we programmed the functionality that was described in the project description. 

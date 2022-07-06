#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include<stdbool.h>  
#include <time.h>
#include <unistd.h> // note: for window use Windows.h
void recursive(Array trace, Array obstacle, struct Point *posList, int *direction, struct Point currentLocation);

/*

	This algorithm was developed for the project named robot vacuum cleaner made in stm32.


	Initially, the device should be placed on one of the 4 sides of a square or rectangular room.

	In the algorithm, we used an obstacle list to keep the position of the obstacles, and a trace list to keep the position of the places they passed before.

	There is only one distance sensor on the front of the robot.

*/

int main()
{


	Array trace;
	Array obstacle;

	initArray(&obstacle,5);
	initArray(&trace,5);

	int direction; // store the direction of robot. There are 4 possibilities 1,2,3,4
			// 1 is up 2 is right 3;below 4; left
	direction = 1; // by default it is 1 direction
	
	struct Point currentLocation; 
	currentLocation.x = 0; // at the beginning put the robot at (0,0) point
	currentLocation.y= 0;
	struct Point *posList = malloc(sizeof(struct Point)*4); 	

	printf("current location (%d,%d)\n", currentLocation.x, currentLocation.y);	

	printf("OBSTACLE array elements: \n");
	printPointList(obstacle.array,obstacle.used);
	
	printf("trace array elements: \n");
	printPointList(trace.array,trace.used);

	printf("possible list elements: \n");	
	posList = createPosList(currentLocation);
	printPointList(posList, 4);
	
		
	recursive(trace, obstacle,posList,&direction, currentLocation);	
}

void recursive(Array trace, Array obstacle, struct Point *posList, int *direction, struct Point currentLocation) // burada currentPoint te olmalı
{
	int distance; // this comes from distance sensor
	
	checkObstacleList(posList,obstacle);
	checkTraceList(posList, trace);
	struct Point selectedPoint = randomSelection(posList);
	printf("randomly selected point:  (%d,%d) \n", selectedPoint.x, selectedPoint.y);
	
	if (selectedPoint.x != -500)
	{// If the x value of selectedPoint is not -500, it means that there is still an element that we can choose with random in the list of possibilities.
	 
		detectDirection(selectedPoint, currentLocation, direction);// detects the direction of the selected point and makes the robot turn in the selected direction
		printf("new direction : %d\n", *direction);
	
		
		printf("\n************ enter the distance value : *************\n");
		scanf("%d", &distance);
		if (getInfoDistanceSensor(distance) == 1) // Returns false if the distance variable is less than 50 cm and true if it has a value above 50 cm.
		{//no obstacles detected and move to the selected point

			movingForward();	
			insertArray(&trace, currentLocation); //The previous point of the robot is added to the trace list
			currentLocation = selectedPoint;

			printf("current location (%d,%d)\n", currentLocation.x, currentLocation.y);	
			
			printf("trace array elements\n");
			printPointList(trace.array,trace.used);
			
			printf("possible list elements: \n");	
			posList = createPosList(currentLocation); //A list of possibilities is created for the new starting point.
			printPointList(posList, 4);

			//sleep(2);			
			recursive(trace,obstacle,posList,direction, currentLocation);// call again recursive function 
			
		}

		else {
			// in this case; The distance sensor has detected an object at a randomly chosen point by the robot (there is an obstacle within 50cm)
			
			insertArray(&obstacle, selectedPoint);// randomly selected point is added to the obstacle list
		
			printf("(%d,%d) point added into OBSTACLE LIST\n",selectedPoint.x, selectedPoint.y);
			printf("OBSTACLE array elements\n");
			printPointList(obstacle.array,obstacle.used);
			//sleep(2);			
			recursive(trace,obstacle,posList,direction,currentLocation); // call again recursion function to select a new direction 
		}
	}

	else {
		// all the elements in the possibilities list are eliminated by the trace list or the obstacles list, 
		
		if (checkDeviceSurrounded(posList) == 4) 
		{//  all points in the possibilities list are eliminated by only the obstacles list. So, stop the machine no need for flushing trace list
			printf("Device surrounded by obstacle can not move anymore\n");
			// it's base point if it is surrounded by obstacle we cannot move any where
		}
		else{  // all points in the possibilities list are not deleted by the obstacle list in other words; at least one of them is deleted by the trace list.

					      
		      	printf("\n\n TRACE lıst and POSLIST deleted\n\n");
			freeArray(&trace); // trace array inin siliyoruz
			free(posList);     // poslist array ini siliyoruz
			
			Array trace; // create empty trace list again
			initArray(&trace,5);
			
			struct Point *posList = malloc(sizeof(struct Point)*4); 	

			printf("ELSE condition possible list elements: \n");	
			posList = createPosList(currentLocation);
			printPointList(posList, 4);
			recursive(trace,obstacle,posList,direction,currentLocation); // call again recursion
		}	
			
	}
}

# VacuumCleaner

it's a navigation algorithm for Vacuum Cleaner Robot. It's written in C. 

Normally, it's an Assembly Language Programming Project with STM32 Microcontrollers. **Hovewer**, only a part of the project, the navigation algorithm, is uploaded here.

----

> Initially, the device should be placed on one of the 4 sides of a square or rectangular room.

> In the algorithm, we used an *obstacle list* to keep the position of the obstacles, and a *trace list* to keep the position of the places they passed before.

> In our asm project there is only one distance sensor on the front of the robot.


### Our algorithm works like this;


>The starting point of the robot is (0,0).

>For this point, the possible destinations of the robot are 4 points. These are the right, left, top and bottom coordinates. The function that lists the places where the robot will probably go is the “createPosList” function. After the possible places to go are listed, it should be checked whether these points are in the trace list or the obstacle list. This control is done by the "checkObstacleList" and "checkTraceList" methods. If one or more of the possible destinations are in this list, it is removed from the list of possible destinations. For example, the possible destinations for the point (5.5) are (6.5), (4.5), (5.4), (5.4) and (5.6). Let's assume that the robot has passed the point (4,5) before, and if it has detected an obstacle at the point (6.5), then we should remove the points (4,5) and (6.5) from the list of possibilities. Remaining in the probability list are the points (5.4) and (5.6).

- 1- If one or more points are left in the list of possibilities, a point is selected among the points with the help of the "randomSelection" method. 

    * The direction of this selected point is selected with the help of the "detectDirection" method and the robot is directed to the selected point. Here we need to provide one more check. After returning to the randomly selected point in the direction of the robot, it checks this point with the distance sensor, if there is an object closer than 50 cm, it realizes that there is an object here and adds it to the selected point on the list of obstacles and does not pass through this point again.  If it does not see an object in this direction or if the object it detects is more than 50 cm away, it moves towards the selected point.


- 2- If all the elements in the possibilities list are eliminated by the trace list or the obstacles list, we encounter two possibilities.

    * All points in the possibilities list are eliminated by the obstacles list only (this check is done by the checkDeviceSurrounded method)
    
        *  In this case, the device does not move, and program terminated.
       
    * If all points in the possibilities list are not deleted by the obstacle list, that is, at least one of them is deleted by the trace list.
    
    
        * Trace list is emptied.
        *	A list of possibilities is created again.
        *	The possible list is checked by calling the checkObstacleList and checkTraceList methods again, but since the trace list is deleted, a point will not be eliminated from the list of possibilities via the trace list.

      * In this way, a point to be chosen randomly in the list of possibilities will be a point that the robot has passed before. Thus, the robot will continue to move.


[Click](https://drive.google.com/file/d/1p-eVuysNDADaJv41tuRiVtfvbhDoDysN/view?usp=sharing) for a video on how the algorithm works.

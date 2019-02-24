CSE 102 Homework Assignment 1 (Due: Sep 28 11:55 pm)
You are going to write a complete C program which implements a simple interactive game.

A hidden rectangular region is marked on a 2D plane. User is given a detector tool and the job is to iteratively guess, find and remove the marked region. At each iteration, user tries to hit the target by placing the tool on the plane. Detecting if it hits or misses the target is determined according to the following rules:

Marked region is a predefined rectangle(initialize it in your source code).
Detector tool is a rectangle(initialize it in your source code)
According to the user input, detector tool is placed on the 2D plane and intersection of the detector and the marked region is calculated.
If detector fully overlaps with the marked region, user wins.
If there is a partial overlap, marked region is updated to the intersected area and user is notified about the shrinkage. Detector width and height are also decreased to half of their value for the next iteration.
Available # of attempts decreases by 1.
If there is no full or partial overlap, it is a miss. Nothing changes. Available # of attempts decreases by 1.
User has to find and destroy the marked region in a predefined number of steps.

Implement your program according to the following scheme:
Area of the board(plane) is predefined(initialize it in your source code).
Detector is bigger than the marked area.
Inform user about the board size, detector size
Ask user to enter the x coordinate of the move.
Ask user to enter the y coordinate of the move.
If the move is not within the boundary of the board, ask user to re-enter x and y coordinates of the move.
For a valid move, calculate the overlap and inform the user about the result of the move(You can inform about the shrinkage and the number of attempts remaining)

Remarks
Any intersection is a rectangle.
If the detector is partially outside of the boundary, do not consider it as a valid move.
x and y coordinates of the detector marks the center of the shape.
Coordinates or the size values can be floating numbers. Ex: A detector of size 20.5 x 33.2 is possible.

Restrictions:
Do not use arrays, linked-lists and other complex data structures.
Do not copy and paste others code.

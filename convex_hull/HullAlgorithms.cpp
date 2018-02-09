/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (implementation).
 *
 */
#include "HullAlgorithms.hpp"

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to HullAlgorithms.hpp if you write a helper function!
 *
 * Our reference implementation has four helper functions and the function(s)
 * copied over from angleSort.cpp.
 */

/**
 * This group of functions will perform the gift wrapping algorithm. There are 
 * a total of four functions that will be used. The first will actually
 * draw the lines between points, which is the DoGiftWrap function.
 * This function will first find the leftmost point with the Return_left
 * funciton, and then add it to the hull using add_to_hull. It then uses 
 * a do while loop to find the next point using get_next_point and adds
 * that point to the the hull, as follows
 *  do 
    {
        Tuple* nextpoint = get_next_point(points, currentpoint);
        app->add_to_hull(nextpoint);
        currentpoint = nextpoint;
    }
    while(startpoint != currentpoint);
    
 * Next is the Return_left function, which goes through all the points
 * in the argument vector and checks if its x value is less than the
 * x value of the first point, which we assumed to be the leftmost point
 * If so, that new point becomes the left most point. We did this using
 * a for loop as follows
 * for(size_t i = 0; i < points.size() - 1; i++)
	{
		if (points[i]->x < leftvalue->x)
		{
			leftvalue = points[i];
			cout << leftvalue << endl;
			
		}
	}
 * Next is the get_next_point function. This function uses a double for
 * loop and the is_left function. The double for loop is in place because the 
 * is_left function takes three arguments, two points that make a theoretical
 * line and a third point to check against. If running the is_left
 * function returns false, then we set a currentvalue variable which we set
 * equal to 1 in the beginning before the loops now equal to 0.
 * If we run through the function for the double for loop and do not return false,
 * then our currentvalue will still be equal to one. We then implement an
 * if statment saying after the loops if currentvalue still equals 1, we return
 * points[i] which is our next point. The double for loop is as follows:
 * for (size_t i = 0; i < points.size() - 1; i++)
	{
		for (size_t j = 0; j < points.size() -1; j++)
		{
			if(points[j] != points[i] and points[j] != current)
			{
				if (is_left(current, points[i], points[j]) == false)
				{
					currentval = 0;
				}
			}
		}
 * Finally, the is_left function uses vector cross products to calculate
 * if a point is above a line. If so, the function returns true, which is
 * what we want; we want all the points to be above the line created by
 * two points on the convex hull.
 */
bool is_left(Tuple* current, Tuple* linepoint, Tuple* testpoint); //helper functions

Tuple* Return_left(vector<Tuple*> points);

Tuple* get_next_point(vector<Tuple*> points, Tuple* current);

void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app)
{
    Tuple* startpoint = Return_left(points);
    app->add_to_hull(startpoint);
    Tuple* currentpoint = startpoint;
    do 
    {
        Tuple* nextpoint = get_next_point(points, currentpoint);
        app->add_to_hull(nextpoint);
        currentpoint = nextpoint; //setting currentpoint equal to next to continue loop
    }
    while(startpoint != currentpoint); //initial condition
    
}

Tuple* Return_left(vector<Tuple*> points)
{
	Tuple* leftvalue = points[0];
	for(size_t i = 0; i < points.size() - 1; i++)
	{
		if (points[i]->x < leftvalue->x)
		{
			leftvalue = points[i];
			
		}
	}

	return leftvalue;
}

Tuple* get_next_point(vector<Tuple*> points, Tuple* current)
{
	int currentval = 1;
	for (size_t i = 0; i < points.size() - 1; i++)
	{
		for (size_t j = 0; j < points.size() -1; j++)
		{
			if(points[j] != points[i] and points[j] != current)
			{
				if (is_left(current, points[i], points[j]) == false)
				{
					currentval = 0;
				}
			}
		}
		if (currentval == 1) //goes through loop, doesn't return false
		{
			
			return points[i];
		}
		currentval = 1;
		
	}
	return current;
	
}

bool is_left(Tuple* current, Tuple* linepoint, Tuple* testpoint)
{
	if((((linepoint->x - current->x) * (testpoint->y - current->y))-
	((linepoint->y - current->y) * (testpoint->x - current->x))) > 0)
		//vector cross product
	{
		return true;
	}
	return false;
}
	
	

 /**
 * TODO: Implement this function.
 */
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app)
{
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        app->add_to_hull(points[i]);
    }
    app->add_to_hull(points[0]);
}

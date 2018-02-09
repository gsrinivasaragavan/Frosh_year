/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief An example of sorting (x, y) pairs by angle.
 *
 */
#include "structs.hpp"
#include <vector>

int partition(vector<Tuple*> &points, vector<double> &angles, int left, int right);

// TODO Modify one of your sorting functions (bubble sort not permitted) and
// implement it here. Add extra arguments as needed.
/**
 * This function is very similar to quicksort in place. It has the same helper
 * function, partition, except that instead of having just a vector with 
 * points, there is also a vector with angles. Whenever we switch the points
 * in partition, we also end up switching the angles at those same indices 
 * because they end up corresponding. 
*/
void sort(vector<Tuple*> &points, vector<double> &angles, int left, int right)
{
    if (left < right)
    {
		int part;
		part = partition(points, angles, left, right);
		sort(points, angles, left, part - 1);
		sort(points, angles, part + 1, right);
		
	}
    return;
}
int partition(vector<Tuple*> &points, vector<double> &angles, int left, int right)
{
	double temp, temp1;
	Tuple* temp2; 
	Tuple* temp3;
	int pivot = angles[right];
	int i = (left);
	if (left < right)
	{
		for (int j = left; j < right; j++)
		{
			if (angles[j] <= pivot)
			{
				temp = angles[j];
				angles[j] = angles[i];
				angles[i] = temp;
				temp2 = points[j];
				points[j] = points[i];
				points[i] = temp2;
				i++;
			}
		}
	
		temp1 = angles[right];
		angles[right] = angles[i];
		angles[i] = temp1;
		temp3 = points[right];
		points[right] = points[i];
		points[i] = temp3;
	}
	return(i);
}


int main(int argc, char const *argv[])
{
    vector<double> angles {4.2, 2.8, 1.4, 5.0, 3.3};
    vector<Tuple*> points;
    // Print the initial points and angles
    for (unsigned int i = 0; i < angles.size(); ++i)
    {
        points.push_back(new Tuple(i, i));
    }
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        cout << *i << endl;
    }

    // Now sort them with respect to angle (points[i] corresponds to angle[i])

    /** THIS IS THE ONLY LINE OF THE MAIN LOOP YOU NEED TO MODIFY. */
    sort(points, angles, 0, int (angles.size()-1));
    /** REPLACE THE LINE ABOVE WITH A CALL TO YOUR SORTING FUNCTION. */

    // and print out the new points and angles
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        cout << *i << endl;
    }

    // Don't want to leak memory...
    // Either of the below implementations works
    // for (std::vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    // {
    //     delete (*i);
    // }
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        delete points[i];
    }
    return 0;
}

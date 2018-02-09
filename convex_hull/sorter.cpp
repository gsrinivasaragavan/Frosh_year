/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The bubble sort, quick sort, merge sort, and in-place quicksort
 * algorithms (implementation).
 *
 */
#include "sorter.hpp"
#include <vector>
#include "fileio.hpp"

int main(int argc, char* argv[])
{
    // Set up buffers and data input
    std::vector<int> nums;
    std::string line;
    char *filename;
    int sort_type;

    // Ensure that at most one type of sort and at least a filename are specified.
    if (argc > 3 || argc < 2)
    {
        usage();
    }

    // default sort is bubble sort
    sort_type = BUBBLE_SORT;

    // Figure out which sort to use
    for (int i = 1; i < argc; ++i)
    {
        char *arg = argv[i];
        if (strcmp(arg, "-b") == 0) { sort_type = BUBBLE_SORT; }
        else if (strcmp(arg, "-q") == 0) { sort_type = QUICK_SORT; }
        else if (strcmp(arg, "-m") == 0) { sort_type = MERGE_SORT; }
        else if (strcmp(arg, "-qi") == 0) { sort_type = QUICK_SORT_INPLACE; }
        else { filename = argv[i]; }
    }

    // Read the file and fill our vector of integers
    // THIS FUNCTION IS STUDENT IMPLEMENTED
    readFile(filename, nums);

    switch (sort_type)
    {
        case BUBBLE_SORT:
        print_vector(bubbleSort(nums));
        break;

        case QUICK_SORT:
        print_vector(quickSort(nums));
        break;

        case MERGE_SORT:
        print_vector(mergeSort(nums));
        break;

        case QUICK_SORT_INPLACE:
        quicksort_inplace(nums, 0, nums.size() - 1);
        print_vector(nums);
        break;

        default:
        usage();
        break;
    }
    return 0;
}

/**
 * Usage    Prints out a usage statement and exits.
 */
void usage()
{
    std::cerr << usage_string << std::endl;
    exit(1);
}

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to sorter.hpp if you write a helper function!
 */

/**
 * TODO: Implement this function.
 */
/**
 * This function will bubble sort a vector. In order to do this, the 
 * user must input some vector (in this case called a list) into the 
 * function. After that, the function will go through our vector and 
 * compare values two at a time that are adjacent, and swap them if 
 * they are out of order
 * So, using a for loop starting at index 0 up to the size of our vector
 * - 1, we create an if statement
 * if(list[i] > list[i+1])
 * if true, the values must be switched, in this case using some 
 * temporary variable temp set equal to list[i].
 * If we iterate through all i's and reach the end of the list, all
 * the values needed to be swapped will be swapped and we can
 * return list;
 * */
std::vector<int> bubbleSort(std::vector<int> &list)
{
    int temp, line = 1;
    int listlength = list.size();
    while(line > 0)
    {
		line = 0;
		for(int i = 0; i < listlength-1; i++)
		{
			if(list[i] > list[i + 1]) //checks if value is greater
			{
				temp = list[i];
				list[i] = list[i + 1]; //swaps the two
				list[i + 1] = temp;
				line = i + 1;
			}
		}
	}
				
    return list;
}

/**
 * This function will quick sort a vector. Again, the user will input 
 * some vector (list). Quicksort uses a pivot and compares the rest of 
 * the values in the list to the pivot, and places them in newly created
 * vectors high and low. We start with our base case, assuming that the 
 * sie of the list is 1 or less. Then we simply return the list as it is 
 * already sorted. If not, our pivot is the first value in the inputted
 * vector, or
 * int pivot = list[0]
 * We use an if/else statement to see if our values in the list are 
 * smaller or equal to the pivot, or if they are larger.
 * if(list[i] <= pivot)
		{
			low.push_back(list[i]);
		}
		else
		{
			high.push_back(list[i]);
		}
 * We then recursively sort through these new vectors by calling our
 * quicksort function. We then can return our "low" vector after pushing
 * back our pivot and pushing back each value in the high vector. 
 * low.push_back(pivot);
	for(size_t i = 0; i < high.size(); i++)
	{
		low.push_back(i);
	}  
 * low is now our fully sorted vector
 */
std::vector<int> quickSort(std::vector<int> &list)
{
    if (list.size() <= 1)
    {
		return list;
	}
    int pivot = list[0];
    std:: vector<int> low;
    std:: vector<int> high; //creates two new vectors
    for(size_t i=1; i < list.size(); i++)
    {
		if(list[i] <= pivot)
		{
			low.push_back(list[i]); //add elements to vectors
		}
		else
		{
			high.push_back(list[i]);
		}
	}
	low = quickSort(low); //calls recursion
	high = quickSort(high);
	low.push_back(pivot);
	for(size_t i = 0; i < high.size(); i++)
	{
		low.push_back(high[i]);
	}  

    return low;
}

/**
 * This function will merge sort a vector. Again, the user will input 
 * some vector called list. Merge sort breaks the vector into halves 
 * recursively until they are size 1. It then merges them into the 
 * correct order and adds them together. Again, our base case is if 
 * the vector size is 1, meaning it is already sorted and the list is 
 * simply returned. If the vector size is not 1, then we set a variable
 * mid equal to the middle of the vector, or
 * int mid = (list.size() / 2)-1;
 * We then create a vector representing the first half and a vector 
 * representing the second half, and add the values into their 
 * respective vectors using a for loop as follows
 * for(int i = 0; i <= mid; i++)
	{
		firsthalf.push_back(i);
	}
	for(size_t i = mid + 1; i < list.size(); i++)
	{
		secondhalf.push_back(i);
	}
 * We then recursively call mergeSort again, and finally set list equal
 * to the merging of the first and second half vectors. 
 * In our merge 
 * function, we declare two iterators i and j to be equal to 0, and 
 * define a new vector that will represent the merged lists. There are 
 * three different scenarios to take into account for, which is why 
 * there are three different while loops. The first is if both i and j 
 * both are less than the size of the left and right vectors. In that
 * case, we have the following if/else loop
 * if (left[i] <= right[j])
		{
			newlist.push_back(left[i]);
			i += 1;
		}
		else
		{
			newlist.push_back(right[j]);
			j += 1;
			
		}
 * in the case that i is done interating but j still has elements to 
 * iterate through, we have to pushback our jth element and continue to
 * add one to j. The same process occurs if j is done iterating but 
 * i still has elements to iterate through.
 */
std::vector<int> mergeSort(std::vector<int> &list)
{
    if (list.size() <= 1)
    {
		return list;
	}
	int mid = (list.size() / 2)-1;
	std:: vector<int> firsthalf;
	std:: vector<int> secondhalf;
	for(int i = 0; i <= mid; i++)
	{
		firsthalf.push_back(list[i]);
	}
	for(size_t i = mid + 1; i < list.size(); i++)
	{
		secondhalf.push_back(list[i]);
	}
	firsthalf = mergeSort(firsthalf);
	secondhalf = mergeSort(secondhalf);
	list = merge(firsthalf, secondhalf);
    return list; //returned at that recursive variable, goes down a 
    //layer, and starts to unfold back up
}


std::vector<int> merge(std::vector<int> &left, std::vector<int> &right)
{
    size_t i = 0;
    size_t j = 0;
    std::vector<int> newlist;
    while(i < left.size() and j < right.size())
    {
		if (left[i] <= right[j])
		{
			newlist.push_back(left[i]);
			i += 1;
		}
		else
		{
			newlist.push_back(right[j]);
			j += 1;
			
		}
	}
	while(j < right.size()) //i is done, j still has stuff to go through
	{
		newlist.push_back(right[j]);
		j += 1;
		
	}
	while(i < left.size())
	{
		newlist.push_back(left[i]);
		i += 1;
	}
    return newlist;
}

/*
 * quicksort_inplace:  In-place version of the quicksort algorithm. Requires
 *              O(1) instead of O(N) space, same time complexity. Each call of
 *              the method partitions the list around the pivot (an item taken
 *              from the middle of the array) with items left of the pivot
 *              smaller than it and items to its right larger than it. Then the
 *              method recursively sorts the left and right portions of the list
 *              until it reaches its base case: a list of length 1 is already
 *              sorted.
 *
 * @param list: pointer to integer array to be sorted
 * @returns:    Nothing, the array is sorted IN-PLACE.
 *
 * TODO: Implement this function.
 */
 /**
  * this function ends up quicksorting a vector in place. Again, the 
  * user inputs a vector (list). The quicksort_inplace function starts
  * by calling the partition function and setting a variable part 
  * equal to that value. It then recursively runs quicksort_inplace 
  * again for the list to the left of the pivot and the list to the
  * right, until the whole list is sorted. The partition function sets 
  * our pivot equal to the last value in the list, and sets an 
  * iterator i equal to left, or
  * int pivot = list[right];
	int i = (left);
  * We then make sure our left value is less than our right, and then
  * use a for loop to iterate through the list and check if a value is 
  * less than the pivot, if so, we switch our value at iterator i with
  * our value at iterator j, as follows
  * for (int j = left; j < right; j++)
		{
			if (list[j] <= pivot)
			{
				temp = list[j];
				list[j] = list[i];
				list[i] = temp;
				i++;
			}
		}
  * Finally, we must swap our pivot into the correct position as follows
  * temp1 = list[right];
	list[right] = list[i];
	list[i] = temp1;
  * and end with returning i, the index of where the pivot now is.
  * */
void quicksort_inplace(std::vector<int> &list, int left, int right)
{
    if (left < right)
    {
		int part;
		part = partition(list, left, right);
		quicksort_inplace(list, left, part - 1); //first half of list
		quicksort_inplace(list, part + 1, right); //second half
		
	}
    return;
}
int partition(std::vector<int> &list, int left, int right)
{
	int temp, temp1;
	int pivot = list[right];
	int i = (left);
	if (left < right)
	{
		for (int j = left; j < right; j++)
		{
			if (list[j] <= pivot)
			{
				temp = list[j];
				list[j] = list[i]; //swapping values
				list[i] = temp;
				i++;
			}
		}
	
		temp1 = list[right];
		list[right] = list[i];
		list[i] = temp1;
	}
	return(i);
}
	


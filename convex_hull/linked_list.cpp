/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief Example of a linked list class and usage.
 *
 */
//The deconstructor deleted head, but since head points to the next node
//which points to the next node, and to the next etc, after deleting
//head we lost access to all the other nodes and cannot free the 
//memory of the rest of the nodes like we need to 
#include <iostream>

/**
 * A class defining the shell of a linked list data structure.
 */
class List
{

/**
 * Public methods accessible by external code.
 */
public:
    List();
    ~List();
    void insert(int item);
    void printList();

/**
 * Private data, including structure definition and class variables.
 */
private:
    struct Node
    {
        int data;
        Node *next;

        /**
         * Constructor for a node structure.
         */
        Node(int data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
    };
    Node *head;
    int num_elements;
};

/**
 * List constructor.
 */
List::List()
{
    head = nullptr; //top of linked list, have list with no nodes, 
    //insert node, is the head (first node), tail is last
    num_elements = 0;
}

/**
 * List destructor.
 */
List::~List() //deconstructor gets rid of all allocated memory
{
    // TODO: Write the destructor so that this code does not leak memory!
    Node *current = head; //points to head of list
    Node *temp; //temporrary pointer
    while(current != nullptr)
    {
		temp = current->next; //temp points to the next node
		delete current; //when you use delete, free memory that pointer
		//is pointing to, do not have to redefine pointer 
		current = temp;
	}
}

/**
 * insert   Insert an integer at the end of the list.
 * @param   item integer to be inserted at the end of the list
 */
void List::insert(int item)
{
    // If we have elements...
    if (num_elements > 0)
    {
        // Set up a pointer to get to end of current list
        Node *temp = head;
        for (int i = 0; i < num_elements - 1; ++i)
        {
            temp = temp->next;
            //temp has its own next variable, points to the next node
            //use arrow if current node is node pointer, dot if not
        }
        // temp now points to node at end of list

        // Construct our new node, it doesn't point to anything yet
        Node *new_node = new Node(item, nullptr);
        //new is like malloc, calls constructor and allocates memory for
        //it

        // Make the old tail point to the new tail, actually pointsto it
        temp->next = new_node;

        // and update the number of elements in the list
        num_elements++;
    }
    else
    {
        head = new Node(item, nullptr);
        num_elements++;
    }
    return;
}

/**
 * printList    Prints the contents of our list out, one integer per line.
 */
void List::printList()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->data << std::endl;
        temp = temp->next;
    }
    return;
}

int main(int argc, char const *argv[])
{
    List lst;
    for (int i = 0; i < 10; ++i)
    {
        lst.insert(i);
    }
    lst.printList();
    return 0;
}

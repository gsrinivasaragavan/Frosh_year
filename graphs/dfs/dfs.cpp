/* debugging example */
/* the problem with the existing code is that there is no visited attribute that keeps track of
which nodes it has already searched through. So the existig code algorithm works for simple cases such as 
the one that I coded in my test case, but would not work if the nodes were all linked in a cycle through 
edges, because it would keep checking through each of the nodes without ever exiting the loop and eventually 
segfault becasue we have not told dfs to keep track of the visited nodes so it will not continue in an endless loop*/

#include <iostream>
#include <vector>
using namespace std;


class Node
{
    int value;
    std::vector<Node*> edges;
    bool visited;
public:
    // insert constructors, destructors,
    // accessors, and mutators here
    Node(int val)//constructor
    {
        this->visited = false;
        this->value = val;
    
    }
    ~Node()//didn't allocate memory so nothing needed in destructor
    {
        
    }
    bool dfs(int to_find);
    void add_edge(Node* node);
    void setVisited(bool v) //so that we can call visited in main function
    {
        visited = v;
    }
};

// true indicates that the value was found, and false indicates that the value was not found.
bool Node::dfs(int to_find) //method of the class
{

    if(this->value == to_find) //creates pointer to value for that specific node
    {
        return true;
    }
    std::vector<Node*>::iterator i; //create iterator for a vector of node pointers
    for(i = this->edges.begin(); i != this->edges.end(); i++) //actual first value of edges to last value
    {
        Node * n = *i; //dereferences i to get the node that it is connected to 
        if (n->visited == false) //if that node was not visited
        {
            n->visited = true;  //it has now been visited so set to true
            bool r = n->dfs(to_find); //recrusively run

            if(r) //if we find point looking for 
            {
                return r;
            }
        }
    }

    return false;
}
void Node::add_edge(Node* node) //the node we will be connecting to
{
    edges.push_back(node); 
}

int main(void)
{
    
    vector <Node*> Nodelist;
    Node* Node1 = new Node(1); //new makes it into a pointer
    Nodelist.push_back(Node1); //push back every node onto the list
    Node* Node2 = new Node(2);
    Nodelist.push_back(Node2);
    Node* Node3 = new Node(3);
    Nodelist.push_back(Node3);
    Node* Node4 = new Node(4);
    Nodelist.push_back(Node4);
    Node2->add_edge(Node1); //use arrow because it is a pointer
    Node1->add_edge(Node2);
    Node2->add_edge(Node3);
    Node3->add_edge(Node4);
    cout << "4 should be found" << endl;

    if (Node1->dfs(4))
    {
        cout << "4 was found" << endl;
        for (unsigned i=0; i < Nodelist.size(); i++)
        { 
            Nodelist[i]->setVisited(false); //set our Nodelist array all back to false(reset)
        }
    }
    else
    {
        cout << "4 is not found" << endl;
    }

    cout<< "2 should be found" << endl;

    if (Node1->dfs(2))
    {
        cout << "2 was found" << endl;
        for (unsigned i=0; i < Nodelist.size(); i++)
        {
            Nodelist[i]->setVisited(false);
        }
    }
    else
    {
        cout << "2 was not found" << endl;
    }
    cout<< "7 should not be found" << endl;


    if (Node1->dfs(7))
    {
        cout << "7 was found" << endl;
        for (unsigned i=0; i < Nodelist.size(); i++)
        {
            Nodelist[i]->setVisited(false);
        }
    }
    else
    {
        cout << "7 was not found" << endl;
    }

    return 0;

}
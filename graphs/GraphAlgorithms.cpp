/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2018
 * @copyright This code is in the public domain.
 *
 * @brief The MST and Shortest Path algorithms
 * (implementation).
 *
 */
#include "GraphAlgorithms.hpp"

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to GraphAlgorithms.hpp if you write a helper
 * function!
 *
 */

/**
 * TODO: Implement Prim's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Prim's algorithm
 *
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				onMST and notOnMST are two vectors defined in
 *				GraphAlgorithms.hpp
 * 				that you can use to store which nodes are both in/not in the
 * 				MST. These are cleared at the start of the MST computation for 
 * 				you. To access the nodes that a specific node connects to
 *				you, you can use the vector<Node *> edges which is part
 *				of the Node struct in structs.hpp
 * 				You can compare two nodes to see if they are the same by
 * 				comparing the id attribute of a Node.
 *				You can calculate distance from one node to another by calling
 * 				the double distance(Node a) function of the Node struct.
 * 				Whenever you decide to add an edge between two nodes
 *				to the MST, you can use the provided drawEdge function
 *				in GraphAlgorithms.cpp
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * Prim's algorithm outline

visited_array = [] - create an array that will store all the visited Nodes
edge_array = [] - create an array with the edges that we didn't use, once used then remove 
point = firstNode - the first Node we will be starting from
visited_array.push_back(point)- add the first point to the visited array


We have now initialized the first point on the MST. We can start to use loops now
while there are still nodes not in the visited array:
For the node we are currently at, add all the edges that stem from that node onto the visited array
check the weights of all the edges that connect the node to another node.
Once we've checked all the weights, select the edge with the least weight. Pushback that node to the visited array, 
delete the edge from the edge_array but still store the other edges we didn't use- add these edges to the edge_array.
set point = the Node we just selected

continue until loop until every node is in the visited array, then break. 
 *
 *
 */
vector <Edge*> get_edge_vector(vector <Node*> ontree, vector <Node*> notontree, vector<Edge*> edgevector)
{
    vector <Edge*> edges;
    unsigned length = edgevector.size();
    
    for(unsigned i=0; i<ontree.size(); i++) //loop through all the elements on the tree and elements in edgevector
    {
       for(unsigned j=0; j < length; j++)
       {
        if (edgevector[j]->a->id == ontree[i]->id) //if Node a in the edegvector is on the tree
        {
            for(unsigned k=0; k < notontree.size(); k++) //loop through the notontree
            {
                if (edgevector[j]->b->id == notontree[k]->id) //if our other Node b from edgevector is not on the tree
                {
                    edges.push_back(edgevector[j]); //push that edge onto edges
                }
            }
        }
        else if (edgevector[j]->b->id == ontree[i]->id) //same process as above, but assuming Node b is on tree
        {
            for(unsigned k=0; k < notontree.size(); k++)
            {
                if (edgevector[j]->a->id == notontree[k]->id)
                {
                    edges.push_back(edgevector[j]);
                }
            }
        }
       }
    }

    return edges;

}
void buildMSTPrim(Graph g, GraphApp *app) 
{
    onMST.erase(onMST.begin(), onMST.end());
    notOnMST.erase(notOnMST.begin(), notOnMST.end());
    for (unsigned i =0; i < g.nodes.size(); i++)
    {
        notOnMST.push_back(g.nodes[i]); //push back all of our nodes onto the not onMST
    }

    Node* point = g.nodes[0]; //set our first point equal to the first element in nodes
    onMST.push_back(point);
    notOnMST.erase(notOnMST.begin());
    vector<Edge*> possible = get_edge_vector(onMST, notOnMST, g.edges); //create a possible edges vector 
    double min = possible[0]->weight; //set minimum equal to the first edges
    Edge* bestone = possible[0];

    for(unsigned j=1; j < possible.size(); j++) //go through all edges, find smallest weight
       {
            if (possible[j]->weight < min)
            {
                min = possible[j]->weight;
                bestone = possible[j];
            }
        }
    drawEdge(bestone->a, bestone->b, g.edges, app, true); //draw the smallest edge
    if(bestone->a->id == point->id) //check if node a in the edge is equal to our first point
    {
        onMST.push_back(bestone->b); //if so, push the other node onto onMST
        unsigned length1 = notOnMST.size();
        for (unsigned j=0; j < length1; j++)
        {
            if (bestone->b->id == notOnMST[j]->id) //erase that same node from notOnMST
            {
                    
                notOnMST.erase(notOnMST.begin() + j);
            }
        }
            
    }
    else 
    {
        onMST.push_back(bestone->a); //same process as above, except pushing node a on onMST
        unsigned length1 = notOnMST.size();
        for (unsigned j=0; j < length1; j++)
        {
            if (bestone->a->id == notOnMST[j]->id)
            {
                notOnMST.erase(notOnMST.begin() + j);
            }
        }
    }

    

    while (onMST.size() < g.nodes.size()) //create a while loop for the rest of the cases
    {


       vector<Edge*> vector_points = get_edge_vector(onMST, notOnMST, g.edges);
       double min = vector_points[0]->weight; //again set minimum equal to first weight
       Edge* best_edge = vector_points[0]; //set the bestedge itself equal to that first edge
       for(unsigned j=1; j < vector_points.size(); j++) //same process to find minimum weight edge as above
       {
       
            if (vector_points[j]->weight < min)
            {
                min = vector_points[j]->weight;
                best_edge = vector_points[j];
               
            }
        }
        drawEdge(best_edge->a, best_edge->b, g.edges, app, true); //draw that edge on 

        unsigned length = onMST.size();

        for (unsigned int i = 0; i < length; i++) //same process as for first edge, push the corresponding nodes onto 
            //MST and take off notonMOST
        {
            
            if(best_edge->a->id == onMST[i]->id)
            {
                onMST.push_back(best_edge->b);
                unsigned length1 = notOnMST.size();
                for (unsigned j=0; j < length1; j++)
                {
                    if (best_edge->b->id == notOnMST[j]->id)
                    {
                        
                        notOnMST.erase(notOnMST.begin() + j);
                    }
                }
                
            }
            else if(best_edge->b->id == onMST[i]->id)
            {
                onMST.push_back(best_edge->a);
                unsigned length1 = notOnMST.size();
                for (unsigned j=0; j < length1; j++)
                {
                    if (best_edge->a->id == notOnMST[j]->id)
                    {
                        notOnMST.erase(notOnMST.begin() + j);
                    }
                }
            }
        }
       

        
    }

}


/**
 * TODO: Implement Kruskal's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Kruskal's algorithm
 *
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than
 *passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				You'll want to use a priority queue to determine which edges
 * 				to add first. We've created the priority queue for you
 * 				along with the compare function it uses. All you need to do
 * 				is call edge_queue.top(), edge_queue.pop(), edge_queue.push()
 * 				The data type that this priority queue stores, KruskalEdge 
 *              is defined in GraphAlgorithms.hpp and is an edge between
 *              any two trees. Each Node has a kruskal_edges attribute to store
 *              all the nodes it connects to in the MST. Make sure to use this
 *				to be able to join trees later!
 * 				To know which tree a node is in, use the which_tree attribute.
 * 				You can still use the edges, distance, and id
 *				attributes of a Node.
 * 				When connecting trees, you can call the
 *				kruskalFloodFill function
 * 				defined in structs.hpp on a node to convert it and its
 * 				MST connected nodes to a different tree number recursively.
 *				As in Prim's algorith, call drawEdge to add a connection between
 * 				two nodes to the MST
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * Add your outline here
 *
 *
 */
void buildMSTKruskal(Graph g, GraphApp *app) {
    auto compare_func = [](KruskalEdge *a, KruskalEdge *b) {
        return (a->weight > b->weight);
    };
    std::priority_queue<KruskalEdge *, std::vector<KruskalEdge *>,
                        decltype(compare_func)>
        edge_queue(compare_func);

    // Write code here
}

/**
 * TODO: Implement Djikstra's shortest path algorithm.
 *
 * @brief Find the shortest path between start and end nodes with Djikstra's
 * 		  shortest path algorithm
 *
 * @param start	Index of start node of path to find
 * 				Can access the Node * element by using
 *				g.nodes[start]
 * @param end	Index of end node of path to find
 * 				Can access the Node * element by using g.nodes[end]
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				You can use the distance_to_start attribute of the Node struct
 * 				in structs.hpp to keep track of what the distance from each
 * 				Node to the start node during computation
 * 				You can use the previous attribute of the Node struct
 *				in structs.hpp to keep track of the path you are taking to
 *				later backtrack.
 *				To access the nodes that a specific node connects to you, you
 * 				can use the vector<Node *> edges which is part of the Node struct
 * 				in structs.hpp
 *				Whenever you decide to add an edge between two nodes
 *				to the MST, you can use the provided drawEdge function in
 *				GraphAlgorithms.cpp
 *
 * Djikstra's algorithm outline
 * Set up some vector Q that will contain all the possible nodes
 * set the distance[source] = 0, since the distance from source to soruce is 0
 * set the previous[source] = null, since there was no previous distance from the starting point
 * Initialize our graph to begin with:
 *  for each node 
 *      if the node != source, then set its distance[node] = infinity, and previous[node] = null
 * add all nodes to Q
 * While our Q is not empty
 *  first find the node the smallest distance away from our source, set it equal to some variable "u"
 *  remove that node from q
 *  for every neighbor of u
 *      set our alternate distance = the distance[u] + the length from u to the neighbor, some node v
 *       if this alternate distance is < an already calculated distance[v] from before,
 *           set distance[v] = alternate distance
 *           and our previous[v] = u
 *
 }
 *
 */
void findShortestPath(int start, int end, Graph g, GraphApp *app) {
    // Write code here
}

/**
 * @brief Adds an edge to either the MST or the shortest path based on the
 * 			nodes to connect given. This is done by iterating through the edges
 * 			to find the correct edge given the nodes.
 *
 * @param pt1	One side of edge to draw
 * @param pt2	Other side of edge to draw
 * @param edges	Vector of edges in the graph
 * @param app	Graphics application class
 * @param mst	True if we are adding edge to MST, False if we are adding edge
 * 				to shortest path
 **/

void drawEdge(Node *pt1, Node *pt2, vector<Edge *> edges, GraphApp *app,
              bool mst) 
{
    for (unsigned int i = 0; i < edges.size(); i++) {
        if ((edges[i]->a == pt1 && edges[i]->b == pt2) ||
            (edges[i]->a == pt2 && edges[i]->b == pt1)) {
            if (mst)
                app->add_to_mst(edges[i]);
            else
                app->add_to_path(edges[i]);
            break;
        }
    }
    return;
}

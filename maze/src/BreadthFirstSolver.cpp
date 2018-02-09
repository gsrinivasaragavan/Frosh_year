/**
 * @file BreadthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements breadth-first search.
 *
 * @section License
 * Copyright (c) 2014-2015 California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the California Institute of Technology.
 *
 */

#include "BreadthFirstSolver.hpp"

/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
BreadthFirstSolver::BreadthFirstSolver(class MazeSolverApp *app)
{
    queue = new CoordinateQueue(app);
    init();
}

/**
 * @brief Initializes the solver (student-implemented).
 */
void BreadthFirstSolver::init()
{
     for(int i = 0 ; i <= MAZE_END_X; i++) //for all x coordinates
    {
        for(int j = 0; j <= MAZE_END_Y; j++)//for all y coordinates
        {
            visited[i][j].visited = false; //set every point in visited array to false
            visited[i][j].from = Coordinate (-1, -1); //set every from coordinate to arbritrary
            //(-1, -1)
        }
    }
}

/**
 * @brief Deinitializes the solver.
 */
BreadthFirstSolver::~BreadthFirstSolver()
{
    delete queue;
    deinit();
}

/**
 * @brief Deinitializes the solver (student-implemented).
 */
void BreadthFirstSolver::deinit()
{
    //no deinit needed because not allocating any memory
}

/**
 * @brief Solve the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void BreadthFirstSolver::solve(MazeGrid *maze)
{
    Coordinate point = Coordinate (MAZE_START_X, MAZE_START_Y);
    queue->enqueue(point); //enqueue first point to queue
    while(queue->is_empty() == false) //while the queue is not empty
    {
        point = queue->peek(); //change point every time to the front of queue
        visited[point.x][point.y].visited = true; //set first point as visited
        if(point.x != MAZE_END_X || point.y != MAZE_END_Y) //if we haven't finished the maze
        {
            int var = maze->get_possible_moves(point.x, point.y);
            if (var &E && visited[point.x + 1][point.y].visited == false) //if it is possible to move East
                //and we haven't visited that point yet
            {
                queue->enqueue(Coordinate (point.x+1, point.y)); //enqueue point to queue
                visited[point.x +1][point.y].from = Coordinate (point.x, point.y); 
                //set the point we are at's from value on the array as the previous point

            }
            if (var &S && visited[point.x][point.y+1].visited == false)//if it is possible to move South
                //and we haven't visited that point yet
            {
                queue->enqueue(Coordinate (point.x, point.y+1)); //enqueue point to queue
                visited[point.x][point.y+1].from = Coordinate(point.x, point.y); 
                //set the point we are at's from value on the array as the previous point

            }
            if (var &N && visited[point.x][point.y - 1].visited == false)//if it is possible to move North
                //and we haven't visited that point yet
            {
                queue->enqueue(Coordinate (point.x, point.y-1));//enqueue point to queue
                visited[point.x ][point.y-1].from = Coordinate (point.x, point.y);
                //set the point we are at's from value on the array as the previous point

            }
            if (var &W && visited[point.x-1][point.y].visited == false)//if it is possible to move West
                //and we haven't visited that point yet
            {
                queue->enqueue(Coordinate (point.x-1, point.y)); //enqueue point to queue
                visited[point.x -1][point.y].from = Coordinate (point.x, point.y);;
                //set the point we are at's from value on the array as the previous point

            }
            
            queue->dequeue(); //dequeue the previous point
        }
        else
        {
            break; //if maze is done
        }

    }
}

/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
vector<Coordinate> BreadthFirstSolver::get_path()
{
    vector<Coordinate> list;
    Coordinate coord1 = queue->peek(); //set coordinate to the one at front of queue
    while(coord1.x != MAZE_START_X || coord1.y != MAZE_START_Y)
    {
        list.push_back(coord1); //add that coordinate to the vector
        coord1 = visited[coord1.x][coord1.y].from; //set coord1 to the previous point (from value)
    }
    list.push_back(Coordinate (MAZE_START_X, MAZE_START_Y)); //add end point of maze to vector
    


    return list;
}


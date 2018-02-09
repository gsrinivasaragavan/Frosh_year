/**
 * @file DepthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements depth-first search.
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

#include "DepthFirstSolver.hpp"
#include <vector>
/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
DepthFirstSolver::DepthFirstSolver(class MazeSolverApp *app)
{
    stack = new CoordinateStack(app);
    init();
}

/**
 * @brief Initializes the solver (student-implemented).
 */
void DepthFirstSolver::init()
{
    for(int i = 0 ; i<= MAZE_END_X; i++) //for all x coordinates
    {
        for(int j = 0; j <= MAZE_END_Y; j++)//for all y coordinates
        {
            visited[i][j] = false; //set every point in visited array to false
        }
    }
}

/**
 * @brief Deinitializes the solver.
 */
DepthFirstSolver::~DepthFirstSolver()
{
    delete stack;
    deinit();
}


/**
 * @brief Deinitializes the solver (student-implemented).
 */
void DepthFirstSolver::deinit()
{
   //no deinit needed because not allocating any memory
}


/**
 * @brief Solves the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void DepthFirstSolver::solve(MazeGrid *maze)
{
    
    Coordinate point = Coordinate (MAZE_START_X, MAZE_START_Y);
    stack->push(point); //add first point to stat
    while(stack->is_empty() == false) //while the stack is not empty
    {
        visited[point.x][point.y] = true; //set first point as visited
        if(point.x != MAZE_END_X || point.y != MAZE_END_Y) //if we haven't finished the maze
        {
            int var = maze->get_possible_moves(point.x, point.y);
            if (var &E && visited[point.x + 1][point.y] == false) //if it is possible to move East
                //and we haven't visited that point yet
            {
                stack->push(point); //push point to stack
                point = Coordinate(point.x + 1, point.y); //redefine our point to the current
            }
            else if (var &S && visited[point.x][point.y+1] == false)//if it is possible to move South
                //and we haven't visited that point yet
            {
                stack->push(point); //push point to stack
                point = Coordinate(point.x, point.y + 1); //redefine our point to the current
            }
            else if (var &N && visited[point.x][point.y - 1] == false)//if it is possible to move North
                //and we haven't visited that point yet
            {
                stack->push(point);//push point to stack
                point = Coordinate(point.x, point.y - 1);//redefine our point to the current
            }
            else if (var &W && visited[point.x-1][point.y] == false)//if it is possible to move West
                //and we haven't visited that point yet
            {
                stack->push(point); //push point to stack
                point = Coordinate(point.x - 1, point.y);//redefine our point to current
            }
            else 
            {
                point = stack->pop(); //if move is not possible, pop our point (it's wrong)
            }
        }
        else
        {
            stack->push(Coordinate (MAZE_END_X, MAZE_END_Y)); //push the end coordiante if maze is done
            break;
        }

    }
}

/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
vector<Coordinate> DepthFirstSolver::get_path()
{
    return stack->get_path();
}


/**
 * @file testsuite.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Performs tests of the CoordinateQueue and CoordinateStack classes.
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

#include <cstdio>
#include "CoordinateStack.hpp"
#include "CoordinateQueue.hpp"

int main()
{
    Coordinate c;
    CoordinateQueue *queue = new CoordinateQueue();
    CoordinateStack *stack = new CoordinateStack(); //Coordinatestack pointer, have a 
    //pointer to the type

    /* TODO: Test all the things! */
    Coordinate cord1 = Coordinate (1,4);
    Coordinate cord2 = Coordinate (2,5);
    Coordinate cord3 = Coordinate (3,7);
    Coordinate cord4 = Coordinate (4,8);
    std::cout << "Pushing Coordinate (1, 4). Pushed value: " << std::endl;
    stack->push(cord1); 
    stack->peek().printcoord();
    std::cout << "Pushing Coordinate (2, 5) " << std::endl;
    stack->push(cord2); 
    std::cout << "Pushing Coordinate (3, 7) " << std::endl;
    stack->push(cord3);
    std::cout << "Pushing Coordinate (4, 8) " << std::endl;
    stack->push(cord4);
    std::cout << "Popping top coordinate (4,8). Popped value: "<< std::endl;
    stack->pop().printcoord();
    std::cout << "Popping top coordinate (3, 7). Popped value: "<< std::endl;
    stack->pop().printcoord();
    std::cout<< "Checking if stack is empty. Should return False. Value returned:" 
    << std:: endl;
    if (stack->is_empty() == true)
    {
    	std::cout<< "True" << endl;
    }
    else
    {
    	std::cout<< "False" << endl;

    }
    std::cout << "Popping top coordinate (2, 5). Popped value: "<< std::endl;
    stack->pop().printcoord();
    std::cout << "Popping top coordinate (1, 4). Popped value: "<< std::endl;
    stack->pop().printcoord();
    std::cout<< "Checking if stack is empty. Should return True. Value returned:" 
    << std:: endl;
    if (stack->is_empty() == true)
    {
    	std::cout<< "True" << endl;
    }
    else
    {
    	std::cout<< "False" << endl;

    }
    Coordinate cord5 = Coordinate (5, 9);
    Coordinate cord6 = Coordinate (6, 10);
    Coordinate cord7 = Coordinate (7, 11);
    Coordinate cord8 = Coordinate (8, 12);
    std::cout << "Enqueing Coordinate (5, 9). Enqued value: " << std::endl;
    queue->enqueue(cord5); 
    queue->peek().printcoord();
    std::cout << "Enqueing Coordinate (6, 10) " << std::endl;
    queue->enqueue(cord6); 
    std::cout << "Enqueing Coordinate (7, 11) " << std::endl;
    queue->enqueue(cord7);
    std::cout << "Enqueing Coordinate (8, 12) " << std::endl;
    queue->enqueue(cord8);
    std::cout << "Dequeueing front coordinate (5, 9). Dequeued value: "<< std::endl;
    queue->dequeue().printcoord();
    std::cout << "Dequeueing front coordinate (6, 10). Dequeued value: "<< std::endl;
    queue->dequeue().printcoord();
    std::cout<< "Checking if stack is empty. Should return False. Value returned:" 
    << std:: endl;
    if (queue->is_empty() == true)
    {
    	std::cout<< "True" << endl;
    }
    else
    {
    	std::cout<< "False" << endl;

    }
    std::cout << "Dequeueing front coordinate (7, 11). Dequeued value: "<< std::endl;
    queue->dequeue().printcoord();
    std::cout << "Dequeueing front coordinate (8, 12). Dequeued value: "<< std::endl;
    queue->dequeue().printcoord();
    std::cout<< "Checking if stack is empty. Should return True. Value returned:" 
    << std:: endl;
    if (queue->is_empty() == true)
    {
    	std::cout<< "True" << endl;
    }
    else
    {
    	std::cout<< "False" << endl;

    }




    delete queue;
    delete stack;

    return 0;
}

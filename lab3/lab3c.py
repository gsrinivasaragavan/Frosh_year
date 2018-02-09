'''
lab3c.py
Simple L-system simulator.
'''

# References: 
#   http://en.wikipedia.org/wiki/L-systems
#   http://www.kevs3d.co.uk/dev/lsystems/
# N.B. http://en.wikipedia.org/wiki/MU_puzzle for midterm?

import math

# ---------------------------------------------------------------------- 
# Example L-systems.
# ---------------------------------------------------------------------- 

# Update function
def update(dict1, string1):
    '''This function will take two arguments, a dictionary and a L-system string
    and will generate the next version of the L-system string by combining all
    the strings into an individual string'''
    newstring = ''
    for x in string1:
        if x in dict1:
            newstring += dict1[x]
        else:
            newstring += x
    return newstring
    

# Koch snowflake.
koch = { 'start' : 'F++F++F', 
         'F'     : 'F-F++F-F' }
koch_draw = { 'F' : 'F 1', 
              '+' : 'R 60', 
              '-' : 'L 60' }

# Hilbert curve.
hilbert  = { 'start' : 'A', 
             'A'     : '-BF+AFA+FB-' , 
             'B'     : '+AF-BFB-FA+' }
hilbert_draw = { 'F' : 'F 1', 
                 '-' : 'L 90', 
                 '+' : 'R 90' }

# Sierpinski triangle.
sierpinski = { 'start' : 'F-G-G', 
               'F'     : 'F-G+F+G-F', 
               'G'     : 'GG' }
sierpinski_draw = { 'F' : 'F 1', 
                    'G' : 'F 1', 
                    '+' : 'L 120', 
                    '-' : 'R 120' }

# ---------------------------------------------------------------------- 
# L-systems functions.
# ---------------------------------------------------------------------- 

def iterate(lsys, n):
    '''This function will take two arguments, an L-system dictionary and an 
    integer greater than n, it will update the string bn times using the update
    function'''
    x=lsys['start']
    for i in range(n):
        x= update(lsys, x)
    return x
        
def lsystemToDrawingCommands(draw, s):
    '''This function will take two arguments, a dictionary whose keys are 
    characters in L-system strings and whose values are drawing commands, and
    an L-system string. It will return the list of drawing commands you need to 
    draw the figure corresponding to the L-system string.'''
    x=[]
    for value in s:
        if value in draw:
            x.append(draw[value])
    return x
    
def bounds(cmds):
    '''This function will take on argument, which is a list of commands 
    generated by lsystemToDrawingcommands, which will compute the bounding 
    coordinates of the drawing, giving x max x min and y max y min values'''
    x = 0
    y = 0
    angle = 0
    xmin = 0
    xmax = 0
    ymin = 0
    ymax = 0
    for i in cmds:
        z = nextLocation(x, y, angle, i)
        x = z[0]
        y = z[1]
        angle = z[2]
        if (z[0]) < xmin:
            xmin = float(z[0])
        if (z[0]) > xmax:
            xmax = float(z[0])
        if (z[1]) > ymax:
            ymax = float(z[1])
        if (z[1]) < ymin:
            ymin = float(z[1])
        
    return (xmin, xmax, ymin, ymax)
        
def nextLocation(x, y, angle, cmd):
    '''This function will take four arguments, the current x coordinate of the
    turtle, current y coordinate of the turtle, current direction the turtle
    is facing, and a drawing command. It will return a tuple of the next x and
    y coordiates with the turtle as well as the next angle'''
    #I bounded the angles between 0 and 360 so that the function is not taking
    #an angle greater than 360 and just taking the same coterminal angle. Why
    #is this not okay?
    import math
    finalx = x
    finaly = y
    nextangle = angle
    a = cmd.split()
    if a[0] =='F':
        finalx += float(a[1]) * (math.cos ((math.pi / 180) * angle))
        finaly += float(a[1]) * (math.sin ((math.pi / 180) * angle))
    if a[0] == 'L':
        nextangle = (angle + float(a[1]) % 360)
    if a[0] == 'R':
        nextangle = (angle - float(a[1]) % 360)
    return (finalx, finaly, nextangle)    

def saveDrawing(filename, bounds, cmds):
    '''This function will take three arguments: a filename, the bounds created
    by the bounds function, and a list of drawing commands. It will write the 
    bounds information on a single line and then write the drawing commands to 
    the file, one per line.'''
    file1 = open(filename, 'w')
    for i in bounds:
        file1.write(str(i) + ' ')
    file1.write('\n')
    for var in cmds:
        file1.write(str(var) + '\n')
        
def makeDrawings(name, lsys, ldraw, imin, imax):
    '''Make a series of L-system drawings.'''
    print('Making drawings for {}...'.format(name))
    for i in range(imin, imax):
        l = iterate(lsys, i)
        cmds = lsystemToDrawingCommands(ldraw, l)
        b = bounds(cmds)
        saveDrawing('%s_%d' % (name, i), b, cmds)

def main():
    makeDrawings('koch', koch, koch_draw, 0, 6)
    makeDrawings('hilbert', hilbert, hilbert_draw, 1, 6)
    makeDrawings('sierpinski', sierpinski, sierpinski_draw, 0, 10)

from tkinter impor-=t *
import random
import math

# Graphics commands.
# Event handlers.

def key_handler(event):
    '''Handle key presses.'''
    global randcol
    global N
    key = event.keysym
    if key == 'x':
        canvas.delete(s)
    elif key == 'c':
        randcol = random_color()
    elif key == 'plus':
        N += 2
    elif key == 'minus':
        if N > 5:
            N -= 2
        
def button_handler(event):
    '''Handle left mouse button click events.'''
    size = random.randint(50, 100)
    x = event.x
    y = event.y
    center = (x, y)
    s = draw_star(center, N)
    starlist.append(s)    
    #gives x and y coordinats of where you press the button so you can draw
    #around it
    

def random_color():
    '''This function will generate random color values in hexadecimal form'''
    list1 = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 
             'd', 'e', 'f']
    hexadecimal = ''
    for i in range(6):
        hexadecimal+= random.choice(list1)
    return '#' + hexadecimal

def draw_line(p1, p2):
    (x1, y1) = p1
    (x2, y2) = p2
    linedrawn = canvas.create_line(x1, y1, x2, y2, fill = randcol)
    linelist.append(linedrawn)

def draw_star(center, N):
    pointstarlist = []
    (x, y) = center
    size = random.randint(20, 50)
    for i in range(N):
        point = (x + size * math.cos((math.pi / 2) + (i / N) * (2 * math.pi)), 
        y - size * math.sin((math.pi / 2) + (i / N) * (2 * math.pi)))
        pointstarlist.append(point)
    #we have a list of the points in the star, need to do use draw function on 
    #two of the points.
    for i in range(N):
        draw_line(pointstarlist[i], pointstarlist[int(i + (N - 1) / 2) % N])
    
    
if __name__ == '__main__':
    root = Tk()
    root.geometry('800x800')
    canvas = Canvas(root, width=800, height=800)
    N = 5
    canvas.pack()
    randcol = random_color()
    linelist = []
    starlist = []
    

    # Bind events to handlers.
    root.bind('<Key>', key_handler)
    canvas.bind('<Button-1>', button_handler)
    root.bind('<q>', quit)
    root.bind('<minus>', key_handler)
    root.bind('<plus>', key_handler)
    

    # Start it up.
    root.mainloop()

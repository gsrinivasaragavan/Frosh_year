from tkinter import *
import random

# Graphics commands.
# Event handlers.

def key_handler(event):
    '''Handle key presses.'''
    global randcol
    key = event.keysym
    if key == 'x':
        circles.remove(o)
    elif key == 'c':
        randcol = random_color()

def button_handler(event):
    '''Handle left mouse button click events.'''
    size = random.randint(20,50)
    x = event.x
    y = event.y
    #gives x and y coordinats of where you press the button so you can draw
    #around it
    global o
    o = canvas.create_oval(x-size/2, y-size/2, x+size/2, y+size/2,
                      fill = randcol, outline = randcol)    
    circles.append(o)



def random_color():
    '''This function will generate random color values in hexadecimal form'''
    list1 = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 
             'd', 'e', 'f']
    hexadecimal = ''
    for i in range(6):
        hexadecimal+= random.choice(list1)
    return '#' + hexadecimal

if __name__ == '__main__':
    root = Tk()
    root.geometry('800x800')
    canvas = Canvas(root, width=800, height=800)
    canvas.pack()
    randcol = random_color()
    circles = []

    # Bind events to handlers.
    root.bind('<Key>', key_handler)
    canvas.bind('<Button-1>', button_handler)
    root.bind('<q>', quit)

    # Start it up.
    root.mainloop()

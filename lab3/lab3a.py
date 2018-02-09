#A.1
def list_reverse(list1):
    '''this function will reverse the order of a user inputted list without
    changing the original list'''
    y=len(list1)
    x=list1[0:y]
    x.reverse()
    return x
#A.2
def list_reverse2(list1):
    '''this function will reverse the order of a user inputted list without
    changing the original list'''    
    y=len(list1)
    x=[]
    for z in range(y, 0, -1):
        x.append(list1[z-1])
    return x
#A.3
def file_info(filename):
    '''This function will take a string representing the name of a text file, 
    and will return the number of lines, words, and characters in the file as a
    tuple'''
    file1 = open(filename, 'r')
    numlines = 0
    numwords = 0
    numcharacters = 0
    while True:
        line = file1.readline()
        if line == '':
            break
        else:
            numlines += 1
            numwords += len(line.split())
            words = line.split()
            for w in words:
                numcharacters += len(w)
    file1.close()
    return (numlines, numwords, numcharacters)
#A.4
def file_info2(filename):
    '''This function will take a string representing the name of a text file and 
    will return a dictionary containing the line count, word count, and 
    character count using the keys 'lines', 'words', and 'characters'''
    file_info(filename)
    d={'lines' : numlines,
       'words' : numwords,
       'characters': numcharacters}
    file1.close()
    return (d)
#A.5
def longest_line(filename):
    '''This function will take th input of a name of a text file and return the 
    length of the longest line as well as the actual line'''
    file1 = open(filename, 'r')
    maxwords = 0
    numwordm = 0
    maxline = ''
    while True:
        line = file1.readline()
        if line == '':
            break
        else:
            numword=len(line.split())
            if numword > maxwords:
                maxwords = numword
                maxline = line
    file1.close()
    return(maxwords, maxline)
#A.6
def sort_words(string1):
    '''This function will take in a string and will convert it into a list, sort
    the list, and then return the sorted list of words'''
    x = ''
    x = string1.split()
    x.sort()
    return x
#A.7
#11011010 converted to decimal: we must start at the end of binary number. This
#number will be represented by (0*1). The next number will be represented by
#(1*2), the next by (0*4), the next by (1*8), the next by (1*16), the next 
#(0*32), the next (1*64), and the last (1*128). We add all these values up 
#to get our value for the binary number, which would be 0+2+0+8+16+0+64+128,
#which would be 218. The biggest eight digit number would be all 1's, and its
#value would be 256.
#A.8
def binaryToDecimal(list1):
    '''This function will take in a binary number and will return its decimal
    value'''
    list1.reverse()
    total = 0
    exponent = 0
    for number in list1:
        total += number * 2 ** exponent
        exponent += 1
    return total
#B.1 Always put a space after a comma, spaces after and before operators, and 
#variable name should not be abbreviated Corrected version:
def sumofcubes(a, b, c):
    return a * a * a + b * b * b + c * c * c
#B.2 Line length is too long, leave a space after the open comment sign, wordy
#variable names, comments should be gramatically correct. Corrected version:
def sumofcubes(argA, argB, argC, argD):
    #return sum of cubes of arguments a, b, c, and d
    return argA ** 3 + argB ** 3 + argC ** 3 + argD ** 3
#B.3 Indentation is not consistent, bad whitespace
# 2 different types of style mistakes
def sum_of_squares(x,y):
    return x * x + y * y
def sum_of_three_cubes(x,y,z):
    return x * x * x + y * y * y + z * z * z

            

    


        
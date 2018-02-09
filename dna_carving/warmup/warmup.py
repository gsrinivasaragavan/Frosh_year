#space time complexity: O(N)
def stringfunction(num):
    list1 = []
    numstring = str(num) #make the input of integers into a string
    for digit in numstring:
        list1.append(digit)
    reallist = list(map(int, list1)) #create a list of the numbers, convert them back to ints
    length = len(reallist)
    if reallist[0] == 0:
        return False
    for i in range(length): #loop through all the ints
        boolval = True #set the initial return value to True
        currentval = reallist[i]
        if i < len(reallist) - 1:
            nextval = reallist[i+1]
            if 3 <= currentval <= 9: 
                if nextval == 0: #if you have a value 3-9, 0 cannot be next number
                    boolval = False
                    break
            if currentval == 0:
                if nextval == 0: #two straight 0's cannot work
                    boolval = False
                    break
    return boolval
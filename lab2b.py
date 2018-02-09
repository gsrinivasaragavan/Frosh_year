import random

def make_random_code():
    '''This function will return a string of four characters from the options
    "R, G. B. Y. O. W"'''
    list1 = ''
    for x in range(0, 4):
        list1 += (random.choice(['R','G','B','Y','O','W']))
    return list1

def count_exact_matches(string1, string2):
    '''This function checks the number of perfect matches between two strings 
    which have the same letter in the correct position'''
    x = 0
    for i in range(0, len(string1)):
        if string1[i] == string2[i]:
            x += 1
    return x

def count_letter_matches(string1, string2):
    '''This function checks the number of letter matches between two strings 
    regardless of position'''
    list1 = list(string1)
    list2 = list(string2)
    x=0
    for a in list1:
        if a in list2:
            x += 1
            list2.remove(a)
    return x

def compare_codes(string1, string2):
    '''This function will compare codes and return a string with the letters b,
    w, or a "-". B's indicate that a color is correct and in the correct 
    location, w inducates that a color is correct and in the wrong position, and
    "-" indicates no match whatsoever'''
    exactmatches = count_exact_matches(string1, string2)
    lettermatches = count_letter_matches(string1, string2)
    bl = exactmatches
    w = lettermatches - exactmatches
    bk = 4 - (bl + w)
    return bl * 'b' + w * 'w' + bk * '-'

def run_game():
    '''This function will run the mastermind game'''
    print('New game.')
    tries = 0
    result = ''
    x = make_random_code()
    while result != 'bbbb':
        guess = input('Enter your guess:')
        result = compare_codes(guess, x)
        print(result)
        tries += 1
    print('Congratulations! You cracked the code in '+ str(tries)+' moves')
                
        
    
    
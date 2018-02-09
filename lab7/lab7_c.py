'''
This program allows the user to interactively play the game of Sudoku.
'''

import sys

class SudokuError(Exception):
    pass

class SudokuMoveError(SudokuError):
    pass

class SudokuCommandError(SudokuError):
    pass

class Sudoku:
    '''Interactively play the game of Sudoku.'''

    def __init__(self):
        self.boardlist = []
        self.moves = []
        for i in range(9):
            self.boardlist.append([0,0,0,0,0,0,0,0,0])

    def load(self, filename):
        file1 = open(filename, 'r')
        column = 0
        row = 0
        for line in file1:
            if len(line) != 10:
                raise IOError('Line must be nine characters')
            for i in line[:-1]:
                if int(i) not in range(10):
                    raise IOError('Values must be between 0 and 9')
                self.boardlist[column][row] = i
                column += 1
            row += 1
            column = 0
        if row != 9:
            raise IOError('There must be nine rows')
        file1.close()
    def save(self, filename):
        file2 = open('filename.txt', 'w')
        for line in file2:
            linereal = str(line)
            file2.write(linereal)
            file2.write('\n')
        file2.close()
        

    def show(self):
        '''Pretty-print the current board representation.'''
        print()
        print('   1 2 3 4 5 6 7 8 9 ')
        for i in range(9):
            if i % 3 == 0:
                print('  +-----+-----+-----+')
            print(f'{i + 1} |', end='')
            for j in range(9):
                if self.boardlist[i][j] == 0:
                    print(end=' ')
                else:
                    print(f'{self.boardlist[i][j]}', end='')
                if j % 3 != 2 :
                    print(end=' ')
                else:
                    print('|', end='')
            print() 
        print('  +-----+-----+-----+')
        print()

    def move(self, row, col, val):
        row = int(row)
        col = int(col)
        row -= 1
        col -= 1
        if self.boardlist[row][col] != '0':
            raise SudokuError('Place is not empty')
        for i in range(9):
            if self.boardlist[row][i] == val:
                raise SudokuError('Value exists in row')
        for i in range(9):    
            if self.boardlist[i][col] == val:
                raise SudokuError('Value exists in column')
        
        if row <= 3:
            if col <= 3:
                for i in range(3):
                    for y in range(3):
                        if self.boardlist[i][y] == val:
                            raise SudokuError('Value exists in box')
            elif 3 < col <= 6:
                for i in range(3, 6):
                    for y in range(3, 6):
                        if self.boardlist[i][y] == val:
                            raise SudokuError('Value exists in box')
            elif 6 < col <= 9:
                for i in range(6, 9):
                    for y in range(6, 9):
                        if self.boardlist[i][y] == val:
                            raise SudokuError('Value exists in box')
            else:
                self.moves.append((row, col, val))
                self.board[row][col] = val
        elif 3 < row <= 6:
            if col <= 3:
                for i in range(3):
                    for y in range(3):
                        if self.boardlist[i][y] == val:
                            raise SudokuError('Value exists in box')
            elif 3 < col <= 6:
                for i in range(3, 6):
                    for y in range(3, 6):
                        if self.boardlist[i][y] == val:
                            raise SudokuError('Value exists in box')
            elif 6 < col <= 9:
                for i in range(6, 9):
                    for y in range(6, 9):
                        if self.boardlist[i][y] == val:
                            raise SudokuError('Value exists in box')
            else:
                self.moves.append((row, col, val))
                self.board[row][col] = val
        elif 6 < row <= 9:
            if col <= 3:
                for i in range(3):
                    for y in range(3):
                        if self.boardlist[i][y] == val:
                            raise SudokuError('Value exists in box')
            elif 3 < col <= 6:
                for i in range(3, 6):
                    for y in range(3, 6):
                        if self.boardlist[i][y] == val:
                            raise SudokuError('Value exists in box')
            elif 6 < col <= 9:
                for i in range(6, 9):
                    for y in range(6, 9):
                        if self.boardlist[i][y] == val:
                            raise SudokuError('Value exists in box')
            else:
                self.moves.append((row, col, val))
                self.board[row][col] = val
                        
    def undo(self):
        value = self.moves.pop()
        self.boardlist[value[0]-1][value[1]-1] = 0

    def solve(self):
        while True:
            inputgiven = input('Enter a move')
            if inputgiven == 'q':
                break
            elif len(inputgiven) == 3:
                self.move(inputgiven[0], inputgiven[1], inputgiven[2])
                self.show()
            elif inputgiven == 'u':
                self.undo()
            elif inputgiven == 's':
                self.save('filename.txt')
            else:
                raise SudokuCommandError('Command is not recognized')
                
            

if __name__ == '__main__':
    s = Sudoku()

    while True:
        filename = input('Enter the sudoku filename: ')
        try:
            s.load(filename)
            break
        except IOError as e:
            print(e)
   
    s.show()
    s.solve()
        
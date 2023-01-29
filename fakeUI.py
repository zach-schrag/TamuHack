# this file will be responsible for reading input from Brigham and being able to tell what to do with that
# information. valid or invalid move as well as where to move, etc. and also responsible for providing the coords
# to perform a move so that the c++ code can check if its valid and make the appropriate changes.
# the coords will look like a source and a destination, which will be validated or invalidated depending on the move.

# validater = open("move.txt", "r")
# line = validater.readline();
# if line == "poop":
#     print("i read accurately from the file!")


# pretty sure this needs to be put into a loop of sorts so that this doesnt execute once.


# the board will be loaded, 2 characters each represent each piece. So eight pieces with spaces
# and 8 lines. So run a getline 8 times and just put it into an array that zach can grab and output into the UI
# based on the characters that are given.


# src_move = False
# while not src_move:
#     python_writer = open("move.txt", "w")
#     source = input("this is the piece that is going to be moved: ")  # will be changed later according to mouse movements
#     python_writer.write(source + " go")
#     python_writer.close()
#     # check if this is a valid place that a piece is at.
#     validater = open("cpp2py.txt", "r")
#     validation_string = validater.readline()
#     if validation_string != "valid go":
#         validater.close()
#         continue
#     src_move = True

# when it gets here that means that the piece to be moved is a valid piece on the board.
# now we give destination and do the same thing, validate that too.
# dest_move = False
# python_writer = open("move.txt", "w")
# while not dest_move:
#     destination = input("this is the piece that we want to move to: ")  # will change to mouse input
#     python_writer.write(destination + " go")
#     python_writer.close()
#     validater = open("
#     cpp2py.txt", "r")
#     validation_string = validater.readline()
#     if validation_string != "valid go":
#         continue
#     dest_move = True
import numpy as np
import os
import time

global end
end = False

def board_loader(reader):
    board = np.empty((8, 8), dtype=object)  # empty array of type object, with the right size.
    # boardfile = open("board.txt", "r")  # read from cpp file the validity and then board
    line = reader.readline()  # skip one line. ez
    for i in range(8):  # 8 times. do this
        line = reader.readline()  # get the line
        liner = np.array(line.split(" "))  # make it into the pieces array per line
        for j in range(len(liner) - 1):  # for each piece on that row:
            board[i][j] = liner[j]  # make the index at that piece equal to the piece that was gotten from the file.
    # reader.close()
    os.remove("board.txt")
    return board  # return the new updated board.


# this is a function that will be used when a move is made. should not use a loop because lowkey it gets fucky
# with the whole file input output shit and reading from different files. this works because it is called when the
# user is ready to make a move, and then writes to the file, gets a validity (hopefully) and then returns the validity.
def move_interpreter(src, dest):
    python_writer = open("move.out", "w")  # open file to write move to.
    print("moving " + src + " " + dest)
    python_writer.write(src + " " + dest)  # write the move set so that logic can see it.
    python_writer.close()  # close so that the file becomes readable for the logic.
    if(os.path.isfile("board.txt")):
        os.remove("board.txt")
    os.rename("move.out", "move.txt")


def validate():
    while not os.path.isfile("board.txt"):
        continue
    updater = open("board.txt", "r")  # open the file that the cpp file wrote on to see validity and new board.
    valid = updater.readline() 
    print(valid) # read the validity line
    if valid == "good\n":  # if its good then:
        # print("valid move")  # this is for debug
        board = board_loader(updater)  # load a new board
        # print(board)  # debug
    elif valid == "CHECKMATE\n" or valid == "STALEMATE\n":
        board = board_loader(updater)  # load a new board
        print("well it's a checkmate")
        updater.close()
        return np.array([])
    else:
        updater.close()
        return np.array([-1])
        # print("not a valid move")  # debug
    updater.close()
    # close, im not deleting anything because im pretty sure that it is overwritten anyways, plus
    return board  # deleting the whole file would cause problems with file I/O. Deleting contents causes
    # problems for some reason that I have forgotten (sorry!) but im pretty sure there is a problem.
    # this is good! this works. goodbye.
    # open("board.txt", "w").close()  # deleting contents of the file


def move(src, dest):
    move_interpreter(src, dest)
    validate()

move("e2","e3")
move("h7","h6")
move("f1","c4")
move("h8","h7")
move("d1","f3")
move("h7","h8")
move("f3","f7")
## move("a2","a3")


##while True:
##    src = input("enter a src: ")
##    dest = input("enter a dest: ")
##    move_interpreter(src, dest)
##    if(validate().size == 0):
##        print("game over")
##        break
    
    
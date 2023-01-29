import pygame
from math import floor
#from random import randint

SCREEN_WIDTH  = 2000
SCREEN_HEIGHT = 2000
# DARK_SQUARE = (58, 117, 29) # green
DARK_SQUARE = (255, 105, 180) # pink
LIGHT_SQUARE = (248, 240, 227)
SELECTED_DARK_SQUARE = (255, 205, 150)
SELECTED_LIGHT_SQUARE = (248, 240, 137)
board = [ # mapping of the global board for testing until I get communications with logic
    ["br", "bn", "bb", "bq", "bk", "bb", "bn", "br"],
    ["bp", "bp", "bp", "bp", "bp", "bp", "bp", "bp"],
    ["ee", "ee", "ee", "ee", "ee", "ee", "ee", "ee"],
    ["ee", "ee", "ee", "ee", "ee", "ee", "ee", "ee"],
    ["ee", "ee", "ee", "ee", "ee", "ee", "ee", "ee"],
    ["ee", "ee", "ee", "ee", "ee", "ee", "ee", "ee"],
    ["wp", "wp", "wp", "wp", "wp", "wp", "wp", "wp"],
    ["wr", "wn", "wb", "wq", "wk", "wb", "wn", "wr"],    
    ]

from pygame.locals import (
    QUIT,
    MOUSEBUTTONDOWN
)


def init_black_pieces():
    ''' loads the black pieces to their starting positions'''
    # load black rook
    br = pygame.image.load("./Chess Pieces/Chess_br45.svg.png")
    br = pygame.transform.scale(br, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    screen.blit(br, br.get_rect()) # light square rook
    screen.blit(br, pygame.Rect(7 * SCREEN_WIDTH/8, 0, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)) # dark square rook
    
    # load black knight (n)
    bn = pygame.image.load("./Chess Pieces/Chess_bn45.svg.png")
    bn = pygame.transform.scale(bn, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    screen.blit(bn, (1 * SCREEN_WIDTH/8, 0, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)) # dark square knight
    screen.blit(bn, (6 * SCREEN_WIDTH/8, 0, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)) # light square knight
    
    # load black bishop
    bb = pygame.image.load("./Chess Pieces/Chess_bb45.svg.png")
    bb = pygame.transform.scale(bb, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    screen.blit(bb, (2 * SCREEN_WIDTH/8, 0, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)) # dark square bishop
    screen.blit(bb, (5 * SCREEN_WIDTH/8, 0, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)) # light square bishop
    
    # load black queen
    bq = pygame.image.load("./Chess Pieces/Chess_bq45.svg.png")
    bq = pygame.transform.scale(bq, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    screen.blit(bq, (3 * SCREEN_WIDTH/8, 0, SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    
    # load black king
    bk = pygame.image.load("./Chess Pieces/Chess_bk45.svg.png")
    bk = pygame.transform.scale(bk, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    screen.blit(bk, (4 * SCREEN_WIDTH/8, 0, SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    
    # load black pawns
    bp = pygame.image.load("./Chess Pieces/Chess_bp45.svg.png")
    bp = pygame.transform.scale(bp, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    for i in range(0, 8):
        screen.blit(bp, (i * SCREEN_WIDTH/8, SCREEN_HEIGHT/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8))

def init_white_pieces():
    ''' loads the white pieces to their starting positions'''
    # load white rook
    wr = pygame.image.load("./Chess Pieces/Chess_wr45.svg.png")
    wr = pygame.transform.scale(wr, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    screen.blit(wr, pygame.Rect(0, 7 * SCREEN_HEIGHT/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)) # dark square rook
    screen.blit(wr, pygame.Rect(7 * SCREEN_WIDTH/8, 7 * SCREEN_HEIGHT/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)) # light square rook
    
    # load white knight (n)
    wn = pygame.image.load("./Chess Pieces/Chess_wn45.svg.png")
    wn = pygame.transform.scale(wn, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    screen.blit(wn, pygame.Rect(1 * SCREEN_WIDTH/8, 7 * SCREEN_HEIGHT/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)) # dark square bishop
    screen.blit(wn, pygame.Rect(6 * SCREEN_WIDTH/8, 7 * SCREEN_HEIGHT/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)) # light square bishop
    
    # load white bishop
    wb = pygame.image.load("./Chess Pieces/Chess_wb45.svg.png")
    wb = pygame.transform.scale(wb, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    screen.blit(wb, pygame.Rect(2 * SCREEN_WIDTH/8, 7 * SCREEN_HEIGHT/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)) # white square knight
    screen.blit(wb, pygame.Rect(5 * SCREEN_WIDTH/8, 7 * SCREEN_HEIGHT/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)) # dark square knight
    
    # load white queen
    wq = pygame.image.load("./Chess Pieces/Chess_wq45.svg.png")
    wq = pygame.transform.scale(wq, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    screen.blit(wq, (3 * SCREEN_WIDTH/8, 7 * SCREEN_HEIGHT/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    
    # load black king
    wk = pygame.image.load("./Chess Pieces/Chess_wk45.svg.png")
    wk = pygame.transform.scale(wk, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    screen.blit(wk, (4 * SCREEN_WIDTH/8, 7 * SCREEN_HEIGHT/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    
    # load black pawns
    wp = pygame.image.load("./Chess Pieces/Chess_wp45.svg.png")
    wp = pygame.transform.scale(wp, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    for i in range(0, 8):
        screen.blit(wp, (i * SCREEN_WIDTH/8, 6 * SCREEN_HEIGHT/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8))

def init_board():
    ''' creates the initial board with pieces in their starting positions'''
    surf = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT))
    surf.fill((0, 0, 0))
    screen.blit(surf, (0, 0))
    
    # draw squares
    for i in range(0, 8):
        for j in range(0, 8):
            square = pygame.Rect(j * SCREEN_WIDTH/8, i * SCREEN_HEIGHT/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)
            if (j + i) % 2 == 0:
                pygame.draw.rect(screen, LIGHT_SQUARE, square)
            else:
                pygame.draw.rect(screen, DARK_SQUARE, square)
     
    # add pieces
    init_black_pieces()
    init_white_pieces()
    # update board before exiting
    pygame.display.flip()
    

def select_square(x, y, piece = "ee"):
    ''' selects the square located at (x, y) where x is a number which represents the file 
        and y is a number which represents the rank '''
    square = pygame.Rect(x * SCREEN_WIDTH/8, y * SCREEN_WIDTH/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)
    
    if (x + y) % 2 == 0:
        pygame.draw.rect(screen, SELECTED_LIGHT_SQUARE, square)
    else:
        pygame.draw.rect(screen, SELECTED_DARK_SQUARE, square)
        
    # add piece back if there is one
    if piece != "ee":
        piece = pygame.image.load("./Chess Pieces/Chess_" + piece + "45.svg.png")
        piece = pygame.transform.scale(piece,(SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
        screen.blit(piece, (x * SCREEN_WIDTH/8, y * SCREEN_WIDTH/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
        

    pygame.display.flip()
    

def deselect_square(x, y, piece = "ee"):
    ''' deselects te square located at (x, y) where x is a number which represents the file
        and y is a number which represents the rank '''
    square = pygame.Rect(x * SCREEN_WIDTH/8, y * SCREEN_WIDTH/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)
    
    if (x + y) % 2 == 0:
        pygame.draw.rect(screen, LIGHT_SQUARE, square)
    else:
        pygame.draw.rect(screen, DARK_SQUARE, square)
        
    # add piece back if there is one
    if piece != "ee":
        piece = pygame.image.load("./Chess Pieces/Chess_" + piece + "45.svg.png")
        piece = pygame.transform.scale(piece, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
        screen.blit(piece, (x * SCREEN_WIDTH/8, y * SCREEN_WIDTH/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
        
    pygame.display.flip()
    
    
def commit_move(src_x, src_y, dest_x, dest_y, last_move = []):
    ''' recieves a source position (src_x, src_y) and a destination position (dest_x, dest_y) which is assumed 
    to be valid input. moves the piece from source to destination. also deselects last move'''
    
    if len(last_move) != 0:
        deselect_square(last_move[0][0], last_move[0][1])
        deselect_square(last_move[1][0], last_move[1][1], board[last_move[1][1]][last_move[0][1]])
        
    src = pygame.Rect(src_x * SCREEN_WIDTH/8, src_y * SCREEN_WIDTH/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)
    
    if (src_x + src_y) % 2 == 0:
        pygame.draw.rect(screen, LIGHT_SQUARE, src)
    else:
        pygame.draw.rect(screen, DARK_SQUARE, src)
        
    
    piece = pygame.image.load("./Chess Pieces/Chess_" + board[dest_y][dest_x] + "45.svg.png")
    piece = pygame.transform.scale(piece, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    select_square(dest_x, dest_y, piece)

    # update last move
    last_move[0][0] = src_x
    last_move[0][1] = src_y
    last_move[1][0] = dest_x
    last_move[1][1] = dest_y
    return last_move    

    
def assign_check(x, y, king):
    ''' places the king piece which is descirbed by 'king' and is at location (x, y) into check (highlighted) ''' 
    check_color = (5,195,221)
    
    square = pygame.Rect(x * SCREEN_WIDTH/8, y * SCREEN_WIDTH/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)
    
    if (x + y) % 2 == 0:
        pygame.draw.rect(screen, check_color, square)
    else:
        pygame.draw.rect(screen, check_color, square)
    
    
    king = pygame.image.load("./Chess Pieces/Chess_" + king + "45.svg.png")
    king = pygame.transform.scale(king, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    screen.blit(king, (x * SCREEN_WIDTH/8, y * SCREEN_WIDTH/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    
    pygame.display.flip()
    
    
def remove_check(x, y, king):
    ''' removes the check from a king piece descirbed by 'king' located at (x, y). (removes highlight) '''
    square = pygame.Rect(x * SCREEN_WIDTH/8, y * SCREEN_WIDTH/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8)
    
    if (x + y) % 2 == 0:
        pygame.draw.rect(screen, LIGHT_SQUARE, square)
    else:
        pygame.draw.rect(screen, DARK_SQUARE, square)
    
    
    king = pygame.image.load("./Chess Pieces/Chess_" + king + "45.svg.png")
    king = pygame.transform.scale(king, (SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    screen.blit(king, (x * SCREEN_WIDTH/8, y * SCREEN_WIDTH/8, SCREEN_WIDTH/8, SCREEN_HEIGHT/8))
    
    pygame.display.flip()


def display_checkmate(winner):
    
    background = pygame.Surface((SCREEN_WIDTH/2 + SCREEN_WIDTH/8, SCREEN_HEIGHT/2 + SCREEN_HEIGHT/8))
    background.set_alpha(12)
    background.fill((0, 192, 163))
    screen.blit(background, (SCREEN_WIDTH/4 - SCREEN_WIDTH/16, SCREEN_HEIGHT/4 - SCREEN_HEIGHT/16))
    
    winner_text = pygame.font.SysFont('Comic Sans MS', 172)
    winner_text_surface = winner_text.render(winner + " Wins!", True, (0, 0, 0))
    screen.blit(winner_text_surface, (SCREEN_WIDTH/4, SCREEN_HEIGHT/4 + SCREEN_HEIGHT/64))
    
    # add a play again button
    play_again_text = pygame.font.SysFont('Comic Sans MS', 172)
    play_again_text_surface = play_again_text.render("Play Again!", True, (0, 0, 0))
    screen.blit(play_again_text_surface, (SCREEN_WIDTH/4 + SCREEN_WIDTH/24, SCREEN_HEIGHT/4 + SCREEN_HEIGHT/5.5))
    
    # add a quit button
    exit_text = pygame.font.SysFont('Comic Sans MS', 172)
    exit_text_surface = exit_text.render("Quit", True, (0, 0, 0))
    screen.blit(exit_text_surface, (SCREEN_WIDTH/4 + SCREEN_WIDTH/7, SCREEN_HEIGHT/1.65))
    
    pygame.display.flip()
    
    

# begin game
pygame.init() # screen global so all methods can access it
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT)) # Create the screen object
pygame.display.set_caption("Chess")
init_board()

# gamestate loop control variables
running = True
white = True # true indicates that it is white's turn
gameover = False
last_click = (-1, -1)

# gamestate
while running:

    for event in pygame.event.get():
        if event.type == QUIT:
            running = False
            
        elif event.type == MOUSEBUTTONDOWN:
            move = pygame.mouse.get_pos()
            xpos = floor(move[0] / (SCREEN_WIDTH/8))
            ypos = floor(move[1] / (SCREEN_HEIGHT/8))
            
            # check if the same piece was clicked
            if xpos == last_click[0] and ypos == last_click[1]:
                deselect_square(xpos, ypos, board[ypos][xpos])
                last_click = (-1, -1)
                continue
        
            # a piece was clicked; highlight it
            if board[ypos][xpos] != "ee":
                if last_click[0] != -1: #previous click was on a piece, send move for validation
                    move_to_send = str(chr(last_click[0] + 97)) + str(8 - last_click[1]) + " " + str(chr(xpos + 97)) + str(8 - ypos)
                    print(move_to_send)
                    # if valid move
                        # commit_move(last_click[0], last_click[1], xpos, ypos, ?)
                        # white = not white
                        # check for in check
                            # if mate gameover = True
                        # last_click = (-1, -1)
                last_click = (xpos, ypos)
                        
                select_square(xpos, ypos, board[ypos][xpos])
            
        pygame.display.flip()
        
    if (gameover):
        display_checkmate("White")
        # while True:
            # if user clicks quit button
                # running = False
                # break
            # elif they click play again
                #  init_board()
            # else
                # stay in this while loop until they do something
        
            
            
            
            
pygame.quit()


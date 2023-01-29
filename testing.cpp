#include "templates.cpp"
#include <fstream>

using std::cin, std::cout, std::endl, std::get;

class Game {

    ChessBoard cb;
    
    bool turn;

    public:

    Game(): cb(), turn(true) {cb.printBoard();}

    ChessSpace& selectPiece(std::ifstream& fin) {
        .
        bool color = turn;
        if(color) {
            cout << "white ";
        } else {
            cout << "black ";
        }

        std::string in;

        cout << "select piece: ";
        
        fin >> in;

        if(cb.at(in).empty) {
            cout << "empty square. ";
            return *(new ChessSpace());
            
        }

        else if(cb.at(in).piece->color != color) {
            cout << "wrong color. ";
            return selectPiece(fin);
            return *(new ChessSpace());
        }

        else {
            cout << "piece selected: ";
            cb.at(in).piece->printPiece();
            return cb.at(in);
        }
    }

    bool inCheck() {
        // check paths away from King for threatening piece.
        
        if(turn) {

            char rank = get<0>(cb.wkc);
            char file = get<1>(cb.wkc);
            char currR = rank;
            char currF = file;
            std::string pr;
            // check rank first
            // if I find a black rook or queen, return true.
    
            for(char i = file; i < 8; i++) {
                currF++;
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(pr == "♖" || pr == "♕") {
                        return true;
                    } else {
                        break;
                    }
                }
            }

            currR = rank;
            currF = file;

            for(char i = file-1; i > 0; i--) {
                currF--;
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(pr == "♖" || pr == "♕") {
                        return true;
                    } else {
                        break;
                    }
                }
            }
            // check col. Same condition as before.
            for(char i = rank; i < 8; i++) {
                currR++;
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(pr == "♖" || pr == "♕") {
                        return true;
                    } else {
                        break;
                    }
                }
            }

            currR = rank;
            currF = file;

            for(char i = rank-1; i > 0; i--) {
                currR--;
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(pr == "♖" || pr == "♕") {
                        return true;
                    } else {
                        break;
                    }
                }
            }

            currR = rank;
            currF = file;

            // check diagonals for black pawns (check direction & proximity!), bishops, queens.

            while(currR > -1 && currR < 6 && currF > -1 && currF < 6) {
                currR++; currF++; // checking top right (look for pawn on first go)
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(currR - rank == 1) {
                        if(pr == "♙") {
                            return true;
                        }
                    }
                    if(pr == "♗" || pr == "♕") {
                        return true;
                    } else {
                        break;
                    }
                }

            }

            currR = rank; currF = file;

            while(currR > -1 && currR < 6 && currF > 0 && currF < 8) {
                currR++; currF--; // checking top left (look for pawn on first go)
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(currR - rank == 1) {
                        if(pr == "♙") {
                            return true;
                        }
                    }
                    if(pr == "♗" || pr == "♕") {
                        return true;
                    } else {
                        break;
                    }
                }
            }

            currR = rank; currF = file;

            while(currR > 0 && currR < 8 && currF > -1 && currF < 6) {
                currR--; currF++; // checking bottom right 
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    
                    if(pr == "♗" || pr == "♕") {
                        return true;
                    } else {
                        break;
                    }
                }

            }

            currR = rank; currF = file;

            while(currR > 0 && currR < 8 && currF > 0 && currF < 8) {
                currR--; currF--; // checking bottom left 
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(pr == "♗" || pr == "♕") {
                        return true;
                    } else {
                        break;
                    }
                }

            }

            currR = rank; currF = file;

            // that's all the diagonals... now knight's moves.

            currR = rank+2;
            currF = file+1;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♘") {
                        return true;
                    }
                }
            }

            currR = rank+2;
            currF = file-1;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♘") {
                        return true;
                    }
                }
            }

            currR = rank-2;
            currF = file-1;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♘") {
                        return true;
                    }
                }
            }

            currR = rank-2;
            currF = file+1;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♘") {
                        return true;
                    }
                }
            }

            currR = rank+1;
            currF = file+2;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♘") {
                        return true;
                    }
                }
            }

            currR = rank+1;
            currF = file-2;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♘") {
                        return true;
                    }
                }
            }

            currR = rank-1;
            currF = file+2;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♘") {
                        return true;
                    }
                }
            }

            currR = rank-1;
            currF = file-2;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♘") {
                        return true;
                    }
                }
            }

            return false;

        } else {
            // black king
            char rank = get<0>(cb.bkc);
            char file = get<1>(cb.bkc);

            char currR = rank;
            char currF = file;
            std::string pr;
            // check rank first
            // if I find a black rook or queen, return true.
    
            for(char i = file+1; i < 8; i++) {
                currF++;
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(pr == "♜" || pr == "♛") {
                        return true;
                    } else {
                        break;
                    }
                }
            }

            currR = rank;
            currF = file;

            for(char i = file-1; i > 0; i--) {
                currF--;
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(pr == "♜" || pr == "♛") {
                        return true;
                    } else {
                        break;
                    }
                }
            }
            // check col. Same condition as before.

            currR = rank;
            currF = file;

            for(++currR; currR < 8; currR++) {
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(pr == "♜" || pr == "♛") {
                        return true;
                    } else {
                        break;
                    }
                }
            }

            currR = rank;
            currF = file;

            for(char i = rank-1; i > 0; i--) {
                currR--;
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(pr == "♜" || pr == "♛") {
                        return true;
                    } else {
                        break;
                    }
                }
            }

            currR = rank;
            currF = file;

            // check diagonals for black pawns (check direction & proximity!), bishops, queens.

            while(currR > -1 && currR < 6 && currF > -1 && currF < 6) {
                currR++; currF++; // checking top right
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    
                    if(pr == "♝" || pr == "♛") {
                        return true;
                    } else {
                        break;
                    }
                }

            }

            currR = rank; currF = file;

            while(currR > -1 && currR < 6 && currF > 0 && currF < 8) {
                currR++; currF--; // checking top left 
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    
                    if(pr == "♝" || pr == "♛") {
                        return true;
                    } else {
                        break;
                    }
                }
            }

            currR = rank; currF = file;

            while(currR > 0 && currR < 8 && currF >-1 && currF < 6) {
                currR--; currF++; // checking bottom right 
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(currF - file == 1) {
                        if(pr == "♟") {
                            return true;
                        }
                    }
                    if(pr == "♝" || pr == "♛") {
                        return true;
                    } else {
                        break;
                    }
                }

            }

            currR = rank; currF = file;

            while(currR > 0 && currR < 8 && currF > 0 && currF < 8) {
                currR--; currF--; // checking bottom left 
                if(!cb.board[currR][currF].empty) {
                    pr = cb.board[currR][currF].piece->printRep;
                    if(file - currF == 1) {
                        if(pr == "♟") {
                            return true;
                        }
                    }
                    if(pr == "♝" || pr == "♛") {
                        return true;
                    } else {
                        break;
                    }
                }

            }

            // that's all the diagonals... now knight's moves.

            currR = rank+2;
            currF = file+1;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♞") {
                        return true;
                    }
                }
            }

            currR = rank+2;
            currF = file-1;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♞") {
                        return true;
                    }
                }
            }

            currR = rank-2;
            currF = file-1;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♞") {
                        return true;
                    }
                }
            }

            currR = rank-2;
            currF = file+1;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♞") {
                        return true;
                    }
                }
            }

            currR = rank+1;
            currF = file+2;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♞") {
                        return true;
                    }
                }
            }

            currR = rank+1;
            currF = file-2;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♞") {
                        return true;
                    }
                }
            }

            currR = rank-1;
            currF = file+2;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♞") {
                        return true;
                    }
                }
            }

            currR = rank-1;
            currF = file-2;
            if(currR > -1 && currR < 8 && currF > -1 && currF < 8) {
                if(!cb.board[currR][currF].empty) {
                    if(cb.board[currR][currF].piece->printRep == "♞") {
                        return true;
                    }
                }
            }
        }
        
        
        return false;
    }

    bool movingIntoCheck(ChessSpace& cs, std::pair<char, char> dest) {
        char backupR = cs.piece->rank;
        char backupF = cs.piece->file;

        bool needReplacePiece = false;
        
        ChessPiece* backupP = nullptr;
        if(!cb.board[get<0>(dest)][get<1>(dest)].empty) {
            ChessPiece* piece = cb.board[get<0>(dest)][get<1>(dest)].piece;
            
           if((piece->outstring()[1] == 'p')) {
                backupP = new Pawn(piece->file, piece->rank, piece->color);
           }
           else if((piece->outstring()[1] == 'q')) {
                backupP = new Queen(piece->file, piece->rank, piece->color);
           }
           else if((piece->outstring()[1] == 'r')) {
                backupP = new Rook(piece->file, piece->rank, piece->color);
           }
           else if((piece->outstring()[1] == 'k')) {
                backupP = new King(piece->file, piece->rank, piece->color);
           }
           else if((piece->outstring()[1] == 'b')) {
                backupP = new Bishop(piece->file, piece->rank, piece->color);
           }
           else if((piece->outstring()[1] == 'n')) {
                backupP = new Knight(piece->file, piece->rank, piece->color);
           }
           needReplacePiece = true;
        } 

        cb.movePiece(cs, dest);
        
        //cout << "checking if moving into check: ";
        bool ret = inCheck();  // if the altered board presents check, remember that
        // and reinstate the former board.
        //cout << std::boolalpha << ret << endl;

        cb.movePiece(cb.board[get<0>(dest)][get<1>(dest)], {backupR, backupF});
        if(needReplacePiece) {
            cb.board[get<0>(dest)][get<1>(dest)].empty = false;
            cb.board[get<0>(dest)][get<1>(dest)].piece = backupP;
            cb.replace(backupP);
        }

        return ret;
    }

    bool movingThroughPiece(ChessSpace& cs, std::pair<char,char> p) {
        char file = cs.piece->file;
        char rank = cs.piece->rank;

        std::string pr = cs.piece->printRep;
        if(pr == "♞" || pr == "♘" || pr == "♚" || pr == "♔") {
            return false;
        }

        char currF = file;
        char currR = rank;

        char endF = get<1>(p);
        char endR = get<0>(p);

        for(size_t i = 0; i < std::max(abs(cs.piece->rank - get<0>(p))-1, abs(cs.piece->file - get<1>(p))-1); i++) {
            if(currF < endF) {
                currF++;
            } else if(currF > endF) {
                currF--;
            }
            if(currR > endR) {
                currR--;
            } else if(currR < endR) {
                currR++;
            }

            if(!cb.board[currR][currF].empty) {
                return true;
            }
        }

        return false;

    }

    std::pair<char,char> selectDest(ChessSpace& cs, std::ifstream& fin) {
        std::string in;
        std::cout << "move to: ";
        fin >> in;

        if(in == "FUCK") {
            move();
        }

        if(cs.piece->isValidMove(std::get<1>(asCoords(in)), std::get<0>(asCoords(in)))) {
            if(cb.at(in).empty) {
                if(movingIntoCheck(cs, asCoords(in))) {
                    cout << "you would be moving into check." << endl;
                    return {-1,-1};
                    //return selectDest(cs, fin);
                }
                
                if(movingThroughPiece(cs, asCoords(in))) {
                    cout << "you can't move through other pieces." << endl;
                    return {-1,-1};
                    //return selectDest(cs, fin);
                }

                if(cs.piece->printRep == "♙" || cs.piece->printRep == "♟") {
                    if(std::get<1>(asCoords(in)) != cs.piece->file) {
                        cout << "pawns only attack diagonally." << endl;
                        return {-1,-1};
                        //return selectDest(cs, fin);
                    }

                    if(std::get<0>(asCoords(in)) == 7) {
                        // pawn promotion at rank 8
                        cout << "promote pawn to (n, b, r, q): ";
                        
                        char choice;
                        fin >> choice;
                        char rank = cs.piece->rank;
                        char file = cs.piece->file;
                        bool color = turn;

                        if(turn) {
                            cb.whitePieces.erase(cs.piece);
                        } else {
                            cb.blackPieces.erase(cs.piece);
                        }

                        delete cs.piece;
                        switch(choice) {
                            case 'n':
                                cs.piece = new Knight(file, rank, color);
                                break;
                            case 'b':
                                cs.piece = new Bishop(file, rank, color);
                                break;
                            case 'r':
                                cs.piece = new Rook(file, rank, color);
                                break;
                            case 'q':
                                cs.piece = new Queen(file, rank, color);
                                break;
                            default:
                                cout << "uhmm... ok?" << endl;
                                cs.piece = new Pawn(file, rank, color);
                        }


                        if(turn) {
                            cb.whitePieces.insert(cs.piece);
                        } else {
                            cb.blackPieces.insert(cs.piece);
                        }

                    }
                }

                return asCoords(in);
            } else if(cb.at(in).piece->color != turn) {
                if(movingThroughPiece(cs, asCoords(in))) {
                    cout << "you can't move through other pieces." << endl;
                    return {-1,-1};
                    //return selectDest(cs, fin);
                }
                if(movingIntoCheck(cs, asCoords(in))) {
                    cout << "you would be moving into check." << endl;
                    return {-1,-1};
                    //return selectDest(cs, fin);
                }
                return asCoords(in);
            } else {
                std::cout << "you can't capture your own piece." << std::endl;
                return {-1,-1};
                    //return selectDest(cs, fin);
            } 
        } else {
            std::cout << "invalid move. ";
            return {-1,-1};
            //return selectDest(cs, fin);
        }
    }

    bool inCheckMate() {

        if(turn) {
            // White King
            
            for(ChessPiece* cp : cb.whitePieces) {
                // try all valid moves.
                ChessSpace& cs = cb.board[cp->rank][cp->file];
                std::list<std::pair<char,char>> moves = cp->allValidMoves();
                

                for(std::pair<char,char> dest : moves) {
                    ChessSpace& csDest = cb.board[std::get<0>(dest)][std::get<1>(dest)];

                    if(!csDest.empty) {
                        if(csDest.piece->color) {
                            continue;
                        }
                    }

                    if(!movingThroughPiece(cs, dest)) {
                        if(!movingIntoCheck(cs, dest)) {
                            return false;
                        }
                    }
                }
            }

        } else {
            // Black King

            for(ChessPiece* cp : cb.blackPieces) {
                // try all valid moves.
                ChessSpace& cs = cb.board[cp->rank][cp->file];
                std::list<std::pair<char,char>> moves = cp->allValidMoves();
                
                // std::cout << cp->printRep << endl;
                for(std::pair<char,char> dest : moves) {
                    
                    ChessSpace& csDest = cb.board[std::get<0>(dest)][std::get<1>(dest)];

                    if(!csDest.empty) {
                        if(!csDest.piece->color) {
                            continue;
                        }
                    }
                    if(!movingThroughPiece(cs, dest)) {
                        if(!movingIntoCheck(cs, dest)) {
                            
                            return false;
                        
                        }
                    }
                }
            }
        }

        return true;

    }

    void move() {
        
        while(true) {
            
            if(inCheck()) {
                cout << "CHECK." << endl;
                if(inCheckMate()) {
                    if(turn) {
                        cout << "CHECKMATE. BLACK WINS." << endl;
                    } else {
                        cout << "CHECKMATE. WHITE WINS." << endl;
                    }
                    std::ofstream fout("board.out");
                    cb.printBoard();
                    fout << "CHECKMATE" << endl;
                    cb.printBoardAsOutput(fout);
                    fout.close();
                    rename("board.out", "board.txt");
                    break;
                } else {
                    std::ofstream fout("board.out");
                    cb.printBoard();
                    fout << "CHECK " << turn << endl;
                    cb.printBoardAsOutput(fout);
                    fout.close();
                    rename("board.out", "board.txt");
                    turn = !turn;
                    continue;
                }
            } else {
                if(inCheckMate()) {
                    if(turn) {
                        cout << "STALEMATE. BLACK WINS." << endl;
                    } else {
                        cout << "STALEMATE. WHITE WINS." << endl;
                    }
                    std::ofstream fout("board.out");
                    fout << "STALEMATE" << endl;
                    cb.printBoardAsOutput(fout);
                    fout.close();
                    rename("board.out", "board.txt");
                    break;
                }
            }

            std::ifstream fin("move.txt");
            while(!fin.good()) {
                fin.open("move.txt");
            }

            ChessSpace& cs = selectPiece(fin);
            if(cs.piece == nullptr) {
                std::ofstream fout("board.out");
                fout << "bad " << turn << endl;
                cb.printBoardAsOutput(fout);
                std::remove("move.txt");
                fout.close();
                rename("board.out", "board.txt");
                continue;
            }
            std::pair<char,char> dest = selectDest(cs, fin);


            std::ofstream fout("board.out");
            if(get<0>(dest) == -1 && get<1>(dest) == -1) {
                fout << "bad " << turn << endl;
                cb.printBoardAsOutput(fout);
                std::remove("move.txt");
                fout.close();
                rename("board.out", "board.txt");
                continue;
            } else {
                cb.movePiece(cs, dest);
                cb.printBoard();
                fout << "good " << !turn << endl;
                cb.printBoardAsOutput(fout);
            }
            fout.close();
            rename("board.out", "board.txt");

            turn = !turn;
            std::remove("move.txt");
        }

    } 

};

int main() {

    Game g;
    g.move();

    return 0;
}
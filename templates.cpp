#include <iostream>

struct ChessPiece {
    public:
        char file;
        char rank;
        std::string printRep;
        bool color;
        virtual bool isValidMove(char pF, char pR) {return false;}
        virtual void printPiece() {
            if(color) {
                std::cout << "WHITE ";
            } else {
                std::cout << "BLACK ";
            }
        }
};

/*
    REMINDER
    I need to update all isValidMove functions to check for moving into check.
    I need to update all isValidMove functions (except Knight, King) to check for moving through pieces.
    I need to make Castling a valid move.
    I need to make En Passant a valid move.
    Need to make pawn promotions
    Check for capture on pawn move (changes move type).

*/

struct King : public ChessPiece {

    King(char f, char r, bool c) {
        this->file = f; this->rank = r; this->color = c; 
        if(c) {
            this->printRep = "♚";
        } else {
            this->printRep = "♔";
        }
    }

    bool isValidMove(char pF, char pR) override {
        return (((abs(pF - file) == 1 && pR == rank)) || ((abs(pR-rank) == 1 && pF == file))) && !(pF == file && pR == rank);
        // difference in one dimension must be one square; the other dimension must match directly.
    }

    void printPiece() override {
        std::cout << "KING at square " << file << +rank << std::endl;
    }

};

struct Rook : public ChessPiece {

    Rook(char f, char r, bool c) {
        this->file = f; this->rank = r; this->color = c; 
        if(c) {
            this->printRep = "♜";
        } else {
            this->printRep = "♖";
        }
    }

    bool isValidMove(char pF, char pR) override {
        return ((pF == file) || (pR == rank)) && !(pF == file && pR == rank);
        // either file or rank must match.
    }

    void printPiece() override {
        std::cout << "ROOK at square " << file << +rank << std::endl;
    }

};

struct Bishop : public ChessPiece {

    Bishop(char f, char r, bool c) {
        this->file = f; this->rank = r; this->color = c; 
        if(c) {
            this->printRep = "♝";
        } else {
            this->printRep = "♗";
        }
    }

    bool isValidMove(char pF, char pR) {
        return (abs(pF-file) == abs (pR-rank)) && !(pF == file && pR == rank);
        // diagonals are squares such that the difference of files and ranks have the same magnitudes.
    }

    void printPiece() override {
        std::cout << "BISHOP at square " << file << +rank << std::endl;
    }

};

struct Queen : public ChessPiece {

    Queen(char f, char r, bool c) {
        this->file = f; this->rank = r; this->color = c; 
        if(c) {
            this->printRep = "♛";
        } else {
            this->printRep = "♕";
        }
    }

    bool isValidMove(char pF, char pR) {
        return ((abs(pF-file) == abs (pR-rank)) || ((pF == file) || (pR == rank))) && !(pF == file && pR == rank);
    }

    void printPiece() override {
        std::cout << "QUEEN at square " << file << +rank << std::endl;
    }

};

struct Pawn : public ChessPiece {
    // code up EN PASSANT

    Pawn(char f, char r, bool c) {
        this->file = f; this->rank = r; this->color = c; 
        if(c) {
            this->printRep = "♟";
        } else {
            this->printRep = "♙";
        }
    }

    bool isValidMove(char pF, char pR) override {
        if(color) {
            // white pawns can move two spaces on first move
            if(pF == file) {
                return ((rank == 1 && pR == 3) || (pR == rank + 1));
            } else {
                // capture check
                return false;
            }
            
            // if capturing, verify (need to ask ChessBoard)
        } else {
            // black pawn

            if(pF == file) {
                return (((rank == 7) && (pR == 5)) || (pR == rank - 1));
            } else {
                // check for capture
                return false;
            }
        }

        return false;

    }

    void printPiece() override {
        std::cout << "PAWN at square " << file << +rank << std::endl;
    }

};

struct Knight : public ChessPiece {

    Knight(char f, char r, bool c) {
        this->file = f; this->rank = r; this->color = c; 
        if(c) {
            this->printRep = "♞";
        } else {
            this->printRep = "♘";
        }
    }

    bool isValidMove(char pF, char pR) override {
        return (abs(pF - file) == 1 && abs(pR - rank) == 2) || (abs(pF - file) == 2 && abs(pR - rank) == 1);
    }

    void printPiece() override {
        std::cout << "KANIGGIT at square " << file << +rank << std::endl;
    }


};

struct ChessSpace {
    bool empty;
    ChessPiece* piece;
    ChessSpace(): empty(true), piece(nullptr) {}
    ~ChessSpace() {
        delete piece;
        piece = nullptr;
    }
};

struct ChessBoard {
    // □ ■
    ChessSpace board[8][8];

    void putPiece(std::string pType, char file, char rank, bool color) {
        ChessSpace& cpr = board[rank][file];
        delete cpr.piece; cpr.piece = nullptr; cpr.empty = false;

        if(false) {

        } 
        
        else if(pType == "pawn") {
            cpr.piece = new Pawn(file, rank, color);
        }

        else if(pType == "rook") {
            cpr.piece = new Rook(file,rank,color);
        }

        else if(pType == "bishop") {
            cpr.piece = new Bishop(file,rank,color);
        }

        else if(pType == "knight") {
            cpr.piece = new Knight(file,rank,color);
        }

        else if(pType == "queen") {
            cpr.piece = new Queen(file,rank,color);
        } 

        else if(pType == "king") {
            cpr.piece = new King(file,rank,color);
        }

        else {
            std::cout << "fuck you asshole" << std::endl;
            cpr.empty = true;
        }
    }

    ChessBoard() {
        for(size_t i = 0; i < 8; i++) {
            for(size_t j = 0; j < 8; j++) {
                board[i][j] = ChessSpace();
            }
        }

        for(size_t i = 0; i < 8; i++) {
            putPiece("pawn", i, 1, true);
            putPiece("pawn", i, 6, false);
        }

        putPiece("rook", 0,0,true);
        putPiece("rook", 7,0,true);

        putPiece("rook", 0,7,false);
        putPiece("rook", 7,7,false);

        putPiece("knight",1,0,true);
        putPiece("knight",6,0,true);

        putPiece("knight",1,7,false);
        putPiece("knight",6,7,false);

        putPiece("bishop",2,0,true);
        putPiece("bishop",5,0,true);

        putPiece("bishop",2,7,false);
        putPiece("bishop",5,7,false);

        putPiece("king",4,0,true);
        putPiece("queen",3,0,true);

        putPiece("king",4,7,false);
        putPiece("queen",3,7,false);

    }

    void printBoard() {

        for(size_t rank = 0; rank < 8; rank++) {
            std::cout << ' ';
            for(size_t file = 0; file < 8; file++) {
                if(rank > 0) {std::cout << "|_____";}
                else {std::cout << "______";}
            }
            if(rank != 0) {
                std::cout << "|" << std::endl;
            } else {
                std::cout << '_' << std::endl;
            }
            
            std::cout << 8-rank;
            for(size_t file = 0; file < 8; file++) {
                std::cout << "|";
                if(board[7-rank][file].empty) {
                    if(((8-rank)+file) % 2 == 0) {
                        std::cout << "■■■■■"; // white
                    } else {
                        std::cout << "□□□□□"; // black
                    }
                } else {
                    std::cout << "     ";
                }
                
                // if theres a piece, print its representation
            }
            std::cout << "|" << std::endl;
            std::cout << ' ';
            for(size_t file = 0; file < 8; file++) {
                std::cout << "|";
                if(board[7-rank][file].empty) {
                    if(((8-rank)+file) % 2 == 0) {
                        std::cout << "■■■■■"; // white
                    } else {
                        std::cout << "□□□□□"; // black
                    }
                } else {
                    std::cout << "  " << board[7-rank][file].piece->printRep << "  ";
                }
                
            }
            
            std::cout << "|" << std::endl;
        }
        std::cout << ' ';
        for(size_t file = 0; file < 8; file++) {
            std::cout << "|_____";
        }
        std::cout << '|' << std::endl << std::endl << std::endl;
        for(size_t file = 0; file < 8; file++) {
            std::cout << "  " << file+1 << "   ";
        }
    }

};



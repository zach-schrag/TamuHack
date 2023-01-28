#include <iostream>

struct ChessSpace {
    bool empty;
    ChessSpace(): empty(true) {}
};

struct ChessPiece : public ChessSpace {
    public:
        char file;
        char rank;
        bool color;
        virtual bool isValidMove(char pF, char pR);
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
        this->file = f; this->rank = r; this->color = c; this->empty = false;
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
        this->file = f; this->rank = r; this->color = c; this->empty = false;
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
        this->file = f; this->rank = r; this->color = c; this->empty = false;
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
        this->file = f; this->rank = r; this->color = c; this->empty = false;
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
        this->file = f; this->rank = r; this->color = c; this->empty = false;
    }

    bool isValidMove(char pF, char pR) override {
        if(color) {
            // white pawns can move two spaces on first move
            if(pF == file) {
                return ((rank == 1 && pR == 3) || (pR == rank + 1));
            } else {
                // capture check
            }
            
            // if capturing, verify (need to ask ChessBoard)
        } else {
            // black pawn

            if(pF == file) {
                return (((rank == 7) && (pR == 5)) || (pR == rank - 1));
            } else {
                // check for capture
            }
        }

    }

    void printPiece() override {
        std::cout << "PAWN at square " << file << +rank << std::endl;
    }

};

struct Knight : public ChessPiece {

    Knight(char f, char r, bool c) {
        this->file = f; this->rank = r; this->color = c; this->empty = false;
    }

    bool isValidMove(char pF, char pR) override {
        return (abs(pF - file) == 1 && abs(pR - rank) == 2) || (abs(pF - file) == 2 && abs(pR - rank) == 1);
    }

    void printPiece() override {
        std::cout << "KANIGGIT at square " << file << +rank << std::endl;
    }


};

struct ChessBoard {
    // □ ■
    ChessSpace board[8][8];

    ChessBoard() {
        for(size_t i = 0; i < 8; i++) {
            for(size_t j = 0; j < 8; j++) {
                board[i][j] = ChessSpace();
            }
        }
    }

    void printBoard() {

        for(size_t rank = 0; rank < 8; rank++) {
            for(size_t file = 0; file < 8; file++) {
                std::cout << " _____";
            }
            std::cout << std::endl;
            for(size_t file = 0; file < 8; file++) {
                std::cout << "|";
                if(board[7-rank][file].empty) {
                    if(((8-rank)+file) % 2 == 0) {
                        std::cout << "■■■■■"; // white
                    } else {
                        std::cout << "□□□□□"; // black
                    }
                } else {
                    std::cout << "piece";
                }
                
                // if theres a piece, print its representation
            }
            std::cout << "|" << std::endl;
            for(size_t file = 0; file < 8; file++) {
                std::cout << "|";
                if(board[7-rank][file].empty) {
                    if(((8-rank)+file) % 2 == 0) {
                        std::cout << "■■■■■";
                    } else {
                        std::cout << "□□□□□";
                    }
                } else {
                    std::cout << "piece";
                }
                
            }
            
            std::cout << "|" << std::endl;
        }
        for(size_t file = 0; file < 8; file++) {
            std::cout << " _____";
        }
        std::cout << std::endl << std::endl << std::endl;

    }

};



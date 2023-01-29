#include <iostream>
#include <set>
#include <list>
#include <fstream>

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
        virtual std::list<std::pair<char,char>> allValidMoves() {
            return std::list<std::pair<char,char>>();
        }
        virtual std::string outstring() {return "";}
};

/*
    REMINDER
    
    I need to make Castling a valid move.
    I need to make En Passant a valid move.
    Need to implement stalemate rules

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
        return (abs(pF - file) <= 1) && (abs(pR-rank) <= 1) && !(pF == file && pR == rank);
    }

    void printPiece() override {
        std::cout << "KING at square " << char(file+'a') << int(1+rank) << std::endl;
    }

    std::list<std::pair<char,char>> allValidMoves() override {
        
        std::list<std::pair<char,char>> ret;

        if(rank+1 < 8) {

            if(file-1 > -1) {
                ret.push_back({rank+1, file-1});
            }

            ret.push_back({rank+1, file});

            if(file+1 < 8) {
                ret.push_back({rank+1, file+1});
            }

        }

        if(file-1 > -1) {
            ret.push_back({rank, file-1});
        }

        if(file+1 < 8) {
            ret.push_back({rank, file+1});
        }

        if(rank-1 > -1) {
            
            if(file-1 > -1) {
                ret.push_back({rank-1, file-1});
            }

            ret.push_back({rank-1, file});

            if(file+1 < 8) {
                ret.push_back({rank-1, file+1});
            }

        }

        return ret;

    } 

    std::string outstring() override {
        char ans[3]; ans[2] = '\0';
        if(color) {
            ans[0] = 'w';
        } else {
            ans[0] = 'b';
        }
        ans[1] = 'k';
        return ans;
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
        std::cout << "ROOK at square " << char(file+'a') << int(1+rank) << std::endl;
    }

    std::list<std::pair<char,char>> allValidMoves() override {
        
        std::list<std::pair<char,char>> ret;

        // right, left, up, down

        for(char i = file+1; i < 8; i++) {
            ret.push_back({rank, i});
        }

        for(char i = file-1; i < -1; i--) {
            ret.push_back({rank, i});
        }

        for(char i = rank+1; i < 8; i++) {
            ret.push_back({i,file});
        }

        for(char i = rank-1; i > -1; i--) {
            ret.push_back({i, file});
        }

        return ret;

    }

    std::string outstring() override {
        char ans[3]; ans[2] = '\0';
        if(color) {
            ans[0] = 'w';
        } else {
            ans[0] = 'b';
        }
        ans[1] = 'r';
        return ans;
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
        std::cout << "BISHOP at square " << char(file+'a') << int(1+rank) << std::endl;
    }

    std::list<std::pair<char,char>> allValidMoves() override {
        std::list<std::pair<char,char>> ret;
        // diag up right, diag up left, diag down right, diag down left

        char currR = rank+1; char currF = file+1;
        while(currR < 8 && currF < 8) {
            ret.push_back({currR++, currF++});
        }

        currR = rank+1; currF = file-1;
        while(currR < 8 && currF > -1) {
            ret.push_back({currR++, currF--});
        }

        currR = rank-1; currF = file+1;
        while(currR > -1 && currF < 8) {
            ret.push_back({currR--, currF++});
        }

        currR = rank-1; currF = file-1;
        while(currR > -1 && currF > -1) {
            ret.push_back({currR--, currF--});
        }

        return ret;

    }

    std::string outstring() override {
        char ans[3]; ans[2] = '\0';
        if(color) {
            ans[0] = 'w';
        } else {
            ans[0] = 'b';
        }
        ans[1] = 'b';
        return ans;
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
        std::cout << "QUEEN at square " << char(file+'a') << int(1+rank) << std::endl;
    }

    std::list<std::pair<char,char>> allValidMoves() override {

        std::list<std::pair<char,char>> ret;
        for(char i = file+1; i < 8; i++) {
            ret.push_back({rank, i});
        }

        for(char i = file-1; i < -1; i--) {
            ret.push_back({rank, i});
        }

        for(char i = rank+1; i < 8; i++) {
            ret.push_back({i,file});
        }

        for(char i = rank-1; i > -1; i--) {
            ret.push_back({i, file});
        }

        ///////////////////////////////////

        char currR = rank+1; char currF = file+1;
        while(currR < 8 && currF < 8) {
            ret.push_back({currR++, currF++});
        }

        currR = rank+1; currF = file-1;
        while(currR < 8 && currF > -1) {
            ret.push_back({currR++, currF--});
        }

        currR = rank-1; currF = file+1;
        while(currR > -1 && currF < 8) {
            ret.push_back({currR--, currF++});
        }

        currR = rank-1; currF = file-1;
        while(currR > -1 && currF > -1) {
            ret.push_back({currR--, currF--});
        }

        return ret;

    }

    std::string outstring() override {
        char ans[3]; ans[2] = '\0';
        if(color) {
            ans[0] = 'w';
        } else {
            ans[0] = 'b';
        }
        ans[1] = 'q';
        return ans;
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
                if((abs(pF - file) == 1) && (pR == rank+1)) {
                    return true;
                }

                return false;
            }
            
            // if capturing, verify (need to ask ChessBoard)
        } else {
            // black pawn

            if(pF == file) {
                return (((rank == 6) && (pR == 4)) || (pR == rank - 1));
            } else {
                // check for capture
                if((abs(pF - file) == 1) && (pR == rank-1)) {
                    return true;
                }
                return false;
            }
        }

        return false;

    }

    void printPiece() override {
        std::cout << "PAWN at square " << char(file+'a') << int(1+rank) << std::endl;
    }

    std::list<std::pair<char,char>> allValidMoves() override {
        std::list<std::pair<char,char>> ret;

        if(color) {
            ret.push_back({rank+1, file});
            if(rank == 1) {
                ret.push_back({rank+2,file});
            }
        } else {
            ret.push_back({rank-1, file});
            if(rank == 6) {
                ret.push_back({rank-2,file});
            }
        }

        return ret;

    }

    std::string outstring() override {
        char ans[3]; ans[2] = '\0';
        if(color) {
            ans[0] = 'w';
        } else {
            ans[0] = 'b';
        }
        ans[1] = 'p';
        return ans;
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
        std::cout << "KANIGGIT at square " << char(file+'a') << int(1+rank) << std::endl;
    }

    std::list<std::pair<char,char>> allValidMoves() override {

        std::list<std::pair<char,char>> ret;

        if(rank+2 < 8 && file+1 < 8) {
            ret.push_back({rank+2, file+1});
        } 
        if(rank+1 < 8 && file+2 < 8) {
            ret.push_back({rank+1, file+2});
        }
        if(rank-2 > -1 && file+1 < 8) {
            ret.push_back({rank-2, file+1});
        }
        if(rank+1 < 8 && file-2 > -1) {
            ret.push_back({rank+1, file-2});
        }
        if(rank-1 > -1 && file+2 < 8) {
            ret.push_back({rank-1, file+2});
        }
        if(rank+2 < 8 && file-1 > -1) {
            ret.push_back({rank+2, file-1});
        }
        if(rank-1 > -1 && file-2 > -1) {
            ret.push_back({rank-1, file-2});
        }
        if(rank-2 > -1 && file-1 > -1) {
            ret.push_back({rank-2, file-1});
        }

        return ret;

    }

    std::string outstring() override {
        char ans[3]; ans[2] = '\0';
        if(color) {
            ans[0] = 'w';
        } else {
            ans[0] = 'b';
        }
        ans[1] = 'n';
        return ans;
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

std::pair<char,char> asCoords(std::string str) {
    return {(str.at(1)-'1'),(str.at(0)-'a')};
}

struct ChessBoard {
    // □ ■
    ChessSpace board[8][8];
    std::pair<char, char> wkc; // white King coordinates
    std::pair<char, char> bkc; // black King coordinates

    std::set<ChessPiece*> whitePieces;
    std::set<ChessPiece*> blackPieces;

    ChessSpace& at(std::string coord) {
        return board[(coord.at(1)-'1')][coord.at(0)-'a'];
    }

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

        if(color == true) {
            whitePieces.insert(cpr.piece);
        } else {
            blackPieces.insert(cpr.piece);
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

        wkc = {0,4}; bkc = {7,4};

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
            
            std::cout << ' ';
            for(size_t file = 0; file < 8; file++) {
                std::cout << "|";
                if(((8-rank)+file) % 2 == 0) {
                    std::cout << "■■■■■"; // white
                } else {
                    std::cout << "□□□□□"; // black
                }
                
                // if theres a piece, print its representation
            }
            std::cout << "|" << std::endl;
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
                    if(((8-rank)+file) % 2 == 0) {
                        std::cout << "■ "; // white
                    } else {
                        std::cout << "□ "; // black
                    }
                    std::cout << board[7-rank][file].piece->printRep;
                    if(((8-rank)+file) % 2 == 0) {
                        std::cout << " ■"; // white
                    } else {
                        std::cout << " □"; // black
                    }
                }
                
                
            }
            
            std::cout << "|" << std::endl;
        }
        std::cout << ' ';
        for(size_t file = 0; file < 8; file++) {
            std::cout << "|_____";
        }
        std::cout << '|' << std::endl;
        for(char file = 'a'; file < 'a'+8; file++) {
            std::cout << "    " << file << " ";
        }
        std::cout << std::endl << std::endl;
    }

    void movePiece(ChessSpace& source, std::pair<char,char> destP) {
        ChessPiece* temp = source.piece;
        source.empty = true;
        source.piece = nullptr;
        ChessSpace& dest = board[std::get<0>(destP)][std::get<1>(destP)];
        if(!dest.empty) {
            if(dest.piece->color) {
                whitePieces.erase(dest.piece);
            } else {
                blackPieces.erase(dest.piece);
            }
        }
        delete dest.piece;
        dest.piece = temp;
        dest.empty = false;
        dest.piece->rank = std::get<0>(destP);
        dest.piece->file = std::get<1>(destP);

        if(dest.piece->printRep ==  "♚") {
            wkc = destP;
        } else if(dest.piece->printRep == "♔") {
            bkc = destP;
        }
    }

    void replace(ChessPiece* pointy) {
        if(pointy->color) {
            whitePieces.insert(pointy);
        } else {
            blackPieces.insert(pointy);
        }
    }

    void printBoardAsOutput(std::ofstream& fout) {

        for(char rank = 7; rank > -1; rank--) {
            for(char file = 0; file < 8; file++) {

                if(board[rank][file].empty) {
                    fout << "ee ";
                } else {
                    fout << board[rank][file].piece->outstring() << ' ';
                }
                
            }
            fout << std::endl;
        }

    }

};


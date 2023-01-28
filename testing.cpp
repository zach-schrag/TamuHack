#include "templates.cpp"

using std::cin, std::cout, std::endl;

void testingChessBoard() {

    ChessBoard cb;

    cb.printBoard();

    bool turn = true;

    while(true) {

        if(turn) {

            cout << "white select piece: ";
            


        } else {

        }
        turn = !turn;
    }

}

int main() {

    testingChessBoard();

    return 0;
}
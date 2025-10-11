#include <iostream>
using namespace std;

// ---------- Clase Pieza Base
class Piece {
public:
    virtual bool checkMove(const string& from, const string& to) = 0;
    virtual ~Piece() {}
};

// --------------- Clase Man
class Man : public Piece {
public:
    bool checkMove(const string& from, const string& to) override {
        int fromCol = from[0] - 'a' + 1;
        int fromRow = from[1] - '0';
        int toCol = to[0] - 'a' + 1;
        int toRow = to[1] - '0';

        int colDiff = toCol - fromCol;
        if (colDiff < 0) { colDiff *= (-1); }

        int rowDiff = toRow - fromRow;
        if (rowDiff < 0) { rowDiff *= (-1); }

        // Chequeo de distancia (solo puede moverse una casilla)
        if (colDiff == 1 && rowDiff == 1) {
            return true;
        }
        else {
            return false;
        }
    }
};

// ------------ Clase King

class King : public Piece
{
public:
    bool checkMove(const string& from, const string& to) override {
        int fromCol = from[0] - 'a' + 1;
        int fromRow = from[1] - '0';
        int toCol = to[0] - 'a' + 1;
        int toRow = to[1] - '0';

        int colDiff = (toCol - fromCol);
        if (colDiff < 0) { colDiff *= (-1); }

        int rowDiff = abs(toRow - fromRow);
        if (rowDiff < 0) { rowDiff *= (-1); }

        //Chequeo de distancia (mas permisivo por ser un rey)
        if (colDiff == rowDiff && colDiff > 0) {
            return true;
        }
        else {
            return false;
        }
    }
};

int main() {
    Man man;
    King king;

    if (man.checkMove("b1", "c2"))
    {
        cout << "Man: b1 -> c2 es un movimiento valido" << endl;
    }
    else {
        cout << "Man: b1 -> c2 NO es valido" << endl;
    }

    if (king.checkMove("b1", "d3"))
    {
        cout << "King: b1 -> d3 es un movimiento valido" << endl;
    }
    else {
        cout << "King: b1 -> d3 NO es valido" << endl;
    }

    if (man.checkMove("b1", "d3"))
    {
        cout << "Man: b1 -> d3 es un movimiento valido" << endl;
    }
    else {
        cout << "Man: b1 -> d3 NO es valido" << endl;
    }

    return 0;
}
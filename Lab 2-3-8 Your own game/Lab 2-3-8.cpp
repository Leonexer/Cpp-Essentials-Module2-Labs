#include <iostream>
#include <string>

// ---------- Clase Board ----------

class Board {
private:
    char grid[3][3];

public:
    Board()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                grid[i][j] = ' ';

            }
        }
    }

    void print() {
        std::cout << "\n";
        for (int i = 0; i < 3; i++)
        {
            std::cout << " ";
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')                 // Si esta vacio, muestra el numero de la casilla
                    std::cout << ((3 * i) + j + 1);
                else
                    std::cout << grid[i][j];            //Sino muestra el simbolo almacenado

                if (j < 2) std::cout << " | ";          //Separaciones verticales
            }

            std::cout << "\n";

            if (i < 2)
            {
                std::cout << "---+---+---\n";    //Separaciones horizontales
            }
        }
        std::cout << "\n";
    }

    bool placeMark(int row, int col, char symbol)
    {
        if (row < 0 || row > 2 || col < 0 || col > 2) //Limites de input
        {
            return false;
        }

        if (grid[row][col] != ' ') // No se puede sobreescribir una marca (ni siquiera del mismo jugador)
        {
            return false;
        }

        grid[row][col] = symbol;
        return true;
    }

    bool isFull()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool checkWin(char symbol)
    {
        // Filas y columnas
        for (int i = 0; i < 3; i++)
        {
            if (grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol)
            {
                return true;
            }
            if (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol)
            {
                return true;
            }
        }
        // Diagonales
        if (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol)
        {
            return true;
        }

        if (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol)
        {
            return true;
        }

        return false;
    }
};

// -------------------- Clase Player --------------------
class Player {
private:
    std::string name;
    char symbol;

public:
    Player(std::string n = "", char s = 'X') {
        name = n;
        symbol = s;
    }

    std::string getName() { return name; }
    char getSymbol() { return symbol; }
};

// -------------------- Clase Game --------------------
class Game {
private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;

public:
    Game(std::string name1, std::string name2) : player1(name1, 'X'), player2(name2, 'O')
    {
        currentPlayer = &player1;
    }

    void switchTurn()
    {
        if (currentPlayer == &player1)
        {
            currentPlayer = &player2;
        }
        else
        {
            currentPlayer = &player1;
        }
    }

    void play()
    {
        int move;

        while (true)
        {
            board.print();
            std::cout << currentPlayer->getName() << " (" << currentPlayer->getSymbol() << "), elige una casilla (1-9): ";
            std::cin >> move;

            int row = (move - 1) / 3;       //Convierte el movimiento a coordenadas del tablero
            int col = (move - 1) % 3;

            if (!board.placeMark(row, col, currentPlayer->getSymbol()))
            {
                std::cout << "Movimiento invalido. Intenta de nuevo." << std::endl;
                continue;
            }

            if (board.checkWin(currentPlayer->getSymbol()))
            {
                board.print();
                std::cout << currentPlayer->getName() << " ha ganado!" << std::endl;
                break;
            }

            if (board.isFull())
            {
                board.print();
                std::cout << "Empate." << std::endl;
                break;
            }

            switchTurn();
        }
    }
};

// -------------------- Funcion principal --------------------
int main() {
    std::string n1, n2;

    std::cout << "=== Tic Tac Toe ===" << std::endl;
    std::cout << "Nombre del jugador 1 (X): ";
    std::cin >> n1;
    std::cout << "Nombre del jugador 2 (O): ";
    std::cin >> n2;

    Game partida(n1, n2);
    partida.play();

    return 0;
}
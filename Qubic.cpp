/**
 * Qubic : 3D Tic-Tac-Toe Game
 * GHorned
 * 
 * This program creates an interface for 3D tic tac toe (4x4x4)
 * and implements an AI bot for the user to play against
 */


#include <iostream>
#include <ctime>
#include <cmath>


char cube[4][4][4] = {};
char ai = 'X';
char human = 'O';
char player;


// Prints out a visual representation of the game's cube
void display() {
    for (int i = 0; i < 4; i++) {
        std::cout << "          ________________\n         /";
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                std::cout << " " << cube[i][j][k] << " /";
            }
            switch (j) {
            case 0:
                std::cout << "\n        /___/___/___/___/\n       /";
                break;
            case 1:
                std::cout << "\n      /___/___/___/___/\n     /";
                break;
            case 2:
                std::cout << "\n    /___/___/___/___/\n   /";
                break;
            case 3:
                std::cout << "\n  /___/___/___/___/\n\n";
                break;
            }
        }
    }
    std::cout << "----------------------------" << std::endl;
}

// Prepares the cube for a new game by setting each position to empty
void reset() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                cube[i][j][k] = ' ';
            }
        }
    }
}

// Returns true if all positions in the cube have been taken
bool full() {
    bool full = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (cube[i][j][k] == ' ') {
                    full = false;
                }
            }
        }
    }
    return full;
}

// A simulated coin flip deciding which player goes first
void first() {
    srand(time(NULL)); // Time seed for random number generator
    if (rand() % 2 == 0) {
        player = ai;
    } else {
        player = human;
    }
}

// Updates the current player
void turn() {
    if (player == human) {
        player = ai;
    } else {
        player = human;
    }
}

// Provides an interface for the user to take their turn
void humanMove() {
    int layer;
    int row;
    int column;
    bool valid = false;

    // Continues to prompt the player until a valid selection is made
    while (!valid) {

        // Player chooses a layer
        std::cout << "Layer: ";
        std::cin >> layer;
        if (std::cin.fail() || layer > 3 || layer < 0) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cerr << "Invalid input : Try again" << std::endl;
        } else {

            // Player chooses a row
            std::cout << "Row: ";
            std::cin >> row;
            if (std::cin.fail() || row > 3 || row < 0) {
                std::cin.clear();
                std::cin.ignore(100, '\n');
                std::cerr << "Invalid input : Try again" << std::endl;
            } else {

                // Player chooses a column
                std::cout << "Column: ";
                std::cin >> column;
                if (std::cin.fail() || column > 3 || column < 0) {
                    std::cin.clear();
                    std::cin.ignore(100, '\n');
                    std::cerr << "Invalid input : Try again" << std::endl;
                } else {

                    // Checks if the chosen position has already been taken
                    if (cube[layer][row][column] != ' ') {
                        std::cin.clear();
                        std::cin.ignore(100, '\n');
                        std::cerr << "Invalid input : Try again" << std::endl;
                    } else {

                        // A valid choice was made and the player's marker is placed
                        cube[layer][row][column] = player;
                        valid = true;
                    }
                }
            }
        }
    }
}

// Returns true if the game has been won by either player
bool win() {

    // Checks vertical and horizontal lines for winning combination
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            if (cube[i][j][0] == cube[i][j][1] && cube[i][j][1] == cube[i][j][2] && cube[i][j][2] == cube[i][j][3] && cube[i][j][3] != ' ') {
                return true;
            }

            if (cube[i][0][j] == cube[i][1][j] && cube[i][1][j] == cube[i][2][j] && cube[i][2][j] == cube[i][3][j] && cube[i][3][j] != ' ') {
                return true;
            }

            if (cube[0][i][j] == cube[1][i][j] && cube[1][i][j] == cube[2][i][j] && cube[2][i][j] == cube[3][i][j] && cube[3][i][j] != ' ') {
                return true;
            }
        }
    }

    // Checks diagonal lines for winning combination
    for (int i = 0; i < 4; i++) {

        if (cube[i][0][0] == cube[i][1][1] && cube[i][1][1] == cube[i][2][2] && cube[i][2][2] == cube[i][3][3] && cube[i][3][3] != ' ') {
            return true;
        }

        if (cube[i][0][3] == cube[i][1][2] && cube[i][1][2] == cube[i][2][1] && cube[i][2][1] == cube[i][3][0] && cube[i][3][0] != ' ') {
            return true;
        }

        if (cube[0][i][0] == cube[1][i][1] && cube[1][i][1] == cube[2][i][2] && cube[2][i][2] == cube[3][i][3] && cube[3][i][3] != ' ') {
            return true;
        }

        if (cube[0][i][3] == cube[1][i][2] && cube[1][i][2] == cube[2][i][1] && cube[2][i][1] == cube[3][i][0] && cube[3][i][0] != ' ') {
            return true;
        }

        if (cube[0][0][i] == cube[1][1][i] && cube[1][1][i] == cube[2][2][i] && cube[2][2][i] == cube[3][3][i] && cube[3][3][i] != ' ') {
            return true;
        }

        if (cube[0][3][i] == cube[1][2][i] && cube[1][2][i] == cube[2][1][i] && cube[2][1][i] == cube[3][0][i] && cube[3][0][i] != ' ') {
            return true;
        }
    }

    // Checks super-diagonal lines for winning combination
    if (cube[0][0][0] == cube[1][1][1] && cube[1][1][1] == cube[2][2][2] && cube[2][2][2] == cube[3][3][3] && cube[3][3][3] != ' ') {
        return true;
    }

    if (cube[3][0][0] == cube[2][1][1] && cube[2][1][1] == cube[1][2][2] && cube[1][2][2] == cube[0][3][3] && cube[0][3][3] != ' ') {
        return true;
    }

    if (cube[0][0][3] == cube[1][1][2] && cube[1][1][2] == cube[2][2][1] && cube[2][2][1] == cube[3][3][0] && cube[3][3][0] != ' ') {
        return true;
    }

    if (cube[3][0][3] == cube[2][1][2] && cube[2][1][2] == cube[1][2][1] && cube[1][2][1] == cube[0][3][0] && cube[0][3][0] != ' ') {
        return true;
    }

    return false;
}

// Provides a numerical score for the current game-state
// Used by the AI to determine most advantageouse next move
int evaluate() {
    int x = 0;
    int o = 0;
    int total = 0;

    // Scores rows
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (cube[i][j][k] == ai) {
                    x++;
                }
                if (cube[i][j][k] == human) {
                    o++;
                }
            }
            if (x > 0 && o == 0) {
                total += pow(x, 2);
            }
            if (o > 0 && x == 0) {
                total -= pow(o, 2);
            }
            x = 0, o = 0;
        }
    }

    // Scores columns
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (cube[i][k][j] == ai) {
                    x++;
                }
                if (cube[i][k][j] == human) {
                    o++;
                }
            }
            if (x > 0 && o == 0) {
                total += pow(x, 2);
            }
            if (o > 0 && x == 0) {
                total -= pow(o, 2);
            }
            x = 0, o = 0;
        }
    }

    // Scores pillars
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (cube[k][i][j] == ai) {
                    x++;
                }
                if (cube[k][i][j] == human) {
                    o++;
                }
            }
            if (x > 0 && o == 0) {
                total += pow(x, 2);
            }
            if (o > 0 && x == 0) {
                total -= pow(o, 2);
            }
            x = 0, o = 0;
        }
    }

    // Scores diagonals (by layer)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (cube[i][j][j] == ai) {
                x++;
            }
            if (cube[i][j][j] == human) {
                o++;
            }
        }
        if (x > 0 && o == 0) {
            total += pow(x, 2);
        }
        if (o > 0 && x == 0) {
            total -= pow(o, 2);
        }
        x = 0, o = 0;
    }

    int k = 3;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (cube[i][j][k] == ai) {
                x++;
            }
            if (cube[i][j][k] == human) {
                o++;
            }
            k--;
        }
        if (x > 0 && o == 0) {
            total += pow(x, 2);
        }
        if (o > 0 && x == 0) {
            total -= pow(o, 2);
        }
        x = 0, o = 0;
    }

    // Scores diagonals (by row)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (cube[j][i][j] == ai) {
                x++;
            }
            if (cube[j][i][j] == human) {
                o++;
            }
        }
        if (x > 0 && o == 0) {
            total += pow(x, 2);
        }
        if (o > 0 && x == 0) {
            total -= pow(o, 2);
        }
        x = 0, o = 0;
    }

    k = 3;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (cube[j][i][k] == ai) {
                x++;
            }
            if (cube[j][i][k] == human) {
                o++;
            }
            k--;
        }
        if (x > 0 && o == 0) {
            total += pow(x, 2);
        }
        if (o > 0 && x == 0) {
            total -= pow(o, 2);
        }
        x = 0, o = 0;
    }

    // Scores diagonals (by column)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (cube[j][j][i] == ai) {
                x++;
            }
            if (cube[j][j][i] == human) {
                o++;
            }
        }
        if (x > 0 && o == 0) {
            total += pow(x, 2);
        }
        if (o > 0 && x == 0) {
            total -= pow(o, 2);
        }
        x = 0, o = 0;
    }

    k = 3;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (cube[j][k][i] == ai) {
                x++;
            }
            if (cube[j][k][i] == human) {
                o++;
            }
            k--;
        }
        if (x > 0 && o == 0) {
            total += pow(x, 2);
        }
        if (o > 0 && x == 0) {
            total -= pow(o, 2);
        }
        x = 0, o = 0;
    }

    // Scores super-diagonals
    for (int i = 0; i < 4; i++) {
        if (cube[i][i][i] == ai) {
            x++;
        }
        if (cube[i][i][i] == human) {
            o++;
        }
    }
    if (x > 0 && o == 0) {
        total += pow(x, 2);
    }
    if (o > 0 && x == 0) {
        total -= pow(o, 2);
    }
    x = 0, o = 0;

    int j = 3;
    for (int i = 0; i < 4; i++) {
        if (cube[j][i][i] == ai) {
            x++;
        }
        if (cube[j][i][i] == human) {
            o++;
        }
        j--;
    }
    if (x > 0 && o == 0) {
        total += pow(x, 2);
    }
    if (o > 0 && x == 0) {
        total -= pow(o, 2);
    }
    x = 0, o = 0;

    j = 3;
    for (int i = 0; i < 4; i++) {
        if (cube[i][i][j] == ai) {
            x++;
        }
        if (cube[i][i][j] == human) {
            o++;
        }
        j--;
    }
    if (x > 0 && o == 0) {
        total += pow(x, 2);
    }
    if (o > 0 && x == 0) {
        total -= pow(o, 2);
    }
    x = 0, o = 0;

    j = 3;
    for (int i = 0; i < 4; i++) {
        if (cube[j][i][j] == ai) {
            x++;
        }
        if (cube[j][i][j] == human) {
            o++;
        }
        j--;
    }
    if (x > 0 && o == 0) {
        total += pow(x, 2);
    }
    if (o > 0 && x == 0) {
        total -= pow(o, 2);
    }
    x = 0, o = 0;

    return total;
}

// Implements alpha-beta style minimax algorithm
int minimax(int depth, int alpha, int beta, bool maximizer) {

    // Scores cube if end-state or max-depth is reached
    if (depth == 0 || win() || full()) {
        return evaluate();
    }

    if (maximizer) {

        // Simulates AI's turn
        int maxEval = INT_MIN;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    if (cube[i][j][k] == ' ') {
                        cube[i][j][k] = ai;
                        int eval = minimax(depth - 1, alpha, beta, false);
                        maxEval = std::max(eval, maxEval);
                        alpha = std::max(eval, alpha);
                        cube[i][j][k] = ' ';
                        if (beta <= alpha) {
                            break;
                        }
                    }
                }
            }
        }
        return maxEval;
    } else {

        // Simulates user's turn
        int minEval = INT_MAX;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    if (cube[i][j][k] == ' ') {
                        cube[i][j][k] = human;
                        int eval = minimax(depth - 1, alpha, beta, true);
                        minEval = std::min(eval, minEval);
                        beta = std::min(eval, beta);
                        cube[i][j][k] = ' ';
                        if (beta <= alpha) {
                            break;
                        }
                    }
                }
            }
        }
        return minEval;
    }
}


// AI for the user to play against
void aiMove(int depth) {

    // Tries every possible next move
    int layer, row, column, best = INT_MIN;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (cube[i][j][k] == ' ') {

                    // Chooses winning move if possible
                    cube[i][j][k] = ai;
                    if (win()) {
                        return;
                    }

                    // Blocks user if their next move could win
                    cube[i][j][k] = human;
                    if (win()) {
                        cube[i][j][k] = ai;
                        return;
                    }

                    // Uses minimax if no immediate wins are possible
                    cube[i][j][k] = ai;
                    int current = minimax(depth, INT_MIN, INT_MAX, false);
                    if (current > best) {
                        best = current;
                        layer = i;
                        row = j;
                        column = k;
                    }
                    cube[i][j][k] = ' ';
                }
            }
        }
    }
    // Chooses maximizing move
    cube[layer][row][column] = ai;
}


// Game-play
int main() {

    // Setting up the game
    std::cout << "-------WELCOME TO QUBIC GAME--------" << std::endl;
    reset(); // Creates the cube
    display(); // Displays the cube
    first(); // Decides who goes first

    // Provide each player with their respective turns until an end-state is reached
    do {
        if (player == human) {
            std::cout << "YOUR TURN" << std::endl;
            humanMove();
            display();
            turn();
        } else {
            std::cout << "COMPUTER'S TURN" << std::endl;
            aiMove(3);
            display();
            turn();
        }
    } while (!win() && !full());

    if (win()) {

        // Notifies the user if the game has been won
        if (player == ai) {
            std::cout << "YOU WIN!!!" << std::endl;
        } else {
            std::cout << "COMPUTER WINS!!!" << std::endl;
        }
    } else {
        
        // Notifies the user if the game ended in a tie
        std::cout << "TIE!!!" << std::endl;
    }
}
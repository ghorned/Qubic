# Qubic

>The user is given the opportunity to play a "challenging" game of 3D tic-tac-toe against an unbeatable AI.  Gameplay takes place in the console where the game's current state is represented as a 4x4x4 cube.
```
-------WELCOME TO QUBIC GAME--------
          ________________
         /   /   /   /   /
        /___/___/___/___/
       /   /   /   /   /
      /___/___/___/___/
     /   /   /   /   /
    /___/___/___/___/
   /   /   /   /   /
  /___/___/___/___/

          ________________
         /   /   /   /   /
        /___/___/___/___/
       /   /   /   /   /
      /___/___/___/___/
     /   /   /   /   /
    /___/___/___/___/
   /   /   /   /   /
  /___/___/___/___/

          ________________
         /   /   /   /   /
        /___/___/___/___/
       /   /   /   /   /
      /___/___/___/___/
     /   /   /   /   /
    /___/___/___/___/
   /   /   /   /   /
  /___/___/___/___/

          ________________
         /   /   /   /   /
        /___/___/___/___/
       /   /   /   /   /
      /___/___/___/___/
     /   /   /   /   /
    /___/___/___/___/
   /   /   /   /   /
  /___/___/___/___/
```

## Installation

The applications consists of a single .cpp file in order to make installation and sharing easy. All that is required to get the game up and running is a copy of the repository...
```
git clone https://github.com/ghorned/Qubic
```
...and a C++ compiler.
```
g++ -o test Qubic.cpp
./test
```


## Usage

The game begins with a simulated coin toss and then turns continue until either player has won or a tie has been reached.

The user plays with the marker `O` while the AI uses the marker `X`. The program notifies the user when it is their turn to play and then prompts them to select where they want to place their next marker.
```
YOUR TURN
Layer:
Row:
Column:
```
Each of the composite squares represents a layer indexed 0 to 3 (top to bottom). Within each of these layers are horizontal rows indexed 0 to 3 (top to bottom). Within each layer are also vertical columns indexed 0 to 3 (left to right). To place their marker in a cell the user just needs to enter the index for each of these three parameters into the command line. If the user tries to pass an invalid parameter, the program gives the user another chance to enter an acceptable value. When the end of a game has been reached, the program will print either who won or that the game ended in a tie.


## Implementation

### Heuristic
In a normal game of 2D tic-tac-toe, a heuristic is not necessary because its game tree is small enough that all leaf nodes can be reached without over-taxing the system. However, with the added dimension in Qubic, the game tree becomes too large to allow for every possible leaf to be evaluated. Because of this, it becomes necessary to develop a heuristic which can evaluate internal nodes (incomplete game states).

The heuristic used in this program, called `evaluate()`, does this by going through each possible winning line and counting both the `X`s and `O`s present within it. If both are present within the same line, the line is ignored. However, if only one type of marker occurs, the number of markers is raised to the second power and added/subtracted to/from the total returned at the end of the function.

The idea is to provide the AI with incentive to place its markers in positions intersected by the most wining lines (higher potential), while also giving preference to placing more markers in a single line (pursue wins). A higher score evaluates to a better state for the AI and a lower score evaluates to a better state for the user.

### Minimax
With a heuristic established, it becomes possible to implement a version of the minimax algorithm with alpha-beta pruning. The function, `minimax()`, takes four parameters, a depth (integer), an initial alpha and beta value (integers), and Boolean representing whether the maximizing player is currently “playing.” By default, I have the depth of the function set to 3, meaning that it looks three plays (or plies) ahead in the game. This seems to be the limit to how deep the algorithm can search without causing significant lag. The alpha value is set to a low integer and the beta value is set to a high integer. The Boolean is inverted each time the function is recursively called.
The minimax algorithm recursively calls itself until it reaches a limiting depth (3 or less when a leaf is encountered). The function then calls on the heuristic function to evaluate the current state and returns it to the previous node.

As the function retreats up the tree, an optimal decision is chosen for each level based upon whether the current player is the maximizer or not. The AI plays as the maximizer and therefore looks for the move that results in the highest score given optimal play on both sides.
The addition of alpha-beta pruning does not drastically affect the function, but theoretically allows for faster decisions and deeper searches. The pruning occurs when the function decides that following a certain branch of the game tree will not affect the overall decision. If this is the case, that branch is “pruned” off and abandoned. All this does is save time that may otherwise be wasted evaluating sub-optimal paths.

### AI
The final driver for the intelligent algorithm is called `aiMove()`. This function uses the information provided by the minimax function to make a final optimal decision. It does this by iterating through all open positions within the board. For each position, the function plays both markers (AI and user) and then evaluates whether either would result in an immediate win. If it will, the AI player leaves its marker in this position and exits the function. The idea behind this is that it either prevents the AI from ever missing an opportunity to win a game or block its opponent from winning.

If neither of these conditions are met, the function continues to call minimax for each of the iterated positions after an AI marker has been placed. By doing so, the AI is effectively searching four plies ahead (one level in `aiMove()`, the other three in `minmax()`). The best score for each possible move evaluated is returned to the current AI function. If this score is greater than the current best score, the best score is replaced by the new score and the position is recorded for later use. By the end of the function, the best score will be associated with a given position which can then be played by the function.

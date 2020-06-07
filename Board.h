#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H

#include <vector>
#include <string>
#include <iostream>
#include <tuple>

using namespace std;

enum Color {
    black = 0, white = 1, none = 2
};

static Color otherColor(Color c) {
    return (c == white) ? black : white;
}

class Node;

class Board {

private:
    static const int WIDTH = 7;
    static const int HEIGHT = 6;
    static const int H1 = HEIGHT + 1;
    static const int H2 = HEIGHT + 2;
    static const int SIZE = HEIGHT * WIDTH;
    static const int SIZE1 = H1 * WIDTH;
    static const uint64_t ALL1 = (1L << SIZE1) - 1L; // assumes SIZE1 < 63
    static const uint64_t COL1 = (1L << H1) - 1;
    static const uint64_t BOTTOM = ALL1 / COL1; // has bits i*H1 set
    const Color player;
    const Color enemy;
    Color turn;
    //  .  .  .  .  .  .  .  TOP
    //  5 12 19 26 33 40 47
    //  4 11 18 25 32 39 46
    //  3 10 17 24 31 38 45
    //  2  9 16 23 30 37 44
    //  1  8 15 22 29 36 43
    //  0  7 14 21 28 35 42  BOTTOM
    Color winner;
public:
    uint64_t board[2]{}; // 0 is black and 1 is white
    /**
     * Creates a Board, where the player 1 (referred as player) plays the black
     */
    Board();

    /**
     * Creates a Board, where the player 1 (referred as player) plays the @param playerColor color
     * @param playerColor the color of player
     */
    explicit Board(Color playerColor);

    /**
     * Prompts a move, so a human can enter coordinates
     */
    void askMove();

    /**
     * Plays a coin at the selected column
     * @param col the column where to play
     */
    bool playOnce(int col);

    /**
     * Changes the turn
     */
    void changeTurn();

    /**
     * Checks if the game is over. Sets the winner as side effect.
     * @return true if the game is over, else false
     */
    bool isOver();

    /**
     * Returns the value of a board, from the @param color point of view
     * @param color the player whom the heuristic is calculated
     * @return the heuristic of the Board as int
     */
    int heuristic(Color color) const;

    /**
     * Returns the value of a board, from the turn player color point of view
     * @param color the player whom the heuristic is calculated
     * @return the heuristic of the Board as int
     */
    int heuristic() const;

    /**
     * Returns the value of a Board, when a game is over, from the @param color point of view
     * @param color the player whom the color is calculated
     * @return the score of the Board as int
     */
    int score(Color color) const;

    /**
     * Returns the value of a Board, when a game is over, from the turn player color point of view
     * @param color the player whom the color is calculated
     * @return the score of the Board as int
     */
    int score() const;

    /**
     * Checks if the player has won, and sets the parameter winner
     * @param color the color checked
     * @return true if the game is over and player has won
     */
    bool hasWon(Color color);

    /**
     * @return the player's color
     */
    Color getPlayer() const;

    /**
     * @return the color of the player that will play
     */
    Color getTurn() const;

    /**
     * Get the next states using possiblePlace
     * @return a vector of states
     */
    vector<Node> children() const;

    /**
     * Prints the Board in the console
     */
    void printBoard() const;

    /**
     * Clones the Board
     * @return
     */
    Board clone() const;


};


struct Node {
    Board board;
    int nextAction{};
};

#endif //OTHELLO_BOARD_H

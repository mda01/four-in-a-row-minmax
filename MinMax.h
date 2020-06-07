#ifndef MINMAX_H
#define MINMAX_H
#define MAX_DEPTH 10

#include "Board.h"
#include <map>
#include <random>


class MinMax {
private:
    Color aiColor;

public:
    /**
     * Creates a minmax AI, that maximise the @param color score
     * @param color the player we want to maximise
     */
    explicit MinMax(Color color);

    /**
     * Starts the minmax algorithm and uses alpha beta pruning, from a @param state, and memorises the best path into @param actions
     * @param state the initial state
     * @param actions the path
     * @return the confidence of the AI as int
     */
    int alpha_beta(Board state, vector<int> &actions);

private:
    enum EntryType {
        EXACT, LOW, HIGH
    };
    struct Entry {
        int value;
        EntryType flag;
        int depth;
    };
    map<long, Entry> transpositionTable;
    long randomNumbers[2][48]{};

    /**
     * Tries to maximize the score
     * @param state initial state
     * @param alpha alpha bound
     * @param beta beta bound
     * @param actions best path
     * @param depth how far we can explore from this state
     * @return the confidence of the AI as int
     */
    int negamax(Board state, int depth, int alpha, int beta, vector<int> &actions, Color color);

    /**
     * Computes the zobrist hash of a given state
     * @param state the state the hash is computed on
     * @return a long hash
     */
    long zobristHash(const Board &state) const;
};


#endif
